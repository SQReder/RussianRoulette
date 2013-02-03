#ifndef AIH
#define AIH

// -----------------------------------------------------------------------------
enum TBotType {
    bbHuman, bbFoooool, bbFooly, bbNormal, bbHard, bbVeryHard
};

class TBot { // класс ботов

public:
    TBot();
    void SetBotType(TBotType bottype);

    bool Get_Answer();

private:
    int bBrain;
    int bIdentity;

};
// -----------------------------------------------------------------------------
#endif
