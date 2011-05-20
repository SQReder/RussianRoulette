// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "About.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutForm* AboutForm;

// ---------------------------------------------------------------------------
__fastcall TAboutForm::TAboutForm(TComponent* Owner) : TForm(Owner) { }

// ---------------------------------------------------------------------------
void __fastcall TAboutForm::tmrScrollTimer(TObject* Sender) {
	if (lblAboutText->Top > -lblAboutText->Height) {
		lblAboutText->Top-- ;
	}
	else {
		lblAboutText->Top = AboutForm->ClientHeight;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TAboutForm::FormShow(TObject* Sender) {
	lblAboutText->Top = 0;
	lblAboutText->Left = 0;
	lblAboutText->Height = 600;

	Caption = "О программе";
}
// ---------------------------------------------------------------------------

void __fastcall TAboutForm::FormCreate(TObject* Sender) { AboutForm->Hide(); }
// ---------------------------------------------------------------------------
