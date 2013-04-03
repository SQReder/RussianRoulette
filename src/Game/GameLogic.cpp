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
#include "GameLogic.h"
#include "MainForm.h"
#include "Hatches.h"
#include "base.h"
#include "audio.h"
// ---------------------------------------------------------------------------

#pragma package(smart_init)
int CurrentHatch;
extern int RoundOfGame;

// -----------------------------------------------------------------------------
/* 1. «десь нужно временно отключить форму вопроса и labels... */
void switchoffquestion() {
    F->imgQuestion->Visible = false;
    F->LabelMoney->Visible = false;
    F->LabelQuestion->Visible = false;
}

// -----------------------------------------------------------------------------
/* 2. ѕосле того, как отработает таймер выбора игрока,
 отобразить их; включить звук */
// -----------------------------------------------------------------------------
void switchonquestion() {
    F->imgQuestion->Visible = true;
    F->imgBorder->Visible = true;
}
// -----------------------------------------------------------------------------

void showquestion() {
    unsigned int rndq; // random question

    do {
        rndq = random(qcount);
    }
    while (!(StrToInt(base[rndq].Round) == RoundOfGame));

    F->LabelQuestion->WordWrap = false;
    F->LabelQuestion->AutoSize = true;
    F->NumberOfQuestion = rndq;
    F->LabelQuestion->Caption = base[F->NumberOfQuestion].Question;
    F->LabelQuestion->Left = (int)(F->imgQuestion->Left + (F->imgQuestion->Width - F->LabelQuestion->Width) / 2.);

    if (F->LabelQuestion->Width == F->LabelQuestion->Constraints->MaxWidth) {
        F->LabelQuestion->WordWrap = true;
        F->LabelQuestion->AutoSize = false;
        F->LabelQuestion->Width = 573;
        F->LabelQuestion->AutoSize = true;
    } else {
        F->LabelQuestion->WordWrap = false;
    }

    F->LabelQuestion->Left = (int)(F->imgQuestion->Left + (F->imgQuestion->Width - F->LabelQuestion->Width) / 2.);
    F->LabelQuestion->Visible = true;
    F->tmrWaiting->Enabled = true;
    base[F->NumberOfQuestion].Round = '0';
    PlaySound(rr_question);
    // считать вопрос из файла; дл€ начала заранее с помощью отдельной программы
}

// -----------------------------------------------------------------------------
/* 2.1. ѕосле этого дать возможность выбрать игрока дл€ ответа
 (если компьютер, выбор случаен) */
void GiveHumanChooseOpponent() {
    if ((CurrentHatch != 1) && (F->isPlayerInGame[0] == true)) {
        F->imgHatch1->Enabled = true;
        F->imgNumber1->Enabled = true;
    }
    if ((CurrentHatch != 2) && (F->isPlayerInGame[1] == true)) {
        F->imgHatch2->Enabled = true;
        F->imgNumber2->Enabled = true;
    }
    if ((CurrentHatch != 3) && (F->isPlayerInGame[2] == true)) {
        F->imgHatch3->Enabled = true;
        F->imgNumber3->Enabled = true;
    }
    if ((CurrentHatch != 4) && (F->isPlayerInGame[3] == true)) {
        F->imgHatch4->Enabled = true;
        F->imgNumber4->Enabled = true;
    }
    if ((CurrentHatch != 5) && (F->isPlayerInGame[4] == true)) {
        F->imgHatch5->Enabled = true;
        F->imgNumber5->Enabled = true;
    }
}

// -----------------------------------------------------------------------------
/* 2.2. «атем игрок должен дать ответ (обработка клавиши) */
void Proverka() {
    PlaySound(F->answer == F->RandomPlace ? rr_true : rr_false);
    F->LabelMoney->Visible = false;
    F->tmrWaiting->Enabled = true;
}

// -----------------------------------------------------------------------------
void hatches_enable_state(bool state) {
    F->imgHatch0->Enabled = state;
    F->imgHatch1->Enabled = state;
    F->imgHatch2->Enabled = state;
    F->imgHatch3->Enabled = state;
    F->imgHatch4->Enabled = state;
    F->imgHatch5->Enabled = state;
    F->imgNumber1->Enabled = state;
    F->imgNumber2->Enabled = state;
    F->imgNumber3->Enabled = state;
    F->imgNumber4->Enabled = state;
    F->imgNumber5->Enabled = state;
}

// -----------------------------------------------------------------------------
void load_final_question() {
    unsigned int rndq; // random question

    do {
        rndq = random(qcount);
    }
    while (!(StrToInt(base[rndq].Round) == RoundOfGame));

    F->LabelQuestion->WordWrap = false;
    F->LabelQuestion->AutoSize = true;
    F->NumberOfQuestion = rndq;
    F->LabelQuestion->Caption = base[F->NumberOfQuestion].Question;

    if (F->LabelQuestion->Width == F->LabelQuestion->Constraints->MaxWidth) {
        F->LabelQuestion->WordWrap = true;
        F->LabelQuestion->AutoSize = false;
        F->LabelQuestion->Width = 573;
        F->LabelQuestion->AutoSize = true;
    } else {
        F->LabelQuestion->WordWrap = false;
    }

    F->LabelQuestion->Left = F->imgQuestion->Left + (int)(F->imgQuestion->Width - F->LabelQuestion->Width) / 2.;
    F->LabelQuestion->Visible = true;
    F->LabelMoney->Visible = true;
    F->imgTotalPrize->Visible = true;
    F->imgPulseBar->Visible = true;
    F->imgTicker->Visible = true;
    base[F->NumberOfQuestion].Round = '0';
}

// -----------------------------------------------------------------------------
String myLowerCase(String str) {
    const wchar_t upper[33] = L"јЅ¬√ƒ≈®∆«» ЋћЌќѕ–—“”‘’÷„ЎўЏџ№Ёёя";
    const wchar_t lower[33] = L"абвгдеЄжзиклмнопрстуфхцчшщъыьэю€";
    wchar_t *ptr;

    for (int i = 1; i <= str.Length(); i++) {
        ptr = wcschr(upper, str[i]);
        if (ptr) {
            str[i] = lower[ptr - upper];
        }
    }

    return str;
}

// -----------------------------------------------------------------------------
bool CheckAnswerAtFinalRound(String ans, int NumberOfQuestion) {
    ans = Trim(ans);
    ans = myLowerCase(ans);
    String trueans[5];
    for (int i = 0; i < 5; i++) {
        trueans[i] = base[NumberOfQuestion].Answers[i];
        trueans[i] = myLowerCase(trueans[i]);
    }
    // удаление двойных пробелов
    for (int i = 0; i < 5; i++) {
        if (ans == trueans[i]) {
            return true;
        }
    }
    return false;
}
// ------------------------------------------
