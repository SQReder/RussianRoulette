#ifndef GfxCacheH
#define GfxCacheH
#include <Graphics.hpp>

// ---------------------------------------------------------------------------
class sGfxCache {
public:
    sGfxCache();
    ~sGfxCache();

    int PulseFramesCount;
    TPicture** PulseFrames;

    TPicture* Tick[21];
    TPicture* Liver[16];

    TPicture* Place;
    TPicture* PlaceRedZero;

    TPicture* rr_quest;
    TPicture* quest_correct;
    TPicture* quest_incorrect;

    // one moar for 1..4
    TPicture* Splash[5];
    TPicture* FinalSplash;

    TPicture* h_state_img[6]; // изображения состояний люков
};

extern sGfxCache* gfx;
#endif
