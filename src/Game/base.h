// ---------------------------------------------------------------------------
#ifndef baseH
#define baseH
#include "pch.h"

void LoadQuestionFromBase(String BaseFile);

class QA {
public:
    QA() : Round(-1), TrueAnswer(-1) { };

    char Round;
    int TrueAnswer;
    String Question;
    String Answers[5];

};

extern QA *base;
extern int qcount;

#endif
