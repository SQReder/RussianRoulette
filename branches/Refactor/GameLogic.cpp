// ---------------------------------------------------------------------------

#pragma hdrstop

#include "GameLogic.h"
#include "MainForm.h"
#include "Hatches.h"
#include "base.h"
// ---------------------------------------------------------------------------

#pragma package(smart_init)
int CurrentHatch;

/* 0. �������� ��������� ����������� ������� ���... */
void DeactivateHatches() {
    F->imgHatch0->Enabled = False;
    F->imgHatch1->Enabled = False;
    F->imgHatch2->Enabled = False;
    F->imgHatch3->Enabled = False;
    F->imgHatch4->Enabled = False;
    F->imgHatch5->Enabled = False;
    F->imgNumber1->Enabled = False;
    F->imgNumber2->Enabled = False;
    F->imgNumber3->Enabled = False;
    F->imgNumber4->Enabled = False;
    F->imgNumber5->Enabled = False;
}

// -----------------------------------------------------------------------------
/* 1. ����� ����� �������� ��������� ����� ������� � labels... */
void switchoffquestion() {
    F->LabelMoney->Visible = False;
    F->LabelQuestion->Visible = False;
    F->imgQuestion->Visible = False;
}

// -----------------------------------------------------------------------------
/* 2. ����� ����, ��� ���������� ������ ������ ������,
 ���������� ��; �������� ���� */
// -----------------------------------------------------------------------------
void switchonquestion() {
    F->imgQuestion->Visible = True;
    F->imgBorder->Visible = True;
}
// -----------------------------------------------------------------------------

void showquestion() {
    int Round = F->RoundOfGame;
    unsigned int rndq; // random question

    do {
        rndq = random(qcount);
    }
    while (!(StrToInt(base[rndq].Round) == Round));

    F->LabelQuestion->WordWrap = false;
    F->LabelQuestion->AutoSize = true;
    F->NumberOfQuestion = rndq;
    F->LabelQuestion->Caption = base[F->NumberOfQuestion].Question;
    F->LabelQuestion->Left = (int)(F->imgQuestion->Left + (F->imgQuestion->Width - F->LabelQuestion->Width) / 2.);
    if (F->LabelQuestion->Width == F->LabelQuestion->Constraints->MaxWidth) {
        F->LabelQuestion->WordWrap = true;
        F->LabelQuestion->AutoSize = false;
        F->LabelQuestion->Width = 573;
        F->LabelQuestion->AutoSize = true;
    }
    else {
        F->LabelQuestion->WordWrap = false;
    }
    F->LabelQuestion->Left = (int)(F->imgQuestion->Left + (F->imgQuestion->Width - F->LabelQuestion->Width) / 2.);
    F->LabelQuestion->Visible = True;
    F->tmrWaiting->Enabled = True;
    base[F->NumberOfQuestion].Round = '0';
    F->PlayMusic("rr_question.wav");
    // ������� ������ �� �����; ��� ������ ������� � ������� ��������� ���������
}

// -----------------------------------------------------------------------------
/* 2.1. ����� ����� ���� ����������� ������� ������ ��� ������
 (���� ���������, ����� �������) */
void activatedplayers() {
    if ((CurrentHatch != 1) && (F->ingame[0] == true)) {
        F->imgHatch1->Enabled = True;
        F->imgNumber1->Enabled = True;
    }
    if ((CurrentHatch != 2) && (F->ingame[1] == true)) {
        F->imgHatch2->Enabled = True;
        F->imgNumber2->Enabled = True;
    }
    if ((CurrentHatch != 3) && (F->ingame[2] == true)) {
        F->imgHatch3->Enabled = True;
        F->imgNumber3->Enabled = True;
    }
    if ((CurrentHatch != 4) && (F->ingame[3] == true)) {
        F->imgHatch4->Enabled = True;
        F->imgNumber4->Enabled = True;
    }
    if ((CurrentHatch != 5) && (F->ingame[4] == true)) {
        F->imgHatch5->Enabled = True;
        F->imgNumber5->Enabled = True;
    }
}

// -----------------------------------------------------------------------------
void choosenplayer() {
    F->LabelMoney->Caption = F->lblMoney[F->chooseplayer - 1]->Caption;
    F->LabelMoney->Visible = True;
    F->imgTotalPrize->Visible = True;
}

// -----------------------------------------------------------------------------
/* 2.2. ����� ����� ������ ���� ����� (��������� �������) */
void Proverka() {
    if (F->answer == F->RandomPlace) {
        F->ModeOfGame = 4; // ����� ����������
        F->tmrWaiting->Enabled = True;
        F->PlayMusic("rr_true.wav");
    }
    else {
        F->ModeOfGame = 4; // ����� ������������
        F->tmrWaiting->Enabled = True;
        F->LabelMoney->Visible = False;
        F->PlayMusic("rr_false.wav");
    }
}

// -----------------------------------------------------------------------------
void activate_final_hatches() {
    F->imgHatch0->Enabled = True;
    F->imgHatch1->Enabled = True;
    F->imgHatch2->Enabled = True;
    F->imgHatch3->Enabled = True;
    F->imgHatch4->Enabled = True;
    F->imgHatch5->Enabled = True;
    F->imgNumber1->Enabled = True;
    F->imgNumber2->Enabled = True;
    F->imgNumber3->Enabled = True;
    F->imgNumber4->Enabled = True;
    F->imgNumber5->Enabled = True;
}

void deactivate_final_hatches() {
    F->imgHatch0->Enabled = False;
    F->imgHatch1->Enabled = False;
    F->imgHatch2->Enabled = False;
    F->imgHatch3->Enabled = False;
    F->imgHatch4->Enabled = False;
    F->imgHatch5->Enabled = False;
    F->imgNumber1->Enabled = True;
    F->imgNumber2->Enabled = True;
    F->imgNumber3->Enabled = True;
    F->imgNumber4->Enabled = True;
    F->imgNumber5->Enabled = True;
}

// -----------------------------------------------------------------------------
void load_final_question() {
    int Round = F->RoundOfGame;
    unsigned int rndq; // random question

    do {
        rndq = random(qcount);
    }
    while (!(StrToInt(base[rndq].Round) == Round));
    F->LabelQuestion->WordWrap = false;
    F->LabelQuestion->AutoSize = true;
    F->NumberOfQuestion = rndq;
    F->LabelQuestion->Caption = base[F->NumberOfQuestion].Question;
    if (F->LabelQuestion->Width == F->LabelQuestion->Constraints->MaxWidth) {
        F->LabelQuestion->WordWrap = true;
        F->LabelQuestion->AutoSize = false;
        F->LabelQuestion->Width = 573;
        F->LabelQuestion->AutoSize = true;
    }
    else {
        F->LabelQuestion->WordWrap = false;
    }
    F->LabelQuestion->Left = (int)(F->imgQuestion->Left + (F->imgQuestion->Width - F->LabelQuestion->Width) / 2.);
    F->LabelQuestion->Visible = True;
    F->LabelMoney->Visible = true;
    F->imgTotalPrize->Visible = true;
    F->imgPulseBar->Visible = true;
    F->imgTicker->Visible = true;
    base[F->NumberOfQuestion].Round = '0';
}

// -----------------------------------------------------------------------------
UnicodeString myLowerCase(UnicodeString str) {
    str = LowerCase(str);
    for (int i = 1; i < str.Length(); i++) {
        WCHAR ch = str[i];
        switch (ch) {
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;
        case L'�':
            str[i] = L'�';
            break;

        }
    }

    return str;
}

// -----------------------------------------------------------------------------
bool TF::_Parse(UnicodeString ans) {
    ans = Trim(ans);
    ans = myLowerCase(ans);
    UnicodeString trueans[5];
    for (int i = 0; i < 5; i++) {
        trueans[i] = base[F->NumberOfQuestion].Answers[i];
        trueans[i] = myLowerCase(trueans[i]);
    }
    // �������� ������� ��������
    for (int i = 0; i < 5; i++) {
        if (ans == trueans[i]) {
            return (1);
        }
    }
    return (0);
}
// ------------------------------------------
