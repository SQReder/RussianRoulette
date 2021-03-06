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

#include "Splash.h"
#include "MainMenu.h"
#include "MainForm.h"
#include "fSettings.h"
#include "GfxCache.h"
#include "audio.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSplashForm *SplashForm;
bool FatalError = false;

// ---------------------------------------------------------------------------
TStringList *nonExisten;

__fastcall TSplashForm::TSplashForm(TComponent *Owner) : TForm(Owner) { }

// ---------------------------------------------------------------------------
inline void UpdateProgress() {
    SplashForm->PBLoad->Position = SplashForm->PBLoad->Position + 1;
    SplashForm->PBLoad->Update();
    SplashForm->Update();
}

void CheckFile(String filename) {
    UpdateProgress();
    if (!FileExists(filename)) {
        nonExisten->Add(filename);
    }
}

void CheckSystemIntegrity() {
    nonExisten = new TStringList;

    CheckFile("base\\main.dat");

    for (int i = 0; i < 21; i++) {
        CheckFile("data\\" + IntToStr(i) + "sec.png");
    }

    for (int i = 0; i < 12; i++) {
        CheckFile("data\\�����_" + IntToStr(i) + ".png");
    }

    for (int i = 1; i < 57; i++) {
        CheckFile("data\\pulse\\pulse_" + IntToStr(i) + ".png");
    }

    for (int i = 1; i < 5; i++) {
        CheckFile("data\\splash-" + IntToStr(i) + ".png");
    }

	CheckFile("data\\final.png");
	CheckFile("data\\red.png");
	CheckFile("data\\base.png");
	CheckFile("data\\blue.png");
	CheckFile("data\\white.png");
	CheckFile("data\\black.png");
	CheckFile("data\\place.png");
	CheckFile("data\\place_red_zero.png");
	CheckFile("data\\menu_bg.jpg");

	CheckFile("sounds\\question_clear.ogg");
	CheckFile("sounds\\rr_20sec.ogg");
	CheckFile("sounds\\rr_bg2.ogg");
	CheckFile("sounds\\rr_bg3.ogg");
	CheckFile("sounds\\rr_bg4.ogg");
	CheckFile("sounds\\rr_choosen.ogg");
	CheckFile("sounds\\rr_closing.ogg");
	CheckFile("sounds\\rr_endround.ogg");
	CheckFile("sounds\\rr_fall.ogg");
	CheckFile("sounds\\rr_fall_with_host.ogg");
	CheckFile("sounds\\rr_false.ogg");
	CheckFile("sounds\\rr_final.ogg");
	CheckFile("sounds\\rr_intro_Take_2.ogg");
	CheckFile("sounds\\rr_intro.ogg");
	CheckFile("sounds\\rr_mexclose.ogg");
	CheckFile("sounds\\rr_mexopen.ogg");
	CheckFile("sounds\\rr_money.ogg");
	CheckFile("sounds\\rr_openhole.ogg");
	CheckFile("sounds\\rr_openround.ogg");
	CheckFile("sounds\\rr_players.ogg");
	CheckFile("sounds\\rr_question.ogg");
	CheckFile("sounds\\rr_round.ogg");
	CheckFile("sounds\\rr_save.ogg");
	CheckFile("sounds\\rr_true.ogg");

	if (nonExisten->Count > 0) {
		FatalError = true;
		nonExisten->SaveToFile("nonExistent.txt");
		MessageDlg("�����! ��������� ������, ����������� ��� ������� ����, ��� �� ����� ������.\n"
			"����������� � ����� nonExistent.txt", mtError, TMsgDlgButtons() << mbOK, 0);
		Application->Terminate();
	}

	nonExisten->Free();
}

void ShowState(String state) { SplashForm->lblLoadState->Caption = state; }

// ---------------------------------------------------------------------------
void Loader() {
    SplashForm->PBLoad->Max = 133;

    ShowState("�������� �������� �����");
    CheckSystemIntegrity();
	UpdateProgress();

	ShowState("�������� �������");
	GfxCache::Instance();
	UpdateProgress();

	ShowState("�������� �����");
	init_audio(Application->Handle);
	UpdateProgress();

	ShowState("�������� �������� �����");
	TSettings::Instance()->LoadFromFile(".\\settings.cfg");
	UpdateProgress();

	ShowState("�������� ���������!");
	SplashForm->tmrSplash->Enabled = true;
}

// ---------------------------------------------------------------------------
int CountDown = 0;

void __fastcall TSplashForm::tmrSplashTimer(TObject *) {
    if (CountDown-- || FatalError) {
        tmrSplash->Enabled = false;
        MenuForm->Show();
        imgSplash->Free();
        tmrSplash->Enabled = false;
        SplashForm->Hide();
    }
}

// ---------------------------------------------------------------------------
void __fastcall TSplashForm::tmrOpenSplashTimer(TObject *) {
    SplashForm->AlphaBlendValue += 15;
    if (SplashForm->AlphaBlendValue >= 255) {
        tmrOpenSplash->Enabled = false;
        Loader();
    }
}
// ---------------------------------------------------------------------------
