// ---------------------------------------------------------------------------
// Russian Roulette is PC version of popular television game show.
// Copyright (C) 2010-2011 Popovskiy Andrey
// Copyright (C) 2010-2011 Boytsov Sergey

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// ---------------------------------------------------------------------------
#include <map>
#include <vector>
#include <vcl.h>
#include <system.hpp>
#include "inifiles.hpp"
#pragma hdrstop

#include "uSettings.h"
#include "MainForm.h"
TSettings* Settings;
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSettingsForm* SettingsForm;
std::map <String, String> BaseFiles;

// ---------------------------------------------------------------------------
TSettings::TSettings() {
    for (int i = 0; i < 5; ++i) {
        PlayerNames[i] = "Игрок № ";
        PlayerNames[i][8] = 49 + i; // generate number 1..5. char 49 is '1'
        PlayerType[i] = bbHuman;
    }

    Fullscreen = True;

    FormsTop = 0;
    FormsLeft = 0;
    FormsWidth = 1024;
    FormsHeight = 768;

    MinWidth = 1024;
    MinHeight = 768;

    SoundEnabled = True;
    SoundVolume = 100;
    MusicEnabled = True;
    MusicVolume = 100;

    Win7Features = False;

    LastBase = "main.dat";

    BaseNames = new TStringList();
    HostMode = false;
};

TSettings::TSettings(UnicodeString filename) {
    TIniFile* ini = new TIniFile(filename);

    Fullscreen = ini->ReadBool("Global", "FullScreen", False);
    FormsWidth = ini->ReadInteger("Global", "Width", 1024);
    FormsHeight = ini->ReadInteger("Global", "Height", 1024);
    FormsLeft = ini->ReadInteger("Global", "Left", 0);
    FormsTop = ini->ReadInteger("Global", "Top", 0);
    SoundEnabled = ini->ReadBool("Global", "Sound", False);
    SoundVolume = ini->ReadInteger("Global", "SoundVolume", 100);
    MusicEnabled = ini->ReadBool("Global", "Music", False);
    MusicVolume = ini->ReadInteger("Global", "MusicVolume", 100);
    HostMode = ini->ReadBool("Global", "HostMode", False);

    MinWidth = 1024;
    MinHeight = 768;

    for (int i = 1; i <= 5; i++) {
        PlayerNames[i - 1] = ini->ReadString("Players", "Player" + IntToStr(i), "FUUUUuuuuu...");
        PlayerType[i - 1] = (TBotType)ini->ReadInteger("Players", "PlayerType" + IntToStr(i), 0);
    }

    LastBase = ini->ReadString("Global", "LastBase", "");
    if (LastBase == "") {
        if (FileExists("base\\main.dat")) {
            LastBase = "main.dat";
        } else {
            MessageBox(Application->Handle,
                "Ошибка загрузки последней базы вопросов\n" "Попытка загрузить base\\main.dat также провалилась - файла не существует.",
                "Критическая ошибка", MB_YESNO);
            MB_YESNO;
        }
    }

    int i = 0;
    BaseNames = new TStringList;
    while (1) {
        String str = ini->ReadString("Bases", "basename" + IntToStr(i++), "");
        if (str != "") {
            BaseNames->Add(str);
        } else {
            break;
        }
    }

    ini->Free();
}

// ---------------------------------------------------------------------------
__fastcall TSettingsForm::TSettingsForm(TComponent* Owner) : TForm(Owner) { }

// ---------------------------------------------------------------------------
void __fastcall TSettingsForm::FormShow(TObject* Sender) {
    // <- Загрузка соответствий файлов баз данных их именам
    TIniFile* ini = new TIniFile(ExtractFilePath(Application->ExeName) + "settings.cfg");

    int i = 0;
    BaseFiles.clear();
    while (1) {
        String name = ini->ReadString("Bases", "basename" + IntToStr(i), "");
        String file = ini->ReadString("Bases", "base" + IntToStr(i), "");
        if ((name != "") && (file != "")) {
            BaseFiles[name] = file;
            cmbListOfBases->Items->Add(name);
        } else {
            break;
        }
        i++ ;
    }

    ini->Free();
    // ->

    cmbListOfBases->Items->Assign(Settings->BaseNames);

    for (std::map <String, String> ::iterator it = BaseFiles.begin(); it != BaseFiles.end(); ++it) {
        if (it->second == Settings->LastBase) {
            for (int i = 0; i < cmbListOfBases->Items->Count; ++i) {
                if (it->first == cmbListOfBases->Items->Strings[i]) {
                    cmbListOfBases->ItemIndex = i;
                }
            }
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

    cbWin7Features->Checked = Settings->Win7Features;
    tbSoundVolume->Position = Settings->SoundVolume;
    tbMusicVolume->Position = Settings->MusicVolume;

    // «режим ведущего» отныне и навеки работает ТОЛЬКО при наличии
    // 2-х и более подключенных мониторов к ПК
    if (Screen->MonitorCount > 1) {
        cbHostModeOnOff->Checked = Settings->HostMode;
        cbHostModeOnOff->Enabled = 1;
    } else {
        cbHostModeOnOff->Checked = false;
        cbHostModeOnOff->Enabled = false;
    }

}
// ---------------------------------------------------------------------------

void __fastcall TSettingsForm::FormCreate(TObject* Sender) {
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
    ini->WriteInteger("Global", "Left", Settings->FormsLeft);
    ini->WriteInteger("Global", "Top", Settings->FormsTop);
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

    int i = 0;
    for (std::map <String, String> ::iterator it = BaseFiles.begin(); it != BaseFiles.end(); ++it) {
        ini->WriteString("Bases", "basename" + IntToStr(i), it->first);
        ini->WriteString("Bases", "base" + IntToStr(i), ExtractFileName(it->second));
        ++i;
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

    Settings->LastBase = BaseFiles[cmbListOfBases->Items->Strings[cmbListOfBases->ItemIndex]];

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
            BaseFiles[name] = OpenDialog1->FileName;

            cmbListOfBases->Clear();
            for (std::map <String, String> ::iterator it = BaseFiles.begin(); it != BaseFiles.end(); ++it) {
                cmbListOfBases->Items->Add(it->first);
            }
            cmbListOfBases->ItemIndex = cmbListOfBases->Items->Count - 1;
        } else {
            ShowMessage("Ошибка добавления базы =(");
        }
    }
}

// ---------------------------------------------------------------------------
void LoadFormPosition(TForm* form) {
    if (Settings->Fullscreen) {
        form->BorderStyle = bsNone;
        form->Width = Screen->Width;
        form->Height = Screen->Height;
        form->Top = 0;
        form->Left = 0;
    } else {
        form->BorderStyle = bsSizeable;
        form->Width = Settings->FormsWidth;
        form->Height = Settings->FormsHeight;
        form->Left = Settings->FormsLeft;
        form->Top = Settings->FormsTop;
    }
}

void SaveFormPosition(TForm* form) {
    if (!Settings->Fullscreen) {
        Settings->FormsWidth = form->Width;
        Settings->FormsHeight = form->Height;
        Settings->FormsTop = form->Top;
        Settings->FormsLeft = form->Left;
    }
}
// ---------------------------------------------------------------------------

void CoolPositionFix(TForm* form) {
    /* АЦЦКИЙ КОСТЫЛЬ
     суть в том, что после перевода формы в состояние Borderless
     она самопроизвольно сдвигается влево, что не есть гут
     при этом контролировать это смещение из LoadFormPosition()
     не представляется возможным =(
     */
    if (form->Top < 0) {
        form->Top = 0;
    }
    if (form->Left < 0) {
        form->Left = 0;
    }
}
// ---------------------------------------------------------------------------

void SwitchFullscreen(TForm* form) {
    Settings->Fullscreen = !Settings->Fullscreen;
    LoadFormPosition(form);
}
