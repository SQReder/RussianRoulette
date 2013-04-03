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
const array<const String, 6> hatchFilenames = {
	"Data\\Black.png",
	"Data\\Base.png",
	"Data\\Blue.png",
	"Data\\Red.png",
	"Data\\White.png",
	"Data\\Base.png",
};

#include "Hatches.h"
#include "GameLogic.h"
#pragma package(smart_init)

using Graphics::TPicture;
array<TPicture*, 6> hatch; // указатели на изображения люков на форме
array<shared_ptr<TPicture>, 6> h_state_img; // изображения состояний люков
array<int, 6> h_state; // текущее состояние люков
int AnimationFrame; // определяет порядок анимации

// from MainForm.cpp
extern int opened_now[6];
extern int CantFall;
extern int chooseplayer;

// ---------------------------------------------------------------------------
inline void LoadHatchImage(int index, int state) { // банальное копирование изображения состояния на форму
	hatch[index]->Assign(h_state_img[state].get());
}

// ---------------------------------------------------------------------------
// приведение изображений на форме в соответствие с состояниями люков
void MechanizmSetHatchesStates(array<int, 6>& states) {
	for (int i = 0; i < 6; i++) {
        LoadHatchImage(i, states[i]);
    }
}

// ---------------------------------------------------------------------------
void ShiftHatches() {
	char tmp = h_state[5]; // проворот барабана осуществляется
	h_state[5] = h_state[4]; // простым сдвигом массива на 1 элемент.
	h_state[4] = h_state[3]; // по своей сути это shr(h_state[]);
	h_state[3] = h_state[2];
	h_state[2] = h_state[1];
	h_state[1] = h_state[0];
	h_state[0] = tmp;

	MechanizmSetHatchesStates(h_state);
};

// ---------------------------------------------------------------------------
inline void InitializeHatches() {
    for (int i = 0; i < 6; i++) {
		h_state[i] = 1; // люки изначально закрыты
	}

	hatch[0] = F->imgHatch0->Picture; // установка ссылок на изображения на форме
    hatch[1] = F->imgHatch1->Picture;
    hatch[2] = F->imgHatch2->Picture;
    hatch[3] = F->imgHatch3->Picture;
    hatch[4] = F->imgHatch4->Picture;
	hatch[5] = F->imgHatch5->Picture;

	MechanizmSetHatchesStates(h_state);
}

// ---------------------------------------------------------------------------
inline void LoadHatchStateImages() {
    for (int i = 0; i < 6; i++) { // конструктор изображений состояний люков
		h_state_img[i] = shared_ptr<TPicture>(new TPicture());
		h_state_img[i]->LoadFromFile(hatchFilenames[i]);
	}
}

// ---------------------------------------------------------------------------
void OpenRandomHatches(const int OpenHatches, int ModeOfGame) {
    assert(OpenHatches <= 6);

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
            if (!F->isPlayerInGame[i] && ModeOfGame == 8) {
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
	MechanizmSetHatchesStates(h_state);
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
    case 0: h_state[CurrentHatch] = 4;
        break;
    case 1: h_state[CurrentHatch] = 3;
        CurrentHatch++ ;
        break;
    default: AnimationFrame = 0;
        break;
    }
    CurrentHatch = CurrentHatch % 6;
}

// ---------------------------------------------------------------------------
void LightHatchesW(int bright, int light) {
    // если 255 то заливаем все вторым цветом
    if (bright == LIGHT_ALL_HATCHES_BLUE)
        for (int i = 0; i < 6; i++) {
            h_state[i] = light;
        } else
        for (int i = 0; i < 6; i++) {
            if (h_state[i] != light) {
                h_state[i] = bright;
            }
		}
	MechanizmSetHatchesStates(h_state);
}

// ---------------------------------------------------------------------------
void ZeroRoundSpin() {
	static array<array<int, 6>, 15> framez = {{
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
	}};

	// copy one line of frames array to hatch states
	h_state.swap(framez[AnimationFrame]);

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
        assert(false);
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
	MechanizmSetHatchesStates(h_state);
}

// ---------------------------------------------------------------------------
void before_spin_lights() {
    for (int i = 0; i < 6; i++) {
        h_state[i] = 4;
    }
    MechanizmSetHatchesStates(h_state);
}

// ---------------------------------------------------------------------------
void after_spin_lights() {
    for (int i = 0; i < 6; i++) {
        h_state[i] = 2;
    }
    h_state[CurrentHatch] = 4;
    h_state[chooseplayer] = 4;
    MechanizmSetHatchesStates(h_state);
}

// ---------------------------------------------------------------------------
void Proverka2() {
    h_state[chooseplayer] = 3;
    MechanizmSetHatchesStates(h_state);
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
	MechanizmSetHatchesStates(h_state);
}

// ---------------------------------------------------------------------------
void OpenHatches() {
    h_state[chooseplayer] = 0;
	MechanizmSetHatchesStates(h_state);
}

// ---------------------------------------------------------------------------
void SwitchesLights() {
    for (int i = 0; i < 6; i++) {
        h_state[i] = 5;
    }

    switch (AnimationFrame) {
    case 0: {
            for (int i = 0; i < 5; i++) {
                if ((F->isPlayerInGame[i]) && (CantFall != i)) {
                    h_state[i + 1] = 4;
                }
            }
        } break;
    case 1: {
            for (int i = 0; i < 5; i++) {
                if ((F->isPlayerInGame[i]) && (CantFall != i)) {
                    h_state[i + 1] = 5;
                }
            }
        } break;
    default: ;
    }
    AnimationFrame = ++AnimationFrame % 2;
}

void OpenRndHatches() // открытие люков
{
    for (int i = 0; i < 6; i++)
        if (opened_now[i] == 1) {
            h_state[i] = 0;
            chooseplayer = i;
        }
    MechanizmSetHatchesStates(h_state);
}

void DoSpin(const RoundEnum round) {
	switch(round) {
		case Zero:
			ZeroRoundRotating();
			break;
		case First:
			ZeroRoundRotating();
			break;
		case Second:
			SecondRoundRotating();
			break;
		case Third:
			ThirdRoundRotating();
			break;
		case Fourth:
			FourthRoundRotating();
			break;
		case Final:
			FifthRoundRotating();
			break;
	}
}
