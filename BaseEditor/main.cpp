// ---------------------------------------------------------------------------
#include <map>
#include <algorithms>
#include <vcl.h>
#pragma hdrstop
#include "main.h"
#include "base.h"
#pragma package(smart_init)
#pragma link "Spin"
#pragma resource "*.dfm"
// ---------------------------------------------------------------------------
Tf* f;
int QuestionRound;
sBase* base;
UnicodeString CurrentBaseFile;
sQuestion* EditQuestion = NULL;
bool IsBaseEdited;
const int MB_YES = 6;
const int MB_NO = 7;

const UnicodeString BlankQuestion = "Enter some question";
const UnicodeString BlankSearch = "Search field";
const UnicodeString BlankAnswer = "Enter some answer";
const UnicodeString BlankComment = "Enter some comment for question";
// ---------------------------------------------------------------------------
std::map <TObject *, UnicodeString> blank;

void LoadBlanks() {
    blank[f->mAnswer] = BlankAnswer;
    blank[f->mQuestion] = BlankQuestion;
    blank[f->mComment] = BlankComment;
    blank[f->mSearch] = BlankSearch;
}

void __fastcall Tf::FieldEnter(TObject* Sender) {
    TMemo* obj = (TMemo *) Sender;
    if (Trim(obj->Text) == blank[obj]) {
        obj->Text = "";
    }
    obj->Font->Color = clBlack;
}

void __fastcall Tf::FieldExit(TObject* Sender) {
    TMemo* obj = (TMemo *)Sender;
    UnicodeString text = obj->Text;
    if (text == "") {
        obj->Text = blank[obj];
        obj->Font->Color = clGray;
    } else if (text == blank[obj]) {
        obj->Font->Color = clGray;
    } else {
        obj->Font->Color = clBlack;
    }
}

// ---------------------------------------------------------------------------
__fastcall Tf::Tf(TComponent* Owner) : TForm(Owner) {
    base = new sBase();
    LoadBlanks();
}

// ---------------------------------------------------------------------------
void Tf::ClearForm() {
    f->mQuestion->Clear();
    f->lstAnswers->Clear();
    f->mAnswer->Clear();
    f->mComment->Clear();

    ExitAllFields();
}

// ---------------------------------------------------------------------------
bool CheckAnswersCount(bool strict = false) {
    int count = f->lstAnswers->Count;

    bool NotNull = !strict || (count != 0);
    bool Range = (strict) ? (count == QuestionRound + 1) : (count <= QuestionRound);
    bool isFinal = QuestionRound == 5;

    bool LessThanMaximal = count <= 32;

    return (Range || isFinal) && NotNull && LessThanMaximal;
}

// ---------------------------------------------------------------------------
void AddAnswerToList() {
    if (CheckAnswersCount()) {
        UnicodeString TrimmedAnswer = Trim(f->mAnswer->Text);
        f->lstAnswers->Items->Add(TrimmedAnswer);
        f->mAnswer->Clear();
    }
}

// ---------------------------------------------------------------------------
void __fastcall Tf::btnAddAnswerClick(TObject* Sender) {
    // cheak that field isn't blank
    if (Trim(mAnswer->Text) != "" && mAnswer->Text != BlankAnswer) {
        // search for equal answer
        for (int i = 0; i < lstAnswers->Count; ++i) {
            if (mAnswer->Text == lstAnswers->Items->Strings[i]) {
                // if equal found - return, coz nothing to do
                return;
            }
        }
        // if not returned at previous step - add answer to list
        AddAnswerToList();
    }

    // move focus
    mAnswer->SetFocus();

    // and turn on a flag
    IsBaseEdited = true;
}
// ---------------------------------------------------------------------------

void __fastcall Tf::mAnswerKeyDown(TObject* Sender, WORD& Key, TShiftState Shift) {
    if (Key == 13 && Trim(mAnswer->Text) != "") {
        AddAnswerToList();
    }
}
// ---------------------------------------------------------------------------

void __fastcall Tf::lstAnswersDblClick(TObject* Sender) {
    int index4delete = lstAnswers->ItemIndex;
    mAnswer->Text = lstAnswers->Items->Strings[index4delete];
    lstAnswers->Items->Delete(index4delete);
}
// ---------------------------------------------------------------------------

void __fastcall Tf::lstAnswersClickCheck(TObject* Sender) {
    if (edRound->Text != "5" && lstAnswers->ItemIndex != -1) {
        lstAnswers->CheckAll(TCheckBoxState(0), 0, 0);
        lstAnswers->Checked[lstAnswers->ItemIndex] = true;
    }
}
// ---------------------------------------------------------------------------

void __fastcall Tf::edRoundChange(TObject* Sender) {
    UnicodeString text = edRound->Text;
    if (text == "") {
        text = "1";
    } else {
        if (text[1] > '5') {
            text = "5";
        }
        if (text[1] < '1') {
            text = "1";
        }
    }
    edRound->Text = text;
    QuestionRound = StrToInt(text);
    edRound->SelectAll();
}

// ---------------------------------------------------------------------------

void __fastcall Tf::SpinRoundUpClick(TObject* Sender) {
    if (++QuestionRound > 5) {
        QuestionRound = 5;
    }
    edRound->Text = IntToStr((int)QuestionRound);
}
// ---------------------------------------------------------------------------

void __fastcall Tf::SpinRoundDownClick(TObject* Sender) {
    if (--QuestionRound == 0) {
        QuestionRound = 1;
    }
    edRound->Text = IntToStr((int)QuestionRound);
}
// ---------------------------------------------------------------------------

void __fastcall Tf::FormCreate(TObject* Sender) {
    QuestionRound = 1;
    edRound->Text = "1";
    ClearForm();
    mSearch->Clear();

    ExitAllFields();
}
// ---------------------------------------------------------------------------

void __fastcall Tf::btnAddQuestionToBaseClick(TObject* Sender) {
    // check some fields for status
    bool QuestionIsNull = Trim(mQuestion->Text).Length() == 0;
    bool QuestionIsBlank = mQuestion->Text == blank[mQuestion];
    if (QuestionIsNull) {
        StatusBar->Panels->Items[0]->Text = "Fill question";
        return;
    }

    if (edRound->Text != "5") {
        // <-- seek for anyone checked answer
        bool TrueAnswerNotChoosed = true;
        for (int i = 0; (i < lstAnswers->Count) && TrueAnswerNotChoosed; ++i) {
            if (lstAnswers->Checked[i]) {
                TrueAnswerNotChoosed = false;
            }
        }

        if (TrueAnswerNotChoosed && edRound->Text != "5") {
            StatusBar->Panels->Items[0]->Text = "Choose true answer";
            return;
        }
        // --> check answers

        bool AnswersNotFilled = lstAnswers->Count <= QuestionRound;
        if (AnswersNotFilled) {
            StatusBar->Panels->Items[0]->Text = "Add more answers";
            return;
        }
    } else {
        if (!lstAnswers->Count) {
            StatusBar->Panels->Items[0]->Text = "Add more answers";
            return;
        }
    }

    // -> end of checking

    if (CheckAnswersCount(true)) {
        // if (Edit pointer == NULL) then "create new unit" else "use Edit pointer"
        sQuestion* q = (EditQuestion) ? EditQuestion : new sQuestion();

        // fill fields with values=)
        q->question = mQuestion->Text;
        // assign list of answers
        q->AssignAnswersList(lstAnswers->Items);
        // set true answer
        q->round = QuestionRound;
        if (QuestionRound == 5) {
            q->true_answer = 255;
        } else {
            for (int i = 0; i < lstAnswers->Count; ++i) {
                if (lstAnswers->Checked[i]) {
                    q->true_answer = i;
                    break;
                }
            }
        }

        q->comment = mComment->Text;
        if (mComment->Text == blank[mComment]) {
            q->comment = "";
        }

        if (!EditQuestion) {
            base->add(q);
        }

        lstQuestions->Items->Assign(base->GetQuestionsList());
        ClearForm();

        EditQuestion = NULL;
    }
    IsBaseEdited = true;
}
// ---------------------------------------------------------------------------

void __fastcall Tf::lstQuestionsDblClick(TObject* Sender) {
    // load unite from base
    EditQuestion = base->GetQuestionPointer(lstQuestions->ItemIndex);

    // show EditQuestion
    mQuestion->Text = EditQuestion->question;
    mAnswer->Clear();

    // show answers in list
    lstAnswers->Items->Assign(EditQuestion->GetAnswersList());

    QuestionRound = EditQuestion->round;

    if (QuestionRound != 5) {
        lstAnswers->CheckAll(TCheckBoxState(0), 0, 0);
        lstAnswers->Checked[EditQuestion->true_answer] = true;
    } else {
        lstAnswers->CheckAll(TCheckBoxState(1), 0, 0);
    }

    mComment->Text = EditQuestion->comment;
    ExitAllFields();
}

// ---------------------------------------------------------------------------
void __fastcall Tf::edSearchChange(TObject* Sender) {
    UnicodeString text = Trim(mSearch->Text);
    if (text != "" && text != BlankSearch) {
        for (int i = 0; i < lstQuestions->Count; ++i) {
            if (!lstQuestions->Items->Strings[i].Pos(text)) {
                lstQuestions->Items->Delete(i);
            }
        }
    } else {
        lstQuestions->Items->Assign(base->GetQuestionsList());
    }
}

// ---------------------------------------------------------------------------
void __fastcall Tf::btnClearSearchFieldClick(TObject* Sender) {
    mSearch->Clear();
    FieldExit(mSearch);
    edSearchChange(NULL);
}
// ---------------------------------------------------------------------------

void __fastcall Tf::mmExitClick(TObject* Sender) {
    int foo = MessageBoxW(Application->Handle, L"text", L"Exit confirmation", MB_YESNO);
    if (foo == MB_YES) {
        exit(0);
    }
}
// ---------------------------------------------------------------------------

void __fastcall Tf::mmNewBaseClick(TObject* Sender) {
    int ret = MessageBoxW(f->Handle, L"¬ы действительно хотите создать новую базу данных вопросов?\n\
»зменени€ в текущей базе не будут сохранены!!", L"¬нимание!", MB_DEFBUTTON2 | MB_YESNO);
    if (ret == MB_YES) {
        delete base;
        base = new sBase();
        CurrentBaseFile = "";
        IsBaseEdited = false;
    }
}
// ---------------------------------------------------------------------------

void __fastcall Tf::mmSaveBaseClick(TObject* Sender) {
    if (!IsBaseEdited) {
        // haven't any change? go ahead! =)
        return;
    }
    if (CurrentBaseFile != "") {
        base->save(CurrentBaseFile);
        IsBaseEdited = false;
    } else {
        if (dlgSave->Execute()) {
            CurrentBaseFile = dlgSave->FileName;
            base->save(CurrentBaseFile);
            IsBaseEdited = false;
        }
    }
}

// ---------------------------------------------------------------------------
void __fastcall Tf::mmOpenBaseClick(TObject* Sender) {
    if (IsBaseEdited) {
        if (MessageBoxW(Application->Handle, L"You made changes. Do you want to save it?", L"Close confirmation",
                MB_YESNO) == MB_YES) {
            return;
        }
    }
    if (dlgOpen->Execute()) {
        base->load(dlgOpen->FileName);
        CurrentBaseFile = dlgOpen->FileName;
        IsBaseEdited = false;
        lstQuestions->Items->Assign(base->GetQuestionsList());
        lstQuestions->SetFocus();
    }
}

// ---------------------------------------------------------------------------
void __fastcall Tf::Button1Click(TObject* Sender) {
    sQuestion* q = new sQuestion();

    q->question = "some question";
    q->comment = "some comment";
    q->round = 1;

    TStringList* answers = new TStringList();
    answers->Add("answer0");
    answers->Add("answer1");
    q->AssignAnswersList(answers);
    base->add(q);

    q->true_answer = 1;

    lstQuestions->Items->Assign(base->GetQuestionsList());
}

// ---------------------------------------------------------------------------
void Tf::ExitAllFields() {
    // put blank values in a fields
    FieldExit(mQuestion);
    FieldExit(mAnswer);
    FieldExit(mSearch);
    FieldExit(mComment);
}

void __fastcall Tf::lstQuestionsKeyDown(TObject* Sender, WORD& Key, TShiftState Shift) {
    if (Key == 13) {
        lstQuestionsDblClick(NULL);
    }
}

// ---------------------------------------------------------------------------
void __fastcall Tf::mmSaveBaseAsClick(TObject* Sender) {
    if (dlgSave->Execute()) {
        CurrentBaseFile = dlgSave->FileName;
        base->save(CurrentBaseFile);
        IsBaseEdited = false;
    }
}
// ---------------------------------------------------------------------------
