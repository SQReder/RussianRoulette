// ---------------------------------------------------------------------------
//    Russian Roulette is PC version of popular television game show.
//    Copyright (C) 2010-2011 Popovskiy Andrey
//    Copyright (C) 2010-2011 Boytsov Sergey

//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
// ---------------------------------------------------------------------------
#include "AI.h"
#include "stdlib.h"

const int BotBrain[6] = {
    0,
    30,
    33,
    70,
    8,
    100
};
const int BotIdent[6] = {
    0,
    10,
    20,
    30,
    25,
    5
};

// -----------------------------------------------------------------------------
TBot::TBot(TBotType BotType) {
    bBrain = BotBrain[BotType];
    bIdentity = BotIdent[BotType];
};

// -----------------------------------------------------------------------------
bool TBot::Get_Answer() {
    // если бот не знает ответ на вопрос, ...
    if (random(100) <= bBrain) {
        return true;
    }
    // ...то он пытается выбрать ответ интуитивно.
    if (random(100) <= bIdentity) {
        return true;
    }
    return false;
}
// -----------------------------------------------------------------------------

int TBot::ChooseAnyPlayer(bool players_state[6], int _ch) {
    int s = random(5);
    while (s == _ch - 1 || players_state[s] == 0) {
        s = random(5);
    }
    return s + 1;
}
// -----------------------------------------------------------------------------
