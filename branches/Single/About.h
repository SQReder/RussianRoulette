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
<<<<<<< .mine
    TTimer* tmrScroll;
    TLabel* lblAboutText;
    TLabel* Label1;
    TLabel* Label2;
    TLabel* Label3;
    TLabel* Label4;
    TLabel* Label5;
    TLabel* Label6;
    TLabel* Label7;
    TLabel* Label8;
    TLabel* Label9;
    TLabel* Label10;
    TLabel* Label11;
    TLabel* Label12;
    TLabel* Label13;
    TLabel* Label14;
    TLabel* Label15;
    TLabel* Label16;
    TLabel* Label17;
    TLabel* Label18;
    TLabel* Label19;
    TLabel* Label20;
    TLabel* Label21;
    TLinkLabel* LinkLabel1;
    void __fastcall tmrScrollTimer(TObject* Sender);
    void __fastcall FormShow(TObject* Sender);
    void __fastcall lblAboutTextClick(TObject* Sender);
    void __fastcall FormCreate(TObject* Sender);
    void __fastcall FormClick(TObject* Sender);
=======
>>>>>>> .r12

	TTimer* tmrScroll;
	TLabel* lblAboutText;
	TLabel* Label1;
	TLabel* Label2;
	TLabel* Label3;
	TLabel* Label4;
	TLabel* Label5;
	TLabel* Label6;
	TLabel* Label7;
	TLabel* Label8;
	TLabel* Label9;
	TLabel* Label10;
	TLabel* Label11;
	TLabel* Label12;
	TLabel* Label13;
	TLabel* Label14;
	TLabel* Label15;
	TLabel* Label16;
	TLabel* Label17;
	TLabel* Label18;
	TLabel* Label19;
	TLabel* Label20;
	TLabel* Label21;
	TLinkLabel* LinkLabel1;

	void __fastcall tmrScrollTimer(TObject* Sender);
	void __fastcall FormShow(TObject* Sender);
	void __fastcall lblAboutTextClick(TObject* Sender);
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall FormClick(TObject* Sender);

private: // User declarations
		public : // User declarations
	__fastcall TAboutForm(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TAboutForm* AboutForm;
// ---------------------------------------------------------------------------
#endif
