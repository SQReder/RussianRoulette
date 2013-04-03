// ---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop

#include <map>
#include "main.h"
#include "base.h"
#include "frm_pass.h"
#include "crc32.cpp"
#pragma package(smart_init)
#pragma resource "*.dfm"
// ---------------------------------------------------------------------------
Tf *f;
int QuestionRound;
sBase *base;
UnicodeString CurrentBaseFile;
sQuestion *EditQuestion = NULL;
bool IsBaseEdited;

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

void __fastcall Tf::FieldEnter(TObject *Sender) {
    TMemo *obj = (TMemo *) Sender;
    if (Trim(obj->Text) == blank[obj]) {
        obj->Text = "";
    }
    obj->Font->Color = clBlack;
}

void __fastcall Tf::FieldExit(TObject *Sender) {
    TMemo *obj = (TMemo *)Sender;
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
__fastcall Tf::Tf(TComponent *Owner) : TForm(Owner) {
    base = new sBase();
    LoadBlanks();
}

// ---------------------------------------------------------------------------
void Tf::ClearForm() {
    mQuestion->Clear();
    lstAnswers->Clear();
    mAnswer->Clear();
    mComment->Clear();
    lstAnswers->Clear();
    lstQuestions->Clear();

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
void __fastcall Tf::btnAddAnswerClick(TObject *Sender) {
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

void __fastcall Tf::mAnswerKeyDown(TObject *Sender, WORD &Key, TShiftState Shift) {
    if (Key == 13 && Trim(mAnswer->Text) != "") {
        AddAnswerToList();
    }
}
// ---------------------------------------------------------------------------

void __fastcall Tf::lstAnswersDblClick(TObject *Sender) {
    int index4delete = lstAnswers->ItemIndex;
    mAnswer->Text = lstAnswers->Items->Strings[index4delete];
    lstAnswers->Items->Delete(index4delete);
}
// ---------------------------------------------------------------------------

void __fastcall Tf::lstAnswersClickCheck(TObject *Sender) {
    if (edRound->Text != "5" && lstAnswers->ItemIndex != -1) {
        lstAnswers->CheckAll(TCheckBoxState(0), 0, 0);
        lstAnswers->Checked[lstAnswers->ItemIndex] = true;
    }
}
// ---------------------------------------------------------------------------

void __fastcall Tf::FormCreate(TObject *Sender) {
    QuestionRound = 1;
    edRound->Text = "1";
    ClearForm();
    mSearch->Clear();

    ExitAllFields();
}
// ---------------------------------------------------------------------------

void __fastcall Tf::btnAddQuestionToBaseClick(TObject *Sender) {
    // check some fields for status
    bool QuestionIsNull = Trim(mQuestion->Text).Length() == 0;
    bool QuestionIsBlank = mQuestion->Text == blank[mQuestion];
    if (QuestionIsNull || QuestionIsBlank) {
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
        sQuestion *q = (EditQuestion) ? EditQuestion : new sQuestion();

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

        ClearForm();
        lstQuestions->Items->Assign(base->GetQuestionsList());

        EditQuestion = NULL;
    }
    IsBaseEdited = true;
}
// ---------------------------------------------------------------------------

void __fastcall Tf::lstQuestionsDblClick(TObject *Sender) {
    // load unite from base
    EditQuestion = base->GetQuestionPointer(lstQuestions->ItemIndex);

    // show EditQuestion
    mQuestion->Text = EditQuestion->question;
    mAnswer->Clear();

    // show answers in list
    lstAnswers->Clear();
    for (int i = 0; i < EditQuestion->GetAnswersCount(); ++i) {
        lstAnswers->Items->Add(EditQuestion->GetAnswer(i));
    }

    QuestionRound = EditQuestion->round;
    edRound->Text = IntToStr(QuestionRound);

    if (QuestionRound != 5) {
        lstAnswers->CheckAll(TCheckBoxState(0), 0, 0);
        lstAnswers->Checked[EditQuestion->true_answer] = true;
    } else {
        lstAnswers->CheckAll(TCheckBoxState(1), 0, 0);
    }

    mComment->Text = EditQuestion->comment;
    ExitAllFields();

    //MessageBoxW(Application->Handle, EditQuestion->c_str(), L"Debug", MB_OK);
}

// ---------------------------------------------------------------------------
void __fastcall Tf::edSearchChange(TObject *Sender) {
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
void __fastcall Tf::btnClearSearchFieldClick(TObject *Sender) {
    mSearch->Clear();
    FieldExit(mSearch);
    edSearchChange(NULL);
}
// ---------------------------------------------------------------------------

void __fastcall Tf::mmExitClick(TObject *Sender) {
    int foo = MessageBoxW(Application->Handle, L"O rly?", L"Exit confirmation", MB_YESNO);
    if (foo == IDYES) {
        exit(0);
    }
}
// ---------------------------------------------------------------------------

void __fastcall Tf::mmNewBaseClick(TObject *Sender) {
    int ret;
    if (IsBaseEdited) {
        ret = MessageBoxW(f->Handle, L"Вы действительно хотите создать новую базу данных вопросов?\n\
Изменения в текущей базе не будут сохранены!!", L"Внимание!", MB_DEFBUTTON2 | MB_YESNO);
    } else {
        ret = IDYES;
    }

    if (ret == IDYES) {
        delete base;
        base = new sBase();
        CurrentBaseFile = "";
        IsBaseEdited = false;
        f->ClearForm();
    }
}
// ---------------------------------------------------------------------------

void __fastcall Tf::mmSaveBaseClick(TObject *Sender) {
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
void __fastcall Tf::mmOpenBaseClick(TObject *Sender) {
    if (IsBaseEdited) {
        if (MessageBoxW(Application->Handle, L"You made changes. Do you want to save it?", L"Close confirmation",
                MB_YESNO) == IDYES) {
            return;
        }
    }

    if (dlgOpen->Execute()) {
        dlgOpen->Filter = "Russian Roulette Base|*.rrb";
        base->load(dlgOpen->FileName);
        if (base->pass_hash()) {
input_pass:
            fpass->ShowModal();
            bool isPasswordCorrect = Crc32(SomePass.c_str(), SomePass.Length()) == base->pass_hash();
            if (!isPasswordCorrect) {
                if (MessageBoxW(Application->Handle, L"Wrong password! Repeat?", L"Error",
                        MB_RETRYCANCEL | MB_ICONWARNING) == IDRETRY) {
                    goto input_pass;
                } else {
                    mmNewBaseClick(NULL);
                    return;
                }
            }
        }

        CurrentBaseFile = dlgOpen->FileName;
        IsBaseEdited = false;
        lstQuestions->Items->Assign(base->GetQuestionsList());
        lstQuestions->SetFocus();
    }
}

// ---------------------------------------------------------------------------
void __fastcall Tf::Button1Click(TObject *Sender) {
    sQuestion *q = new sQuestion();

    q->question = "some question";
    q->comment = "some comment";
    q->round = 1;

    TStringList *answers = new TStringList();
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

// ---------------------------------------------------------------------------
void __fastcall Tf::lstQuestionsKeyDown(TObject *Sender, WORD &Key, TShiftState Shift) {
    if (Key == 13) {
        lstQuestionsDblClick(NULL);
    }
}

// ---------------------------------------------------------------------------
void __fastcall Tf::mmSaveBaseAsClick(TObject *Sender) {
    if (dlgSave->Execute()) {
        CurrentBaseFile = dlgSave->FileName;
        base->save(CurrentBaseFile);
        IsBaseEdited = false;
    }
}
// ---------------------------------------------------------------------------

void __fastcall Tf::mSetPassClick(TObject *Sender) {
    fpass->ShowModal();
    base->set_pass(SomePass);
}

// ---------------------------------------------------------------------------
String FillChars(String str, int count) {
    for (int i = str.Length(); i < count; i++) {
        str += '|';
    }

    return str;
}

// ---------------------------------------------------------------------------
// import old base
// ---------------------------------------------------------------------------
String ClearStr(String str) {
    String cl_str = "";
    int i = 1;

    while (str[i] != '|') {
        cl_str += str[i];
        if (i++ == str.Length()) {
            break;
        }
    }

    return cl_str;
}

// ---------------------------------------------------------------------------
String GetStr(String str, int begin, int size) {
    String ret = "";

    for (int i = begin; i < begin + size; i++) {
        ret += str[i];
    }

    return ret;
}

// ---------------------------------------------------------------------------

void __fastcall Tf::mImportBaseClick(TObject *Sender) {
    mmNewBaseClick(NULL);
    dlgOpen->Filter = "Russian Roulette Old Base|*.dat";
    if (dlgOpen->Execute()) {
        class OldQuestion {
        public:
            char Round;
            UnicodeString Question;
            UnicodeString Answers[5];
            int TrueAnswer;

            OldQuestion() {
                TrueAnswer = -1;
                Round = -1;
            }
        };

        /*
         5 символов - количество вопросов в базе
         далее блоками по 457 символов
         1 символ - номер раунда
         255 символов - вопрос
         по 40 символов ответы
         1 символ - номер правильного
         индексация начинается с нуля =)
         */

        // открываем базу
        try {
            TFileStream *stream = new TFileStream(dlgOpen->FileName, fmOpenRead);
            // подготавливаем строку и считываем в нее количество вопросов в базе
            String tstr = "     "; // длина строки = количеству считываемых символов
            // считываем строку длиной в 10 байт, ибо юникод, а символов 5 =/
            stream->Read(&tstr[1], 10);

            tstr = ClearStr(tstr); // теперя тута храниццо кол-во вопросов в базе =^__^=
            int qcount = StrToInt(tstr);

            OldQuestion *old_base = new OldQuestion[qcount];

            for (int i = 0; i < qcount; i++) {
                String str = "";
                // ну тут все ясно =)
                str = FillChars(str, 457); // подготавливаем память для загрузки
                stream->ReadBuffer(&str[1], 457 *2);
                // и считываем блок данных

                for (int i = 1; i < str.Length(); i++) // расшифровываем
                {
                    str[i] = str[i] ^ (i % 7);
                }

                old_base[i].Round = GetStr(str, 1, 1)[1]; // суть номер раунда 1-4

                old_base[i].Question = ClearStr(GetStr(str, 2, 255)); // вопрос

                old_base[i].Answers[0] = ClearStr(GetStr(str, 257, 40));
                // варианты ответа
                old_base[i].Answers[1] = ClearStr(GetStr(str, 297, 40));
                old_base[i].Answers[2] = ClearStr(GetStr(str, 337, 40));
                old_base[i].Answers[3] = ClearStr(GetStr(str, 377, 40));
                old_base[i].Answers[4] = ClearStr(GetStr(str, 417, 40));

                old_base[i].TrueAnswer = StrToInt(GetStr(str, 457, 1));
                // правильный ответ
            }
            stream->Free();

            for (int i = 0; i < qcount; ++i) {
                sQuestion *q = new sQuestion();

                OldQuestion old_q = old_base[i];

                q->question = old_q.Question;
                q->round = old_q.Round - 48;

                TStringList *answers = new TStringList;
                int acount = (q->round == 5) ? 5 : q->round + 1;
                for (int i = 0; i < acount; ++i) {
                    answers->Add(old_q.Answers[i]);
                }

                q->AssignAnswersList(answers);
                delete answers;
                q->true_answer = old_q.TrueAnswer;

                base->add(q);
            }

            delete[]old_base;

            lstQuestions->Items->Assign(base->GetQuestionsList());
            lstQuestions->SetFocus();
        }
        catch (...) {
        }
    }
}
// ---------------------------------------------------------------------------
void __fastcall Tf::edRoundChange(TObject *Sender)
{
    QuestionRound = edRound->ItemIndex + 1;
}
//---------------------------------------------------------------------------

