#ifndef AIH
#define AIH

// -----------------------------------------------------------------------------
enum TBotType {
	bbHuman, bbFoooool, bbFooly, bbNormal, bbHard, bbVeryHard
};

class TBot { // ����� �����

private:
	float bBrain;
	float bIdentity;

public:
	bool Get_Answer();
	int ChooseAnyPlayer(bool players_state[6], int _ch);
	TBot(TBotType bottype);
};
// -----------------------------------------------------------------------------
#endif
