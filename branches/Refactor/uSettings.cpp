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
TSettings* Settings;
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSettingsForm* SettingsForm;
std::vector <std::pair <UnicodeString, UnicodeString> > BaseFiles;

// ---------------------------------------------------------------------------

void ReadCfgFile() {
    TIniFile* ini = new TIniFile(ExtractFilePath(Application->ExeName) + "settings.cfg");
    Settings->Fullscreen = ini->ReadBool("Global", "FullScreen", False);
    Settings->FormsWidth = ini->ReadInteger("Global", "Width", 1024);
    Settings->FormsHeight = ini->ReadInteger("Global", "Height", 1024);
    Settings->SoundEnabled = ini->ReadBool("Global", "Sound", False);
    Settings->SoundVolume = ini->ReadInteger("Global", "SoundVolume", 100);
    Settings->MusicEnabled = ini->ReadBool("Global", "Music", False);
    Settings->MusicVolume = ini->ReadInteger("Global", "MusicVolume", 100);
    Settings->HostMode = ini->ReadBool("Global", "HostMode", False);

    for (int i = 1; i <= 5; i++) {
        Settings->PlayerNames[i - 1] = ini->ReadString("Players", "Player" + IntToStr(i), "FUUUUuuuuu...");
        Settings->PlayerType[i - 1] = (TBotType)ini->ReadInteger("Players", "PlayerType" + IntToStr(i), 0);
    }

    Settings->LastBase = ini->ReadString("Global", "LastBase", "");

    int i = 0;
    while (1) {
        String str = ini->ReadString("Bases", "basename" + IntToStr(i), "");
        if (str != "") {
            Settings->BaseNames->Add(str);
        }
        else {
            break;
        }
        i++ ;
    }

    if (Settings->LastBase == "") {
        ShowError(1);
    }

    ini->Free();
}

// ---------------------------------------------------------------------------
void InitializeSettings() {
    Settings = new TSettings();
    ReadCfgFile();
}

// ---------------------------------------------------------------------------
__fastcall TSettingsForm::TSettingsForm(TComponent* Owner) : TForm(Owner) { }

// ---------------------------------------------------------------------------
void __fastcall TSettingsForm::FormShow(TObject* Sender) {
    cbWin7Features->Checked = Settings->Win7Features;
    tbSoundVolume->Position = Settings->SoundVolume;
    tbMusicVolume->Position = Settings->MusicVolume;
}
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
        else {
            break;
        }
        i++ ;
    }

    ini->Free();
    // ->

    cmbListOfBases->Items->Assign(Settings->BaseNames);

    for (int i = 0; i < cmbListOfBases->Items->Count; i++) {
        if (BaseFiles[i].second == Settings->LastBase) {
            cmbListOfBases->ItemIndex = i;
        }
    }

    edPlayer0->Text = Settings->PlayerNames[0];
    edPlayer1->Text = Settings->PlayerNames[1];
    edPlayer2->Text = Settings->PlayerNames[2];
    edPlayer3->Text = Settings->PlayerNames[3];
    edPlayer4->Text = Settings->PlayerNames[4];

    cmbPlayerType0->ItemIndex = (int)Settings->PlayerType[0];
    cmbPlayerType1->ItemIndex = (int)Settings->PlayerType[1];
    cmbPlayerType2->ItemIndex = (int)Settings->PlayerType[2];
    cmbPlayerType3->ItemIndex = (int)Settings->PlayerType[3];
    cmbPlayerType4->ItemIndex = (int)Settings->PlayerType[4];

    cbSoundOnOff->Checked = Settings->SoundEnabled;
    cbMusicOnOff->Checked = Settings->MusicEnabled;
    cbFullscreen->Checked = Settings->Fullscreen;
    // «режим ведущего» отныне и навеки работает ТОЛЬКО при наличии
    // 2-х и более подключенных мониторов к ПК
    if (Screen->MonitorCount > 1) {
        cbHostModeOnOff->Checked = Settings->HostMode;
        cbHostModeOnOff->Enabled = 1;
    }
    else {
        cbHostModeOnOff->Checked = 0;
        cbHostModeOnOff->Enabled = 0;
    }

    btnCancel->Caption = "Cancel";
    btnOK->Caption = "OK";
    gbPlayerNames->Caption = "Имена игроков";
    gbChooseQuestionBase->Caption = "База вопросов для игры";
    gbOptions->Caption = "Опции игры";
    cbSoundOnOff->Caption = "Включить звук";
    cbMusicOnOff->Caption = "Включить музыку";
    cbFullscreen->Caption = "Полный экран";
    cbHostModeOnOff->Caption = "Режим ведущего";
    tbSoundVolumeChange(NULL);
    tbMusicVolumeChange(NULL);
    cbSoundOnOffClick(NULL);
    cbMusicOnOffClick(NULL);
}
// ---------------------------------------------------------------------------

void __fastcall TSettingsForm::btnCancelClick(TObject* Sender) {
    SettingsForm->Hide();
    SettingsForm->Close();
}

// ---------------------------------------------------------------------------
void SaveSettings() {
    TIniFile* ini = new TIniFile(ExtractFilePath(Application->ExeName) + "settings.cfg");
    ini->WriteBool("Global", "FullScreen", Settings->Fullscreen);
    ini->WriteInteger("Global", "Width", Settings->FormsWidth);
    ini->WriteInteger("Global", "Height", Settings->FormsHeight);
    ini->WriteBool("Global", "Sound", Settings->SoundEnabled);
    ini->WriteInteger("Global", "SoundVolume", Settings->SoundVolume);
    ini->WriteBool("Global", "Music", Settings->MusicEnabled);
    ini->WriteInteger("Global", "MusicVolume", Settings->MusicVolume);
    ini->WriteBool("Global", "HostMode", Settings->HostMode);
    ini->WriteString("Global", "LastBase", Settings->LastBase);

    for (int i = 1; i <= 5; i++) {
        ini->WriteString("Players", "Player" + IntToStr(i), Settings->PlayerNames[i - 1]);
        ini->WriteInteger("Players", "PlayerType" + IntToStr(i), (int) Settings->PlayerType[i - 1]);
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
    Settings->PlayerNames[0] = edPlayer0->Text;
    Settings->PlayerNames[1] = edPlayer1->Text;
    Settings->PlayerNames[2] = edPlayer2->Text;
    Settings->PlayerNames[3] = edPlayer3->Text;
    Settings->PlayerNames[4] = edPlayer4->Text;

    Settings->PlayerType[0] = (TBotType)cmbPlayerType0->ItemIndex;
    Settings->PlayerType[1] = (TBotType)cmbPlayerType1->ItemIndex;
    Settings->PlayerType[2] = (TBotType)cmbPlayerType2->ItemIndex;
    Settings->PlayerType[3] = (TBotType)cmbPlayerType3->ItemIndex;
    Settings->PlayerType[4] = (TBotType)cmbPlayerType4->ItemIndex;

    Settings->SoundEnabled = cbSoundOnOff->Checked;
    Settings->SoundVolume = tbSoundVolume->Position;
    Settings->MusicEnabled = cbMusicOnOff->Checked;
    Settings->MusicVolume = tbMusicVolume->Position;
    Settings->Fullscreen = cbFullscreen->Checked;
    Settings->Win7Features = cbWin7Features->Checked;
    Settings->HostMode = cbHostModeOnOff->Checked;

    Settings->LastBase = BaseFiles[cmbListOfBases->ItemIndex].second;

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
            for (unsigned int i = 0; i < BaseFiles.size(); i++) {
                cmbListOfBases->Items->Add(BaseFiles[i].first);
            }
            cmbListOfBases->ItemIndex = cmbListOfBases->Items->Count - 1;
        }
        else {
            ShowMessage("Ошибка добавления базы =(");
        }
    }
}
// ---------------------------------------------------------------------------
