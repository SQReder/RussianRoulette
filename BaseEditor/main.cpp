// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "base.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Spin"
#pragma resource "*.dfm"
TMainForm* MainForm;
unsigned QuestionRound;
sBase* base;

// ---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner) { base = new sBase(); }

// ---------------------------------------------------------------------------
void __fastcall TMainForm::btnAddAnswerClick(TObject* Sender) {
	lstAnswers->Items->Add(edAnswer->Text);
	edAnswer->Clear();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::edAnswerKeyDown(TObject* Sender, WORD& Key, TShiftState Shift) {
	if (Key == 13)
		btnAddAnswerClick(this);
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::lstAnswersDblClick(TObject* Sender) {
	int index4delete = lstAnswers->ItemIndex;
	edAnswer->Text = lstAnswers->Items->Strings[index4delete];
	lstAnswers->Items->Delete(index4delete);
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::lstAnswersClickCheck(TObject* Sender) {
	if (edRound->Text != "5") {
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::edRoundChange(TObject* Sender) {
	if (edRound->Text == "")
		edRound->Text = "1";
	else if (StrToInt(edRound->Text) > 5)
		edRound->Text = "5";
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::SpinRoundUpClick(TObject* Sender) {
	if (++QuestionRound > 5)
		QuestionRound = 5;
	edRound->Text = IntToStr((int)QuestionRound);
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::SpinRoundDownClick(TObject* Sender) {
	if (--QuestionRound == 0)
		QuestionRound = 1;
	edRound->Text = IntToStr((int)QuestionRound);
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject* Sender) {
	QuestionRound = 1;
	edRound->Text = "1";
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::btnAddQuestionToBaseClick(TObject* Sender) {
	// create unit
	sQuestion* question = new sQuestion();

	question->question = mQuestion->Text;
	// assign list of answers
	question->AssignAnswersList(lstAnswers->Items);
	// set true answer
	if (QuestionRound == 5)
		question->true_answer = -1;
	else
		for (int i = 0; i < lstAnswers->Count; ++i)
			if (lstAnswers->Checked[i])
				question->true_answer = i;

	base->add(question);

	lstQuestions->Items->Assign(base->GetQuestionsList());
}
// ---------------------------------------------------------------------------
