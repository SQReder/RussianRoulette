// ---------------------------------------------------------------------------
#include "alloc.h"
#pragma hdrstop

#include "uAnimate.h"
#include "MainForm.h"
#define FramesCount 56

TPicture* nya[FramesCount];
int frame;

Graphics::TPicture* pulse_pic;

// ---------------------------------------------------------------------------

#pragma package(smart_init)

void Initialize() {
    for (int i = 0; i < FramesCount; i++) {
        nya[i] = new TPicture;
        nya[i]->LoadFromFile("data\\pulse\\pulse_" + Trim(IntToStr(i + 1)) + ".png");
    }

    pulse_pic = new TPicture;

    frame = 0;
}

// ---------------------------------------------------------------------------
void NextFrame() {
    F->imgPulse->Picture->Assign(nya[frame]);
    if (frame < FramesCount - 1)
        frame++ ;
    else
        frame = 0;
}
