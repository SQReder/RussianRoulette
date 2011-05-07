// ---------------------------------------------------------------------------

#ifndef uSettingsH
#define uSettingsH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>

// ---------------------------------------------------------------------------
class TSettingsForm : public TForm {
__published: // IDE-managed Components

	TButton* btnCancel;
	TCheckBox* cbSoundOnOff;
	TGroupBox* gbPlayerNames;
	TLabeledEdit* edPlayer0;
	TLabeledEdit* edPlayer1;
	TLabeledEdit* edPlayer2;
	TLabeledEdit* edPlayer3;
	TLabeledEdit* edPlayer4;
	TButton* btnOK;
	TPanel* Panel1;
	TCheckBox* cbFullscreen;
	TCheckBox* cbWin7Features;
	TComboBox* cmbListOfBases;
	TComboBox* cmbPlayerType0;
	TComboBox* cmbPlayerType1;
	TComboBox* cmbPlayerType2;
	TComboBox* cmbPlayerType3;
	TComboBox* cmbPlayerType4;
	TCheckBox* cbMusicOnOff;
	TFileListBox* FileListBox1;
	TCheckBox* cbHostModeOnOff;
	TTrackBar* tbSoundVolume;
	TGroupBox* gbChooseQuestionBase;
	TGroupBox* gbOptions;
	TLabel* lblSoundVolume;
	TTrackBar* tbMusicVolume;
	TLabel* lblMusicVolume;
	TButton* addBase;
	TOpenDialog* OpenDialog1;

	void __fastcall FormShow(TObject* Sender);
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall btnCancelClick(TObject* Sender);
	void __fastcall btnOKClick(TObject* Sender);
	void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
	void __fastcall tbSoundVolumeChange(TObject* Sender);
	void __fastcall tbMusicVolumeChange(TObject* Sender);
	void __fastcall cbSoundOnOffClick(TObject* Sender);
	void __fastcall cbMusicOnOffClick(TObject* Sender);
	void __fastcall addBaseClick(TObject* Sender);

private: // User declarations
		public : // User declarations
	__fastcall TSettingsForm(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TSettingsForm* SettingsForm;
// ---------------------------------------------------------------------------
#endif
