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
TPicture* hatch[6]; // ��������� �� ����������� ����� �� �����
TPicture* h_state_img[6]; // ����������� ��������� �����
int h_state[6]; // ������� ��������� �����
int AnimationFrame; // ���������� ������� ��������

// ---------------------------------------------------------------------------
void ShiftHatches() {
    char tmp = h_state[5]; // �������� �������� ��������������
    h_state[5] = h_state[4]; // ������� ������� ������� �� 1 �������.
    h_state[4] = h_state[3]; // �� ����� ���� ��� shr(h_state[]);
    h_state[3] = h_state[2];
    h_state[2] = h_state[1];
    h_state[1] = h_state[0];
    h_state[0] = tmp;
};

// ---------------------------------------------------------------------------
inline void InitializeHatches() {
    for (int i = 0; i < 6; i++) {
        hatch[i] = new TPicture; // ������������ ����������� �����
        h_state[i] = 1; // � �������� ��
    }

    hatch[0] = F->imgHatch0->Picture; // ��������� ������ �� ����������� �� �����
    hatch[1] = F->imgHatch1->Picture;
    hatch[2] = F->imgHatch2->Picture;
    hatch[3] = F->imgHatch3->Picture;
    hatch[4] = F->imgHatch4->Picture;
    hatch[5] = F->imgHatch5->Picture;
}

// ---------------------------------------------------------------------------
inline void LoadHatchStateImages() {
    for (int i = 0; i < 6; i++) { // ����������� ����������� ��������� �����
        h_state_img[i] = new TPicture;
    }

    h_state_img[0]->LoadFromFile(imgBlackHatch); // � ��������� �� ������ �� �����
    h_state_img[1]->LoadFromFile(imgBaseHatch); // �������� �������� �������
    h_state_img[2]->LoadFromFile(imgBlueHatch); // � ������ ������
    h_state_img[3]->LoadFromFile(imgRedHatch);
    h_state_img[4]->LoadFromFile(imgWhiteHatch);
    h_state_img[5]->LoadFromFile(imgGreyHatch);
}

// ---------------------------------------------------------------------------
inline void LoadHatchImage(int index, int state) { // ��������� ����������� ����������� ��������� �� �����
    hatch[index]->Assign(h_state_img[state]);
}

// ---------------------------------------------------------------------------
void MechanizmSetHatchesStates() { // ���������� ����������� �� ����� � ������������ � ����������� �����
    for (int i = 0; i < 6; i++) {
        LoadHatchImage(i, h_state[i]);
    }
}

// ---------------------------------------------------------------------------
void OpenRandomHatches(const unsigned char OpenHatches) {
    if (OpenHatches > 6) {
        ShowMessage("� ����� ��� ����� ����� ���������?!");
        exit(1);
    }

    F->RndHatch = 0;
    for (int i = 0; i < 6; i++) {
        F->opened_now[i] = 0;
    } // ��������� �������� ����,

    do {
        F->opened_now[random(6)] = 1; // � ��������� ��������� ���� �� �������

        if (F->CantFall != -1) {
            F->opened_now[F->CantFall + 1] = 0;
        } // � ������� ������ ��! ^_^"

        // ��������� ����, ������� �� ����� �����������
        for (int i = 0; i < 5; i++) { // ��, ��� ��� �� � ����
            if (!F->ingame[i] && F->ModeOfGame == 8) {
                F->opened_now[i + 1] = 0;
            }
        }

        // ��������� ��� ��������, ���� �� ����� ��� ��� ��������.
        if (F->FinalRoundOfGame < 1) { /* && (F->GameMode != minigame) */
            F->opened_now[0] = 0;
        }

    }
    while // ������ ��� ����������
        (F->opened_now[0] + F->opened_now[1] + F->opened_now[2] + F->opened_now[3] + F->opened_now[4] +
        F->opened_now[5] < OpenHatches);

}

// ---------------------------------------------------------------------------
void Hatches() { // ������������� ���������
    randomize();
    InitializeHatches();
    LoadHatchStateImages();
    MechanizmSetHatchesStates();

};

// ---------------------------------------------------------------------------
// �� ����� ��� ��������� �������� ���������� ������ � ������ ������
// ���-�� ��� ��������?!
void ZeroRoundRotating() // ��������� ��� �������� ������
{ // ���� ��� ��������� �����
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
    // ���� 255 �� �������� ��� ������ ������
    if (bright == 255)
        for (int i = 0; i < 6; i++) {
            h_state[i] = light;
        }
    else
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
    h_state[F->chooseplayer] = 4;
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
    h_state[F->chooseplayer] = 4;
    MechanizmSetHatchesStates();
}

// ---------------------------------------------------------------------------
void Proverka2() {
    h_state[F->chooseplayer] = 3;
    MechanizmSetHatchesStates();
    F->imgPlace->Picture->LoadFromFile("Data\\Place_red_zero.png");
}

// ---------------------------------------------------------------------------
void UpdateHatches() {
    if (F->FinalRoundOfGame > 0) {
        for (int i = 0; i < 6; i++) {
            h_state[i] = 1;
        }
    }
    else {
        for (int i = 0; i < 6; i++) {
            h_state[i] = 2;
        }
    }
    h_state[CurrentHatch] = 4;
    MechanizmSetHatchesStates();
}

// ---------------------------------------------------------------------------
void OpenHatches() {
    h_state[F->chooseplayer] = 0;
    MechanizmSetHatchesStates();
}

// ---------------------------------------------------------------------------
void SwitchesLights() {
    for (int i = 0; i < 6; i++) {
        h_state[i] = 5;
    }
    F->Wait = 0;

    // for (int i = 0; i < 5; i++) {
    // if ((F->ingame[i]) && (F->CantFall != i)) {
    // h_state[i + 1] = 4 + AnimationFrame;
    // }
    // }

    switch (AnimationFrame) {
    case 0: {
            for (int i = 0; i < 5; i++) {
                if ((F->ingame[i]) && (F->CantFall != i)) {
                    h_state[i + 1] = 4;
                }
            }
        } break;
    case 1: {
            for (int i = 0; i < 5; i++) {
                if ((F->ingame[i]) && (F->CantFall != i)) {
                    h_state[i + 1] = 5;
                }
            }
        } break;
    default:
        AnimationFrame = 3;
    }
    // AnimationFrame = ++AnimationFrame % 2;
}

void OpenRndHatches() // �������� �����
{
    for (int i = 0; i < 6; i++)
        if (F->opened_now[i] == 1) {
            h_state[i] = 0;
            F->chooseplayer = i;
        }
    MechanizmSetHatchesStates();
}
