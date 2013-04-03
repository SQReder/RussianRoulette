//---------------------------------------------------------------------------

#ifndef frm_passH
#define frm_passH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class Tfpass : public TForm
{
__published:	// IDE-managed Components
    TEdit *edPass;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall Tfpass(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfpass *fpass;
extern AnsiString SomePass;
//---------------------------------------------------------------------------
#endif
