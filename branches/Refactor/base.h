// ---------------------------------------------------------------------------
#ifndef baseH
#define baseH
void LoadQuestionFromBase(String BaseFile);

class QA {
public:
	QA() : Round(-1), TrueAnswer(-1) { };

	char Round;
	int TrueAnswer;
	UnicodeString Question;
	UnicodeString Answers[5];

};
#endif
