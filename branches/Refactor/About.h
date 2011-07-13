// ---------------------------------------------------------------------------

#ifndef AboutH
#define AboutH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

// ---------------------------------------------------------------------------
class TAboutForm : public TForm {
__published: // IDE-managed Components
    TLabel *lblProjTitle;
    TLabel *lblLicence;
    TLabel *Label22;
    TLabel *Label1;
    void __fastcall FormCreate(TObject* Sender);
    void __fastcall lblLicenceClick(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

public: // User declarations
    __fastcall TAboutForm(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TAboutForm* AboutForm;
// ---------------------------------------------------------------------------
#endif
