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
/* 1. Здесь нужно временно отключить форму вопроса и labels... */
void switchoffquestion() {
    F->imgQuestion->Visible = false;
    F->LabelMoney->Visible = false;
    F->LabelQuestion->Visible = false;
}

// -----------------------------------------------------------------------------
/* 2. После того, как отработает таймер выбора игрока,
 отобразить их; включить звук */
// -----------------------------------------------------------------------------
void switchonquestion() {
    F->imgQuestion->Visible = true;
    F->imgBorder->Visible = true;
}
// -----------------------------------------------------------------------------

void showquestion() {
	const shared_ptr<QuestionBase> base = QuestionBase::Instance();
	size_t rndq = base->GetRandomQuestionForRound(RoundOfGame);

	F->LabelQuestion->WordWrap = false;
	F->LabelQuestion->AutoSize = true;
	F->NumberOfQuestion = rndq;
	F->LabelQuestion->Caption = base->GetQuestion(F->NumberOfQuestion);
	int offset = (F->imgQuestion->Width - F->LabelQuestion->Width) / 2;
	F->LabelQuestion->Left = F->imgQuestion->Left + offset;

	if (F->LabelQuestion->Width == F->LabelQuestion->Constraints->MaxWidth) {
		F->LabelQuestion->WordWrap = true;
		F->LabelQuestion->AutoSize = false;
		F->LabelQuestion->Width = 573;
		F->LabelQuestion->AutoSize = true;
	} else {
		F->LabelQuestion->WordWrap = false;
	}

	offset = (F->imgQuestion->Width - F->LabelQuestion->Width) / 2;
	F->LabelQuestion->Left = F->imgQuestion->Left + offset;
	F->LabelQuestion->Visible = true;
    F->tmrWaiting->Enabled = true;
	PlaySFX(rr_question);
    // считать вопрос из файла; для начала заранее с помощью отдельной программы
}

// -----------------------------------------------------------------------------
/* 2.1. После этого дать возможность выбрать игрока для ответа
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
/* 2.2. Затем игрок должен дать ответ (обработка клавиши) */
void Proverka() {
    PlaySFX(F->answer == F->RandomPlace ? rr_true : rr_false);
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
	const shared_ptr<QuestionBase> base = QuestionBase::Instance();
	size_t rndq = base->GetRandomQuestionForRound(RoundOfGame);

    F->LabelQuestion->WordWrap = false;
    F->LabelQuestion->AutoSize = true;
    F->NumberOfQuestion = rndq;
    F->LabelQuestion->Caption = base->GetQuestion(F->NumberOfQuestion);

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
}

// -----------------------------------------------------------------------------
String myLowerCase(const String& str) {
	static const array<wchar_t, 33> upper = {L"АБВГДЕЁЖЗИКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"};
	static const array<wchar_t, 33> lower = {L"абвгдеёжзиклмнопрстуфхцчшщъыьэюя"};

	wstring wstr;
	wstr = str.c_str();

	for(unsigned i = 0; i != upper.size(); ++i) {
		::replace(wstr.begin(), wstr.end(), upper[i], lower[i]);
    }
	
    return wstr.c_str();
}

// -----------------------------------------------------------------------------
bool CheckAnswerAtFinalRound(String ans, int NumberOfQuestion) {
	const shared_ptr<QuestionBase> base = QuestionBase::Instance();

    ans = Trim(ans);
    ans = myLowerCase(ans);
    String trueans[5];
    for (int i = 0; i < 5; i++) {
        trueans[i] = base->GetAnswer(NumberOfQuestion, i);
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
