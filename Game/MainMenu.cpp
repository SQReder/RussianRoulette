// ---------------------------------------------------------------------------
// Russian Roulette is PC version of popular television game show.
// Copyright (C) 2010-2012 Popovskiy Andrey
// Copyright (C) 2010-2012 Boytsov Sergey

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
#include "pch.h"
#include "MainMenu.h"
#include "MainForm.h"
#include "fSettings.h"
#include "About.h"
#include "GfxCache.h"
#include "audio.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TMenuForm *MenuForm;

// ---------------------------------------------------------------------------
__fastcall TMenuForm::TMenuForm(TComponent *Owner) : TForm(Owner) { }

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::FormCreate(TObject *Sender) {
    Color = clBlack;

    btnNewGame->Caption = "����� ����";
    btnShowSettings->Caption = "���������";
    btnGameRules->Caption = "������� ����";
    btnBblNTuHaxep->Caption = "�����";
    btnAbout->Caption = "About";
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::FormClose(TObject *Sender, TCloseAction &Action) {
    delete TSettings::Instance();
    delete gfx;
    Application->Terminate();
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::btnBblNTuHaxepClick(TObject *Sender) {
    TCloseAction ca = caFree;
    FormClose(NULL, ca);
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::btnNewGameClick(TObject *Sender) {
    LoadQuestionFromBase(TSettings::Instance()->LastBase);

    // ���������� �������� ��������� � �������� �����
    SaveFormPosition(MenuForm);

    F->Show();
    Hide();
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::btnShowSettingsClick(TObject *Sender) {
    SettingsForm->ShowModal();

    LoadFormPosition(MenuForm);
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::btnAboutClick(TObject *Sender) { AboutForm->ShowModal(); }
// ---------------------------------------------------------------------------

void __fastcall TMenuForm::FormResize(TObject *Sender) {
    static bool lock_form = false;
    if (lock_form) {
        return;
    }

    lock_form = true;
    CoolPositionFix(MenuForm);
    const spacer = 0;

    btnNewGame->Top = spacer;
    btnNewGame->Left = MenuForm->ClientWidth - btnNewGame->ClientWidth - spacer;

    btnShowSettings->Top = btnNewGame->Top + btnNewGame->ClientHeight + spacer;
    btnShowSettings->Left = MenuForm->ClientWidth - btnShowSettings->ClientWidth - spacer;

    btnGameRules->Top = btnShowSettings->Top + btnShowSettings->ClientHeight + spacer;
    btnGameRules->Left = MenuForm->ClientWidth - btnGameRules->ClientWidth - spacer;

    btnBblNTuHaxep->Top = MenuForm->ClientHeight - btnBblNTuHaxep->ClientHeight - spacer;
    btnBblNTuHaxep->Left = MenuForm->ClientWidth - btnBblNTuHaxep->ClientWidth - spacer;

    Background->Top = int((MenuForm->ClientHeight - Background->Height) / 2);
    Background->Left = int((MenuForm->ClientWidth - Background->Width) / 2);

    btnAbout->Top = MenuForm->ClientHeight - btnBblNTuHaxep->ClientHeight - btnAbout->ClientHeight - spacer * 2;
    btnAbout->Left = MenuForm->ClientWidth - btnAbout->ClientWidth - spacer;

    lock_form = false;
}
// ---------------------------------------------------------------------------

void __fastcall TMenuForm::FormShow(TObject *Sender) {
    TSettings *Settings = TSettings::Instance();
    MenuForm->Constraints->MinWidth = Settings->MinWidth;
    MenuForm->Constraints->MinHeight = Settings->MinHeight;

    Background->Picture->Assign(gfx->Menu_bg);

    LoadFormPosition(MenuForm);
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift) {
    if (Shift.Contains(ssAlt) && (Key == 13)) {
        SwitchFullscreen(MenuForm);
    } else if (Shift.Empty()) {
        switch (Key) {
        case 'N': btnNewGameClick(NULL);
            break;
        case 27: btnBblNTuHaxepClick(NULL);
            break;
        case 'S': btnShowSettingsClick(NULL);
            break;
        case 'A': btnAboutClick(NULL);
            break;
        }
    }
}

// ---------------------------------------------------------------------------