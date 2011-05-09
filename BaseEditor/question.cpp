#include "question.h"
#pragma package(smart_init)

// ------------------------------------------------------------------
sQuestion::sQuestion() {
	question = "";
	comment = "";
	answers = new TStringList();
	_true_answer = -1;
  _round = 0;
}

sQuestion::~sQuestion() { delete answers; }
// ------------------------------------------------------------------

void sQuestion::SetTrue(int new_value) {
	if (new_value <= answers->Count)
		_true_answer = new_value;
}

void sQuestion::SetRound(unsigned new_value) {
	if (new_value > 0 || new_value < 5)
		_round = new_value;
}
// ------------------------------------------------------------------

void sQuestion::AssignAnswersList(const TStrings* answers_list) {
	answers->Assign(answers_list);
}

// ------------------------------------------------------------------
const TStrings* sQuestion::GetAnswersList() const {
	return answers;
}
