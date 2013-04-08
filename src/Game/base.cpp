// ---------------------------------------------------------------------------
// Russian Roulette is PC version of popular television game show.
// Copyright (C) 2010-2013 Popovskiy Andrey
// Copyright (C) 2010-2013 Boytsov Sergey

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// ---------------------------------------------------------------------------
#include "base.h"
#pragma package(smart_init)

class QA {
public:
    QA() : Round(-1), TrueAnswer(-1) { };

    char Round;
    int TrueAnswer;
    String Question;
    array<String, 5> Answers;

};

String FillChars(String str, int count);
String ClearStr(const String& str);
// ---------------------------------------------------------------------------

const char *BaseDir = "base\\";

// ---------------------------------------------------------------------------
String FillChars(String str, int count) {
    for (int i = str.Length(); i < count; i++) {
        str += '|';
    }

    return str;
}

// ---------------------------------------------------------------------------
String ClearStr(const String& str) {
	return str.SubString(0, str.Pos('|')-1);
}
// ===========================================================================
QA parseQuestionData(const String& data) {
	QA item;
	item.Round = StrToInt(data.SubString(1, 1)); // ���� ����� ������ 1-4

	item.Question = ClearStr(data.SubString(2, 255)); // ������

	// �������� ������
	item.Answers[0] = ClearStr(data.SubString(257, 40));
	item.Answers[1] = ClearStr(data.SubString(297, 40));
	item.Answers[2] = ClearStr(data.SubString(337, 40));
	item.Answers[3] = ClearStr(data.SubString(377, 40));
	item.Answers[4] = ClearStr(data.SubString(417, 40));

	item.TrueAnswer = StrToInt(data.SubString(457, 1));
	return item;
}

// ===========================================================================
void QuestionBase::LoadFromFile(const String filename) {
	questions.clear();
	/*
     5 �������� - ���������� �������� � ����
     ����� ������� �� 457 ��������
     1 ������ - ����� ������
     255 �������� - ������
     �� 40 �������� ������
     1 ������ - ����� �����������
     ���������� ���������� � ���� =)
     */

    // ��������� ����
    try {
		shared_ptr<TMemoryStream> stream(new TMemoryStream);
		stream->LoadFromFile(BaseDir + filename);
		// �������������� ������ � ��������� � ��� ���������� �������� � ����
		String tstr = "     "; // ����� ������ = ���������� ����������� ��������
        // ��������� ������ ������ � 10 ����, ��� ������, � �������� 5 =/
        stream->Read(&tstr[1], 10);

		tstr = ClearStr(tstr); // ������ ���� �������� ���-�� �������� � ���� =^__^=
		int qcount = StrToInt(tstr);

		QA item;

		for (int i = 0; i < qcount; i++) {
			String str = "";
			// �� ��� ��� ���� =)
			str = FillChars(str, 457); // �������������� ������ ��� ��������
			stream->ReadBuffer(&str[1], 457 *2);
			// � ��������� ���� ������

			for (int i = 1; i < str.Length(); i++) // ��������������
			{
				str[i] = str[i] ^ (i % 7);
			}


			questions.push_back(parseQuestionData(str));
		}
	}
	catch (...) {
		ShowMessage("������ �������� ���� ��������: ���� � ������ '" + filename + "' �� ����������!");
		Application->Terminate();
	}
}


const shared_ptr<QuestionBase> QuestionBase::Instance() {
	static shared_ptr<QuestionBase> instance(new QuestionBase());
	return instance;
}


const QA& QuestionBase::item(size_t index) const {
	return questions.at(index);
}


const String QuestionBase::GetQuestion(size_t index) const{
	return item(index).Question;
}


const String QuestionBase::GetAnswer(size_t question, size_t answer) const{
	return item(question).Answers.at(answer);
}


const int QuestionBase::GetTrueAnswer(size_t question) const{
	return item(question).TrueAnswer;
}


const int QuestionBase::GetRound(size_t question) const{
	return item(question).Round;
}


const size_t QuestionBase::GetQuestionsCount() const{
	return questions.size();
}


const size_t QuestionBase::GetRandomQuestionForRound(int round) {
	static vector<size_t> used;

	const size_t max = questions.size();

	size_t rndq = 0;
	bool isUsed = false;
	bool wrongRound = false;
	do {
		rndq = random(max);
		wrongRound = GetRound(rndq) != round;
		isUsed = (find(used.begin(), used.end(), rndq) != used.end());
	}
	while (wrongRound && isUsed);

	used.push_back(rndq);
	return rndq;
}
