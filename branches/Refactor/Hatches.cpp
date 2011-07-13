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
#include <vcl.h>
#include <winbase.h>
#pragma hdrstop

#define imgBlackHatch	"Data\\Black.png"	//state index 0
#define imgBaseHatch	"Data\\Base.png"	//state index 1
#define imgBlueHatch	"Data\\Blue.png"	//state index 2
#define imgRedHatch		"Data\\Red.png"		//state index 3
#define imgWhiteHatch	"Data\\White.png"	//state index 4
#define imgGreyHatch	"Data\\Base.png"	//state index 5

#include "Hatches.h"
#include "GameLogic.h"
#pragma package(smart_init)
using Graphics::TPicture;
TPicture* hatch[6]; // указатели на изображения люков на форме
TPicture* h_state_img[6]; // изображения состояний люков
int h_state[6]; // текущее состояние люков
int AnimationFrame; // определяет порядок анимации

// from MainForm.cpp
extern int opened_now[6];
extern int CantFall;
extern int chooseplayer;

// ---------------------------------------------------------------------------
void ShiftHatches() {
    char tmp = h_state[5]; // проворот барабана осуществляется
    h_state[5] = h_state[4]; // простым сдвигом массива на 1 элемент.
    h_state[4] = h_state[3]; // по своей сути это shr(h_state[]);
    h_state[3] = h_state[2];
    h_state[2] = h_state[1];
    h_state[1] = h_state[0];
    h_state[0] = tmp;
};

// ---------------------------------------------------------------------------
inline void InitializeHatches() {
    for (int i = 0; i < 6; i++) {
        hatch[i] = new TPicture; // конструкторы изображений люков
        h_state[i] = 1; // и закрытие их
    }

    hatch[0] = F->imgHatch0->Picture; // установка ссылок на изображения на форме
    hatch[1] = F->imgHatch1->Picture;
    hatch[2] = F->imgHatch2->Picture;
    hatch[3] = F->imgHatch3->Picture;
    hatch[4] = F->imgHatch4->Picture;
    hatch[5] = F->imgHatch5->Picture;
}

// ---------------------------------------------------------------------------
inline void LoadHatchStateImages() {
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

// ---------------------------------------------------------------------------
inline void LoadHatchImage(int index, int state) { // банальное копирование изображения состояния на форму
    hatch[index]->Assign(h_state_img[state]);
}

// ---------------------------------------------------------------------------
void MechanizmSetHatchesStates() { // приведение изображений на форме в соответствие с состояниями люков
    for (int i = 0; i < 6; i++) {
        LoadHatchImage(i, h_state[i]);
    }
}

// ---------------------------------------------------------------------------
void OpenRandomHatches(const int OpenHatches, int ModeOfGame) {
    if (OpenHatches > 6) {
        ShowMessage("А фигли так много люков открываем?!");
        exit(1);
    }

    // F->RndHatch = 0;
    for (int i = 0; i < 6; i++) {
        opened_now[i] = 0;
    } // закрываем открытые люки,

    do {
        opened_now[random(6)] = 1; // и открываем случайный пока не откроем

        if (CantFall != -1) {
            opened_now[CantFall + 1] = 0;
        } // и спасаем игрока же! ^_^"

        // закрываем люки, которые не могут открываться
        for (int i = 0; i < 5; i++) { // те, что уже не в игре
            if (!F->ingame[i] && ModeOfGame == 8) {
                opened_now[i + 1] = 0;
            }
        }

        // закрываем люк ведущего, если не финал еще или миниигра.
        if (F->FinalRoundOfGame < 1) { /* && (F->GameMode != minigame) */
            opened_now[0] = 0;
        }

    }
    while // нужное нам количество
        (opened_now[0] + opened_now[1] + opened_now[2] + opened_now[3] + opened_now[4] + opened_now[5] < OpenHatches);

}

// ---------------------------------------------------------------------------
void Hatches() { // инициализация механизма
    randomize();
    InitializeHatches();
    LoadHatchStateImages();
    MechanizmSetHatchesStates();

};

// ---------------------------------------------------------------------------
// на самом эта процедура выбирает случайного игрока в начале раунда
// кто-бы мог подумать?!
void ZeroRoundRotating() // установки для нулевого раунда
{ // один люк подсвечен белым
    for (int i = 0; i < 6; i++) {
        h_state[i] = 1;
    }
    int blah = random(6);
    h_state[blah] = 4;
    CurrentHatch = blah;
}

// ---------------------------------------------------------------------------
void FirstRoundRotating() {
    for (int i = 0; i < 6; i++) {
        h_state[i] = 2;
    }

    switch (AnimationFrame++ % 2) {
    case 0:
        h_state[CurrentHatch] = 4;
        break;
    case 1:
        h_state[CurrentHatch] = 3;
        CurrentHatch++ ;
        break;
    default:
        AnimationFrame = 0;
        break;
    }
    CurrentHatch = CurrentHatch % 6;
}

// ---------------------------------------------------------------------------
void LightHatchesW(int bright, int light) {
    // если 255 то заливаем все вторым цветом
    if (bright == 255)
        for (int i = 0; i < 6; i++) {
            h_state[i] = light;
        } else
        for (int i = 0; i < 6; i++) {
            if (h_state[i] != light) {
                h_state[i] = bright;
            }
        }
}

// ---------------------------------------------------------------------------
void ZeroRoundSpin() {
    static const int frames[15][6] = {
        { 1, 4, 1, 1, 1, 1 },
        { 1, 4, 1, 1, 1, 1 },
        { 1, 4, 4, 1, 1, 1 },
        { 4, 4, 4, 1, 1, 1 },
        { 4, 4, 4, 4, 1, 1 },
        { 4, 4, 4, 4, 1, 1 },
        { 4, 1, 4, 4, 4, 1 },
        { 4, 1, 4, 4, 4, 1 },
        { 1, 1, 1, 4, 4, 4 },
        { 1, 1, 1, 4, 4, 4 },
        { 1, 1, 1, 1, 4, 4 },
        { 1, 1, 1, 1, 4, 4 },
        { 1, 1, 1, 1, 1, 4 },
        { 1, 1, 1, 1, 1, 4 },
        { 1, 1, 1, 1, 1, 4 }
    };

    // copy one line of frames array to hatch states
    memcpy(h_state, frames[AnimationFrame], sizeof(frames[AnimationFrame]));

    AnimationFrame = ++AnimationFrame % 15;
    CurrentHatch = 1 + AnimationFrame % 5;
}

// ---------------------------------------------------------------------------
void SecondRoundRotating() {

    for (int i = 0; i < 6; i++) {
        h_state[i] = 2;
    }

    switch (AnimationFrame++ % 2) {
    case 0:
        h_state[CurrentHatch] = 4;
        h_state[(CurrentHatch + 3) % 6] = 4;
        break;
    case 1:
        h_state[CurrentHatch] = 3;
        h_state[(CurrentHatch + 3) % 6] = 3;
        CurrentHatch++ ;
        break;
    default:
        AnimationFrame = 0;
        break;
    }
    CurrentHatch = CurrentHatch % 6;
}

// ---------------------------------------------------------------------------
void ThirdRoundRotating() {
    for (int i = 0; i < 6; i++) {
        h_state[i] = 2;
    }

    switch (AnimationFrame++ % 2) {
    case 0:
        h_state[CurrentHatch] = 4;
        h_state[(CurrentHatch + 2) % 6] = 4;
        h_state[(CurrentHatch + 4) % 6] = 4;
        break;
    case 1:
        h_state[CurrentHatch] = 3;
        h_state[(CurrentHatch + 2) % 6] = 3;
        h_state[(CurrentHatch + 4) % 6] = 3;
        CurrentHatch++ ;
        break;
    }
    CurrentHatch = CurrentHatch % 6;
}

// ---------------------------------------------------------------------------
void FourthRoundRotating() {

    for (int i = 0; i < 6; i++) {
        h_state[i] = 2;
    }

    switch (AnimationFrame++ % 2) {
    case 0:
        h_state[CurrentHatch] = 4;
        h_state[(CurrentHatch + 1) % 6] = 4;
        h_state[(CurrentHatch + 3) % 6] = 4;
        h_state[(CurrentHatch + 4) % 6] = 4;
        break;
    case 1:
        h_state[CurrentHatch] = 3;
        h_state[(CurrentHatch + 1) % 6] = 3;
        h_state[(CurrentHatch + 3) % 6] = 3;
        h_state[(CurrentHatch + 4) % 6] = 3;
        CurrentHatch++ ;
        break;
    }
    CurrentHatch = CurrentHatch % 6;
}

// ---------------------------------------------------------------------------
void FifthRoundRotating() {

    for (int i = 0; i < 6; i++) {
        h_state[i] = 2;
    }

    switch (AnimationFrame++ % 2) {
    case 0:
        h_state[CurrentHatch] = 4;
        h_state[(CurrentHatch + 1) % 6] = 4;
        h_state[(CurrentHatch + 2) % 6] = 4;
        h_state[(CurrentHatch + 3) % 6] = 4;
        h_state[(CurrentHatch + 4) % 6] = 4;
        break;
    case 1:
        h_state[CurrentHatch] = 3;
        h_state[(CurrentHatch + 1) % 6] = 3;
        h_state[(CurrentHatch + 2) % 6] = 3;
        h_state[(CurrentHatch + 3) % 6] = 3;
        h_state[(CurrentHatch + 4) % 6] = 3;
        CurrentHatch++ ;
        break;
    default:
        AnimationFrame = 0;
        break;
    }
    CurrentHatch = CurrentHatch % 6;
}

// ---------------------------------------------------------------------------
void choosingplayer() {
    h_state[chooseplayer] = 4;
    MechanizmSetHatchesStates();
}

// ---------------------------------------------------------------------------
void before_spin_lights() {
    for (int i = 0; i < 6; i++) {
        h_state[i] = 4;
    }
    MechanizmSetHatchesStates();
}

// ---------------------------------------------------------------------------
void after_spin_lights() {
    for (int i = 0; i < 6; i++) {
        h_state[i] = 2;
    }
    h_state[CurrentHatch] = 4;
    h_state[chooseplayer] = 4;
    MechanizmSetHatchesStates();
}

// ---------------------------------------------------------------------------
void Proverka2() {
    h_state[chooseplayer] = 3;
    MechanizmSetHatchesStates();
    F->imgPlace->Picture->LoadFromFile("Data\\Place_red_zero.png");
}

// ---------------------------------------------------------------------------
void UpdateHatches() {
    if (F->FinalRoundOfGame > 0) {
        for (int i = 0; i < 6; i++) {
            h_state[i] = 1;
        }
    } else {
        for (int i = 0; i < 6; i++) {
            h_state[i] = 2;
        }
    }
    h_state[CurrentHatch] = 4;
    MechanizmSetHatchesStates();
}

// ---------------------------------------------------------------------------
void OpenHatches() {
    h_state[chooseplayer] = 0;
    MechanizmSetHatchesStates();
}

// ---------------------------------------------------------------------------
void SwitchesLights() {
    for (int i = 0; i < 6; i++) {
        h_state[i] = 5;
    }
    F->Wait = 0;

    switch (AnimationFrame) {
    case 0: {
            for (int i = 0; i < 5; i++) {
                if ((F->ingame[i]) && (CantFall != i)) {
                    h_state[i + 1] = 4;
                }
            }
        } break;
    case 1: {
            for (int i = 0; i < 5; i++) {
                if ((F->ingame[i]) && (CantFall != i)) {
                    h_state[i + 1] = 5;
                }
            }
        } break;
    default:
        AnimationFrame = 3;
    }
    // AnimationFrame = ++AnimationFrame % 2;
}

void OpenRndHatches() // открытие люков
{
    for (int i = 0; i < 6; i++)
        if (opened_now[i] == 1) {
            h_state[i] = 0;
            chooseplayer = i;
        }
    MechanizmSetHatchesStates();
}
