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
#include "AI.h"
#include "pch.h"
array<int, 6> BotBrain = { 0, 30, 33, 70, 8, 100 };
array<int, 6> BotIdent = { 0, 10, 20, 30, 25, 5 };

// -----------------------------------------------------------------------------
TBot::TBot() {
    bBrain = 0;
	bIdentity = 0;
	bAction = baStoppingMech;
}

// -----------------------------------------------------------------------------
void TBot::SetBotType(TBotType BotType) {
	bBrain = BotBrain.at(BotType);
	bIdentity = BotIdent.at(BotType);
};

// -----------------------------------------------------------------------------
bool TBot::Get_Answer() {
    // ���� ��� ����� ����� �� ������, ��� ��� ������� ��������
    if (random(100) <= bBrain || random(100) <= bIdentity) {
        // �������� �����
        return true;
    }

    // ����� ���������
    return false;
}
// -----------------------------------------------------------------------------
