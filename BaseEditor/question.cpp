#include "pch.h"
#pragma hdrstop
#include "question.h"
#pragma package(smart_init)

// ------------------------------------------------------------------
sQuestion::sQuestion() {
    question = "";
    comment = "";
    answers = new TStringList();
    _true_answer = 255;
    _round = 0;
}

sQuestion::~sQuestion() { delete answers; }
// ------------------------------------------------------------------

void sQuestion::SetTrue(int new_value) {
    if (new_value <= answers->Count || new_value == 255) {
        _true_answer = new_value;
    }
}

void sQuestion::SetRound(unsigned new_value) {
    if (new_value > 0 || new_value < 5) {
        _round = new_value;
    }
}
// ------------------------------------------------------------------

void sQuestion::AssignAnswersList(const TStrings *answers_list) { answers->Assign(answers_list); }

// sQuestion inbase structure
// 1 byte        round
// 2 byte        lengths
// 1 byte        question length
// 1 byte        comment length
// 1-256 bytes   question text
// 1-256 bytes   comment text
// ------
// 1 byte        answers count
// 1-1312 bytes  answers
// 1 byte        answer length
// 1-40 bytes    answer text
// 1 byte        true answer
