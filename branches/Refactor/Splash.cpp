// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Splash.h"
#include "MainMenu.h"
#include "MainForm.h"
#include "inifiles.hpp"
#include "classes.hpp"
#include <windows.h>
#include "uSettings.h"
#include "GfxCache.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSplashForm* SplashForm;
bool FatalError = false;

// ---------------------------------------------------------------------------
TStringList* nonExisten;

__fastcall TSplashForm::TSplashForm(TComponent* Owner) : TForm(Owner) { }
// ---------------------------------------------------------------------------

void CheckFile(UnicodeString filename) {
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

    for (int i = 0; i < 16; i++) {
        CheckFile("data\\рычаг_" + IntToStr(i) + ".png");
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

    CheckFile("sounds\\question_clear.wav");
    CheckFile("sounds\\rr_20sec.wav");
    CheckFile("sounds\\rr_bg2.wav");
    CheckFile("sounds\\rr_bg3.wav");
    CheckFile("sounds\\rr_bg4.wav");
    CheckFile("sounds\\rr_choosen.wav");
    CheckFile("sounds\\rr_closing.wav");
    CheckFile("sounds\\rr_endround.wav");
    CheckFile("sounds\\rr_fall.wav");
    CheckFile("sounds\\rr_fall_with_host.wav");
    CheckFile("sounds\\rr_false.wav");
    CheckFile("sounds\\rr_final.wav");
    CheckFile("sounds\\rr_intro Take 2.wav");
    CheckFile("sounds\\rr_intro.wav");
    CheckFile("sounds\\rr_mexclose.wav");
    CheckFile("sounds\\rr_mexopen.wav");
    CheckFile("sounds\\rr_money.wav");
    CheckFile("sounds\\rr_openhole.wav");
    CheckFile("sounds\\rr_openround.wav");
    CheckFile("sounds\\rr_players.wav");
    CheckFile("sounds\\rr_question.wav");
    CheckFile("sounds\\rr_round.wav");
    CheckFile("sounds\\rr_save.wav");
    CheckFile("sounds\\rr_true.wav");

    if (nonExisten->Count > 0) {
        FatalError = true;
        nonExisten->SaveToFile("nonExistent.txt");
        MessageDlg(
            "ЕГГОГ! Некоторых файлов, необходимых для запуска игры, нет на своих местах. Подробности в файле nonExistent.txt",
            mtError, TMsgDlgButtons() << mbOK, 0);
        std::exit(1);
    }

    nonExisten->Free();
}

// ---------------------------------------------------------------------------
inline void UpdPB() {
    SplashForm->PBLoad->Position = SplashForm->PBLoad->Position + 1;
    SplashForm->Update();
}

void Loader() {
    SplashForm->PBLoad->Max = 3;

    CheckSystemIntegrity();
    UpdPB();
    Settings = new TSettings(ExtractFilePath(Application->ExeName) + "\settings.cfg");
    UpdPB();
    gfx = new sGfxCache;
    UpdPB();

    SplashForm->PBLoad->Visible = false;
    SplashForm->tmrSplash->Enabled = True;
}

// ---------------------------------------------------------------------------

#define BUFSIZE 80

BOOL OSIsWin7() {
    OSVERSIONINFOEX osvi;
    BOOL bOsVersionInfoEx;

    // Пытаемся вызвать GetVersionEx используя структуру OSVERSIONINFOEX.
    // В случае ошибки пытаемся проделать тоже самое со структурой OSVERSIONINFO.

    ZeroMemory(& osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

    if (!GetVersionEx((OSVERSIONINFO *) &osvi)) {
        // Если OSVERSIONINFOEX не работает, то используем OSVERSIONINFO.
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
        if (!GetVersionEx((OSVERSIONINFO *) &osvi)) {
            return FALSE;
        }
    }

    // ShowMessage(IntToStr((int)osvi.dwMajorVersion));
    if (osvi.dwMajorVersion >= 6) {
        return true;
    }

    return false;
}

// ---------------------------------------------------------------------------
void __fastcall TSplashForm::FormCreate(TObject* Sender) {
    Width = 800;
    Height = 600;

    if (OSIsWin7()) {
        BorderStyle = bsToolWindow;
        imgSplash->Top -= 25;
    } else {
        BorderStyle = bsNone;
        Color = clBlack;
    };

    imgSplash->Top = (SplashForm->Height - imgSplash->Height) / 2;
    imgSplash->Left = (SplashForm->Width - imgSplash->Width) / 2;
}

// ---------------------------------------------------------------------------
void __fastcall TSplashForm::FormClick(TObject* Sender) {
    tmrSplash->Enabled = False;
    MenuForm->Show();
    imgSplash->Free();
    tmrSplash->Enabled = False;
    SplashForm->Hide();
}
// ---------------------------------------------------------------------------
int CountDown = 2;

void __fastcall TSplashForm::tmrSplashTimer(TObject* Sender) {
    if (CountDown-- || FatalError) {
        SplashForm->Click();
    }
}

// ---------------------------------------------------------------------------
void __fastcall TSplashForm::imgSplashClick(TObject* Sender) { SplashForm->Click(); }

// ---------------------------------------------------------------------------
void __fastcall TSplashForm::tmrOpenSplashTimer(TObject* Sender) {
    SplashForm->AlphaBlendValue += 15;
    if (SplashForm->AlphaBlendValue >= 255) {
        tmrOpenSplash->Enabled = False;
        Loader();
    }
}
// ---------------------------------------------------------------------------
