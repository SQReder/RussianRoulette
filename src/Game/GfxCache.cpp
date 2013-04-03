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
#include "GfxCache.h"
#pragma package(smart_init)

GfxCache::GfxCache() {
	for (size_t i = 0; i < PulseFramesCount; i++) {
		shared_ptr<TPicture> tmp(new TPicture());
		tmp->LoadFromFile("data\\pulse\\pulse_" + Trim(IntToStr(static_cast<int>(i) + 1)) + ".png");
		PulseFrames.at(i) = tmp;
	}

	for (size_t i = 0; i < TickFramesCount; ++i) {
		shared_ptr<TPicture> tmp(new TPicture());
		tmp->LoadFromFile("data\\" + Trim(IntToStr(static_cast<int>(i))) + "sec.png");
		TickFrames.at(i) = tmp;
	}

	for (size_t i = 0; i < LiverFramesCount; ++i) {
		shared_ptr<TPicture> tmp(new TPicture());
		tmp->LoadFromFile("Data\\рычаг_" + Trim(IntToStr(static_cast<int>(i))) + ".png");
		LiverFrames.at(i) = tmp;
    }

    for (int i = 1; i < 5; ++i) {
		shared_ptr<TPicture> tmp(new TPicture());
		tmp->LoadFromFile("Data\\splash-" + IntToStr(i) + ".png");
        Splashes.at(i) = tmp;
    }

	Place = shared_ptr<TPicture>(new TPicture());
	rr_quest = shared_ptr<TPicture>(new TPicture());
	PlaceRedZero = shared_ptr<TPicture>(new TPicture());
	PlaceRedMechActive = shared_ptr<TPicture>(new TPicture());
	quest_correct = shared_ptr<TPicture>(new TPicture());
	quest_incorrect = shared_ptr<TPicture>(new TPicture());
	FinalSplash = shared_ptr<TPicture>(new TPicture());
	Menu_bg = shared_ptr<TPicture>(new TPicture());

	Place->LoadFromFile("data\\place.png");
	rr_quest->LoadFromFile("data\\rr_quest.png");
	PlaceRedZero->LoadFromFile("Data\\Place_red_zero.png");
	PlaceRedMechActive->LoadFromFile("Data\\Place_red_zero2.png");
	quest_correct->LoadFromFile("Data\\quest_correct.png");
	quest_incorrect->LoadFromFile("Data\\quest_incorrect.png");
	FinalSplash->LoadFromFile("Data\\Final.png");
	Menu_bg->LoadFromFile("Data\\menu_bg.jpg");
}

TPicture *GfxCache::GetPulseFrame(size_t index) const
{ return PulseFrames.at(index).get(); }

TPicture *GfxCache::GetTickFrame(size_t index) const
{ return TickFrames.at(index).get(); }

TPicture *GfxCache::GetLiverFrame(size_t index) const
{ return LiverFrames.at(index).get(); }

TPicture *GfxCache::GetSplash(size_t index) const
{ return Splashes.at(index).get(); }

const shared_ptr<GfxCache> GfxCache::Instance() {
	static shared_ptr<GfxCache> instance(new GfxCache());
	return instance;
}
