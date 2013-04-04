#ifndef baseH
#define baseH
#include "pch.h"

class QA;
class QuestionBase {
	QuestionBase() {};
	QuestionBase(const QuestionBase& root);
	QuestionBase& operator=(const QuestionBase&);

	vector<QA> questions;
	const QA& item(size_t index) const;
public:
	static const shared_ptr<QuestionBase> Instance();
	void LoadFromFile(const String filename);

	const String GetQuestion(size_t index) const;
	const String GetAnswer(size_t question, size_t answer) const;
	const int GetTrueAnswer(size_t question) const;
	const int GetRound(size_t question) const;

	const size_t GetQuestionsCount() const;

	const size_t GetRandomQuestionForRound(int round);
};

#endif
