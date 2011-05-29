// ---------------------------------------------------------------------------
#include <algorithm>
#pragma hdrstop
#include "base.h"
#pragma package(smart_init)

// ---------------------------------------------------------------------------
sBase::sBase() {
    questions.clear();
    question_is_used.clear();
}

sBase::~sBase() {
    questions.clear();
    question_is_used.clear();
}

// ---------------------------------------------------------------------------
void sBase::add(sQuestion* question) { questions.push_back(question); }

void sBase::drop(sQuestion* question) { questions.remove(question); }

void sBase::replace(sQuestion* question) {
    std::find(questions.begin(), questions.end(), question);
    questions.remove(question);
}
// ---------------------------------------------------------------------------

sQuestion* sBase::GetQuestionPointer(unsigned index) const {
    if (index < questions.size()) {
        // get first element of list
        std::list <sQuestion *> ::const_iterator it = questions.begin();

        // and go for [index] steps
        for (unsigned i = 0; i < index; ++i, ++it) { ;
        }
        return* it;
    }
    return NULL;
}

// ---------------------------------------------------------------------------
const TStrings* sBase::GetQuestionsList() const {
    TStringList* list = new TStringList();
    std::list <sQuestion *> ::const_iterator it;
    for (it = questions.begin(); it != questions.end(); ++it) {
        sQuestion* q = *it;
        list->Add(q->question);
    }
    return list;
}
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

// set default base signature and password
const AnsiString signature = "rrb1";
const AnsiString pass = "pass";

// stream for i|o base file
TFileStream* stream;

// templates for easy manipulate with some types in stream
template <class T>
void WriteString(T str) { stream->WriteBuffer(&str[1], str.Length() *sizeof(str[1])); }

template <class T>
T ReadString(unsigned length) {
    char* buff = new char[length *sizeof(T)];
    stream->ReadBuffer(& buff[0], length* sizeof(T));
    T str = buff;
    return str;
};

template <class T>
void WriteN(T x) { stream->WriteBuffer(&x, sizeof(T)); }

void WriteChar(char x) { stream->WriteBuffer(&x, sizeof(char)); }

void ReadChar(char* x) { stream->ReadBuffer(x, sizeof(char)); };
// -> templates

void sBase::save(UnicodeString filename) {
    stream = new TFileStream(filename, fmCreate);
    WriteString(signature);
    WriteString(pass);
    WriteN(questions.size());

    // start writing questions
    std::list <sQuestion *> ::iterator it;
    for (it = questions.begin(); it != questions.end(); ++it) {
        sQuestion* q = *it;
        WriteChar(q->round);
        WriteChar(q->question.Length());
        WriteChar(q->comment.Length());
        WriteString(q->question);
        WriteString(q->comment);

        TStringList* answers = const_cast <TStringList *> (q->GetAnswersList());
        WriteChar(answers->Count);
        for (int i = 0; i < answers->Count; ++i) {
            WriteChar(answers->Strings[i].Length());
            WriteString(answers->Strings[i]);
        }
        WriteChar(q->true_answer);
    }

    stream->Free();
}
// ---------------------------------------------------------------------------

void sBase::load(UnicodeString filename) {
    stream = new TFileStream(filename, fmOpenRead);
    if (ReadString <AnsiString> (4) != signature) {
        MessageBoxA(0, "Base Loading Err", "ÅÃÃÎÃ", 0);
        return;
    }
    stream->Free();
}
