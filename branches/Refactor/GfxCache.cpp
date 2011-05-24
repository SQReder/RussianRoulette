// ---------------------------------------------------------------------------
#pragma hdrstop
#include "GfxCache.h"
#pragma package(smart_init)

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
        Splash[i]->LoadFromFile("Data\\splash-" + IntToStr(1) + ".png");
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
}
