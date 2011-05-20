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
