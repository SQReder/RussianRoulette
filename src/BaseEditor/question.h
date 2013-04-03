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
    UnicodeString comment;

    __property int true_answer = { read = _true_answer, write = SetTrue };
    __property int round = { read = _round, write = SetRound };

    void AssignAnswersList(const TStrings* answers_list);
    const String sQuestion::GetAnswer(int i) const;
    const int GetAnswersCount() const;

private:
    // round may be it [1..5]. 5 is a final round
    int _round;

    void SetRound(int);

    // if (it == 255) then it is a question for final round
    int _true_answer;

    void SetTrue(int);

    // one question may have multiply answers
    TStringList* answers;
};
// ---------------------------------------------------------------------------
#endif