// ---------------------------------------------------------------------------
#include <algorithm>
#pragma hdrstop
#include "base.h"
#include "crc32.cpp"
#include "frm_pass.h"
#pragma package(smart_init)
extern HWND msg_hwnd;

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
const AnsiString pass = ""; // "soooo strong password!!11";

// stream for i|o base file
TFileStream* stream;

// templates for easy manipulate with some types in stream
template <class T>
void WriteString(T str) {
    if (str != "") {
        stream->WriteBuffer(& str[1], str.Length()* sizeof(str[1]));
    }
}

AnsiString ReadStringA(unsigned length) {
    char* buff = new char[length + 1];
    for (unsigned i = 0; i < length + 1; ++i) {
        buff[i] = L'\0';
    }
    stream->ReadBuffer(& buff[0], length* sizeof(char));
    return buff;
};

UnicodeString ReadStringW(unsigned length) {
    wchar_t* buff = new wchar_t[length + 1];
    for (unsigned i = 0; i < length + 1; ++i) {
        buff[i] = L'\0';
    }
    stream->ReadBuffer(& buff[0], length* sizeof(wchar_t));
    return buff;
};

template <class T>
void WriteN(T x) { stream->WriteBuffer(&x, sizeof(T)); }

template <class T>
T ReadN() {
    T buff;
    stream->ReadBuffer(& buff, sizeof(T));
    return buff;
}

void WriteChar(char x) { stream->WriteBuffer(&x, sizeof(char)); }

void ReadChar(char* x) { stream->ReadBuffer(x, sizeof(char)); };

char ReadChar() {
    char ch;
    stream->ReadBuffer(& ch, sizeof(char));
    return ch;
};
// -> templates

void sBase::save(UnicodeString filename) {
    try {
        stream = new TFileStream(filename, fmCreate);
        WriteString(signature);
        WriteN(Crc32(pass.c_str(), pass.Length()));
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
            WriteChar((char)answers->Count);
            for (int i = 0; i < answers->Count; ++i) {
                WriteChar(answers->Strings[i].Length());
                WriteString(answers->Strings[i]);
            }
            WriteChar(q->true_answer);
        }
    }
    catch (Exception&) {
        MessageBoxA(msg_hwnd, "Неизвестная ошибка сохранения файла", "Base Loading Err", 0);
    }
    stream->Free();
}

// ---------------------------------------------------------------------------
bool check_pass(unsigned __int32 hash) {
    if (hash) {
        fpass->ShowModal();
        return true;
    } else {
        return true;
    }
}

void sBase::load(UnicodeString filename) {
    try {
        stream = new TFileStream(filename, fmOpenRead);
    }
    catch (Exception&) {
        MessageBoxA(msg_hwnd, "Невозможно открыть файл", "Base Loading Err", 0);
        return;
    }
    try {
        if (ReadStringA(4) == signature) {
            unsigned __int32 pass_crc = ReadN <unsigned __int32> ();
            if (!check_pass(pass_crc)) {
                MessageBoxA(msg_hwnd, "Неверный пароль", "Base Loading Err", 0);
            }

            // MessageBoxW(0, IntToStr((__int64)pass_crc).c_str(), L"Password CRC32", 0);
            unsigned q_count = ReadN <unsigned> ();
            // MessageBoxW(0, IntToStr((int)q_count).c_str(), L"Count of questions", 0);

            questions.clear();
            for (unsigned i = 0; i < q_count; ++i) {
                sQuestion* q = new sQuestion;
                q->round = ReadChar();
                unsigned question_len = ReadChar();
                unsigned comment_len = ReadChar();
                q->question = ReadStringW(question_len);
                q->comment = ReadStringW(comment_len);

                TStringList* answers = new TStringList;
                unsigned answers_count = ReadChar();
                for (unsigned i = 0; i < answers_count; ++i) {
                    unsigned answer_len = ReadChar();
                    answers->Add(ReadStringW(answer_len));
                }
                q->AssignAnswersList(answers);
                delete answers;

                q->true_answer = ReadChar();
                questions.push_back(q);
            }

        } else {
            MessageBoxA(msg_hwnd, "Ошибка загрузки базы вопросов: сигнатура неверна", "Base Loading Err", 0);
        }
    }
    catch (Exception&) {
        MessageBoxA(msg_hwnd, "Ошибка загрузки базы вопросов: ошибка чтения файла", "Base Loading Err", 0);
    }
    stream->Free();
}
