#ifndef baseH
#define baseH
#include <vector>
#include "question.h"

// ---------------------------------------------------------------------------
class sBase {
public:
    sBase();
    ~sBase();

    void add(sQuestion* question);
    void drop(sQuestion* question);
    void replace(sQuestion* question);

    sQuestion* GetQuestionPointer(unsigned index) const ;
    const TStrings* GetQuestionsList() const ;

    const sQuestion* GetRandomQuestion() const ;

    void save(UnicodeString filename);
    void load(UnicodeString filename);

    unsigned __int32 pass_hash() const ;
    void set_pass(AnsiString pass);

private:
    std::vector <sQuestion *> questions;
    std::vector <bool> question_is_used;

    unsigned __int32 pass_crc;
};
// ---------------------------------------------------------------------------
#endif
