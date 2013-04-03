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
#ifndef SETTINGS_IMPLH
#define SETTINGS_IMPLH
#include "pch.h"
#include "AI.h"

// ---------------------------------------------------------------------------
class TSettings {
public:
    String PlayerNames[5];
    TBotType PlayerType[5];
    bool Fullscreen;
    int FormsWidth;
    int FormsHeight;
    int FormsTop;
    int FormsLeft;
    int MinWidth;
    int MinHeight;
    bool SoundEnabled;
    int SoundVolume;
    bool MusicEnabled;
    int MusicVolume;
    bool HostMode;

    TStringList *BaseNames;
    map <String, String> BaseFiles;
    String LastBase;

    ~TSettings();

    static TSettings *Instance();

    void LoadFromFile(String filename);
    void SaveToFile();

private:
    TSettings() { };

    static TSettings *SingleInstance;

    TSettings(TSettings &) { };
};
// ---------------------------------------------------------------------------
#endif
