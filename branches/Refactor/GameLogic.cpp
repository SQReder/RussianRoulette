// ---------------------------------------------------------------------------

#pragma hdrstop

#include "GameLogic.h"
#include "MainForm.h"
#include "Hatches.h"
#include "base.h"
// ---------------------------------------------------------------------------

#pragma package(smart_init)
int CurrentHatch;

/* 0. Временно отключаем возможность выбрать люк... */
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
/* 1. Здесь нужно временно отключить форму вопроса и labels... */
void switchoffquestion() {
    F->LabelMoney->Visible = False;
    F->LabelQuestion->Visible = False;
    F->imgQuestion->Visible = False;
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
void choosenplayer() {
    F->LabelMoney->Caption = F->lblMoney[F->chooseplayer - 1]->Caption;
    F->LabelMoney->Visible = True;
    F->imgTotalPrize->Visible = True;
}

// -----------------------------------------------------------------------------
/* 2.2. Затем игрок должен дать ответ (обработка клавиши) */
void Proverka() {
    if (F->answer == F->RandomPlace) {
        F->ModeOfGame = 4; // ответ правильный
        F->tmrWaiting->Enabled = True;
        F->PlayMusic("rr_true.wav");
    }
    else {
        F->ModeOfGame = 4; // ответ неправильный
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
            return (1);
        }
    }
    return (0);
}
// ------------------------------------------
