#ifndef baseH
#define baseH
#include <list>
#include "question.h"

// ---------------------------------------------------------------------------
class sBase {
public:
	sBase();
	~sBase();

	void add(sQuestion* question);
	void drop(sQuestion* question);
	void replace(sQuestion* question);

	sQuestion* GetQuestionPointer(unsigned index);
	const TStrings* GetQuestionsList() const ;

private:
	std::list <sQuestion *> questions;
	std::list <bool> question_is_used;
};
// ---------------------------------------------------------------------------
#endif
