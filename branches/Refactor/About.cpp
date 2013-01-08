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
#include "About.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutForm *AboutForm;

// ---------------------------------------------------------------------------
__fastcall TAboutForm::TAboutForm(TComponent *Owner) : TForm(Owner) { }

// ---------------------------------------------------------------------------
typedef enum {
    r, l
} align;

const int padding = 4;
const int main_offcet = 8;
const int tiny_offcet = 2;

TLabel *new_label(String caption, int top, align al, bool bold = false) {
    TLabel *lbl = new TLabel(AboutForm);
    lbl->Parent = AboutForm;

    lbl->Caption = caption;
    lbl->Font->Charset = RUSSIAN_CHARSET;
    lbl->Font->Size = 10;
    lbl->Font->Color = clWhite;
    lbl->Font->Name = "Verdana";
    lbl->Font->Style = (TFontStyles)(bold ? 1 : 0);

    lbl->AutoSize = true;

    lbl->Top = top;
    lbl->Left = (al == l) ? padding : (AboutForm->ClientWidth - lbl->Width - padding);

    return lbl;
}

const char *licence =
    "Russian Roulette это PC версия популярного телешоу.\nCopyright © 2010-2012 Popovskiy Andrey\n" "Copyright © 2010-2012 Boytsov Sergey\n\nЭто свободная программа; вы можете повторно рас-\n"
    "пространять её и/или модифицировать её в соответ-\nствии с Стандартной Общественной Лицензий GNU,\n" "опубликованной Фондом Свободного ПО; либо вер-\nсии 3, либо (по вашему выбору) любой более позд-\n"
    "ней версии.\n\n" "Эта программа распространяется в надежде, что\n"
    "она будет полезной, но БЕЗ КАКИХ-ЛИБО ГАРАНТИЙ;\nдаже без подразумеваемых гарантий КОММЕРЧЕ-\n" "СКОЙ ЦЕННОСТИ или ПРИГОДНОСТИ ДЛЯ\nКОНКРЕТНОЙ ЦЕЛИ. Для получения подробных\n"
    "сведений смотрите Стандартную Общественную\nЛицензию GNU.\n\n" "Вы должны были получить копию Стандартной Об-\nщественной Лицензии GNU вместе с этой програм-\n"
    "мой; если нет,смотрите\n" "                            http://www.gnu.org/licenses/";

// People who works with project
String sversion = "1.5 alpha";

#define dev_count 2
const char *sdevelopers[dev_count] = {
    "Сергей Бойцов",
    "Андрей Поповский"
};

String scomposer = "Сергей Чекрыжов";

#define tnx_count 6
const char *sthank_list[tnx_count] = {
    "Денису Колобаеву",
    "Павлу Кашлакову",
    "Ирине Матысик",
    "Марку-Юлиусу Пикату",
    "Михаилу Григорчуку",
    "и многим-многим другим"
};

#define qautors_count 6
const char *squestions_by[qautors_count] = {
    "Сергей Бойцов",
    "Андрей Поповский",
    "Владимир Крупин",
    "Артур Асаёнок",
    "Артём Горячев",
    "Денис Долгоруков"
};
// end people list

std::vector <TLabel *> lbl_dev, lbl_tnx, lbl_qa;
TLabel *lblversion;
TLabel *lbldev;
TLabel *lblcomposer, *lblcompo, *tnx_title, *qa_title;
TLabel *mLicence;

void __fastcall TAboutForm::FormCreate(TObject *Sender) {
    AboutForm->Hide();
    GlassFrame->Enabled = true;

    lblversion = new_label("Версия игры: " + sversion, lblProjTitle->Top + lblProjTitle->Height + main_offcet, l, true);
    lbldev = new_label("Разработчики:", lblversion->Top + lblversion->Height + main_offcet, l, true);

    int offcet = lbldev->Top;
    for (int i = 0; i < dev_count; ++i) {
        lbl_dev.push_back(new_label(sdevelopers[i], offcet, r));
        offcet += lbl_dev[i]->Height;
    }

    lblcompo = new_label("Композитор:", lbl_dev[lbl_dev.size() - 1]->Top + lbl_dev[lbl_dev.size() - 1]->Height +
        main_offcet, l, true);
    lblcomposer = new_label(scomposer, lblcompo->Top, r);

    tnx_title = new_label("Наши благодарности:", lblcompo->Top + lblcompo->Height + main_offcet, l, true);

    offcet = tnx_title->Top;
    for (int i = 0; i < tnx_count; ++i) {
        lbl_tnx.push_back(new_label(sthank_list[i], offcet, r));
        offcet += lbl_tnx[i]->Height;
    }

    qa_title = new_label("Авторы вопросов:", lbl_tnx[lbl_tnx.size() - 1]->Top + lbl_tnx[lbl_tnx.size() - 1]->Height +
        main_offcet, l, true);

    offcet = qa_title->Top;
    for (int i = 0; i < qautors_count; ++i) {
        lbl_qa.push_back(new_label(squestions_by[i], offcet, r));
        offcet += lbl_qa[i]->Height;
    }

    mLicence = new_label(licence, 0, r);
    mLicence->Align = alClient;
    mLicence->AlignWithMargins = true;
    mLicence->Visible = false;
    mLicence->BringToFront();
}

// ---------------------------------------------------------------------------
void __fastcall TAboutForm::lblLicenceClick(TObject *Sender) {
    mLicence->Visible = !mLicence->Visible;

    lblversion->Visible = !lblversion->Visible;
    lbldev->Visible = !lbldev->Visible;
    lblcomposer->Visible = !lblcomposer->Visible;
    lblcompo->Visible = !lblcompo->Visible;
    tnx_title->Visible = !tnx_title->Visible;
    qa_title->Visible = !qa_title->Visible;

    for (int i = 0; i < dev_count; ++i) {
        lbl_dev[i]->Visible = !lbl_dev[i]->Visible;
    }
    for (int i = 0; i < tnx_count; ++i) {
        lbl_tnx[i]->Visible = !lbl_tnx[i]->Visible;
    }
    for (int i = 0; i < qautors_count; ++i) {
        lbl_qa[i]->Visible = !lbl_qa[i]->Visible;
    }

}

// ---------------------------------------------------------------------------
void __fastcall TAboutForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift) {
    if (Shift.Empty()) {
        if (Key == 32) {
            lblLicenceClick(NULL);
        } else if (Key == 27) {
            AboutForm->Close();
        }
    }
}

// ---------------------------------------------------------------------------
