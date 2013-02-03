// ---------------------------------------------------------------------------
// Russian Roulette is PC version of popular television game show.
// Copyright (C) 2010-2011 Popovskiy Andrey
// Copyright (C) 2010-2011 Boytsov Sergey

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

QA *base;
int qcount;

String FillChars(String str, int count);
String ClearStr(String str);
String GetStr(String str, int begin, int size);
// ---------------------------------------------------------------------------

const char *BaseDir = "base\\";

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
        TFileStream *stream = new TFileStream(BaseDir + BaseFile, fmOpenRead);
        // �������������� ������ � ��������� � ��� ���������� �������� � ����
        String tstr = "     "; // ����� ������ = ���������� ����������� ��������
        // ��������� ������ ������ � 10 ����, ��� ������, � �������� 5 =/
        stream->Read(&tstr[1], 10);

        tstr = ClearStr(tstr); // ������ ���� �������� ���-�� �������� � ���� =^__^=
        qcount = StrToInt(tstr);

        base = new QA[qcount];

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
        ShowMessage("������ �������� ���� ��������: ���� � ������ '" + BaseFile + "' �� ����������!");
        Application->Terminate();
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
        if (i++ == str.Length()) {
            break;
        }
    }

    return cl_str;
}

// ---------------------------------------------------------------------------
String GetStr(String str, int begin, int size) {
    String ret = "";

    for (int i = begin; i < begin + size; i++) {
        ret += str[i];
    }

    return ret;
}
