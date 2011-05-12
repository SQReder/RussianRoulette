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

	Caption = "О программе";

	tmrScroll->Interval = 1000;

	// lblAboutText->Caption = "«Русская рулетка» v0.98\n\nРазработчик: QWERule Inc.\nОфф. сайт: http://rusrul.ru\n\nВыражаем нашу\nблагодарность:\nТехническое обеспечение:\nKanashimi Watari\nМатысик Ирина Алексеевна\n\nВосстановление саундтрека\nДенис Колобаев";
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
