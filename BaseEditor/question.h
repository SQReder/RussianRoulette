#ifndef questionH
#define questionH
#include <classes.hpp>
// ---------------------------------------------------------------------------
class sQuestion {
public:
	sQuestion();
	~sQuestion();

	UnicodeString question;

	// one question may have multiply answers
	TStringList* answers;

	// comment may be empty
	UnicodeString question_comment;

	__property int true_answer = {read = _true_answer, write = SetTrue};
private:
	void SetTrue(int);
	// if (it == -1) then it is a question for final round
	int _true_answer;
};
// ---------------------------------------------------------------------------
#endif
