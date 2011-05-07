#include "question.h"
#pragma package(smart_init)
// ------------------------------------------------------------------
sQuestion::sQuestion() {
	question = "";
	question_comment = "";
	answers = new TStringList();
}

sQuestion::~sQuestion() {
	question = "";
	question_comment = "";
	delete answers;
}
// ------------------------------------------------------------------

