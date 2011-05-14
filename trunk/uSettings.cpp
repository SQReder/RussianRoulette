// ---------------------------------------------------------------------------
#include <utility>
#include <vector>
#pragma hdrstop
#include <vcl.h>
#pragma hdrstop
#include "inifiles.hpp"
#pragma hdrstop

#include "uSettings.h"
#include "MainForm.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSettingsForm* SettingsForm;
void ListFiles(String path, TStrings* List);
std::vector <std::pair <UnicodeString, UnicodeString> > BaseFiles;

// ---------------------------------------------------------------------------
__fastcall TSettingsForm::TSettingsForm(TComponent* Owner) : TForm(Owner) { }

// ---------------------------------------------------------------------------
void __fastcall TSettingsForm::FormShow(TObject* Sender) { F->InitializeSettings(); }
// ---------------------------------------------------------------------------

void __fastcall TSettingsForm::FormCreate(TObject* Sender) {
	// <- Загрузка соответствий файлов баз данных их именам
	TIniFile* ini = new TIniFile(ExtractFilePath(Application->ExeName) + "settings.cfg");

	int i = 0;
	BaseFiles.clear();
	while (1) {
		String name = ini->ReadString("Bases", "basename" + IntToStr(i), "");
		String file = ini->ReadString("Bases", "base" + IntToStr(i), "");
		if ((name != "") && (file != "")) {
			BaseFiles.push_back(std::make_pair(name, file));
			cmbListOfBases->Items->Add(BaseFiles[BaseFiles.size() - 1].first);
		}
		else
			break;
		i++ ;
	}

	ini->Free();
	// ->

	cmbListOfBases->Items->Assign(F->Settings->BaseNames);

	edPlayer0->Text = F->Settings->PlayerNames[0];
	edPlayer1->Text = F->Settings->PlayerNames[1];
	edPlayer2->Text = F->Settings->PlayerNames[2];
	edPlayer3->Text = F->Settings->PlayerNames[3];
	edPlayer4->Text = F->Settings->PlayerNames[4];

	cmbPlayerType0->ItemIndex = (int)F->Settings->PlayerType[0];
	cmbPlayerType1->ItemIndex = (int)F->Settings->PlayerType[1];
	cmbPlayerType2->ItemIndex = (int)F->Settings->PlayerType[2];
	cmbPlayerType3->ItemIndex = (int)F->Settings->PlayerType[3];
	cmbPlayerType4->ItemIndex = (int)F->Settings->PlayerType[4];

	cbSoundOnOff->Checked = F->Settings->SoundEnabled;
	cbMusicOnOff->Checked = F->Settings->MusicEnabled;
	cbFullscreen->Checked = F->Settings->Fullscreen;
	// «режим ведущего» отныне и навеки работает ТОЛЬКО при наличии
	// 2-х и более подключенных мониторов к ПК
	if (Screen->MonitorCount > 1) {
		cbHostModeOnOff->Checked = F->Settings->HostMode;
		cbHostModeOnOff->Enabled = 1;
	}
	else {
		cbHostModeOnOff->Checked = 0;
		cbHostModeOnOff->Enabled = 0;
	}
	cbWin7Features->Checked = F->Settings->Win7Features;
	tbSoundVolume->Position = F->Settings->SoundVolume;
	tbMusicVolume->Position = F->Settings->MusicVolume;

	btnCancel->Caption = "Cancel";
	btnOK->Caption = "OK";
	gbPlayerNames->Caption = "Имена игроков";
	gbChooseQuestionBase->Caption = "База вопросов для игры";
	gbOptions->Caption = "Опции игры";
	cbSoundOnOff->Caption = "Включить звук";
	cbMusicOnOff->Caption = "Включить музыку";
	cbFullscreen->Caption = "Полный экран";
	cbHostModeOnOff->Caption = "Режим ведущего";
	tbSoundVolumeChange(tbSoundVolume);
	tbMusicVolumeChange(tbMusicVolume);
	cbSoundOnOffClick(cbSoundOnOff);
	cbMusicOnOffClick(cbMusicOnOff);
}
// ---------------------------------------------------------------------------

void __fastcall TSettingsForm::btnCancelClick(TObject* Sender) {
	SettingsForm->Hide();
	SettingsForm->Close();
}

// ---------------------------------------------------------------------------
void SaveSettings() {
	TIniFile* ini = new TIniFile(ExtractFilePath(Application->ExeName) + "settings.cfg");
	ini->WriteBool("Global", "FullScreen", F->Settings->Fullscreen);
	ini->WriteInteger("Global", "Width", F->Settings->FormsWidth);
	ini->WriteInteger("Global", "Height", F->Settings->FormsHeight);
	ini->WriteBool("Global", "Sound", F->Settings->SoundEnabled);
	ini->WriteInteger("Global", "SoundVolume", F->Settings->SoundVolume);
	ini->WriteBool("Global", "Music", F->Settings->MusicEnabled);
	ini->WriteInteger("Global", "MusicVolume", F->Settings->MusicVolume);
	ini->WriteBool("Global", "HostMode", F->Settings->HostMode);
	ini->WriteString("Global", "LastBase", F->Settings->LastBase);

	for (int i = 1; i <= 5; i++) {
		ini->WriteString("Players", "Player" + IntToStr(i), F->Settings->PlayerNames[i - 1]);
		ini->WriteInteger("Players", "PlayerType" + IntToStr(i), (int) F->Settings->PlayerType[i - 1]);
	}

	// SettingsForm->FileListBox1->Directory = ExtractFileDir(Application->ExeName) + "\\base\\";
	// SettingsForm->FileListBox1->Update();
	for (int i = 0; i < SettingsForm->cmbListOfBases->Items->Count; i++) {
		ini->WriteString("Bases", "basename" + IntToStr(i), BaseFiles[i].first);
		ini->WriteString("Bases", "base" + IntToStr(i), ExtractFileName(BaseFiles[i].second));
	}
	ini->Free();

}

// -----------------------------------------------------------------------------
void __fastcall TSettingsForm::btnOKClick(TObject* Sender) {
	F->Settings->PlayerNames[0] = edPlayer0->Text;
	F->Settings->PlayerNames[1] = edPlayer1->Text;
	F->Settings->PlayerNames[2] = edPlayer2->Text;
	F->Settings->PlayerNames[3] = edPlayer3->Text;
	F->Settings->PlayerNames[4] = edPlayer4->Text;

	F->Settings->PlayerType[0] = (TBotType)cmbPlayerType0->ItemIndex;
	F->Settings->PlayerType[1] = (TBotType)cmbPlayerType1->ItemIndex;
	F->Settings->PlayerType[2] = (TBotType)cmbPlayerType2->ItemIndex;
	F->Settings->PlayerType[3] = (TBotType)cmbPlayerType3->ItemIndex;
	F->Settings->PlayerType[4] = (TBotType)cmbPlayerType4->ItemIndex;

	F->Settings->SoundEnabled = cbSoundOnOff->Checked;
	F->Settings->SoundVolume = tbSoundVolume->Position;
	F->Settings->MusicEnabled = cbMusicOnOff->Checked;
	F->Settings->MusicVolume = tbMusicVolume->Position;
	F->Settings->Fullscreen = cbFullscreen->Checked;
	F->Settings->Win7Features = cbWin7Features->Checked;
	F->Settings->HostMode = cbHostModeOnOff->Checked;

	SaveSettings();
	SettingsForm->Hide();
	SettingsForm->Close();
}
// ---------------------------------------------------------------------------


void __fastcall TSettingsForm::tbSoundVolumeChange(TObject* Sender) {
	lblSoundVolume->Caption = "Громкость звука: " + IntToStr(tbSoundVolume->Position) + "%"; }
// ---------------------------------------------------------------------------

void __fastcall TSettingsForm::tbMusicVolumeChange(TObject* Sender) {
	lblMusicVolume->Caption = "Громкость музыки: " + IntToStr(tbMusicVolume->Position) + "%"; }
// ---------------------------------------------------------------------------

void __fastcall TSettingsForm::cbSoundOnOffClick(TObject* Sender) {
	tbSoundVolume->Enabled = cbSoundOnOff->Checked;
	lblSoundVolume->Enabled = cbSoundOnOff->Checked;
}
// ---------------------------------------------------------------------------

void __fastcall TSettingsForm::cbMusicOnOffClick(TObject* Sender) {
	tbMusicVolume->Enabled = cbMusicOnOff->Checked;
	lblMusicVolume->Enabled = cbMusicOnOff->Checked;
}
// ---------------------------------------------------------------------------

void __fastcall TSettingsForm::addBaseClick(TObject* Sender) {
	if (OpenDialog1->Execute()) {
		WCHAR* from = (OpenDialog1->FileName).w_str();
		WCHAR* to = (ExtractFilePath(Application->ExeName) + "Base\\" + ExtractFileName(OpenDialog1->FileName)).w_str();
		if (CopyFileW(from, to, 0)) {
			String name = InputBox("Русская рулетка :: Добавить базу", "Введите имя новой базы",
				ExtractFileName(OpenDialog1->FileName));
			BaseFiles.push_back(std::make_pair(name, OpenDialog1->FileName));

			cmbListOfBases->Clear();
			for (unsigned int i = 0; i < BaseFiles.size(); i++)
				cmbListOfBases->Items->Add(BaseFiles[i].first);
			cmbListOfBases->ItemIndex = cmbListOfBases->Items->Count - 1;
		}
		else {
			ShowMessage("Ошибка добавления базы =(");
		}
	}
}
// ---------------------------------------------------------------------------
