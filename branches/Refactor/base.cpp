#include <classes.hpp>
#include <system.hpp>
#pragma hdrstop
#include "base.h"
#pragma package(smart_init)

extern void ShowError(int);

QA* base;
int qcount;

String FillChars(String str, int count);
String ClearStr(String str);
String GetStr(String str, int begin, int size);
// ---------------------------------------------------------------------------

const char* BaseDir = "base\\";
void LoadQuestionFromBase(String BaseFile) {
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
		TFileStream* stream = new TFileStream(BaseDir + BaseFile, fmOpenRead);
		// �������������� ������ � ��������� � ��� ���������� �������� � ����
		String tstr = "     "; // ����� ������ = ���������� ����������� ��������
		// ��������� ������ ������ � 10 ����, ��� ������, � �������� 5 =/
		stream->Read(& tstr[1], 10);

		tstr = ClearStr(tstr); // ������ ���� �������� ���-�� �������� � ���� =^__^=
		qcount = StrToInt(tstr);

		base = new QA[qcount];

		for (int i = 0; i < qcount; i++) {
			String str = "";
			// �� ��� ��� ���� =)
			str = FillChars(str, 457); // �������������� ������ ��� ��������
			stream->ReadBuffer(& str[1], 457* 2);
			// � ��������� ���� ������

			for (int i = 1; i < str.Length(); i++) // ��������������
			{
				str[i] = str[i] ^ (i % 7);
			}

			base[i].Round = GetStr(str, 1, 1)[1]; // ���� ����� ������ 1-4

			base[i].Question = ClearStr(GetStr(str, 2, 255)); // ������

			base[i].Answers[0] = ClearStr(GetStr(str, 257, 40));
			// �������� ������
			base[i].Answers[1] = ClearStr(GetStr(str, 297, 40));
			base[i].Answers[2] = ClearStr(GetStr(str, 337, 40));
			base[i].Answers[3] = ClearStr(GetStr(str, 377, 40));
			base[i].Answers[4] = ClearStr(GetStr(str, 417, 40));

			base[i].TrueAnswer = StrToInt(GetStr(str, 457, 1));
			// ���������� �����
		}
		stream->Free();
	}
	catch (...) {
		ShowError(2);
	}
}

// ---------------------------------------------------------------------------
String FillChars(String str, int count) {
	for (int i = str.Length(); i < count; i++) {
		str += '|';
	}

	return str;
}

// ---------------------------------------------------------------------------
String ClearStr(String str) {
	String cl_str = "";
	int i = 1;

	while (str[i] != '|') {
		cl_str += str[i];
		if (i++ == str.Length())
			break;
	}

	return cl_str;
}

// ---------------------------------------------------------------------------
String GetStr(String str, int begin, int size) {
	String ret = "";

	for (int i = begin; i < begin + size; i++)
		ret += str[i];

	return ret;
}