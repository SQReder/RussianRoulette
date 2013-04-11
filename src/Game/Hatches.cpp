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
const array<const String, COUNT_HATCHES> hatchFilenames = {
	"Data\\Black.png",
	"Data\\Base.png",
	"Data\\Blue.png",
	"Data\\Red.png",
	"Data\\White.png",
};

#include "Hatches.h"
#include "GameLogic.h"
#pragma package(smart_init)

using Graphics::TPicture;
array<TPicture*, COUNT_HATCHES> ptrHatch; // указатели на изображения люков на форме
map<LightColorsEnum, shared_ptr<TPicture> > h_state_img; // изображения состояний люков
array<HatchLightState, COUNT_HATCHES> h_state; // текущее состояние люков
int AnimationFrame; // определяет порядок анимации

// from MainForm.cpp
extern array<bool, COUNT_HATCHES> opened_now;
extern int CantFall;
extern int chooseplayer;

// ---------------------------------------------------------------------------
inline void AssignHatchImage(int index, HatchLightState state) { // банальное копирование изображения состояния на форму
	ptrHatch.at(index)->Assign(h_state_img[state].get());
}

// ---------------------------------------------------------------------------
// приведение изображений на форме в соответствие с состояниями люков
void MechanizmSetHatchesStates(array<HatchLightState, COUNT_HATCHES>& states) {
	for (int i = 0; i < COUNT_HATCHES; i++) {
		AssignHatchImage(i, states[i]);
	}
}

// ---------------------------------------------------------------------------
void ShiftHatches() {
	HatchLightState tmp = h_state[5]; // проворот барабана осуществляется
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
	for (int i = 0; i < COUNT_HATCHES; i++) {
		h_state[i] = lcBase; // люки изначально закрыты
	}

	ptrHatch[0] = F->imgHatch0->Picture; // установка ссылок на изображения на форме
	ptrHatch[1] = F->imgHatch1->Picture;
	ptrHatch[2] = F->imgHatch2->Picture;
	ptrHatch[3] = F->imgHatch3->Picture;
	ptrHatch[4] = F->imgHatch4->Picture;
	ptrHatch[5] = F->imgHatch5->Picture;

	MechanizmSetHatchesStates(h_state);
}

// ---------------------------------------------------------------------------
inline void LoadHatchStateImages() {
	for (int i = 0; i < COUNT_HATCHES; i++) { // конструктор изображений состояний люков
		h_state_img[LightColorsEnum(i)] = shared_ptr<TPicture>(new TPicture());
	}

	h_state_img[lcBlack]->LoadFromFile(hatchFilenames[0]);
	h_state_img[lcBase]->LoadFromFile(hatchFilenames[1]);
	h_state_img[lcBlue]->LoadFromFile(hatchFilenames[2]);
	h_state_img[lcRed]->LoadFromFile(hatchFilenames[3]);
	h_state_img[lcWhite]->LoadFromFile(hatchFilenames[4]);
}

// ---------------------------------------------------------------------------
void OpenRandomHatches(const int OpenHatches, int ModeOfGame) {
	assert(OpenHatches <= COUNT_HATCHES);

	// F->RndHatch = 0;
	for (int i = 0; i < COUNT_HATCHES; i++) {
		opened_now[i] = false;
	} // закрываем открытые люки,

	do {
		opened_now[random(COUNT_HATCHES)] = true; // и открываем случайный пока не откроем

		if (CantFall != -1) {
			opened_now[CantFall + 1] = false;
		} // и спасаем игрока же! ^_^"

		// закрываем люки, которые не могут открываться
		for (int i = 0; i < COUNT_PLAYERS; i++) { // те, что уже не в игре
			if (!F->isPlayerInGame[i] && ModeOfGame == 8) {
				opened_now[i + 1] = false;
			}
		}

		// закрываем люк ведущего, если не финал еще или миниигра.
		if (F->FinalRoundOfGame < 1) { /* && (F->GameMode != minigame) */
			opened_now[0] = false;
		}

	}
	while // нужное нам количество
		(count(opened_now.begin(), opened_now.end(), true) < int(OpenHatches));

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
    for (int i = 0; i < COUNT_HATCHES; i++) {
        h_state[i] = lcBase;
    }
    int blah = random(COUNT_HATCHES);
    h_state[blah] = lcWhite;
    CurrentHatch = blah;
}

// ---------------------------------------------------------------------------
void FirstRoundRotating() {
	for (int i = 0; i < COUNT_HATCHES; i++) {
		h_state[i] = lcBlue;
    }

    switch (AnimationFrame++ % 2) {
	case 0: h_state[CurrentHatch] = lcWhite;
		break;
	case 1: h_state[CurrentHatch] = lcRed;
		CurrentHatch++ ;
		break;
    default: AnimationFrame = 0;
        break;
    }
    CurrentHatch = CurrentHatch % COUNT_HATCHES;
}

// ---------------------------------------------------------------------------
void ZeroRoundSpin() {
	static array<array<HatchLightState, COUNT_HATCHES>, 15> framez = {{
		{ lcBase,  lcWhite, lcBase,  lcBase,  lcBase,  lcBase  },
		{ lcBase,  lcWhite, lcBase,  lcBase,  lcBase,  lcBase  },
		{ lcBase,  lcWhite, lcWhite, lcBase,  lcBase,  lcBase  },
		{ lcWhite, lcWhite, lcWhite, lcBase,  lcBase,  lcBase  },
		{ lcWhite, lcWhite, lcWhite, lcWhite, lcBase,  lcBase  },
		{ lcWhite, lcWhite, lcWhite, lcWhite, lcBase,  lcBase  },
		{ lcWhite, lcBase,  lcWhite, lcWhite, lcWhite, lcBase  },
		{ lcWhite, lcBase,  lcWhite, lcWhite, lcWhite, lcBase  },
		{ lcBase,  lcBase,  lcBase,  lcWhite, lcWhite, lcWhite },
		{ lcBase,  lcBase,  lcBase,  lcWhite, lcWhite, lcWhite },
		{ lcBase,  lcBase,  lcBase,  lcBase,  lcWhite, lcWhite },
		{ lcBase,  lcBase,  lcBase,  lcBase,  lcWhite, lcWhite },
		{ lcBase,  lcBase,  lcBase,  lcBase,  lcBase,  lcWhite },
		{ lcBase,  lcBase,  lcBase,  lcBase,  lcBase,  lcWhite },
		{ lcBase,  lcBase,  lcBase,  lcBase,  lcBase,  lcWhite }
	}};

	// copy one line of frames array to ptrHatch states
	h_state.swap(framez[AnimationFrame]);

    AnimationFrame = ++AnimationFrame % 15;
    CurrentHatch = 1 + AnimationFrame % 5;
}

// ---------------------------------------------------------------------------
void SecondRoundRotating() {

	for (int i = 0; i < COUNT_HATCHES; i++) {
        h_state[i] = lcBlue;
    }

    switch (AnimationFrame++ % 2) {
    case 0:
        h_state[CurrentHatch] = lcWhite;
		h_state[(CurrentHatch + 3) % COUNT_HATCHES] = lcWhite;
		break;
	case 1:
		h_state[CurrentHatch] = lcRed;
		h_state[(CurrentHatch + 3) % COUNT_HATCHES] = lcRed;
		CurrentHatch++ ;
		break;
	default:
		assert(false);
		AnimationFrame = 0;
		break;
	}
    CurrentHatch = CurrentHatch % COUNT_HATCHES;
}

// ---------------------------------------------------------------------------
void ThirdRoundRotating() {
	for (int i = 0; i < COUNT_HATCHES; i++) {
        h_state[i] = lcBlue;
    }

    switch (AnimationFrame++ % 2) {
    case 0:
        h_state[CurrentHatch] = lcWhite;
        h_state[(CurrentHatch + 2) % COUNT_HATCHES] = lcWhite;
        h_state[(CurrentHatch + 4) % COUNT_HATCHES] = lcWhite;
        break;
    case 1:
        h_state[CurrentHatch] = lcRed;
        h_state[(CurrentHatch + 2) % COUNT_HATCHES] = lcRed;
        h_state[(CurrentHatch + 4) % COUNT_HATCHES] = lcRed;
        CurrentHatch++ ;
        break;
    }
    CurrentHatch = CurrentHatch % COUNT_HATCHES;
}

// ---------------------------------------------------------------------------
void FourthRoundRotating() {

	for (int i = 0; i < COUNT_HATCHES; i++) {
        h_state[i] = lcBlue;
    }

    switch (AnimationFrame++ % 2) {
    case 0:
        h_state[CurrentHatch] = lcWhite;
        h_state[(CurrentHatch + 1) % COUNT_HATCHES] = lcWhite;
        h_state[(CurrentHatch + 3) % COUNT_HATCHES] = lcWhite;
        h_state[(CurrentHatch + 4) % COUNT_HATCHES] = lcWhite;
        break;
    case 1:
        h_state[CurrentHatch] = lcRed;
        h_state[(CurrentHatch + 1) % COUNT_HATCHES] = lcRed;
        h_state[(CurrentHatch + 3) % COUNT_HATCHES] = lcRed;
        h_state[(CurrentHatch + 4) % COUNT_HATCHES] = lcRed;
        CurrentHatch++ ;
        break;
    }
    CurrentHatch = CurrentHatch % COUNT_HATCHES;
}

// ---------------------------------------------------------------------------
void FifthRoundRotating() {

	for (int i = 0; i < COUNT_HATCHES; i++) {
        h_state[i] = lcBlue;
    }

    switch (AnimationFrame++ % 2) {
    case 0:
        h_state[CurrentHatch] = lcWhite;
        h_state[(CurrentHatch + 1) % COUNT_HATCHES] = lcWhite;
        h_state[(CurrentHatch + 2) % COUNT_HATCHES] = lcWhite;
        h_state[(CurrentHatch + 3) % COUNT_HATCHES] = lcWhite;
        h_state[(CurrentHatch + 4) % COUNT_HATCHES] = lcWhite;
        break;
    case 1:
        h_state[CurrentHatch] = lcRed;
        h_state[(CurrentHatch + 1) % COUNT_HATCHES] = lcRed;
        h_state[(CurrentHatch + 2) % COUNT_HATCHES] = lcRed;
        h_state[(CurrentHatch + 3) % COUNT_HATCHES] = lcRed;
        h_state[(CurrentHatch + 4) % COUNT_HATCHES] = lcRed;
        CurrentHatch++ ;
        break;
    default:
        AnimationFrame = 0;
        break;
    }
    CurrentHatch = CurrentHatch % COUNT_HATCHES;
}

// ---------------------------------------------------------------------------
void LightAllHatchesWith(HatchLightState light) {
	for (int i = 0; i < COUNT_HATCHES; i++) {
		h_state[i] = light;
	}
	MechanizmSetHatchesStates(h_state);
}

// ---------------------------------------------------------------------------
void ChangeHatchesLight(HatchLightState exclude, HatchLightState to) {
	for (int i = 0; i < COUNT_HATCHES; i++) {
		if (h_state[i] != exclude) {
			h_state[i] = to;
		}
	}
	MechanizmSetHatchesStates(h_state);
}

// ---------------------------------------------------------------------------
void choosingplayer() {
    h_state[chooseplayer] = lcWhite;
	MechanizmSetHatchesStates(h_state);
}

// ---------------------------------------------------------------------------
void before_spin_lights() {
	for (int i = 0; i < COUNT_HATCHES; i++) {
        h_state[i] = lcWhite;
    }
    MechanizmSetHatchesStates(h_state);
}

// ---------------------------------------------------------------------------
void after_spin_lights() {
	for (int i = 0; i < COUNT_HATCHES; i++) {
        h_state[i] = lcBlue;
    }
    h_state[CurrentHatch] = lcWhite;
    h_state[chooseplayer] = lcWhite;
    MechanizmSetHatchesStates(h_state);
}

// ---------------------------------------------------------------------------
void Proverka2() {
    h_state[chooseplayer] = lcRed;
    MechanizmSetHatchesStates(h_state);
    F->imgPlace->Picture->LoadFromFile("Data\\Place_red_zero.png");
}

// ---------------------------------------------------------------------------
void UpdateHatches() {
    if (F->FinalRoundOfGame > 0) {
		for (int i = 0; i < COUNT_HATCHES; i++) {
            h_state[i] = lcBase;
        }
    } else {
		for (int i = 0; i < COUNT_HATCHES; i++) {
            h_state[i] = lcBlue;
        }
    }
    h_state[CurrentHatch] = lcWhite;
	MechanizmSetHatchesStates(h_state);
}

// ---------------------------------------------------------------------------
void OpenHatchNow(int hatchToOpen) {
    h_state[hatchToOpen] = lcBlack;
	MechanizmSetHatchesStates(h_state);
}

// ---------------------------------------------------------------------------
void SwitchesLights() {
	for (int i = 0; i < COUNT_HATCHES; i++) {
        h_state[i] = lcBase;
    }

    switch (AnimationFrame) {
    case 0: {
			for (int i = 0; i < COUNT_PLAYERS; i++) {
                if ((F->isPlayerInGame[i]) && (CantFall != int(i))) {
                    h_state[i + 1] = lcWhite;
                }
            }
        } break;
    case 1: {
			for (int i = 0; i < COUNT_PLAYERS; i++) {
				if ((F->isPlayerInGame[i]) && (CantFall != int(i))) {
                    h_state[i + 1] = lcBase;
                }
            }
        } break;
    default: ;
    }
    AnimationFrame = ++AnimationFrame % 2;
}

void OpenHatches() // открытие люков
{
	for (int i = 0; i < COUNT_HATCHES; i++)
        if (opened_now[i] == true) {
            h_state[i] = lcBlack;
            chooseplayer = i;
        }
	MechanizmSetHatchesStates(h_state);
}

void DoSpin(const RoundEnum round) {
	switch(round) {
		case Zero:
			ZeroRoundSpin();
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
	MechanizmSetHatchesStates(h_state);
}
