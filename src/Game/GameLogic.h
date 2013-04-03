// ---------------------------------------------------------------------------
#ifndef GameLogicH
#define GameLogicH
#include "pch.h"

void switchoffquestion();
void switchonquestion();
void showquestion();
void GiveHumanChooseOpponent();
void Proverka();
void load_final_question();
bool CheckAnswerAtFinalRound(String ans, int NumberOfQuestion);
// ---------------------------------------------------------------------------
extern int CurrentHatch;
extern void hatches_enable_state(bool state);

#endif
