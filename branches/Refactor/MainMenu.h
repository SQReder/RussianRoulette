// ---------------------------------------------------------------------------

#ifndef MainMenuH
#define MainMenuH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <pngimage.hpp>

// ---------------------------------------------------------------------------
class TMenuForm : public TForm {
__published: // IDE-managed Components

	TLabel* btnNewGame;
	TLabel* btnShowSettings;
	TLabel* btnGameRules;
	TLabel* btnAbout;
	TLabel* btnBblNTuHaxep;
	TImage* Background;

	void __fastcall FormCreate(TObject* Sender);
	void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
	void __fastcall _btnBblNTuHaxepClick(TObject* Sender);
	void __fastcall btnNewGameClick(TObject* Sender);
	void __fastcall btnShowSettingsClick(TObject* Sender);
	void __fastcall btnAboutClick(TObject* Sender);
	void __fastcall FormResize(TObject* Sender);
	void __fastcall FormShow(TObject* Sender);
	void __fastcall FormHide(TObject* Sender);

private: // User declarations
		public : // User declarations
	__fastcall TMenuForm(TComponent* Owner);

	bool MenuVisible;
};

// ---------------------------------------------------------------------------
extern PACKAGE TMenuForm* MenuForm;
// ---------------------------------------------------------------------------
#endif