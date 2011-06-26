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
#pragma hdrstop
#include "GfxCache.h"
#pragma package(smart_init)

#define imgBlackHatch	"Data\\Black.png"	//state index 0
#define imgBaseHatch	"Data\\Base.png"	//state index 1
#define imgBlueHatch	"Data\\Blue.png"	//state index 2
#define imgRedHatch		"Data\\Red.png"		//state index 3
#define imgWhiteHatch	"Data\\White.png"	//state index 4
#define imgGreyHatch	"Data\\Base.png"	//state index 5

sGfxCache* gfx;

sGfxCache::sGfxCache() {
    PulseFramesCount = 56;
    PulseFrames = new TPicture *[PulseFramesCount];
    for (int i = 0; i < PulseFramesCount; i++) {
        PulseFrames[i] = new TPicture();
        PulseFrames[i]->LoadFromFile("data\\pulse\\pulse_" + Trim(IntToStr(i + 1)) + ".png");
    }

    for (int i = 0; i < 21; ++i) {
        Tick[i] = new TPicture();
        Tick[i]->LoadFromFile("data\\" + Trim(IntToStr(i)) + "sec.png");
    }

    for (int i = 0; i < 16; ++i) {
        Liver[i] = new TPicture();
        Liver[i]->LoadFromFile("Data\\рычаг_" + IntToStr(i) + ".png");
    }

    for (int i = 1; i < 5; ++i) {
        Splash[i] = new TPicture();
        Splash[i]->LoadFromFile("Data\\splash-" + IntToStr(i) + ".png");
    }

    Place = new TPicture();
    Place->LoadFromFile("data\\place.png");

    rr_quest = new TPicture();
    rr_quest->LoadFromFile("data\\rr_quest.png");

    PlaceRedZero = new TPicture();
    PlaceRedZero->LoadFromFile("Data\\Place_red_zero.png");

    quest_correct = new TPicture();
    quest_correct->LoadFromFile("Data\\quest_correct.png");

    quest_incorrect = new TPicture();
    quest_incorrect->LoadFromFile("Data\\quest_incorrect.png");

    FinalSplash = new TPicture();
    FinalSplash->LoadFromFile("Data\\Final.png");

    for (int i = 0; i < 6; i++) { // конструктор изображений состояний люков
        h_state_img[i] = new TPicture;
    }

    h_state_img[0]->LoadFromFile(imgBlackHatch); // и подгрузка из файлов на диске
    h_state_img[1]->LoadFromFile(imgBaseHatch); // значения констант описаны
    h_state_img[2]->LoadFromFile(imgBlueHatch); // в начале модуля
    h_state_img[3]->LoadFromFile(imgRedHatch);
    h_state_img[4]->LoadFromFile(imgWhiteHatch);
    h_state_img[5]->LoadFromFile(imgGreyHatch);

}

sGfxCache::~sGfxCache() {
    for (int i = 0; i < PulseFramesCount; i++) {
        delete PulseFrames[i];
    }
    delete PulseFrames;

    for (int i = 0; i < 21; ++i) {
        delete Tick[i];
    }

    for (int i = 0; i < 16; ++i) {
        delete Liver[i];
    }

    for (int i = 1; i < 5; ++i) {
        delete Splash[i];
    }

    delete Place;
    delete rr_quest;
    delete PlaceRedZero;
    delete quest_correct;
    delete quest_incorrect;
    delete FinalSplash;

    for (int i = 0; i < 6; i++) {
        delete h_state_img[i];
    }

}
