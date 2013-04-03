// ---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop

#include "frm_pass.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfpass* fpass;
AnsiString SomePass;

// ---------------------------------------------------------------------------
__fastcall Tfpass::Tfpass(TComponent* Owner) : TForm(Owner) {

}

// ---------------------------------------------------------------------------
void __fastcall Tfpass::FormClose(TObject* Sender, TCloseAction& Action) { SomePass = edPass->Text; }
// ---------------------------------------------------------------------------

void __fastcall Tfpass::FormKeyDown(TObject* Sender, WORD& Key, TShiftState Shift) {
    if (Key == 13 || Key == 27) {
        Close();
    }
}
// ---------------------------------------------------------------------------
void __fastcall Tfpass::FormShow(TObject *Sender)
{
    edPass->Clear();
    SomePass = "";
}
//---------------------------------------------------------------------------

