// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainMenu.h"
#include "MainForm.h"
#include "uSettings.h"
#include "About.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TMenuForm* MenuForm;
extern void InitializeSettings();

// ---------------------------------------------------------------------------
__fastcall TMenuForm::TMenuForm(TComponent* Owner) : TForm(Owner) { }

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::FormCreate(TObject* Sender) {
    // MenuVisible = True;
    InitializeSettings();

    MenuForm->Constraints->MinWidth = Settings->MinWidth;
    MenuForm->Constraints->MinHeight = Settings->MinHeight;

    Color = clBlack;

    btnNewGame->Caption = "����� ����";
    btnShowSettings->Caption = "���������";
    btnGameRules->Caption = "������� ����";
    btnBblNTuHaxep->Caption = "�����";
    btnAbout->Caption = "About";
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::FormClose(TObject* Sender, TCloseAction& Action) { exit(0); }

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::_btnBblNTuHaxepClick(TObject* Sender) { exit(0); }

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::btnNewGameClick(TObject* Sender) {
    LoadQuestionFromBase(Settings->LastBase);

    if (!Settings->Fullscreen) {
        Settings->FormsWidth = Width;
        Settings->FormsHeight = Height;
        Settings->FormsTop = Top;
        Settings->FormsLeft = Left;
    }
    F->Show();
    MenuForm->Hide();
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::btnShowSettingsClick(TObject* Sender) {
    SettingsForm->ShowModal();
    if (Settings->Fullscreen) {
        BorderStyle = bsNone;
        Width = Screen->Width;
        Height = Screen->Height;
        Top = 0;
        Left = 0;
    }
    else {
        BorderStyle = bsSizeable;
        Width = Settings->FormsWidth;
        Height = Settings->FormsHeight;
        // Left = F->Sett
    }
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::btnAboutClick(TObject* Sender) { AboutForm->ShowModal(); }
// ---------------------------------------------------------------------------

void __fastcall TMenuForm::FormResize(TObject* Sender) {
    const spacer = 0;

    if (Settings->Fullscreen) {
        BorderStyle = bsNone;
        Width = Screen->Width;
        Height = Screen->Height;
        Top = 0;
        Left = 0;
    }
    else {
        BorderStyle = bsSizeable;
        Width = Settings->FormsWidth;
        Height = Settings->FormsHeight;
        // Left = F->Sett
    }

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

}
// ---------------------------------------------------------------------------

void __fastcall TMenuForm::FormShow(TObject* Sender) {
    MenuForm->Resize();
    // SettingsForm->FileListBox1->Directory = "\Base";
    if (Settings->Fullscreen) {
        BorderStyle = bsNone;
        Width = Screen->Width;
        Height = Screen->Height;
        Top = 0;
        Left = 0;
    }
    else {
        BorderStyle = bsSizeable;
        Width = Settings->FormsWidth;
        Height = Settings->FormsHeight;
        Left = Settings->FormsLeft;
        Top = Settings->FormsTop;
    }
}
// ---------------------------------------------------------------------------

void __fastcall TMenuForm::FormHide(TObject* Sender) {
    if (!Settings->Fullscreen) {
        Settings->FormsWidth = Width;
        Settings->FormsHeight = Height;
        Settings->FormsTop = Top;
        Settings->FormsLeft = Left;
    }
}
// ---------------------------------------------------------------------------
