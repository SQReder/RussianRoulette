// ---------------------------------------------------------------------------

#pragma hdrstop
#include "GameLogic.h"
#include "MainForm.h"
#include "Hatches.h"
#include "base.h"
// ---------------------------------------------------------------------------

#pragma package(smart_init)
int CurrentHatch;
extern int RoundOfGame;

// -----------------------------------------------------------------------------
/* 1. Здесь нужно временно отключить форму вопроса и labels... */
void switchoffquestion() {
    F->imgQuestion->Visible = False;
    F->LabelMoney->Visible = False;
    F->LabelQuestion->Visible = False;
}

// -----------------------------------------------------------------------------
/* 2. После того, как отработает таймер выбора игрока,
 отобразить их; включить звук */
// -----------------------------------------------------------------------------
void switchonquestion() {
    F->imgQuestion->Visible = True;
    F->imgBorder->Visible = True;
}
// -----------------------------------------------------------------------------

void showquestion() {
    unsigned int rndq; // random question

    do {
        rndq = random(qcount);
    }
    while (!(StrToInt(base[rndq].Round) == RoundOfGame));

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
    } else {
        F->LabelQuestion->WordWrap = false;
    }

    F->LabelQuestion->Left = (int)(F->imgQuestion->Left + (F->imgQuestion->Width - F->LabelQuestion->Width) / 2.);
    F->LabelQuestion->Visible = True;
    F->tmrWaiting->Enabled = True;
    base[F->NumberOfQuestion].Round = '0';
    F->PlayMusic("rr_question.wav");
    // считать вопрос из файла; для начала заранее с помощью отдельной программы
}

// -----------------------------------------------------------------------------
/* 2.1. После этого дать возможность выбрать игрока для ответа
 (если компьютер, выбор случаен) */
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
void choosenplayer(int chooseplayer) {
    F->LabelMoney->Caption = F->lblMoney[chooseplayer - 1]->Caption;
    F->LabelMoney->Visible = True;
    F->imgTotalPrize->Visible = True;
}

// -----------------------------------------------------------------------------
/* 2.2. Затем игрок должен дать ответ (обработка клавиши) */
void Proverka() {
    F->PlayMusic(F->answer == F->RandomPlace ? "rr_true.wav" : "rr_false.wav");
    F->LabelMoney->Visible = False;
    F->tmrWaiting->Enabled = true;
}

// -----------------------------------------------------------------------------
void hatches_enable_state(bool state) {
    F->imgHatch0->Enabled = state;
    F->imgHatch1->Enabled = state;
    F->imgHatch2->Enabled = state;
    F->imgHatch3->Enabled = state;
    F->imgHatch4->Enabled = state;
    F->imgHatch5->Enabled = state;
    F->imgNumber1->Enabled = state;
    F->imgNumber2->Enabled = state;
    F->imgNumber3->Enabled = state;
    F->imgNumber4->Enabled = state;
    F->imgNumber5->Enabled = state;
}

// -----------------------------------------------------------------------------
void load_final_question() {
    unsigned int rndq; // random question

    do {
        rndq = random(qcount);
    }
    while (!(StrToInt(base[rndq].Round) == RoundOfGame));

    F->LabelQuestion->WordWrap = false;
    F->LabelQuestion->AutoSize = true;
    F->NumberOfQuestion = rndq;
    F->LabelQuestion->Caption = base[F->NumberOfQuestion].Question;

    if (F->LabelQuestion->Width == F->LabelQuestion->Constraints->MaxWidth) {
        F->LabelQuestion->WordWrap = true;
        F->LabelQuestion->AutoSize = false;
        F->LabelQuestion->Width = 573;
        F->LabelQuestion->AutoSize = true;
    } else {
        F->LabelQuestion->WordWrap = false;
    }

    F->LabelQuestion->Left = F->imgQuestion->Left + (int)(F->imgQuestion->Width - F->LabelQuestion->Width) / 2.;
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
        case L'А':
            str[i] = L'а';
            break;
        case L'Б':
            str[i] = L'б';
            break;
        case L'В':
            str[i] = L'в';
            break;
        case L'Г':
            str[i] = L'г';
            break;
        case L'Д':
            str[i] = L'д';
            break;
        case L'Е':
            str[i] = L'е';
            break;
        case L'Ё':
            str[i] = L'ё';
            break;
        case L'Ж':
            str[i] = L'ж';
            break;
        case L'З':
            str[i] = L'з';
            break;
        case L'И':
            str[i] = L'и';
            break;
        case L'Й':
            str[i] = L'й';
            break;
        case L'К':
            str[i] = L'к';
            break;
        case L'Л':
            str[i] = L'л';
            break;
        case L'М':
            str[i] = L'м';
            break;
        case L'Н':
            str[i] = L'н';
            break;
        case L'О':
            str[i] = L'о';
            break;
        case L'П':
            str[i] = L'п';
            break;
        case L'Р':
            str[i] = L'р';
            break;
        case L'С':
            str[i] = L'с';
            break;
        case L'Т':
            str[i] = L'т';
            break;
        case L'У':
            str[i] = L'у';
            break;
        case L'Ф':
            str[i] = L'ф';
            break;
        case L'Х':
            str[i] = L'х';
            break;
        case L'Ц':
            str[i] = L'ц';
            break;
        case L'Ч':
            str[i] = L'ч';
            break;
        case L'Ш':
            str[i] = L'ш';
            break;
        case L'Щ':
            str[i] = L'щ';
            break;
        case L'Ъ':
            str[i] = L'ъ';
            break;
        case L'Ы':
            str[i] = L'ы';
            break;
        case L'Ь':
            str[i] = L'ь';
            break;
        case L'Э':
            str[i] = L'э';
            break;
        case L'Ю':
            str[i] = L'ю';
            break;
        case L'Я':
            str[i] = L'я';
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
    // удаление двойных пробелов
    for (int i = 0; i < 5; i++) {
        if (ans == trueans[i]) {
            return true;
        }
    }
    return false;
}
// ------------------------------------------
