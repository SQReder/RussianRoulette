// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Spin"
#pragma resource "*.dfm"
TMainForm* MainForm;

// ---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner) { }

// ---------------------------------------------------------------------------
void __fastcall TMainForm::btnAddAnswerClick(TObject *Sender)
{
	lstAnswers->Items->Add(edAnswer->Text);
	edAnswer->Clear();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::edAnswerKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == 13)
		btnAddAnswerClick(this);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::lstAnswersDblClick(TObject *Sender)
{
	lstAnswers->Items->Delete(lstAnswers->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::lstAnswersClickCheck(TObject *Sender)
{
	if (edRound->Text != "5") {

	}
}
//---------------------------------------------------------------------------

