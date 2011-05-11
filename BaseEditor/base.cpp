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

TFileStream* stream;

template <class T>
void WriteString(T str) { stream->WriteBuffer(&str[1], str.Length() *sizeof(str[1])); }

template <class T>
void WriteX(T x) { stream->WriteBuffer(&x, sizeof(T)); }

void sBase::save(UnicodeString filename) {
	stream = new TFileStream(filename, fmCreate);
	WriteString(signature);

	// start writing questions
	std::list <sQuestion *> ::iterator it;
	for (it = questions.begin(); it != questions.end(); ++it) {
		sQuestion* q = *it;
		WriteX((char)q->question.Length());
		WriteString(q->question);
	}

	delete stream;
}
// ---------------------------------------------------------------------------
