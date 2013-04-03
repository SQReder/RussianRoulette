#ifndef AIH
#define AIH

// -----------------------------------------------------------------------------
enum TBotType {
    bbHuman, bbFoooool, bbFooly, bbNormal, bbHard, bbVeryHard
};

enum TBotActionType {
	baStoppingMech, baChoosingOpp, baChoosingHatch, baDecideStayOrLeave
};

class TBot { // класс ботов

public:
    TBot();
	void SetBotType(TBotType bottype);
    int bAction;

	bool Get_Answer();

private:
    int bBrain;
	int bIdentity;
};
// -----------------------------------------------------------------------------
#endif
