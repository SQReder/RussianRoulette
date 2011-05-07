#include "question.h"
#pragma package(smart_init)
// ------------------------------------------------------------------
sQuestion::sQuestion() {
	question = "";
	question_comment = "";
	answers = new TStringList();
	_true_answer = -1;
}

sQuestion::~sQuestion() {
	question = "";
	question_comment = "";
	delete answers;
}
// ------------------------------------------------------------------

void sQuestion::SetTrue(int new_true) {
	if (new_true <= answers->Count)
		_true_answer = new_true;
}
