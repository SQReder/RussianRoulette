#ifndef GfxCacheH
#define GfxCacheH
#include "pch.h"

// ---------------------------------------------------------------------------
class GfxCache {
public:
	static const shared_ptr<GfxCache> Instance();

	static const size_t PulseFramesCount = 56;
	static const size_t TickFramesCount = 21;
	static const size_t LiverFramesCount = 16;

	// one moar for 1..4
	static const size_t SplashesCount = 5;

	shared_ptr<TPicture> Place;
	shared_ptr<TPicture> PlaceRedZero;
	shared_ptr<TPicture> PlaceRedMechActive;

	shared_ptr<TPicture> rr_quest;
	shared_ptr<TPicture> quest_correct;
	shared_ptr<TPicture> quest_incorrect;

	shared_ptr<TPicture> FinalSplash;
	shared_ptr<TPicture> Menu_bg;

	TPicture *GetPulseFrame(size_t index) const;
	TPicture *GetTickFrame(size_t index) const;
	TPicture *GetLiverFrame(size_t index) const;
	TPicture *GetSplash(size_t index) const;
private:
	GfxCache();
	GfxCache(const GfxCache& root);
	GfxCache& operator=(const GfxCache&);

	array<shared_ptr<TPicture>, PulseFramesCount> PulseFrames;
	array<shared_ptr<TPicture>, TickFramesCount> TickFrames;
	array<shared_ptr<TPicture>, LiverFramesCount> LiverFrames;
	array<shared_ptr<TPicture>, SplashesCount> Splashes;
};
#endif
