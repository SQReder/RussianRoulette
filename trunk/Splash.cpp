// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Splash.h"
#include "MainMenu.h"
#include "MainForm.h"
#include "inifiles.hpp"
#include "classes.hpp"
#include <windows.h>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSplashForm* SplashForm;
bool FatalError = false;
// ---------------------------------------------------------------------------
void CheckSystemIntegrity() {
    TStringList* nonExisten = new TStringList;

    if (!FileExists("base\\main.dat"))
        nonExisten->Add("base\\main.dat");

    for (int i = 0; i < 21; i++) {
        if (!FileExists("data\\" + IntToStr(i) + "sec.png"))
            nonExisten->Add("data\\" + IntToStr(i) + "sec.png");
    }

    for (int i = 1; i < 17; i++) {
        if (!FileExists("data\\рычаг_" + IntToStr(i) + ".png"))
            nonExisten->Add("data\\рычаг_" + IntToStr(i) + ".png");
    }

    for (int i = 1; i < 57; i++) {
        if (!FileExists("data\\pulse\\pulse_" + IntToStr(i) + ".png"))
            nonExisten->Add("data\\pulse\\pulse_" + IntToStr(i) + ".png");
    }

    for (int i = 1; i < 5; i++) {
        if (!FileExists("data\\splash-" + IntToStr(i) + ".png"))
            nonExisten->Add("data\\splash-" + IntToStr(i) + ".png");
    }
    if (!FileExists("data\\final.png"))
        nonExisten->Add("data\\base.png");

    if (!FileExists("data\\red.png"))
        nonExisten->Add("data\\red.png");
    if (!FileExists("data\\base.png"))
        nonExisten->Add("data\\base.png");
    if (!FileExists("data\\blue.png"))
        nonExisten->Add("data\\blue.png");
    if (!FileExists("data\\white.png"))
        nonExisten->Add("data\\white.png");
    if (!FileExists("data\\black.png"))
        nonExisten->Add("data\\black.png");

    if (!FileExists("data\\place.png"))
        nonExisten->Add("data\\place.png");
    if (!FileExists("data\\place_red_zero.png"))
        nonExisten->Add("data\\place_red_zero.png");

    if (!FileExists("sounds\\question_clear.wav"))
        nonExisten->Add("sounds\\question_clear.wav");
    if (!FileExists("sounds\\rr_20sec.wav"))
        nonExisten->Add("sounds\\rr_20sec.wav");
    if (!FileExists("sounds\\rr_bg2.wav"))
        nonExisten->Add("sounds\\rr_bg2.wav");
    if (!FileExists("sounds\\rr_bg3.wav"))
        nonExisten->Add("sounds\\rr_bg3.wav");
    if (!FileExists("sounds\\rr_bg4.wav"))
        nonExisten->Add("sounds\\rr_bg4.wav");
    if (!FileExists("sounds\\rr_choosen.wav"))
        nonExisten->Add("sounds\\rr_choosen.wav");
    if (!FileExists("sounds\\rr_closing.wav"))
        nonExisten->Add("sounds\\rr_closing.wav");
    if (!FileExists("sounds\\rr_endround.wav"))
        nonExisten->Add("sounds\\rr_endround.wav");
    if (!FileExists("sounds\\rr_fall.wav"))
        nonExisten->Add("sounds\\rr_fall.wav");
    if (!FileExists("sounds\\rr_fall_with_host.wav"))
        nonExisten->Add("sounds\\rr_fall_with_host.wav");
    if (!FileExists("sounds\\rr_false.wav"))
        nonExisten->Add("sounds\\rr_false.wav");
    if (!FileExists("sounds\\rr_final.wav"))
        nonExisten->Add("sounds\\rr_final.wav");
    if (!FileExists("sounds\\rr_intro Take 2.wav"))
        nonExisten->Add("sounds\\rr_intro Take 2.wav");
    if (!FileExists("sounds\\rr_intro.wav"))
        nonExisten->Add("sounds\\rr_intro.wav");
    if (!FileExists("sounds\\rr_mexclose.wav"))
        nonExisten->Add("sounds\\rr_mexclose.wav");
    if (!FileExists("sounds\\rr_mexopen.wav"))
        nonExisten->Add("sounds\\rr_mexopen.wav");
    if (!FileExists("sounds\\rr_money.wav"))
        nonExisten->Add("sounds\\rr_money.wav");
    if (!FileExists("sounds\\rr_openhole.wav"))
        nonExisten->Add("sounds\\rr_openhole.wav");
    if (!FileExists("sounds\\rr_openround.wav"))
        nonExisten->Add("sounds\\rr_openround.wav");
    if (!FileExists("sounds\\rr_players.wav"))
        nonExisten->Add("sounds\\rr_players.wav");
    if (!FileExists("sounds\\rr_question.wav"))
        nonExisten->Add("sounds\\rr_question.wav");
    if (!FileExists("sounds\\rr_round.wav"))
        nonExisten->Add("sounds\\rr_round.wav");
    if (!FileExists("sounds\\rr_save.wav"))
        nonExisten->Add("sounds\\rr_save.wav");
    if (!FileExists("sounds\\rr_true.wav"))
        nonExisten->Add("sounds\\rr_true.wav");

    if (nonExisten->Count > 0) {
        FatalError = true;
        nonExisten->SaveToFile("nonExistent.txt");
        MessageDlg(
            "ЕГГОГ! Некоторых файлов, необходимых для запуска игры нет на своих местах. Подробности в файле nonExistent.txt",
            mtError, TMsgDlgButtons() << mbOK, 0);
        std::exit(1);
    }
}
// ---------------------------------------------------------------------------
__fastcall TSplashForm::TSplashForm(TComponent* Owner): TForm(Owner) {CheckSystemIntegrity();}

#define BUFSIZE 80

BOOL OSIsWin7() {
    OSVERSIONINFOEX osvi;
    BOOL bOsVersionInfoEx;

    // Пытаемся вызвать GetVersionEx используя структуру OSVERSIONINFOEX.
    // В случае ошибки пытаемся проделать тоже самое со структурой OSVERSIONINFO.

    ZeroMemory(& osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

    if (!(bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO *) &osvi))) {
        // Если OSVERSIONINFOEX не работает, то используем OSVERSIONINFO.
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
        if (!GetVersionEx((OSVERSIONINFO*)& osvi))
            return FALSE;
    }

    // ShowMessage(IntToStr((int)osvi.dwMajorVersion));
    if (osvi.dwMajorVersion >= 6)
        return True;

    return 0;
}
// ---------------------------------------------------------------------------
void __fastcall TSplashForm::FormCreate(TObject* Sender) {
    Width = 800;
    Height = 600;
    FormStyle = fsStayOnTop;

    imgSplash->Top = (SplashForm->Height - imgSplash->Height) / 2;
    imgSplash->Left = (SplashForm->Width - imgSplash->Width) / 2;

    if (OSIsWin7()) {
        BorderStyle = bsToolWindow;
        imgSplash->Top -= 25;
    } else {
        BorderStyle = bsNone;
        Color = clBlack;
    } ;
}

// ---------------------------------------------------------------------------
void __fastcall TSplashForm::FormClick(TObject* Sender) {
    tmrSplash->Enabled = False;
    // if (!MenuForm->MenuVisible) {
    MenuForm->Show();
    // }
    imgSplash->Free();
    tmrSplash->Enabled = False;
    SplashForm->Hide();
}
// ---------------------------------------------------------------------------
int CountDown = 2;

void __fastcall TSplashForm::tmrSplashTimer(TObject* Sender) {
    if (CountDown-- || FatalError)
        SplashForm->Click();
}

// ---------------------------------------------------------------------------
void __fastcall TSplashForm::imgSplashClick(TObject* Sender) {SplashForm->Click();}

// ---------------------------------------------------------------------------
void __fastcall TSplashForm::tmrOpenSplashTimer(TObject* Sender) {
    SplashForm->AlphaBlendValue += 15;
    if (SplashForm->AlphaBlendValue >= 255) {
        tmrOpenSplash->Enabled = False;
        tmrSplash->Enabled = True;
    }
}
// ---------------------------------------------------------------------------
