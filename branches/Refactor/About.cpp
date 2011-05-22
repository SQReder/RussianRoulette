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
void __fastcall TAboutForm::FormShow(TObject* Sender) {
    Caption = "О программе";
}
// ---------------------------------------------------------------------------

void __fastcall TAboutForm::FormCreate(TObject* Sender) { AboutForm->Hide(); }
// ---------------------------------------------------------------------------

