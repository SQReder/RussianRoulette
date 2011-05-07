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
};
// ---------------------------------------------------------------------------
#endif
