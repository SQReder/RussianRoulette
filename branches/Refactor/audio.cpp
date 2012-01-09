// ---------------------------------------------------------------------------
// Russian Roulette is PC version of popular television game show.
// Copyright (C) 2010-2011 Popovskiy Andrey
// Copyright (C) 2010-2011 Boytsov Sergey

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

using namespace std;
using boost::shared_ptr;

const String extention = ".ogg";
const String sounds_path = ".\\sounds\\";

class Sound {
public:
    Sound(String filename) {
        mem = new TMemoryStream;
        mem->LoadFromFile(sounds_path + filename + extention);
        stream = BASS_StreamCreateFile(1, mem->Memory, 0, mem->Size, 0);
    }

    ~Sound() {
        BASS_StreamFree(stream);
        delete mem;
    }

    void Play() { BASS_ChannelPlay(stream, 1); }

    void Stop() { BASS_ChannelStop(stream); }

    void SetVolume(float volume) { BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, volume); }

private:
    HSTREAM stream;
    TMemoryStream *mem;
};

// ---------------------------------------------------------------------------
map <rrSoundEvent, shared_ptr <Sound> > event_map;

#define MAP_FILE_TO_EVENT(X) event_map[X] = shared_ptr <Sound> (new Sound(#X))

void init_audio(HWND hwnd) {
    if (!BASS_Init(-1, 44100, 0, hwnd, NULL)) {
        __asm INT 3;
    }

    MAP_FILE_TO_EVENT(Next_Question);
    MAP_FILE_TO_EVENT(question_clear);
    MAP_FILE_TO_EVENT(rr_20sec);
    MAP_FILE_TO_EVENT(rr_bg1);
    MAP_FILE_TO_EVENT(rr_bg2);
    MAP_FILE_TO_EVENT(rr_bg3);
    MAP_FILE_TO_EVENT(rr_bg4);
    MAP_FILE_TO_EVENT(rr_bg5);
    MAP_FILE_TO_EVENT(rr_choosen);
    MAP_FILE_TO_EVENT(rr_closing);
    MAP_FILE_TO_EVENT(rr_endround);
    MAP_FILE_TO_EVENT(rr_fall);
    MAP_FILE_TO_EVENT(rr_fall_with_host);
    MAP_FILE_TO_EVENT(rr_false);
    MAP_FILE_TO_EVENT(rr_final);
    MAP_FILE_TO_EVENT(rr_intro_Take_2);
    MAP_FILE_TO_EVENT(rr_intro);
    MAP_FILE_TO_EVENT(rr_mexclose);
    MAP_FILE_TO_EVENT(rr_mexopen);
    MAP_FILE_TO_EVENT(rr_money);
    MAP_FILE_TO_EVENT(rr_nextq);
    MAP_FILE_TO_EVENT(rr_notfall);
    MAP_FILE_TO_EVENT(rr_openhole);
    MAP_FILE_TO_EVENT(rr_openround);
    MAP_FILE_TO_EVENT(rr_players);
    MAP_FILE_TO_EVENT(rr_question);
    MAP_FILE_TO_EVENT(rr_round);
    MAP_FILE_TO_EVENT(rr_save);
    MAP_FILE_TO_EVENT(rr_true);
}

void PlaySound(rrSoundEvent event) {
    switch (event) {
    case Next_Question: break;
    case question_clear: break;
    case rr_20sec:
        event_map[rr_choosen]->Stop();
        event_map[rr_question]->Stop();
        break;
    case rr_bg1: break;
    case rr_bg2: break;
    case rr_bg3: break;
    case rr_bg4: break;
    case rr_bg5: break;
    case rr_choosen:
        event_map[rr_question]->Stop();
        break;
    case rr_closing:
    case rr_endround:
    case rr_mexopen:
        {
            event_map[rr_bg1]->Stop();
            event_map[rr_bg2]->Stop();
            event_map[rr_bg3]->Stop();
            event_map[rr_bg4]->Stop();
            event_map[rr_bg5]->Stop();
        }
        break;
    case rr_fall:
        event_map[rr_mexclose]->Stop();
        break;
    case rr_fall_with_host: break;
    case rr_false: break;
    case rr_final: break;
    case rr_intro_Take_2: break;
    case rr_intro: break;
    case rr_mexclose:
        event_map[rr_mexopen]->Stop();
        break;
    case rr_money: break;
    case rr_nextq: break;
    case rr_notfall: break;
    case rr_openhole: break;
    case rr_openround: break;
    case rr_players: break;
    case rr_question:
        {
            event_map[rr_bg1]->Stop();
            event_map[rr_bg2]->Stop();
            event_map[rr_bg3]->Stop();
            event_map[rr_bg4]->Stop();
            event_map[rr_bg5]->Stop();
            event_map[rr_mexclose]->Stop();
        }
        break;
    case rr_round: break;
    case rr_save:
        event_map[rr_mexclose]->Stop();
        break;
    case rr_true: break;
    }
    event_map[event]->Play();
}

void StopSound(rrSoundEvent event) { event_map[event]->Stop(); }

void SetVolumeAll(float volume) {
    if (volume < 0) {
        volume = 0;
    } else if (volume > 1) {
        volume = 1;
    }

    map <rrSoundEvent, shared_ptr <Sound> > ::iterator it;
    for (it = event_map.begin(); it != event_map.end(); ++it) {
        it->second->SetVolume(volume);
    }
}

void StopSoundAll() {
    map <rrSoundEvent, shared_ptr <Sound> > ::iterator it;
    for (it = event_map.begin(); it != event_map.end(); ++it) {
        it->second->Stop();
    }
}
