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
sQuestion* EditQuestion = NULL;

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
    if (obj->Text == blank[obj]) {
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

    return (Range || isFinal) && NotNull && LessThanValue;
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
    if (Trim(mAnswer->Text) != "" && mAnswer->Text != BlankAnswer) {
        AddAnswerToList();
    }
    mAnswer->SetFocus();
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
    if (QuestionIsNull) {
        StatusBar->Panels->Items[0]->Text = "Fill question";
        return;
    }
    // --

    bool TrueAnswerNotChoosed = true;
    // seek for anyone checked item
    for (int i = 0; (i < lstAnswers->Count) && TrueAnswerNotChoosed; ++i) {
        if (lstAnswers->Checked[i]) {
            TrueAnswerNotChoosed = false;
        }
    }

    if (TrueAnswerNotChoosed) {
        StatusBar->Panels->Items[0]->Text = "Choose true answer";
        return;
    }
    // --

    bool AnswersNotFilled = lstAnswers->Count <= QuestionRound;
    if (AnswersNotFilled) {
        StatusBar->Panels->Items[0]->Text = "Add more answers";
        return;
    }

    // -> end of checking

    if (CheckAnswersCount(true)) {
        // if (Edit pointer == NULL) then "create new unit" else "use Edit pointer"
        sQuestion* question = (EditQuestion) ? EditQuestion : new sQuestion();

        // fill fields with values=)
        question->question = mQuestion->Text;
        // assign list of answers
        question->AssignAnswersList(lstAnswers->Items);
        // set true answer
        if (QuestionRound == 5) {
            question->round = 5;
            question->true_answer = 255;
        } else {
            question->round = QuestionRound;
            for (int i = 0; i < lstAnswers->Count; ++i) {
                if (lstAnswers->Checked[i]) {
                    question->true_answer = i;
                }
            }
        }

        question->comment = mComment->Text;

        if (!EditQuestion) {
            base->add(question);
        }

        lstQuestions->Items->Assign(base->GetQuestionsList());
        ClearForm();

        EditQuestion = NULL;
    }
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

void __fastcall Tf::mmExitClick(TObject* Sender) { exit(0); }
// ---------------------------------------------------------------------------

void __fastcall Tf::mmNewBaseClick(TObject* Sender) {
    int ret = MessageBoxW(f->Handle, L"¬ы действительно хотите создать новую базу данных вопросов?\n\
»зменени€ в текущей базе не будут сохранены!!", L"¬нимание!", MB_DEFBUTTON2 | MB_YESNO);
    if (ret == 6) {
        delete base;
        base = new sBase();
    }
}
// ---------------------------------------------------------------------------

void __fastcall Tf::mmSaveBaseClick(TObject* Sender) { base->save(L"base.rrb"); }

// ---------------------------------------------------------------------------
void __fastcall Tf::mmOpenBaseClick(TObject* Sender) {
    base->load(L"base.rrb");
    lstQuestions->Items->Assign(base->GetQuestionsList());
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
