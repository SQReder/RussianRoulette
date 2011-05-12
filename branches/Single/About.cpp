// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "About.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutForm* AboutForm;

// ---------------------------------------------------------------------------
__fastcall TAboutForm::TAboutForm(TComponent* Owner) : TForm(Owner) {

}

// ---------------------------------------------------------------------------
void __fastcall TAboutForm::tmrScrollTimer(TObject* Sender) {
	if (lblAboutText->Top > -lblAboutText->Height)
		lblAboutText->Top-- ;
	else
		lblAboutText->Top = AboutForm->ClientHeight;
	tmrScroll->Interval = 30;
}

// ---------------------------------------------------------------------------
void __fastcall TAboutForm::FormShow(TObject* Sender) {
	lblAboutText->Top = 0;
	lblAboutText->Left = 0;
	lblAboutText->Height = 600;

	Caption = "� ���������";

	tmrScroll->Interval = 1000;

	// lblAboutText->Caption = "�������� ������� v0.98\n\n�����������: QWERule Inc.\n���. ����: http://rusrul.ru\n\n�������� ����\n�������������:\n����������� �����������:\nKanashimi Watari\n������� ����� ����������\n\n�������������� ����������\n����� ��������";
}
// ---------------------------------------------------------------------------

void __fastcall TAboutForm::lblAboutTextClick(TObject* Sender) {
	// AboutForm->Close();
}
// ---------------------------------------------------------------------------

void __fastcall TAboutForm::FormCreate(TObject* Sender) { AboutForm->Close(); }
// ---------------------------------------------------------------------------

void __fastcall TAboutForm::FormClick(TObject* Sender) { AboutForm->Close(); }
// ---------------------------------------------------------------------------
