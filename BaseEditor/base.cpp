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
		for (unsigned i = 0; i < index; ++i, ++it);
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

const AnsiString signature = "rrb1";
const AnsiString pass = "pass";

TFileStream* stream;

template <class T>
void WriteString(T str) { stream->WriteBuffer(&str[1], str.Length() *sizeof(str[1])); }

// for some classes
template <class T>
void WriteN(T x) { stream->WriteBuffer(&x, sizeof(T)); }

void WriteChar(char x) { stream->WriteBuffer(&x, sizeof(char)); }

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
//	delete stream;
}
// ---------------------------------------------------------------------------

template <class T>
T ReadString(unsigned length) {
	char* str = new char[length + 1];
	stream->ReadBuffer(& str[1], length* sizeof(T));
	T ret = str;
	return ret;
}

char ReadN() {
	char N = '\0';
	stream->ReadBuffer(& N, sizeof(char));
	return N;
}

void sBase::load(UnicodeString filename) {
	stream = new TFileStream(filename, fmOpenRead);
	if (ReadString <AnsiString> (4) != signature) {
		MessageBoxA(0, "Base Loading Err", "ÅÃÃÎÃ", 0);
		return;
	}
	stream->Free();
}             	      	
