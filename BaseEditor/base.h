#ifndef baseH
#define baseH
#include <map>
#include <vector>
#include "question.h"

// ---------------------------------------------------------------------------
class sBase {
public:
	sBase();
	~sBase();

	void add(sQuestion* question);

private:
	std::vector <sQuestion> questions;
	std::vector <bool> question_is_used;
};
// ---------------------------------------------------------------------------
#endif
