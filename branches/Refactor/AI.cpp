#ifndef AIH
#define AIH
#include "stdlib.h"
const float _bbVeryHard = 1.0;
const float _biVeryHard = 0.05;
const float _bbHard = 0.85;
const float _biHard = 0.25;
const float _bbNormal = 0.70;
const float _biNormal = 0.3;
const float _bbFooly = 1 / 3;
const float _biFooly = 0.20;
const float _bbFoooool = 0.30;
const float _biFoooool = 0.10;

// -----------------------------------------------------------------------------
enum TBotType {
	bbHuman, bbFoooool, bbFooly, bbNormal, bbHard, bbVeryHard
};

class TBot { // класс ботов

protected:
	float bBrain;
	float bIdentity;

	void SetBotIdentity(TBotType BotType);
	void SetBotBrain(TBotType BotType);

public:
	bool Get_Answer();
	int ChooseAnyPlayer(bool* players_state, int _ch);

	TBot(TBotType bottype) {
		switch (bottype) {
		case bbVeryHard:
			bBrain = _bbVeryHard;
			bIdentity = _biVeryHard;
			break;
		case bbHard:
			bBrain = _bbHard;
			bIdentity = _biHard;
			break;
		case bbNormal:
			bBrain = _bbNormal;
			bIdentity = _biNormal;
			break;
		case bbFooly:
			bBrain = _bbFooly;
			bIdentity = _biFooly;
			break;
		case bbFoooool:
			bBrain = _bbFoooool;
			bIdentity = _biFoooool;
			break;
		}
	};
};
#pragma hdrstp
// -----------------------------------------------------------------------------

bool TBot::Get_Answer() {
	// если человек не знает ответ на вопрос, ...
	if ((random(100) / 100.) <= bBrain)
		return (1);
	// ...то он пытается добиться ответа интуицией.
	if ((random(100) / 100.) <= bIdentity)
		return (1);
	return (0);
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
#endif
