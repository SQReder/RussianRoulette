#ifndef questionH
#define questionH
#include <classes.hpp>

// ---------------------------------------------------------------------------
class sQuestion {
public:
	sQuestion();
	~sQuestion();

	UnicodeString question;

	// comment may be empty
	UnicodeString question_comment;

	__property int true_answer = { read = _true_answer, write = SetTrue };
	__property unsigned round = { read = _round, write = SetRound };

	void AssignAnswersList(const TStrings* answers_list);

private:
	// round may be it [1..5]. 5 is a final round
	unsigned _round;
	void SetRound(unsigned);

	// if (it == -1) then it is a question for final round
	int _true_answer;
	void SetTrue(int);

	// one question may have multiply answers
	TStringList* answers;
};
// ---------------------------------------------------------------------------
#endif
