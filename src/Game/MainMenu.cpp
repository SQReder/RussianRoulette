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
#include "pch.h"
#include "MainMenu.h"
#include "MainForm.h"
#include "fSettings.h"
#include "About.h"
#include "GfxCache.h"
#include "audio.h"
#include "base.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TMenuForm *MenuForm;

// ---------------------------------------------------------------------------
__fastcall TMenuForm::TMenuForm(TComponent *Owner) : TForm(Owner) { }

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::FormCreate(TObject *) {
    Color = clBlack;

    btnNewGame->Caption = "����� ����";
    btnShowSettings->Caption = "���������";
    btnGameRules->Caption = "������� ����";
    btnBblNTuHaxep->Caption = "�����";
    btnAbout->Caption = "About";
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::FormClose(TObject *, TCloseAction &) {
    delete TSettings::Instance();
    Application->Terminate();
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::btnBblNTuHaxepClick(TObject *) {
	memoRules->Visible = false;
	imgRulesBgUp->Visible = false;
	imgRulesBgDown->Visible = false;
	this->GlassFrame->SheetOfGlass = true;
	TCloseAction ca = caFree;
    FormClose(NULL, ca);
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::btnNewGameClick(TObject *) {
	memoRules->Visible = false;
	imgRulesBgUp->Visible = false;
	imgRulesBgDown->Visible = false;
	this->GlassFrame->SheetOfGlass = true;
	const shared_ptr<QuestionBase> base = QuestionBase::Instance();
	base->LoadFromFile(TSettings::Instance()->LastBase);

	// ���������� �������� ��������� � �������� �����
    SaveFormPosition(MenuForm);

    F->Show();
    Hide();
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::btnShowSettingsClick(TObject *) {
	memoRules->Visible = false;
	imgRulesBgUp->Visible = false;
	imgRulesBgDown->Visible = false;
	this->GlassFrame->SheetOfGlass = true;
	SettingsForm->ShowModal();

    LoadFormPosition(MenuForm);
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::btnAboutClick(TObject *) {
	memoRules->Visible = false;
	imgRulesBgUp->Visible = false;
	imgRulesBgDown->Visible = false;
	this->GlassFrame->SheetOfGlass = true;
	AboutForm->ShowModal();
}
// ---------------------------------------------------------------------------

void __fastcall TMenuForm::FormResize(TObject *) {
    static bool lock_form = false;
    if (lock_form) {
        return;
    }

    lock_form = true;
    CoolPositionFix(MenuForm);
    const spacer = 0;

	btnNewGame->Top = spacer;
	btnNewGame->Left = MenuForm->ClientWidth - btnNewGame->ClientWidth - spacer;
	btnNewGame->Transparent = true;

    btnShowSettings->Top = btnNewGame->Top + btnNewGame->ClientHeight + spacer;
	btnShowSettings->Left = MenuForm->ClientWidth - btnShowSettings->ClientWidth - spacer;
	btnShowSettings->Transparent = true;

    btnGameRules->Top = btnShowSettings->Top + btnShowSettings->ClientHeight + spacer;
	btnGameRules->Left = MenuForm->ClientWidth - btnGameRules->ClientWidth - spacer;
	btnGameRules->Transparent = true;

    btnBblNTuHaxep->Top = MenuForm->ClientHeight - btnBblNTuHaxep->ClientHeight - spacer;
	btnBblNTuHaxep->Left = MenuForm->ClientWidth - btnBblNTuHaxep->ClientWidth - spacer;
	btnBblNTuHaxep->Transparent = true;

    Background->Top = int((MenuForm->ClientHeight - Background->Height) / 2);
	Background->Left = int((MenuForm->ClientWidth - Background->Width) / 2);

	memoRules->Top = 150;
	memoRules->Left = 30;
	memoRules->Width = MenuForm->Width - btnGameRules->Width - 130;
	memoRules->Height = MenuForm->Height - 300;
	imgRulesBgUp->Top = 100;
	imgRulesBgUp->Left = memoRules->Left;
	imgRulesBgUp->Width = memoRules->Width;
	imgRulesBgDown->Top = 150 + memoRules->Height;
	imgRulesBgDown->Left = memoRules->Left;
	imgRulesBgDown->Width = memoRules->Width;

    btnAbout->Top = MenuForm->ClientHeight - btnBblNTuHaxep->ClientHeight - btnAbout->ClientHeight - spacer * 2;
	btnAbout->Left = MenuForm->ClientWidth - btnAbout->ClientWidth - spacer;
	btnAbout->Transparent = true;

    lock_form = false;
}
// ---------------------------------------------------------------------------

void __fastcall TMenuForm::FormShow(TObject *) {
    TSettings *Settings = TSettings::Instance();
    MenuForm->Constraints->MinWidth = Settings->MinWidth;
    MenuForm->Constraints->MinHeight = Settings->MinHeight;

	const shared_ptr<GfxCache> gfx = GfxCache::Instance();
	Background->Picture->Assign(gfx->Menu_bg.get());

    LoadFormPosition(MenuForm);
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::FormKeyDown(TObject *, WORD &Key, TShiftState Shift) {
    if (Shift.Contains(ssAlt) && (Key == 13)) {
        SwitchFullscreen(MenuForm);
	} else if (Shift.Empty()) {
        switch (Key) {
        case 'N': btnNewGameClick(NULL);
            break;
        case 27: btnBblNTuHaxepClick(NULL);
			break;
		case 'R':
			btnGameRulesClick(NULL);
			break;
        case 'S': btnShowSettingsClick(NULL);
            break;
        case 'A': btnAboutClick(NULL);
            break;
        }
    }
}
// ---------------------------------------------------------------------------
void __fastcall TMenuForm::btnGameRulesClick(TObject *Sender)
{
	memoRules->Top = 150;
	memoRules->Left = 30;
	memoRules->Width = MenuForm->Width - btnGameRules->Width - 130;
	memoRules->Height = MenuForm->Height - 300;
	imgRulesBgUp->Top = 100;
	imgRulesBgUp->Left = memoRules->Left;
	imgRulesBgUp->Width = memoRules->Width;
	imgRulesBgDown->Top = 150 + memoRules->Height;
	imgRulesBgDown->Left = memoRules->Left;
	imgRulesBgDown->Width = memoRules->Width;
	this->GlassFrame->SheetOfGlass = false;
	LoadRulesText();
	memoRules->Visible = true;
	imgRulesBgUp->Visible = true;
	imgRulesBgDown->Visible = true;
}
//---------------------------------------------------------------------------
void TMenuForm::LoadRulesText() {
	array<const String, 86> rules =
	 { "���� ��� �������� ������� � ����, ������� � ",
	   "������� ���������� ����� ������� ������. (� ������ �����)\r\n\r\n������� ����",
	   " ������� � ��������� ��������� �� ������������ �������� ������������� ����.",
	   "\r\n\r\n������ ��� ���� ����� ���������� � ����� �����������. ",
	   "������ ��� ����� ����� ������ �������� �� ����� � �����, ��� �������� � ",
	   "����� ���������� 1000000 ����������� ������.\r\n\r\n",
	   "= ������� �������� ���� =\r\n\r\n",
	   "����� � ���� ������ ������. � ������ ������� �� ��� ������� � ������� ",
	   "��������� ������� � �������� �������� �������� �������, ������� ��������",
	   " ���������� ���������, ��������� ������ ������. ����� ����� ������ ������ ",
	   "���� ����� ������� �� ������, � ����� ������� ������ ����� ��������� �� ",
	   "��������� 1000 ������ ��� ����, ����� ����, �� ��� ������.\r\n\r\n",
	   "�������� ������� ���� �����: ��������� � ������ �� ������� ����� ����������",
	   " ���� ����� �������, �������� �����������. �����, �������� ��� ������� ������, ",
	   "������ � ������� 20 ������ � ������� ������ ������� ������� ���� ����� �� ������."
	   " �������� ��������� ������� �� ���������� ��������� ������: � �����������",
	   " �� ������, ���������� ��������� ����� ������������� �� 2-� �� 5-�� � �����",
	   " � ���� �������. �����������, �� �������� ������ ���������� ������ ���� ",
	   "������ �����.\r\n\r\n",
	   "���� ����� ��� ������ ����� �� ������, �� �������� �� ���� ���� ",
	   "�������������� � ����� �� 1000 �� 4000 ����������� ������ (������ ����� ",
	   "������� �� ������ ������). ���� �� ���������, �� �� ������ ��� ������������",
	   " ������ (��� ��������� ���������, ������������� ��� �������� ������), � � ",
	   "����� ������ ��� ������� �������� � �������� �������� �������� �������.\r\n\r\n",
	   "� ��������� ����� �����. � ������ ������ ���� ���� ���� �� ��� ����� ",
	   "������, ������ �� ���� ����������� ���� ���������� ������ ����� ����� ",
	   "�������������: � �������� ������ ��� ������ �� ����� ����� ����� ��������"
	   " ������. ���� ����� ��������� ��������� ��� ������� ����������� ",
	   "������������ ������, �� �� ������� � ���� � ����� ����� ���������� ",
	   "��������� ������ ����-�� �� ����������. � ��������� ������ ���������� ",
	   "������� �� �������� �����������, � ����� ��������� �����������.\r\n\r\n",
	   "���� ������� ������ �����������, �� ����� �� ������� �� ����������, �� ",
	   "����� �� ���������� ����� ������ �������� � �������� �������� ",
	   "�������� �������, � ���� �� ��� ���������� ������� ���� ����� ��������� ",
	   "���������. �� � ������, ����� �� �������� ��� ������ ������ (��������� ",
	   "���������� ����� ���������� ���������� �����), ����� �������� �������� � ",
	   "�������� �������, � ���� � ����� ������� ���� �� ���� ���������� �� ",
	   "�������� �������.\r\n\r\n",
	   "���� �� ����� � ���������, ����������� ���� � ���������� ����� ��������, ",
	   "���� �����-���� ������, �� ��� ������� � ������ ����� ����� ����������� ",
	   "��������.\r\n\r\n",
	   "= ������� ���������� ������ =\r\n\r\n",
	   "�����, ������� ���� �������� ����� ���������� �� ���������� ���� ������ ",
	   "�������, ���������� ���������� ����.\r\n\r\n",
	   "������� ������ �������� ������. ��� ��������� ����� ���� ������� �� ��� ",
	   "������, � ������ �� ������� ����� ���������� ������� ������� ������ ",
	   "��������� �� ������ ���������.\r\n\r\n",
	   "� ������ ������� ������ �������� ����� ������������������ ������� ������ ",
	   "�������� � �������� �������� �������� �������, ����� ���������� ",
	   "����������� ������ ����� � ������. ����� ��������� ��������� ����� ������ ",
	   "������� ���� �� ����� �����, ������� �� � �����.\r\n\r\n",
	   "� ���������� ����� ������ ������ ���������� 50000, 100000 ��� 1000000 ",
	   "����������� ������ (������� �� �������� ������ ������). ��������� ������ ",
	   "� ����� ������� ���� �� �����, � � ��������� ����� ���� 10 ������ �� �����.",
	   " �� ��� ����� ���������� ������ ����� � ����������� ���� � ������ ������� ",
	   "Enter.\r\n\r\n",
	   "���� ����� �������� ������, ����� ��������� ����������, � ����� �������� ",
	   "��������� ������� � ���� �� ����. ����� ����� �� ������ ������, ���������� ",
	   "���� � ������� � ���������� ������, ��� �� ������� ��������� ����� � ",
	   "�������� ����. ������, ���� ������ ����� 1000000 ����������� ������, ",
	   "���� ������������� ����� ��.\r\n\r\n",
	   "���� ����� �������� ��������, �� ���, ������ ��� ���� ����� �� ����� ",
	   "��������� �������������. � ������, ���� ����� ��������� �� ��������, �� ",
	   "������ ������� ����� ������ ��� �� ���������, �� ����� ���� ��� ������� ",
	   "����� �������� � �������� ��������. ���� �� ����� �������������, ���� ",
	   "�����������, � ��������� ��������� ���������� ������, ������������ � ",
	   "�������� ����� ����.\r\n\r\n",
	   "���� ����� ��������� �������� � ������ ������ �� ������� ���������� ",
	   "1000000 ����������� ������, �� ������� ������������ �� ���� ��������� � ",
	   "���� �� ���� �������������. ���� ����� ������������� � ������, ���� ",
	   "����� ������ ������ �� ������������� ������ ��� ����������.\r\n\r\n",
	   "= ���������� =\r\n\r\n",
	   "� ������ ������ ����������� ������ �������� �1�, �2�, �3�, �4� � �5� ",
	   "����� ������� ���������, ����������� �� ������. ����� ��� ����� �������, ",
	   "������� �� ���� � �������.\r\n\r\n",
	   "����� �� ������ ����������� �������� ������ �1�, �2�, �3�, �4� ��� �5�, ",
	   "� ������������ � ���������� ������� ������. ����� ����� ����������� ",
	   "������� ����� ������� ���� �� �������� ������.\r\n\r\n",
	   "�������� � ��������, � ����� ���������� �������� ����� ������� �� ������, ",
	   "� ����� �������� ������ �������.\r\n\r\n",
	   "����� ������������� ������� �������� ������ ��� ����������� ���� ",
	   "� ��������� ������, ���������� �������� �� ������ � ��������������� ",
	   "�������� ����� ������� ����.\r\n\r\n",
	   "������������ ����� ������� � ������������� ������� � �������� ���� ",
	   "�������������� �� ������� ��������� ������ �Alt�+�Enter�.\r\n\r\n",
	   "����� �� ���� � ������� �Esc� ��� ��������� �Alt�+�F4�, � ����� ",
	   "������ �� ������ ������ �� �����. �������� ���� ��� ���� ��������."};

	 String all_rules;

	 for (unsigned int i = 0; i < rules.size(); i++) {
		 all_rules += rules[i];
	 }
	 memoRules->Lines->Text = all_rules;
}
