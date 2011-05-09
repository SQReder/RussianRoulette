// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "main.h"
#include "base.h"
#pragma package(smart_init)
#pragma link "Spin"
#pragma resource "*.dfm"
// ---------------------------------------------------------------------------
Tf* f;
unsigned QuestionRound;
sBase* base;

// ---------------------------------------------------------------------------
__fastcall Tf::Tf(TComponent* Owner) : TForm(Owner) { base = new sBase(); }

// ---------------------------------------------------------------------------
void ClearForm() {
	f->mQuestion->Clear();
	f->lstAnswers->Clear();
	f->edAnswer->Clear();
	f->mComment->Clear();
}

// ---------------------------------------------------------------------------
bool CheckAnswersCount(bool strict = false) {
	unsigned count = f->lstAnswers->Count;
	bool NotNull = !strict || (count != 0);
	bool Range = (strict) ? (count == QuestionRound + 1) : (count <= QuestionRound);
	bool isFinal = QuestionRound == 5;

	return NotNull && (Range || isFinal);
}

// ---------------------------------------------------------------------------
void AddAnswerToList() {
	// getting coutn of exist answers
	unsigned AnswersCount = f->lstAnswers->Count;
	if (CheckAnswersCount()) {
		UnicodeString TrimmedAnswer = Trim(f->edAnswer->Text);
		f->lstAnswers->Items->Add(TrimmedAnswer);
		f->edAnswer->Clear();
	}
}

// ---------------------------------------------------------------------------
void __fastcall Tf::btnAddAnswerClick(TObject* Sender) { AddAnswerToList(); }
// ---------------------------------------------------------------------------

void __fastcall Tf::edAnswerKeyDown(TObject* Sender, WORD& Key, TShiftState Shift) {
	if (Key == 13 && Trim(edAnswer->Text) != "")
		AddAnswerToList();
}
// ---------------------------------------------------------------------------

void __fastcall Tf::lstAnswersDblClick(TObject* Sender) {
	int index4delete = lstAnswers->ItemIndex;
	edAnswer->Text = lstAnswers->Items->Strings[index4delete];
	lstAnswers->Items->Delete(index4delete);
}
// ---------------------------------------------------------------------------

void __fastcall Tf::lstAnswersClickCheck(TObject* Sender) {
	if (edRound->Text != "5") {
		lstAnswers->CheckAll(TCheckBoxState(0), 0, 0);
		lstAnswers->Checked[lstAnswers->ItemIndex] = true;
	}
}
// ---------------------------------------------------------------------------

void __fastcall Tf::edRoundChange(TObject* Sender) {
	UnicodeString text = edRound->Text;
	if (text == "")
		text = "1";
	else {
		if (text[1] > '5')
			text = "5";
		if (text[1] < '1')
			text = "1";
	}
	edRound->Text = text;
	QuestionRound = StrToInt(text);
	edRound->SelectAll();
}
// ---------------------------------------------------------------------------

void __fastcall Tf::SpinRoundUpClick(TObject* Sender) {
	if (++QuestionRound > 5)
		QuestionRound = 5;
	edRound->Text = IntToStr((int)QuestionRound);
}
// ---------------------------------------------------------------------------

void __fastcall Tf::SpinRoundDownClick(TObject* Sender) {
	if (--QuestionRound == 0)
		QuestionRound = 1;
	edRound->Text = IntToStr((int)QuestionRound);
}
// ---------------------------------------------------------------------------

void __fastcall Tf::FormCreate(TObject* Sender) {
	QuestionRound = 1;
	edRound->Text = "1";
}
// ---------------------------------------------------------------------------

void __fastcall Tf::btnAddQuestionToBaseClick(TObject* Sender) {
	bool QuestionNotNull = Trim(mQuestion->Text).Length() > 0;
	if (QuestionRound ) {

	}

	if (CheckAnswersCount(true)) {
		// create unit
		sQuestion* question = new sQuestion();

		question->question = mQuestion->Text;
		// assign list of answers
		question->AssignAnswersList(lstAnswers->Items);
		// set true answer
		if (QuestionRound == 5) {
			question->round = 5;
			question->true_answer = -1;
		}
		else {
			question->round = QuestionRound;
			for (int i = 0; i < lstAnswers->Count; ++i)
				if (lstAnswers->Checked[i])
					question->true_answer = i;
		}

		base->add(question);

		lstQuestions->Items->Assign(base->GetQuestionsList());
		ClearForm();
	}
}
// ---------------------------------------------------------------------------

void __fastcall Tf::lstQuestionsDblClick(TObject* Sender) {
	// load unite from base
	sQuestion* question = base->GetQuestionPointer(lstQuestions->ItemIndex);

	// show question
	mQuestion->Text = question->question;
	edAnswer->Clear();

	// show answers in list
	lstAnswers->Items->Assign(question->GetAnswersList());

	QuestionRound = question->round;

	if (QuestionRound != 5) {
		lstAnswers->CheckAll(TCheckBoxState(0), 0, 0);
		lstAnswers->Checked[question->true_answer] = true;
	}
	else
		lstAnswers->CheckAll(TCheckBoxState(1), 0, 0);

	mComment->Text = question->comment;
}

// ---------------------------------------------------------------------------
