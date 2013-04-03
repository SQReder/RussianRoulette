// ---------------------------------------------------------------------------
// Russian Roulette is PC version of popular television game show.
// Copyright (C) 2010-2013 Popovskiy Andrey
// Copyright (C) 2010-2013 Boytsov Sergey

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
#include "settings_impl.h"
#include "pch.h"
#include "audio.h"
#pragma package(smart_init)

// ---------------------------------------------------------------------------
TSettings *TSettings::SingleInstance = NULL;

TSettings *TSettings::Instance() {
    if (SingleInstance == NULL) {
        SingleInstance = new TSettings();
    }
    return SingleInstance;
}
// ---------------------------------------------------------------------------

void TSettings::LoadFromFile(String filename) {
    TIniFile *ini = new TIniFile(filename);

    Fullscreen = ini->ReadBool("Global", "FullScreen", false);
    FormsWidth = ini->ReadInteger("Global", "Width", 1024);
    FormsHeight = ini->ReadInteger("Global", "Height", 1024);
    FormsLeft = ini->ReadInteger("Global", "Left", 0);
    FormsTop = ini->ReadInteger("Global", "Top", 0);
    SoundEnabled = ini->ReadBool("Global", "Sound", false);
    SoundVolume = ini->ReadInteger("Global", "SoundVolume", 100);
    SetVolumeAll(SoundVolume/100.);
    MusicEnabled = ini->ReadBool("Global", "Music", false);
    MusicVolume = ini->ReadInteger("Global", "MusicVolume", 100);
    HostMode = ini->ReadBool("Global", "HostMode", false);

    MinWidth = 1024;
    MinHeight = 768;

    for (int i = 1; i <= 5; i++) {
        PlayerNames[i - 1] = ini->ReadString("Players", "Player" + IntToStr(i), "PlayerName");
        PlayerType[i - 1] = (TBotType)ini->ReadInteger("Players", "PlayerType" + IntToStr(i), 0);
    }

    LastBase = ini->ReadString("Global", "LastBase", "");
    if (LastBase == "") {
        if (FileExists("base\\main.dat")) {
            LastBase = "main.dat";
        } else {
            MessageBox(Application->Handle,
                "Ошибка загрузки последней базы вопросов\n" "Попытка загрузить base\\main.dat также провалилась - файла не существует.",
                "Критическая ошибка", MB_OK | MB_ICONSTOP);
            Application->Terminate();
        }
    }

    int i = 0;
    BaseFiles.clear();
    BaseNames = new TStringList;
    while (1) {
        String name = ini->ReadString("Bases", "basename" + IntToStr(i), "");
        String file = ini->ReadString("Bases", "base" + IntToStr(i), "");
        if ((name != "") && (file != "")) {
            BaseFiles[name] = file;
            BaseNames->Add(name);
        } else {
            break;
        }
        i++ ;
    }

    ini->Free();
}
// ---------------------------------------------------------------------------

void TSettings::SaveToFile() {
    TSettings *Settings = TSettings::Instance();
    TIniFile *ini = new TIniFile(".\\settings.cfg");

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

    int i = 0;
    for (std::map <String, String> ::iterator it = BaseFiles.begin(); it != BaseFiles.end(); ++it) {
        ini->WriteString("Bases", "basename" + IntToStr(i), it->first);
        ini->WriteString("Bases", "base" + IntToStr(i), ExtractFileName(it->second));
        ++i;
    }
    ini->Free();

}
// ---------------------------------------------------------------------------

TSettings::~TSettings() { delete BaseNames; }
// ---------------------------------------------------------------------------
