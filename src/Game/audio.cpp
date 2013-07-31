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

#include "bass\bass.h"
#pragma hdrstop
#pragma comment(lib,"bass\bassbcb.lib")
#pragma package(smart_init)

#include "audio.h"
#include "pch.h"

const String extention = ".ogg";
const String sounds_path = ".\\sounds\\";

class Sound {
public:
    Sound(String filename) {
        mem = shared_ptr<TMemoryStream>(new TMemoryStream());
        mem->LoadFromFile(sounds_path + filename + extention);
        stream = BASS_StreamCreateFile(1, mem->Memory, 0, mem->Size, 0);
    }

    ~Sound() {
        BASS_StreamFree(stream);
    }

	void Play() { BASS_ChannelPlay(stream, 1); }

	void PlayWithPos(int seconds) {
		BASS_ChannelSetPosition(stream, BASS_ChannelSeconds2Bytes(stream, seconds), BASS_POS_BYTE);
		BASS_ChannelPlay(stream, 0);
	}

	void Stop() { BASS_ChannelStop(stream); }

	void SetVolume(float volume) { BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, volume); }

private:
	HSTREAM stream;
	shared_ptr<TMemoryStream> mem;
};

// ---------------------------------------------------------------------------
map <rrSoundEvent, shared_ptr <Sound> > bg_event_map;
map <rrSoundEvent, shared_ptr <Sound> > snd_event_map;

#define ADD_BG_FILE_TO_MAP(X) bg_event_map[X] = shared_ptr <Sound> (new Sound(#X))
#define ADD_SFX_FILE_TO_MAP(X) snd_event_map[X] = shared_ptr <Sound> (new Sound(#X))

void init_audio(HWND hwnd) {
	if (!BASS_Init(-1, 44100, 0, hwnd, NULL)) {
		__asm INT 3;
	}

	ADD_BG_FILE_TO_MAP(question_clear);
	ADD_BG_FILE_TO_MAP(rr_bg1);
	ADD_BG_FILE_TO_MAP(rr_bg2);
	ADD_BG_FILE_TO_MAP(rr_bg3);
	ADD_BG_FILE_TO_MAP(rr_bg4);
	ADD_BG_FILE_TO_MAP(rr_bg5);
	ADD_BG_FILE_TO_MAP(rr_question);
	//-------------------------------------
	ADD_SFX_FILE_TO_MAP(Next_Question);
	ADD_SFX_FILE_TO_MAP(rr_20sec);
	ADD_SFX_FILE_TO_MAP(rr_choosen);
	ADD_SFX_FILE_TO_MAP(rr_closing);
	ADD_SFX_FILE_TO_MAP(rr_endround);
	ADD_SFX_FILE_TO_MAP(rr_fall);
	ADD_SFX_FILE_TO_MAP(rr_fall_with_host);
	ADD_SFX_FILE_TO_MAP(rr_false);
	ADD_SFX_FILE_TO_MAP(rr_final);
	ADD_SFX_FILE_TO_MAP(rr_intro_Take_2);
	ADD_SFX_FILE_TO_MAP(rr_intro);
	ADD_SFX_FILE_TO_MAP(rr_mexclose);
	ADD_SFX_FILE_TO_MAP(rr_mexopen);
	ADD_SFX_FILE_TO_MAP(rr_money);
	ADD_SFX_FILE_TO_MAP(rr_nextq);
	ADD_SFX_FILE_TO_MAP(rr_notfall);
	ADD_SFX_FILE_TO_MAP(rr_openhole);
	ADD_SFX_FILE_TO_MAP(rr_openround);
	ADD_SFX_FILE_TO_MAP(rr_players);
	ADD_SFX_FILE_TO_MAP(rr_round);
	ADD_SFX_FILE_TO_MAP(rr_save);
	ADD_SFX_FILE_TO_MAP(rr_true);
}

void PlaySound(rrSoundEvent event, int startPosInSeconds) {
	switch (event) {
	case Next_Question: break;
	case question_clear: break;
    case rr_20sec:
		snd_event_map[rr_choosen]->Stop();
		bg_event_map[rr_question]->Stop();
        break;
    case rr_bg1: break;
    case rr_bg2: break;
    case rr_bg3: break;
    case rr_bg4: break;
    case rr_bg5: break;
    case rr_choosen:
		bg_event_map[rr_question]->Stop();
        break;
    case rr_closing:
    case rr_endround:
    case rr_mexopen:
        {
			bg_event_map[rr_bg1]->Stop();
			bg_event_map[rr_bg2]->Stop();
			bg_event_map[rr_bg3]->Stop();
			bg_event_map[rr_bg4]->Stop();
			bg_event_map[rr_bg5]->Stop();
		}
        break;
    case rr_fall:
		snd_event_map[rr_mexclose]->Stop();
        break;
    case rr_fall_with_host: break;
    case rr_false: break;
    case rr_final: break;
    case rr_intro_Take_2: break;
    case rr_intro: break;
    case rr_mexclose:
		snd_event_map[rr_mexopen]->Stop();
        break;
    case rr_money: break;
    case rr_nextq: break;
    case rr_notfall: break;
    case rr_openhole: break;
    case rr_openround: break;
    case rr_players: break;
    case rr_question:
        {
			bg_event_map[rr_bg1]->Stop();
			bg_event_map[rr_bg2]->Stop();
			bg_event_map[rr_bg3]->Stop();
			bg_event_map[rr_bg4]->Stop();
			bg_event_map[rr_bg5]->Stop();
			snd_event_map[rr_mexclose]->Stop();
        }
        break;
    case rr_round: break;
    case rr_save:
		snd_event_map[rr_mexclose]->Stop();
        break;
    case rr_true: break;
	}

	if (startPosInSeconds <= 0) {
		if (bg_event_map[event] != NULL) { bg_event_map[event]->Play(); }
		if (snd_event_map[event] != NULL) {	snd_event_map[event]->Play(); }
	}
	else {
		if (bg_event_map[event] != NULL) {
			bg_event_map[event]->PlayWithPos(startPosInSeconds);
		}
		if (snd_event_map[event] != NULL) {
			snd_event_map[event]->PlayWithPos(startPosInSeconds);
        }
    }
}

// алиасы для вызова PlaySound с указанием стартовой позиции в секундах и без
// воспроизведение музыки
void PlayMusic(rrSoundEvent event) { PlaySound(event, 0); }
void PlayMusic(rrSoundEvent event, int startPos) { PlaySound(event, startPos); }
// воспроизведение звука
void PlaySFX(rrSoundEvent event) { PlaySound(event, 0); }
void PlaySFX(rrSoundEvent event, int startPos) { PlaySound(event, startPos); }

// остановка музыки и звуков
void StopMusic(rrSoundEvent event) { bg_event_map[event]->Stop(); }
void StopSFX(rrSoundEvent event) { snd_event_map[event]->Stop(); }

void SetVolumeMusic(float volume) {
	if (volume < 0) {
		volume = 0;
	} else if (volume > 1) {
		volume = 1;
	}

	map <rrSoundEvent, shared_ptr <Sound> > ::iterator it;
	for (it = bg_event_map.begin(); it != bg_event_map.end(); ++it) {
		if (it->second != NULL) { it->second->SetVolume(volume); }
	}
}

void SetVolumeSFX(float volume) {
	if (volume < 0) {
		volume = 0;
	} else if (volume > 1) {
		volume = 1;
	}

	map <rrSoundEvent, shared_ptr <Sound> > ::iterator it;
	for (it = snd_event_map.begin(); it != snd_event_map.end(); ++it) {
		if (it->second != NULL) { it->second->SetVolume(volume); }
	}
}

void StopAllMusic() {
	map <rrSoundEvent, shared_ptr <Sound> > ::iterator it;
	for (it = bg_event_map.begin(); it != bg_event_map.end(); ++it) {
		if (it->second != NULL) { it->second->Stop(); }
	}
}

void StopAllSFX() {
	map <rrSoundEvent, shared_ptr <Sound> > ::iterator it;
	for (it = snd_event_map.begin(); it != snd_event_map.end(); ++it) {
		if (it->second != NULL) { it->second->Stop(); }
	}
}
