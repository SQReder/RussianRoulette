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

#ifndef audioH
#define audioH
typedef enum {
    Next_Question,
    question_clear,
    rr_20sec,
    rr_bg1,
    rr_bg2,
    rr_bg3,
    rr_bg4,
    rr_bg5,
    rr_choosen,
    rr_closing,
    rr_endround,
    rr_fall,
    rr_fall_with_host,
    rr_false,
    rr_final,
    rr_intro_Take_2,
    rr_intro,
    rr_mexclose,
    rr_mexopen,
    rr_money,
    rr_nextq,
    rr_notfall,
    rr_openhole,
    rr_openround,
    rr_players,
    rr_question,
    rr_round,
    rr_save,
    rr_true
} rrSoundEvent;

void init_audio(HWND hwnd);

void SetVolumeAll(float volume);

void PlaySound(rrSoundEvent sound_event);
void StopSound(rrSoundEvent sound_event);
void StopSoundAll();
#endif
