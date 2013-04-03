#ifndef GfxCacheH
#define GfxCacheH
#include "pch.h"

// ---------------------------------------------------------------------------
class sGfxCache {
public:
    sGfxCache();
    ~sGfxCache();

    int PulseFramesCount;
    vector<shared_ptr<TPicture> > PulseFrames_;

	TPicture *PulseFrames[56];

	TPicture *Tick[21];
    TPicture *Liver[16];

    TPicture *Place;
	TPicture *PlaceRedZero;
	TPicture *PlaceRedMechActive;

    TPicture *rr_quest;
    TPicture *quest_correct;
    TPicture *quest_incorrect;

    // one moar for 1..4
    TPicture *Splash[5];
    TPicture *FinalSplash;
    TPicture *Menu_bg;
};

extern sGfxCache *gfx;
#endif
