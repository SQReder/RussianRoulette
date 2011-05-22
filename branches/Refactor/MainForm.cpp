// ---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "MainForm.h"
#include "mainmenu.h"
#include "Hatches.h"
#include "GameLogic.h"
#include "Splash.h"
#include "inifiles.hpp"
#include "AI.h"
#include "uSettings.h"
#include "uHostMode.h"
#include "base.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TeeFilters"
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"
#define _StartRotaingSpeed 50

TF* F;
int MechanizmOn = 0;
int SpeedOfRotation = _StartRotaingSpeed;
bool SoundOn = true;
int TimeOfQuestion; // �����, ������ �� ����� ������
int MoneyTransferMode = 0; // ����� ���������� ����� (1 - 1-��� ������, 2 - 2-��� � �.�.; a - ����)
int ModeOfGame; // ����� ���� (���������� ������� �������� � GameLogic � tmrWaiting)
int ModeOfFinalGame; // ����� ��������� ���� (���. ������� �������� � tmrWaitingFinal)
bool TransferAll = 1; // ����� ���������� ����� ���� �������
int WaitForFate; // ����������, ������������ ����� �������� "������� ������" (������ ��� ���)
bool CanAnswer = 0; // ����������, ������������, ����� �� �������� �����
bool CanChoose = 1; // ����������, ������������, ����� �� �������� ������/������� ����� ��� ���
int QuestionsLeft; // ����������, ������������ ���������� ���������� �������� � ������
int colquestions[4]; // ������, ������������ ������������ ���������� �������� �� �������
int MaximalSumm; // ����������, ������������ ������������ �������� ����� ���� �������
int MaximalSummCount; // ����������, ������������ ���-�� ���������� ����� �������
int indexes[5], variants[5]; // �������, ���������� �������� ����������� �������� �������
int MechState = 1;
bool spin_round_mode; // ���������� �������� (1 - �� �������, 0 - ������ �������)
int TimeToDecide; // �����, ����������� ���� ��� �������� �������
int LeaderPlayerAtFinal; // ���������� ������ ������, ���������� � ����� (���������� ��� �������� �������)
int RoundOfGame; // ����������� ����� �������� ������ (������ �� ��������)

int opened_now[6]; // ��������� ����� ���� ����� ������� ����� ��������� ���������
int TempRoundOfGame;
int chooseplayer;
int CantFall;

const int FramesCount = 56;
TPicture* PulseFrames[FramesCount];

// Some controls pointers
TImage* imgPlayer[5];
TImage* imgHatch[6];
TImage* imgNumber[5];

TBot* bot[5];
void SetQuestionsMaximum(int FirstRound, int SecondRound, int ThirdRound, int FouthRound);
// -----------------------------------------------------------------------------

void __fastcall TF::LoadGraphic() {

    imgPlace->Picture->LoadFromFile("Data\\Place.png");
    Wait = 0;

    hatches_enable_state(false);
    tmrWaiting->Enabled = False;
    imgTotalPrize->Visible = False;
    MechState = 1;

    F->Constraints->MinWidth = Settings->MinWidth;
    F->Constraints->MinHeight = Settings->MinHeight;

    if (Settings->Fullscreen) {
        BorderStyle = bsNone;
        Width = Screen->Width;
        Height = Screen->Height;
        Left = 0;
        Top = 0;
    } else {
        BorderStyle = bsSizeable;
        Width = Settings->FormsWidth;
        Height = Settings->FormsHeight;
    }

    btnMechStart->Enabled = True;

    for (unsigned i = 0; i < 5; ++i) {
        CreateLabel(lblAnswers, i, 0, 0, 0, 0, "");
    }

    edFinalAnswer->Visible = False;

    for (int i = 0; i < 5; ++i) {
        imgNumber[0]->Visible = false;
    }

    imgChoosenAnswer->Visible = false;

    imgQuestion->Picture->LoadFromFile("data\\rr_quest.png");

    for (int i = 0; i < FramesCount; i++) {
        PulseFrames[i] = new TPicture();
        PulseFrames[i]->LoadFromFile("data\\pulse\\pulse_" + Trim(IntToStr(i + 1)) + ".png");
    }

    btnMechStop->Enabled = 0;
    CantFall = -1;
    AnimationFrame = 1;
}

// ---------------------------------------------------------------------------
void TF::CreateLabel(TLabel** type, int index, int top, int left, int width, int height, UnicodeString caption) {
    if (!type[index]) {
        TLabel* lbl = new TLabel(F);
        lbl->Parent = F;
        lbl->Font->Color = clWhite;
        lbl->Font->Size = 12;
        lbl->Font->Name = "ARIAL";
        lbl->Font->Charset = TFontCharset(RUSSIAN_CHARSET);
        lbl->AutoSize = false;
        lbl->Font->Style = (TFontStyles)1; // bold

        if (type != lblMoney) {
            lbl->OnClick = ControlLabel->OnClick;
        }

        if (type == lblAnswers) {
            lbl->Alignment = taLeftJustify;
            lbl->BringToFront();
        } else if (type == lblMoney) {
            lbl->Alignment = taRightJustify;
        } else if (type == lblPlayer) {
            lbl->Alignment = taCenter;
        }

        type[index] = lbl;
    }

    type[index]->Top = top;
    type[index]->Left = left;
    type[index]->Width = width;
    type[index]->Height = height;

    type[index]->Caption = caption;

    type[index]->Visible = True;
}

// ---------------------------------------------------------------------------
void __fastcall TF::PlaySound(String path) {
    if (Settings->SoundEnabled) {

        MediaPlayer1->FileName = "sounds\\" + path;
        MediaPlayer1->Open();
        MediaPlayer1->Play();
    }
}

// ---------------------------------------------------------------------------
void __fastcall TF::PlayMusic(String path) {
    if (Settings->MusicEnabled) {
        MediaPlayer2->FileName = "sounds\\" + path;
        MediaPlayer2->Open();
        MediaPlayer2->Play();
        MediaPlayer2->AutoRewind = true;
    }
}

// ---------------------------------------------------------------------------
__fastcall TF::TF(TComponent* Owner) : TForm(Owner) {
    UnicodeString ch;
    ch = ExtractFilePath(Application->ExeName);
    CurrentHatch = 0;
    for (int i = 0; i < 5; i++) {
        ingame[i] = 1;
    }
    RoundOfGame = -1; // ����������� ����� �������� ������ (������ �� ��������)
}

// ---------------------------------------------------------------------------
void __fastcall TF::imgPlaceClick(TObject* Sender) {
    // UnicodeString
}

// ---------------------------------------------------------------------------
void __fastcall TF::Button1Click(TObject* Sender) {
    // Hatches();
    DumpMemory(0);
}

// ---------------------------------------------------------------------------
void __fastcall TF::FormCreate(TObject* Sender) {
    // initialise control pointer arrays
    imgPlayer[0] = imgPlayer1;
    imgPlayer[1] = imgPlayer2;
    imgPlayer[2] = imgPlayer3;
    imgPlayer[3] = imgPlayer4;
    imgPlayer[4] = imgPlayer5;

    imgNumber[0] = imgNumber1;
    imgNumber[1] = imgNumber2;
    imgNumber[2] = imgNumber3;
    imgNumber[3] = imgNumber4;
    imgNumber[4] = imgNumber5;

    imgHatch[0] = imgHatch0;
    imgHatch[1] = imgHatch1;
    imgHatch[2] = imgHatch2;
    imgHatch[3] = imgHatch3;
    imgHatch[4] = imgHatch4;
    imgHatch[5] = imgHatch5;
}

// ---------------------------------------------------------------------------

void __fastcall TF::tmrPulseAnimationTimer(TObject* Sender) {
    static frame = 0;
    imgPulse->Picture->Assign(PulseFrames[frame]);
    frame = ++frame % FramesCount;
}
// ---------------------------------------------------------------------------

void ReadCfgFile() {
    TIniFile* ini = new TIniFile(ExtractFilePath(Application->ExeName) + "settings.cfg");
    Settings->Fullscreen = ini->ReadBool("Global", "FullScreen", False);
    Settings->FormsWidth = ini->ReadInteger("Global", "Width", 1024);
    Settings->FormsHeight = ini->ReadInteger("Global", "Height", 1024);
    Settings->SoundEnabled = ini->ReadBool("Global", "Sound", False);
    Settings->SoundVolume = ini->ReadInteger("Global", "SoundVolume", 100);
    Settings->MusicEnabled = ini->ReadBool("Global", "Music", False);
    Settings->MusicVolume = ini->ReadInteger("Global", "MusicVolume", 100);
    Settings->HostMode = ini->ReadBool("Global", "HostMode", False);

    for (int i = 1; i <= 5; i++) {
        Settings->PlayerNames[i - 1] = ini->ReadString("Players", "Player" + IntToStr(i), "FUUUUuuuuu...");
        Settings->PlayerType[i - 1] = (TBotType)ini->ReadInteger("Players", "PlayerType" + IntToStr(i), 0);
    }

    Settings->LastBase = ini->ReadString("Global", "LastBase", "");

    int i = 0;
    while (1) {
        String str = ini->ReadString("Bases", "basename" + IntToStr(i), "");
        if (str != "") {
            Settings->BaseNames->Add(str);
        } else {
            break;
        }
        i++ ;
    }

    if (Settings->LastBase == "") {
        ShowError(1);
    }

    ini->Free();
}

// ---------------------------------------------------------------------------
void SetPlayers() {
    for (int i = 0; i < 5; i++) {
        bot[i] = new TBot(Settings->PlayerType[i]);
    }
}

// ---------------------------------------------------------------------------
void InitializeSettings() {
    Settings = new TSettings();
    ReadCfgFile();
    SetPlayers();
}

void __fastcall TF::btnMechStartClick(TObject* Sender) {
    if (ModeOfGame == 8) {
        SpeedOfRotation = 75;
    } else {
        SpeedOfRotation = _StartRotaingSpeed;
    }
    if (RoundOfGame == -1 || FinalRoundOfGame > 0) {
        SpeedOfRotation = 35;
    }
    tmrRotator->Interval = SpeedOfRotation;
    MechanizmOn = -1;
    imgPlace->Picture->LoadFromFile("Data\\Place_red_zero.png");
    tmrRotator->Enabled = True;
    PlayMusic("rr_mexopen.wav");
    btnMechStart->Enabled = 0;
    btnMechStop->Enabled = 1;
}

// ---------------------------------------------------------------------------
void SwitchOffMech_WhiteLights() {
    F->tmrRotator->Enabled = False;
    LightHatchesW(255, 4);
    MechanizmSetHatchesStates();
}

// ---------------------------------------------------------------------------
void __fastcall TF::btnMechStopClick(TObject* Sender) {
    MechanizmOn = 1;
    if (RoundOfGame == -1) {
        RoundOfGame = 0;
    }
    PlayMusic("rr_mexclose.wav");
    randomize();
    WaitForFate = 5 + random(11);
    if (RoundOfGame < 1) {
        imgPlace->Picture->LoadFromFile("Data\\Place.png");
    }

    bool b1 = FinalRoundOfGame > 0;
    bool b2 = RoundOfGame >= 1 && ModeOfGame != 8;
    bool b3 = !b2 && ModeOfGame == 8;

    if (b1) {
        SwitchOffMech_WhiteLights();
        CanChoose = 1;
        OpenRandomHatches(FinalRoundOfGame + 2, ModeOfGame);
    }
    if (b2 || b3) {
        SwitchOffMech_WhiteLights();
    }
    // ------------------

    if (RoundOfGame == 0) {
        ZeroRoundRotating();
    } else {
        if (ModeOfGame != 8) {
            OpenRandomHatches(RoundOfGame, ModeOfGame);
            ModeOfGame = 7;
            tmrWaiting->Enabled = True;
        } else {
            OpenRandomHatches(1, ModeOfGame);
            ModeOfGame = 9;
        }
        tmrWaiting->Enabled = True;
    }

    imgMechanizm->Enabled = 0;

    btnMechStart->Enabled = 0;
    btnMechStop->Enabled = 0;
}

// ---------------------------------------------------------------------------
void __fastcall TF::btnExitClick(TObject* Sender) {
    int r;
    r = MessageDlg("�� ������������� ������ ��������� ����?\n��� ������ �� ���� ���� ����� ��������!", mtCustom,
        mbYesNo, 0);
    if (r == mrYes) {
        F->Close();
    }
}

// ---------------------------------------------------------------------------
void __fastcall TF::tmrRotatorTimer(TObject* Sender) {
    if (ModeOfGame == 8) {
        SwitchesLights();
    } else {
        switch (RoundOfGame) {
        case -1:
            ZeroRoundSpin();
            break;
        case 0:
            ShiftHatches();
            break;
        case 1:
            FirstRoundRotating();
            break;
        case 2:
            SecondRoundRotating();
            break;
        case 3:
            ThirdRoundRotating();
            break;
        case 4:
            FourthRoundRotating();
            break;
        case 5:
            ZeroRoundSpin();
            break;
        }
    }

    if (FinalRoundOfGame > 0) {
        ZeroRoundSpin();
    }

    if (RoundOfGame < 1) {
        CurrentHatch = ++CurrentHatch % 6;
    }

    if (MechanizmOn == 1) // ���� �������� � ������ ����������
    {

        SpeedOfRotation += 30; // ��������� ��������
        tmrRotator->Interval = SpeedOfRotation;
        if ((SpeedOfRotation > 450) && (CurrentHatch != 0) && (ingame[CurrentHatch - 1]))
            // � ���� �������� ����� �� ���������
        {
            tmrRotator->Enabled = 0; // �������� ������
            switch (RoundOfGame) {
            case 0: {
                    LightHatchesW(2, 4);
                    if (TempRoundOfGame != 0) {
                        RoundOfGame = TempRoundOfGame;
                    } else {
                        QuestionsLeft = colquestions[0];
                        RoundOfGame = 1;
                    }
                } break;
            default:
                LightHatchesW(255, 4);
                break;
            }
            PlayMusic("rr_endround.wav");
            switchonquestion();
            ModeOfGame = 0;
            if (Settings->HostMode == false) {
                tmrWaiting->Enabled = True;
                Wait = 0;
            }
        }
    }
    MechanizmSetHatchesStates();
}

// ---------------------------------------------------------------------------
void __fastcall TF::tmrWaitingTimer(TObject* Sender) {
    Wait++ ;
    switch (ModeOfGame) {
        // if (RoundOfGame != 5)

    case 0: // ����� �������
        if (Wait == 5) {
            if (QuestionsLeft > 0) {
                for (int i = 0; i < 5; i++) {
                    indexes[i] = -1;
                    variants[i] = -1;
                    PlaySound("rr_nextq.wav");
                }
                tmrWaiting->Enabled = False;
                showquestion();
                CanChoose = 0;
                hatches_enable_state(false);
                btnMechStart->Enabled = 0;
                TimeOfQuestion = 20;
                lblTimer->Caption = IntToStr(TimeOfQuestion);
                Wait = 0;
                if (TransferAll == 1) {
                    ModeOfGame = 1;
                    RoundOfGame = 1;
                } else {
                    ModeOfGame = 1;
                }
            } else {
                imgQuestion->Visible = False;
                imgBorder->Visible = False;
                LabelMoney->Visible = False;
                imgPulse->Visible = False;
                ModeOfGame = 8;
            }
        }
        break;
    case 1: // ���������� ��������� ����� ����� �������
        if (Wait == 3) {
            tmrWaiting->Enabled = False;
            Wait = 2;
            if (TransferAll == 1) {
                F->Reward = 1000;
                tmrMoney->Enabled = True;
                MoneyTransferMode = 'a';
            } else {
                CanChoose = 1;
            }
            if (RoundOfGame != 4) {
                if (Settings->PlayerType[CurrentHatch - 1] == bbHuman) {
                    activatedplayers();
                } else {
                    chooseplayer = bot[CurrentHatch - 1]->ChooseAnyPlayer(ingame, CurrentHatch);
                    choosingplayer();
                    MechanizmSetHatchesStates();
                    ModeOfGame = 2;
                    if (!Settings->HostMode) {
                        tmrWaiting->Enabled = True;
                    }
                }
            } else {
                hatches_enable_state(false);
                CanChoose = 0;
                for (int i = 0; i < 5; i++) {
                    if ((ingame[i]) && (CurrentHatch != i + 1)) {
                        chooseplayer = i + 1;
                    }
                }
                choosingplayer();
                ModeOfGame = 2;
                if (!Settings->HostMode) {
                    tmrWaiting->Enabled = True;
                }
            }
        }
        break;
    case 2: // ����� ������
        if (Wait == 3) {
            // tmrWaiting->Enabled = False;
            if (RoundOfGame != 4) {
                spin_round_mode = 1;
                PlayMusic("rr_choosen.wav");
            }
            MoneyTransferMode = 'c';
            choosenplayer(chooseplayer);
            if (Settings->PlayerType[chooseplayer - 1] != bbHuman) {
                switch (Settings->PlayerType[chooseplayer - 1]) {
                case bbFoooool:
                    TimeToDecide = 2 + random(20);
                    break;
                case bbFooly:
                    TimeToDecide = 7 + random(13);
                    break;
                case bbNormal:
                    TimeToDecide = 7 + random(9);
                    break;
                case bbHard:
                    TimeToDecide = 5 + random(6);
                    break;
                case bbVeryHard:
                    TimeToDecide = 1 + random(4);
                    break;
                }
#ifdef _DEBUG
                TimeToDecide = 1;
#endif

            }
        }
        if (Wait == 4) {
            tmrWaiting->Enabled = false;
            if (RoundOfGame != 4) {
                before_spin_lights();
                tmrLightAnimation->Enabled = true;
            }
            ModeOfGame = 3;
            Wait = 0;
            tmrWaiting->Enabled = True;
        }
        break;
    case 3: // ����� ������� � �������
        if (Wait == 7) {
            // -=[��������� ������������� ��������� ������]=-
            // --[ 1. ���������� ������� ��������� ]--
            for (int i = 0; i < RoundOfGame + 1; i++) {
                indexes[i] = i;
            }
            // --[ 2. ��������� ������������� �������� ]--
            int step = 0, ind;
            do {
                ind = random(RoundOfGame + 1);
                if (indexes[ind] != -1) {
                    variants[step] = indexes[ind];
                    indexes[ind] = -1;
                    step++ ;
                }
            }
            while (indexes[0] + indexes[1] + indexes[2] + indexes[3] + indexes[4] != -5);

            // --[ 3. ������ ��������� ������, �������� ��������]--
            TimeOfQuestion = 20;
            imgPulse->Visible = True;
            imgPulseBar->Visible = True;
            imgTicker->Visible = True;
            imgTimer->Picture->LoadFromFile("Data\\" + IntToStr(TimeOfQuestion) + "sec.png");
            ShowAnswers();
            ResizeAnswers();
            // --[ 4. ���������: ����������� �������, � ������� ����� ���������� ����� ]--
            int trueans;
            switch (RoundOfGame) {
            case 1:
                trueans = base[NumberOfQuestion].TrueAnswer;
                break;
            case 2:
                trueans = base[NumberOfQuestion].TrueAnswer;
                break;
            case 3:
                trueans = base[NumberOfQuestion].TrueAnswer;
                break;
            case 4:
                trueans = base[NumberOfQuestion].TrueAnswer;
                break;
            }
            for (int i = 0; i < RoundOfGame + 1; i++) {
                if (variants[i] == trueans) {
                    RandomPlace = i;
                }
            }
            // -=[ ��������� ��������� ������������� ]=-
            lblTimer->Visible = True;
            imgTimer->Visible = True;
            break;
        }
        // Wait=0;

        if (Wait == 12) {
            tmrWaiting->Enabled = False;
            if (!Settings->HostMode) {
                CanAnswer = 1;
                PlayMusic("rr_20sec.wav");
                tmrTime->Enabled = True;
            }
            Wait = 0;
        }
        break;
    case 4: // �������� ������
        if (Wait == 2) {
            CanAnswer = 0;
            if (answer == RandomPlace) {
                imgQuestion->Picture->LoadFromFile("Data\\quest_correct.png");
                if (!Settings->HostMode) {
                    tmrWaiting->Enabled = True;
                }
                imgChoosenAnswer->Visible = True;
                imgChAnsLeft->Visible = true;
                imgChAnsRight->Visible = true;
                imgChoosenAnswer->AutoSize = False;
                imgChoosenAnswer->Stretch = True;
                imgChoosenAnswer->Height = imgNumber[0]->Height + 20;
                imgChoosenAnswer->Width = 20 + lblAnswers[answer]->Width - 5;
                Choosen_Answer_Change_Position();
                CurrentHatch = chooseplayer;
                chooseplayer = 255;
                QuestionsLeft-- ;
            } else {
                imgQuestion->Picture->LoadFromFile("Data\\quest_incorrect.png");
                if (answer != -1) {
                    imgChoosenAnswer->Visible = True;
                    imgChAnsLeft->Visible = true;
                    imgChAnsRight->Visible = true;
                }
                imgChoosenAnswer->AutoSize = False;
                imgChoosenAnswer->Stretch = True;
                imgChoosenAnswer->Height = imgNumber[0]->Height + 20;
                imgChoosenAnswer->Width = 20 + lblAnswers[answer]->Width - 5;
                Choosen_Answer_Change_Position();
                Proverka2();
                Reward = money[chooseplayer - 1];
                QuestionsLeft-- ;
            }
        }
        if (Wait == 8) {
            if (answer != RandomPlace) {
                PlayMusic("rr_bg1.mp3");
            } else {
                PlayMusic("rr_bg" + IntToStr(2 + random(4)) + ".mp3");
            }
            if (!Settings->HostMode) {
                tmrWaiting->Enabled = True;
            } else {
                tmrWaiting->Enabled = False;
            }
            ModeOfGame = 5;
            Wait = 0;
        }
        TransferAll = 0;
        break;
    case 5: // ���������� ����� � ����������� ����������� ������
        if (Wait == 2) {
            imgChoosenAnswer->Visible = True;
            imgChAnsLeft->Visible = true;
            imgChAnsRight->Visible = true;
            imgChoosenAnswer->Width = 20 + lblAnswers[RandomPlace]->Width - 5;
            Choosen_Answer_Change_Position();
            MoneyTransferMode = chooseplayer;
            tmrMoney->Enabled = True;
            PlaySound("rr_money.wav");
        }
        if (Wait == 7) {
            tmrWaiting->Enabled = False;
            if (Settings->PlayerType[chooseplayer - 1] == bbHuman) {
                btnMechStart->Enabled = 1;
                imgMechanizm->Enabled = 1;
            } else {
                switch (Settings->PlayerType[chooseplayer - 1]) {
                case bbFoooool:
                    TimeToDecide = 10 + random(31);
                    break;
                case bbFooly:
                    TimeToDecide = 10 + random(21);
                    break;
                case bbNormal:
                    TimeToDecide = 5 + random(16);
                    break;
                case bbHard:
                    TimeToDecide = 5 + random(11);
                    break;
                case bbVeryHard:
                    TimeToDecide = 1 + random(11);
                    break;
                }
#ifdef _DEBUG
                TimeToDecide = 1;
#endif
                imgMechanizmClick(imgMechanizm);
                tmrDecided->Enabled = true;
            }
            Wait = 0;
        }
        break;
    case 7: // �������� ����������� ������� ������������ ������
        {
            if (Wait == WaitForFate) {
                if (opened_now[chooseplayer] == 1) {
                    OpenHatches();
                    PlayMusic("rr_fall.wav");
                    ingame[chooseplayer - 1] = 0;
                    imgPulse->Visible = False;
                    LabelMoney->Visible = False;
                    lblPlayer[chooseplayer - 1]->Visible = False;
                    lblMoney[chooseplayer - 1]->Visible = False;
                    F->money[chooseplayer - 1] = 0;
                    imgQuestion->Visible = False;
                    imgBorder->Visible = False;
                    imgTicker->Visible = False;
                    imgPulseBar->Visible = False;
                    imgTotalPrize->Visible = False;
                    for (int i = 0; i < 5; i++) {
                        if (F->lblAnswers[i] != NULL) {
                            F->lblAnswers[i]->Visible = False;
                        }
                    }
                    switch (chooseplayer) {
                    case 1:
                        imgPlayer[0]->Visible = False;
                        break;
                    case 2:
                        imgPlayer[1]->Visible = False;
                        break;
                    case 3:
                        imgPlayer[2]->Visible = False;
                        break;
                    case 4:
                        imgPlayer[3]->Visible = False;
                        break;
                    case 5:
                        imgPlayer[4]->Visible = False;
                        break;
                    }
                    imgNumber[0]->Visible = False;
                    imgNumber[1]->Visible = False;
                    imgNumber[2]->Visible = False;
                    imgNumber[3]->Visible = False;
                    imgNumber[4]->Visible = False;
                    F->imgChoosenAnswer->Visible = False;
                    F->imgChAnsLeft->Visible = false;
                    F->imgChAnsRight->Visible = false;
                    F->imgTimer->Visible = False;
                    F->lblTimer->Visible = False;
                    F->imgQuestion->Picture->LoadFromFile("Data\\rr_quest.png");
                    F->LabelQuestion->Visible = False;
                    if (!Settings->HostMode) {
                        tmrWaiting->Enabled = true;
                        Wait = 0;
                    } else {
                        tmrWaiting->Enabled = false;
                        Wait = 9;
                    }
                    ModeOfGame = 10;
                } else {
                    PlayMusic("rr_save.wav");
                    CurrentHatch = chooseplayer;
                    chooseplayer = 255;
                    imgPlace->Picture->LoadFromFile("Data\\Place.png");
                    ResetForm();
                }
            }
            if (Wait == (WaitForFate + 3)) {
                if (!Settings->HostMode) {
                    F->tmrWaiting->Enabled = True;
                    Wait = 0;
                } else {
                    F->tmrWaiting->Enabled = false;
                    Wait = 4;
                }
                ModeOfGame = 0;
                PlayMusic("rr_bg" + IntToStr(4 + random(2)) + ".mp3");
            }
            break;
        }
    case 8: // ����������� ������ � ������ ��������� ��������
        {
            if (Wait == 8) {
                MaximalSumm = 0;
                MaximalSummCount = 0;
                for (int i = 0; i < 5; i++) {
                    if (money[i] > MaximalSumm) {
                        MaximalSumm = money[i];
                    }
                }
                for (int i = 0; i < 5; i++) {
                    if (money[i] == MaximalSumm) {
                        MaximalSummCount++ ;
                        CantFall = i;
                    }
                }
                if (MaximalSummCount > 1 || RoundOfGame == 4) {
                    CantFall = -1;
                }
                tmrWaiting->Enabled = False;
                btnMechStart->Enabled = 1;
                imgMechanizm->Enabled = 1;
                // btnMechStart->SetFocus();
            }
        } break;
    case 9: // ��������, ����� ���� �� ������� ��������� ������ �������� ����
        {
            if (Wait == WaitForFate) {
                int NumberOfPlayers = 0;
                OpenRndHatches();
                PlayMusic("rr_fall.wav");
                ingame[chooseplayer - 1] = 0;
                MoneyTransferMode = 'a';
                for (int i = 0; i < 5; i++) {
                    if (ingame[i]) {
                        NumberOfPlayers++ ;
                    }
                }
                Reward = money[chooseplayer - 1] / NumberOfPlayers / 1.;
                tmrMoney->Enabled = True;
                money[chooseplayer - 1] = 0;
                lblPlayer[chooseplayer - 1]->Visible = False;
                lblMoney[chooseplayer - 1]->Visible = False;
                switch (chooseplayer) {
                case 1:
                    imgPlayer[0]->Visible = False;
                    break;
                case 2:
                    imgPlayer[1]->Visible = False;
                    break;
                case 3:
                    imgPlayer[2]->Visible = False;
                    break;
                case 4:
                    imgPlayer[3]->Visible = False;
                    break;
                case 5:
                    imgPlayer[4]->Visible = False;
                    break;
                }
            }
            if (Wait == (WaitForFate + 7)) {
                PlayMusic("rr_bg1.mp3");
                if (!Settings->HostMode) {
                    tmrWaiting->Enabled = True;
                    Wait = 0;
                } else {
                    Wait = 5;
                    tmrWaiting->Enabled = false;
                }
                ModeOfGame = 10;
            }
        } break;
    case 10: {
            if (Wait == 10) {
                PlayMusic("rr_endround.wav");
                LightHatchesW(2, 0);
                MechanizmSetHatchesStates();
                Wait = 0;
                switch (RoundOfGame) {
                case 1:
                    RoundOfGame = 2;
                    QuestionsLeft = colquestions[1];
                    break;
                case 2:
                    RoundOfGame = 3;
                    QuestionsLeft = colquestions[2];
                    break;
                case 3:
                    RoundOfGame = 4;
                    QuestionsLeft = colquestions[3];
                    break;
                case 4:
                    RoundOfGame = 5;
                    break;
                }
                if (RoundOfGame != 5) {
                    ModeOfGame = 11;
                    imgSplash->Picture->LoadFromFile("Data\\Splash-" + IntToStr(RoundOfGame) + ".png");
                } else {
                    ModeOfGame = 0;
                    tmrWaiting->Enabled = False;
                    tmrWaitingFinal->Enabled = True;
                }
            }
        } break;
    case 11: {
            if (Wait == 5) {
                PlayMusic("rr_round.wav");
                imgSplash->Visible = True;
                LightHatchesW(255, 2);
                MechanizmSetHatchesStates();
                imgPlace->Picture->LoadFromFile("Data\\Place.png");
            }
            if (Wait == 12) {
                imgSplash->Visible = False;
                PlayMusic("rr_openround.wav");
                Wait = 0;
                ModeOfGame = 12;
            }
        } break;
    case 12: {
            MaximalSumm = 0;
            MaximalSummCount = 0;
            switch (RoundOfGame) {
            case 2:
                QuestionsLeft = colquestions[1];
                break;
            case 3:
                QuestionsLeft = colquestions[2];
                break;
            case 4:
                QuestionsLeft = colquestions[3];
                break;
            }
            if (Wait == 5) {
                for (int i = 0; i < 5; i++) {
                    if (money[i] > MaximalSumm) {
                        MaximalSumm = money[i];
                        CurrentHatch = i + 1;
                        chooseplayer = 255;
                    }
                }
                for (int i = 0; i < 5; i++) {
                    if (money[i] == MaximalSumm) {
                        MaximalSummCount++ ;
                        CurrentHatch = i + 1;
                    }
                }
                if (MaximalSummCount > 1) {
                    CurrentHatch = 0;
                    TempRoundOfGame = RoundOfGame;
                    RoundOfGame = -1;
                    btnMechStart->Enabled = 1;
                    imgMechanizm->Enabled = 1;
                    // btnMechStart->SetFocus();
                    tmrWaiting->Enabled = False;
                } else {
                    UpdateHatches();
                }
                switchonquestion();
            }
            if (Wait == 12) {
                PlayMusic("rr_bg4.mp3");
                if (!Settings->HostMode) {
                    Wait = 0;
                    tmrWaiting->Enabled = true;
                } else {
                    Wait = 4;
                    tmrWaiting->Enabled = false;
                }
                ModeOfGame = 0;
            }
        } break;
    }
}
// ---------------------------------------------------------------------------

void __fastcall TF::tmrMoneyTimer(TObject* Sender) {
    if (MoneyTransferMode == 'a') {
        int control = 0;
        if (ModeOfGame != 9) // ��������� ���������� �� 1000 �������
        {
            for (int i = 0; i < 5; i++) { // ���������� ����� �������
#define slowest_money 4
                if (((Reward - money[slowest_money]) / 66) > 0) {
                    if (ingame[i]) {
                        money[i] += 66;
                    } // ����, ��� ����� ���� � ��-�� � ��������� �������
                    control = control + 66;
                } else {
                    if (ingame[i]) {
                        money[i] += (Reward - money[slowest_money]) % 66;
                    }
                    control = Reward;
                } // -> if (((Reward - money[slowest_money]) / 66) > 0)
                lblMoney[i]->Caption = IntToStr(money[i]);
            }
            if (control == Reward) {
                tmrMoney->Enabled = False;
                CanChoose = 1;
                activatedplayers();
            }
        } else { // �� ����, ��� ���������� ������� �����...
            for (int i = 0; i < 5; i++)
                if (ingame[i]) {
                    money[i] = money[i] + Reward;
                    lblMoney[i]->Caption = IntToStr(money[i]);

                    /* switch (money[i] % 1000) {
                     case 998:
                     money[i] = money[i] + 2;
                     break;
                     case 999:
                     money[i] = money[i] + 1;
                     break;
                     default:
                     break;
                     } */
                    if ((money[i] % 1000 == 998) || (money[i] % 1000 == 999)) {
                        money[i] = 1000;
                    }
                    lblMoney[i]->Caption = IntToStr(money[i]);
                }
            tmrMoney->Enabled = False;
        }
    }

    else {
        if (FinalRoundOfGame < 1) {
            TransferMoney();
        } else {
            TransferMoneyFinal();
        }
    }
}
// ---------------------------------------------------------------------------

void __fastcall TF::imgHatch4Click(TObject* Sender) {
    if (FinalRoundOfGame > 0 && CanChoose == 1) {
        CurrentHatch = 4;
        CanChoose = 0;
        UpdateHatches();
        tmrWaitingFinal->Enabled = True;
        for (int i = 0; i < 5; i++) {
            if (ingame[i]) {
                switch (i) {
                case 0: {
                        imgPlayer[0]->Top =
                            int(imgHatch[4]->Top + (imgHatch[4]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[0]->Left =
                            int(imgHatch[4]->Left + (imgHatch[4]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 1: {
                        imgPlayer[1]->Top =
                            int(imgHatch[4]->Top + (imgHatch[4]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[1]->Left =
                            int(imgHatch[4]->Left + (imgHatch[4]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 2: {
                        imgPlayer[2]->Top =
                            int(imgHatch[4]->Top + (imgHatch[4]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[2]->Left =
                            int(imgHatch[4]->Left + (imgHatch[4]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 3: {
                        imgPlayer[3]->Top =
                            int(imgHatch[4]->Top + (imgHatch[4]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[3]->Left =
                            int(imgHatch[4]->Left + (imgHatch[4]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 4: {
                        imgPlayer[4]->Top =
                            int(imgHatch[4]->Top + (imgHatch[4]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[4]->Left =
                            int(imgHatch[4]->Left + (imgHatch[4]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                }
            }
        }
    } else if (ModeOfGame == 1) {
        chooseplayer = 4;
        CanChoose = 0;
        choosingplayer();
        ModeOfGame = 2;
        tmrWaiting->Enabled = True;
    }
}

// ---------------------------------------------------------------------------
void __fastcall TF::imgHatch5Click(TObject* Sender) {
    if (FinalRoundOfGame > 0 && CanChoose == 1) {
        CurrentHatch = 5;
        CanChoose = 0;
        UpdateHatches();
        tmrWaitingFinal->Enabled = True;
        for (int i = 0; i < 5; i++) {
            if (ingame[i]) {
                switch (i) {
                case 0: {
                        imgPlayer[0]->Top =
                            int(imgHatch[5]->Top + (imgHatch[5]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[0]->Left =
                            int(imgHatch[5]->Left + (imgHatch[5]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 1: {
                        imgPlayer[1]->Top =
                            int(imgHatch[5]->Top + (imgHatch[5]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[1]->Left =
                            int(imgHatch[5]->Left + (imgHatch[5]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 2: {
                        imgPlayer[2]->Top =
                            int(imgHatch[5]->Top + (imgHatch[5]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[2]->Left =
                            int(imgHatch[5]->Left + (imgHatch[5]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 3: {
                        imgPlayer[3]->Top =
                            int(imgHatch[5]->Top + (imgHatch[5]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[3]->Left =
                            int(imgHatch[5]->Left + (imgHatch[5]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 4: {
                        imgPlayer[4]->Top =
                            int(imgHatch[5]->Top + (imgHatch[5]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[4]->Left =
                            int(imgHatch[5]->Left + (imgHatch[5]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                }
            }
        }
    } else if (ModeOfGame == 1) {
        chooseplayer = 5;
        CanChoose = 0;
        choosingplayer();
        ModeOfGame = 2;
        tmrWaiting->Enabled = True;
    }
}

void __fastcall TF::imgHatch3Click(TObject* Sender) {
    if (FinalRoundOfGame > 0 && CanChoose == 1) {
        CurrentHatch = 3;
        CanChoose = 0;
        UpdateHatches();
        tmrWaitingFinal->Enabled = True;
        for (int i = 0; i < 5; i++) {
            if (ingame[i]) {
                switch (i) {
                case 0: {
                        imgPlayer[0]->Top =
                            int(imgHatch[3]->Top + (imgHatch[3]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[0]->Left =
                            int(imgHatch[3]->Left + (imgHatch[3]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 1: {
                        imgPlayer[1]->Top =
                            int(imgHatch[3]->Top + (imgHatch[3]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[1]->Left =
                            int(imgHatch[3]->Left + (imgHatch[3]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 2: {
                        imgPlayer[2]->Top =
                            int(imgHatch[3]->Top + (imgHatch[3]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[2]->Left =
                            int(imgHatch[3]->Left + (imgHatch[3]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 3: {
                        imgPlayer[3]->Top =
                            int(imgHatch[3]->Top + (imgHatch[3]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[3]->Left =
                            int(imgHatch[3]->Left + (imgHatch[3]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 4: {
                        imgPlayer[4]->Top =
                            int(imgHatch[3]->Top + (imgHatch[3]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[4]->Left =
                            int(imgHatch[3]->Left + (imgHatch[3]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                }
            }
        }
    } else if (ModeOfGame == 1) {
        chooseplayer = 3;
        CanChoose = 0;
        choosingplayer();
        ModeOfGame = 2;
        tmrWaiting->Enabled = True;
    }
    mlog->Lines->Add("3");
}

void __fastcall TF::imgHatch1Click(TObject* Sender) {
    if (FinalRoundOfGame > 0 && CanChoose == 1) {
        CurrentHatch = 1;
        CanChoose = 0;
        UpdateHatches();
        tmrWaitingFinal->Enabled = True;
        for (int i = 0; i < 5; i++) {
            if (ingame[i]) {
                switch (i) {
                case 0: {
                        imgPlayer[0]->Top =
                            int(imgHatch[1]->Top + (imgHatch[1]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[0]->Left =
                            int(imgHatch[1]->Left + (imgHatch[1]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 1: {
                        imgPlayer[1]->Top =
                            int(imgHatch[1]->Top + (imgHatch[1]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[1]->Left =
                            int(imgHatch[1]->Left + (imgHatch[1]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 2: {
                        imgPlayer[2]->Top =
                            int(imgHatch[1]->Top + (imgHatch[1]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[2]->Left =
                            int(imgHatch[1]->Left + (imgHatch[1]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 3: {
                        imgPlayer[3]->Top =
                            int(imgHatch[1]->Top + (imgHatch[1]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[3]->Left =
                            int(imgHatch[1]->Left + (imgHatch[1]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 4: {
                        imgPlayer[4]->Top =
                            int(imgHatch[1]->Top + (imgHatch[1]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[4]->Left =
                            int(imgHatch[1]->Left + (imgHatch[1]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                }
            }
        }
    } else if (ModeOfGame == 1) {
        chooseplayer = 1;
        CanChoose = 0;
        choosingplayer();
        ModeOfGame = 2;
        tmrWaiting->Enabled = True;
    }
}

void __fastcall TF::imgHatch2Click(TObject* Sender) {
    if (FinalRoundOfGame > 0 && CanChoose == 1) {
        CurrentHatch = 2;
        CanChoose = 0;
        UpdateHatches();
        tmrWaitingFinal->Enabled = True;
        for (int i = 0; i < 5; i++) {
            if (ingame[i]) {
                switch (i) {
                case 0: {
                        imgPlayer[0]->Top =
                            int(imgHatch[2]->Top + (imgHatch[2]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[0]->Left =
                            int(imgHatch[2]->Left + (imgHatch[2]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 1: {
                        imgPlayer[1]->Top =
                            int(imgHatch[2]->Top + (imgHatch[2]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[1]->Left =
                            int(imgHatch[2]->Left + (imgHatch[2]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 2: {
                        imgPlayer[2]->Top =
                            int(imgHatch[2]->Top + (imgHatch[2]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[2]->Left =
                            int(imgHatch[2]->Left + (imgHatch[2]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 3: {
                        imgPlayer[3]->Top =
                            int(imgHatch[2]->Top + (imgHatch[2]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[3]->Left =
                            int(imgHatch[2]->Left + (imgHatch[2]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 4: {
                        imgPlayer[4]->Top =
                            int(imgHatch[2]->Top + (imgHatch[2]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[4]->Left =
                            int(imgHatch[2]->Left + (imgHatch[2]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                }
            }
        }
    } else if (ModeOfGame == 1) {
        chooseplayer = 2;
        CanChoose = 0;
        choosingplayer();
        ModeOfGame = 2;
        tmrWaiting->Enabled = True;
    }
}

void __fastcall TF::FormKeyDown(TObject* Sender, WORD& Key, TShiftState Shift) {
    if (Screen->MonitorCount > 1 && Key == 'H') {
        initialize_host_mode();
    }
    if (Key == VK_RIGHT && Settings->HostMode == true) {
        if (RoundOfGame >= 1 && RoundOfGame <= 4) {
            if (ModeOfGame == 3) {
                CanAnswer = 1;
                PlayMusic("rr_20sec.wav");
                tmrTime->Enabled = true;
            } else {
                tmrWaiting->Enabled = true;
            }
        }
        if (FinalRoundOfGame > 0) {
            tmrWaitingFinal->Enabled = true;
        }
    }
    if ((imgMechanizm->Enabled) && (Key == 32)) {
        imgMechanizmClick(imgMechanizm);
    }
    // ����� �������� ����� � ������
    if (FinalRoundOfGame > 0 && ModeOfGame == 0 && (((Key >= '1') && (Key <= '6')) || ((Key >= VK_NUMPAD1) && (Key <=
                    VK_NUMPAD6))) && Settings->PlayerType[LeaderPlayerAtFinal] == bbHuman) {
        switch (Key) {
        case '1':
        case VK_NUMPAD1:
            if (imgHatch[1]->Enabled) {
                imgHatch1Click(imgHatch[1]);
            }
            break;
        case '2':
        case VK_NUMPAD2:
            if (imgHatch[2]->Enabled) {
                imgHatch2Click(imgHatch[2]);
            }
            break;
        case '3':
        case VK_NUMPAD3:
            if (imgHatch[3]->Enabled) {
                imgHatch3Click(imgHatch[3]);
            }
            break;
        case '4':
        case VK_NUMPAD4:
            if (imgHatch[4]->Enabled) {
                imgHatch4Click(imgHatch[4]);
            }
            break;
        case '5':
        case VK_NUMPAD5:
            if (imgHatch[5]->Enabled) {
                imgHatch5Click(imgHatch[5]);
            }
            break;
        case '6':
        case VK_NUMPAD6:
            if (imgHatch[0]->Enabled) {
                imgHatch0Click(imgHatch[0]);
            }
            break;
        }
    }
    if (ModeOfGame == 1 && (((Key >= '1') && (Key <= '5')) || ((Key >= VK_NUMPAD1) && (Key <= VK_NUMPAD5)))
        && Settings->PlayerType[CurrentHatch - 1] == bbHuman && CanChoose == 1) {
        switch (Key) {
        case '1':
        case VK_NUMPAD1:
            if (ingame[0] == true && CurrentHatch != 1) {
                imgHatch1Click(imgHatch[1]);
            }
            break;
        case '2':
        case VK_NUMPAD2:
            if (ingame[1] == true && CurrentHatch != 2) {
                imgHatch2Click(imgHatch[2]);
            }
            break;
        case '3':
        case VK_NUMPAD3:
            if (ingame[2] == true && CurrentHatch != 3) {
                imgHatch3Click(imgHatch[3]);
            }
            break;
        case '4':
        case VK_NUMPAD4:
            if (ingame[3] == true && CurrentHatch != 4) {
                imgHatch4Click(imgHatch[4]);
            }
            break;
        case '5':
        case VK_NUMPAD5:
            if (ingame[4] == true && CurrentHatch != 5) {
                imgHatch5Click(imgHatch[5]);
            }
            break;
        }
    }
    if (ModeOfGame == 3 && CanAnswer == 1 && Settings->PlayerType[chooseplayer - 1] == bbHuman &&
        (((Key >= '1') && (Key <= '5')) || ((Key >= VK_NUMPAD1) && (Key <= VK_NUMPAD5)))) {
        switch (Key) {
        case '1':
        case VK_NUMPAD1:
            answer = 0;
            break;
        case '2':
        case VK_NUMPAD2:
            answer = 1;
            break;
        case '3':
        case VK_NUMPAD3:
            if (RoundOfGame >= 2) {
                answer = 2;
            }
            break;
        case '4':
        case VK_NUMPAD4:
            if (RoundOfGame >= 3) {
                answer = 3;
            }
            break;
        case '5':
        case VK_NUMPAD5:
            if (RoundOfGame >= 4) {
                answer = 4;
            }
            break;
        }

        if (answer <= RoundOfGame) {
            Proverka();
            ModeOfGame = 4;
            tmrTime->Enabled = False;
        }

        // switch (RoundOfGame) {
        // case 1:
        // F->Reward = 1000;
        // break;
        // case 2:
        // F->Reward = 2000;
        // break;
        // case 3:
        // F->Reward = 3000;
        // break;
        // case 4:
        // F->Reward = 4000;
        // break;
        // }
        F->Reward = RoundOfGame * 1000;
    }
}
// ---------------------------------------------------------------------------

void __fastcall TF::tmrTimeTimer(TObject* Sender) {
    TimeOfQuestion-- ;
    if (RoundOfGame < 5) {
        if (TimeOfQuestion == (20 - TimeToDecide)) {
            if (bot[chooseplayer - 1]->Get_Answer()) {
                F->answer = F->RandomPlace;
                Reward = RoundOfGame * 1000;
            } else {
                do {
                    F->answer = random(RoundOfGame + 1);
                }
                while (F->answer == F->RandomPlace);
            }
            Proverka();
            ModeOfGame = 4;
            tmrTime->Enabled = False;
        }
    } else {
        if (TimeOfQuestion == (10 - TimeToDecide)) {
            if (bot[LeaderPlayerAtFinal]->Get_Answer()) {
                String q = base[NumberOfQuestion].Answers[0];
                edFinalAnswer->Text = q;
                ModeOfGame = 3;
                tmrWaitingFinal->Enabled = True;
            } else {
                ModeOfGame = 3;
                tmrWaitingFinal->Enabled = True;
            }
            Reward = StrToInt(LabelMoney->Caption);
            tmrTime->Enabled = False;
        }
    }
    if (TimeOfQuestion >= 0) {
        lblTimer->Caption = IntToStr(TimeOfQuestion);
        imgTimer->Picture->LoadFromFile("Data\\" + IntToStr(TimeOfQuestion) + "sec.png");
    }
    if (TimeOfQuestion < 0) {
        if (TimeOfQuestion == -3) {
            tmrTime->Enabled = False;
            if (FinalRoundOfGame < 1) {
                answer = -1;
                Proverka();
                ModeOfGame = 4;
            } else {
                tmrTime->Enabled = False;
                ModeOfGame = 3;
                edFinalAnswer->Visible = False;
                tmrWaitingFinal->Enabled = True;
            }
        }
    }
}

// ---------------------------------------------------------------------------
void TF::TransferMoney() {
    if (chooseplayer != 255) {
        if (Reward >= 100) {
            money[chooseplayer - 1] -= 100;
        } else {
            money[chooseplayer - 1] -= Reward;
        }
        lblMoney[chooseplayer - 1]->Caption = IntToStr(money[chooseplayer - 1]);
        LabelMoney->Caption = IntToStr(money[chooseplayer - 1]);
    }

    if (Reward > 0) {
        if (Reward >= 100) {
            money[CurrentHatch - 1] += 100;
        } else {
            money[CurrentHatch - 1] += Reward;
        }
        lblMoney[CurrentHatch - 1]->Caption = IntToStr(money[CurrentHatch - 1]);
        LabelMoney->Caption = IntToStr(money[CurrentHatch - 1]);
    } else {
        if (money[chooseplayer - 1] % 1000 == 998) {
            money[chooseplayer - 1] += 2;
            lblMoney[chooseplayer - 1]->Caption = IntToStr(money[chooseplayer - 1]);
            LabelMoney->Caption = IntToStr(money[chooseplayer - 1]);
        }
        if (money[chooseplayer - 1] % 1000 == 999) {
            money[chooseplayer - 1] += 1;
            lblMoney[chooseplayer - 1]->Caption = IntToStr(money[chooseplayer - 1]);
            LabelMoney->Caption = IntToStr(money[chooseplayer - 1]);
        }
        if (money[CurrentHatch - 1] % 10 == 8) {
            money[CurrentHatch - 1] += 2;
            lblMoney[CurrentHatch - 1]->Caption = IntToStr(money[CurrentHatch - 1]);
            LabelMoney->Caption = IntToStr(money[CurrentHatch - 1]);
        }
        if (money[CurrentHatch - 1] % 10 == 9) {
            money[CurrentHatch - 1] += 1;
            lblMoney[CurrentHatch - 1]->Caption = IntToStr(money[CurrentHatch - 1]);
            LabelMoney->Caption = IntToStr(money[CurrentHatch - 1]);
        }
        tmrMoney->Enabled = False;
    }

    if (Reward >= 100) {
        Reward -= 100;
    } else {
        Reward = 0;
        if (answer == RandomPlace) {
            ModeOfGame = 0;
            if (!Settings->HostMode) {
                Wait = 0;
                tmrWaiting->Enabled = true;
            } else {
                Wait = 4;
                tmrWaiting->Enabled = false;
            }
            ResetForm();
        }
    }
}

// ---------------------------------------------------------------------------
void __fastcall TF::tmrLogTimer(TObject* Sender) {
    mlog->Clear();
    mlog->Lines->Add("chooseplayer = " + IntToStr(chooseplayer));
    mlog->Lines->Add("CurrentHatch = " + IntToStr(CurrentHatch));
    mlog->Lines->Add("ingame[5] = {" + BoolToStr(ingame[0], 0) + ", " + BoolToStr(ingame[1], 0) + ", " +
        BoolToStr(ingame[2], 0) + ", " + BoolToStr(ingame[3], 0) + ", " + BoolToStr(ingame[4], 0) + "}");
    mlog->Lines->Add("opened_now[6] = {" + IntToStr(opened_now[0]) + ", " + IntToStr(opened_now[1]) + ", " +
        IntToStr(opened_now[2]) + ", " + IntToStr(opened_now[3]) + ", " + IntToStr(opened_now[4]) + ", " +
        IntToStr(opened_now[5]) + "}");
    mlog->Lines->Add("CantFall = " + IntToStr(CantFall));
    mlog->Lines->Add("RoundOfGame = " + IntToStr(RoundOfGame));
}

// ---------------------------------------------------------------------------
void TF::ResetForm() // ���������� ����� � �������� ���������
{
    for (int i = 0; i <= RoundOfGame; ++i) {
        F->lblAnswers[i]->Visible = false;
    }

    imgNumber[0]->Visible = False;
    imgNumber[1]->Visible = False;
    imgNumber[2]->Visible = False;
    imgNumber[3]->Visible = False;
    imgNumber[4]->Visible = False;
    F->imgChoosenAnswer->Visible = False;
    F->imgChAnsLeft->Visible = false;
    F->imgChAnsRight->Visible = false;
    F->imgTimer->Visible = False;
    F->lblTimer->Visible = False;
    F->imgTicker->Visible = False;
    F->imgPulse->Visible = False;
    F->imgTotalPrize->Visible = False;
    F->imgPulseBar->Visible = False;
    F->imgQuestion->Picture->LoadFromFile("Data\\rr_quest.png");
    F->LabelQuestion->Visible = False;
    F->LabelMoney->Visible = False;
    hatches_enable_state(false);
    UpdateHatches();
}

void __fastcall TF::tmrWaitingFinalTimer(TObject* Sender) {
    // ��������� ����� ���� "������� �������"
    Wait++ ;
    switch (ModeOfGame) {
    case 0: {
            if (Wait == 5) {
                imgNumber[0]->Enabled = False;
                imgNumber[1]->Enabled = False;
                imgNumber[2]->Enabled = False;
                imgNumber[3]->Enabled = False;
                imgNumber[4]->Enabled = False;
                CanChoose = 0;
                for (int i = 0; i < 5; i++) {
                    if (ingame[i]) {
                        LeaderPlayerAtFinal = i;
                    }
                }
                PlaySound("rr_final.wav");
                hatches_enable_state(false);
                imgSplash->Picture->LoadFromFile("Data\\Final.png");
                imgSplash->Visible = True;
                CantFall = -1;
                LightHatchesW(255, 2);
                MechanizmSetHatchesStates();
                imgPlace->Picture->LoadFromFile("Data\\Place.png");
                FinalRoundOfGame = 1;
            }
            if (Wait == 11) {
                imgSplash->Visible = False;
                hatches_enable_state(false);
                for (int i = 0; i < 5; i++) {
                    if (ingame[i]) {
                        switch (i) {
                        case 0: {
                                imgPlayer[0]->Top = int(imgPlace->Top + (imgPlace->Height - imgPlayer[0]->Height) / 2);
                                imgPlayer[0]->Left = int(imgPlace->Left + (imgPlace->Width - imgPlayer[0]->Width) / 2);
                            } break;

                        case 1: {
                                imgPlayer[1]->Top = int(imgPlace->Top + (imgPlace->Height - imgPlayer[0]->Height) / 2);
                                imgPlayer[1]->Left = int(imgPlace->Left + (imgPlace->Width - imgPlayer[0]->Width) / 2);
                            } break;

                        case 2: {
                                imgPlayer[2]->Top = int(imgPlace->Top + (imgPlace->Height - imgPlayer[0]->Height) / 2);
                                imgPlayer[2]->Left = int(imgPlace->Left + (imgPlace->Width - imgPlayer[0]->Width) / 2);
                            } break;

                        case 3: {
                                imgPlayer[3]->Top = int(imgPlace->Top + (imgPlace->Height - imgPlayer[0]->Height) / 2);
                                imgPlayer[3]->Left = int(imgPlace->Left + (imgPlace->Width - imgPlayer[0]->Width) / 2);
                            } break;

                        case 4: {
                                imgPlayer[4]->Top = int(imgPlace->Top + (imgPlace->Height - imgPlayer[0]->Height) / 2);
                                imgPlayer[4]->Left = int(imgPlace->Left + (imgPlace->Width - imgPlayer[0]->Width) / 2);
                            } break;
                        }
                    }
                }
            }
            if (Wait == 18) {
                imgChoosenAnswer->Visible = False;
                imgTimer->Visible = False;
                lblTimer->Visible = False;
                LabelMoney->Visible = False;
                imgPulse->Visible = False;
                imgPulseBar->Visible = false;
                imgTotalPrize->Visible = false;
                imgTicker->Visible = false;
                imgChAnsLeft->Visible = false;
                imgChAnsRight->Visible = false;
                imgQuestion->Picture->LoadFromFile("Data\\rr_quest.png");
                imgQuestion->Visible = False;
                LabelQuestion->Visible = False;
                lblRightAnswer->Visible = False;
                if (Settings->PlayerType[LeaderPlayerAtFinal] == bbHuman) {
                    btnMechStart->Enabled = True;
                    imgMechanizm->Enabled = True;
                } else {
                    switch (Settings->PlayerType[LeaderPlayerAtFinal]) {
                    case bbFoooool:
                        TimeToDecide = 5 + random(41);
                        break;
                    case bbFooly:
                        TimeToDecide = 5 + random(31);
                        break;
                    case bbNormal:
                        TimeToDecide = 5 + random(21);
                        break;
                    case bbHard:
                        TimeToDecide = 1 + random(16);
                        break;
                    case bbVeryHard:
                        TimeToDecide = 1 + random(11);
                        break;
                    }
#ifdef _DEBUG
                    TimeToDecide = 1;
#endif

                    imgMechanizmClick(imgMechanizm);
                    Wait = 0;
                    tmrDecided->Enabled = true;
                }
                RoundOfGame = -1;
                chooseplayer = 255;
                hatches_enable_state(true);
                tmrWaitingFinal->Enabled = False;
            }
            if (Wait == 19) {
                ModeOfGame = 1;
                Wait = 0;
                hatches_enable_state(false);
            }
        } break;
    case 1: {
            if (Wait == 5) {
                RoundOfGame = 5;
                imgQuestion->Visible = True;
                imgBorder->Visible = true;
                imgPulseBar->Visible = true;
                imgTicker->Visible = true;
                imgPulse->Visible = True;
                imgTotalPrize->Visible = True;
                if (FinalRoundOfGame == 1) {
                    LabelMoney->Caption = "50000";
                }
                if (FinalRoundOfGame == 2) {
                    LabelMoney->Caption = "100000";
                }
                if (FinalRoundOfGame == 3) {
                    LabelMoney->Caption = "1000000";
                }
                LabelMoney->Visible = True;
            }
            if (Wait == 8) {
                PlayMusic("rr_question.wav");
                TimeOfQuestion = 10;
                load_final_question();
                lblTimer->Caption = IntToStr(TimeOfQuestion);
                lblTimer->Visible = True;
                imgTimer->Picture->LoadFromFile("Data\\" + IntToStr(TimeOfQuestion) + "sec.png");
                imgTimer->Visible = True;
                edFinalAnswer->Top = imgQuestion->Top + imgQuestion->Height - 30 - edFinalAnswer->Height;
                edFinalAnswer->Left = (int)(imgQuestion->Left + (imgQuestion->Width - edFinalAnswer->Width) / 2.);
                edFinalAnswer->Visible = True;
                if (Settings->PlayerType[LeaderPlayerAtFinal] == bbHuman) {
                    edFinalAnswer->Enabled = true;
                } else {
                    edFinalAnswer->Enabled = false;
                }
                edFinalAnswer->Text = "";
            }
            if (Wait == 13) {
                tmrTime->Enabled = True;
                PlayMusic("rr_20sec.wav");
                ModeOfGame = 2;
                tmrWaitingFinal->Enabled = False;
            }
        } break;
    case 3: { // ����� ��� �����
            edFinalAnswer->Visible = false;
            if (_Parse(edFinalAnswer->Text)) {
                PlayMusic("rr_true.wav");
                lblRightAnswer->Top = imgQuestion->Top + 160;
                lblRightAnswer->Height = 19;
                lblRightAnswer->AutoSize = true;
                lblRightAnswer->Caption = base[NumberOfQuestion].Answers[0];
                lblRightAnswer->Left =
                    (int)(imgQuestion->Left + (imgQuestion->Width / 2.) - (lblRightAnswer->Width / 2.));
                lblRightAnswer->Visible = True;
                imgChoosenAnswer->Width = lblRightAnswer->Width;
                imgChoosenAnswer->Top = lblRightAnswer->Top - 10;
                imgChoosenAnswer->Left = lblRightAnswer->Left;
                imgChAnsLeft->Top = imgChoosenAnswer->Top;
                imgChAnsLeft->Left = imgChoosenAnswer->Left - imgChAnsLeft->Width;
                imgChAnsRight->Left = imgChoosenAnswer->Left + imgChoosenAnswer->Width;
                imgChAnsRight->Top = imgChoosenAnswer->Top;
                imgChoosenAnswer->Visible = True;
                imgChAnsLeft->Visible = true;
                imgChAnsRight->Visible = true;
                Reward = StrToInt(LabelMoney->Caption);
                imgQuestion->Picture->LoadFromFile("Data\\quest_correct.png");
                LightHatchesW(255, 4);
                MechanizmSetHatchesStates();
                ModeOfGame = 4;
            } else {
                PlayMusic("rr_false.wav");
                lblRightAnswer->Top = imgQuestion->Top + 160;
                lblRightAnswer->Height = 19;
                lblRightAnswer->AutoSize = true;
                lblRightAnswer->Caption = base[NumberOfQuestion].Answers[0];
                lblRightAnswer->Left =
                    (int)(imgQuestion->Left + (imgQuestion->Width / 2.) - (lblRightAnswer->Width / 2.));
                lblRightAnswer->Visible = True;
                imgChoosenAnswer->Width = lblRightAnswer->Width;
                imgChoosenAnswer->Top = lblRightAnswer->Top - 10;
                imgChoosenAnswer->Left = lblRightAnswer->Left;
                imgChAnsLeft->Top = imgChoosenAnswer->Top;
                imgChAnsLeft->Left = imgChoosenAnswer->Left - imgChAnsLeft->Width;
                imgChAnsRight->Left = imgChoosenAnswer->Left + imgChoosenAnswer->Width;
                imgChAnsRight->Top = imgChoosenAnswer->Top;
                imgChoosenAnswer->Visible = True;
                imgChAnsLeft->Visible = true;
                imgChAnsRight->Visible = true;
                LightHatchesW(3, 4);
                ModeOfGame = 5;
                WaitForFate = 10 + random(11);
                MechanizmSetHatchesStates();
                imgQuestion->Picture->LoadFromFile("Data\\quest_incorrect.png");
                imgPlace->Picture->LoadFromFile("Data\\Place_red_zero.png");
            }
            Wait = 0;
        } break;
    case 4: {
            if (Wait == 8) {
                MoneyTransferMode = 0;
                tmrMoney->Enabled = True;
            }
            if (Wait == 18) {
                if (FinalRoundOfGame < 3) {
                    btnGetMoney->Visible = True;
                    btnContinueGame->Visible = True;
                }
                tmrWaitingFinal->Enabled = False;
                imgChoosenAnswer->Visible = False;
                imgBorder->Visible = false;
                imgChAnsLeft->Visible = false;
                imgChAnsRight->Visible = false;
                imgTimer->Visible = False;
                lblTimer->Visible = False;
                LabelMoney->Visible = False;
                imgPulse->Visible = False;
                imgQuestion->Picture->LoadFromFile("Data\\rr_quest.png");
                imgQuestion->Visible = False;
                LabelQuestion->Visible = False;
                lblRightAnswer->Visible = False;
                imgTicker->Visible = false;
                imgPulseBar->Visible = false;
                imgTotalPrize->Visible = false;
                if (FinalRoundOfGame == 3) {
                    Wait = 0;
                    ModeOfGame = 8;
                    tmrWaitingFinal->Enabled = True;
                }
            }
        } break;
    case 5: { // ����� ��� �������� �����, �� ������� � ����
            if (Wait == WaitForFate) {
                OpenRndHatches();
                if (opened_now[CurrentHatch] == 1) {
                    PlayMusic("rr_fall.wav");
                    for (int i = 0; i < 5; i++)
                        if (ingame[i]) {
                            lblPlayer[i]->Visible = False;
                            lblMoney[i]->Visible = False;
                            LabelMoney->Caption = IntToStr(money[i]);
                            switch (i) {
                            case 0:
                                imgPlayer[0]->Visible = False;
                                break;
                            case 1:
                                imgPlayer[1]->Visible = False;
                                break;
                            case 2:
                                imgPlayer[2]->Visible = False;
                                break;
                            case 3:
                                imgPlayer[3]->Visible = False;
                                break;
                            case 4:
                                imgPlayer[4]->Visible = False;
                                break;
                            }
                        }
                    imgChoosenAnswer->Visible = False;
                    imgChAnsLeft->Visible = false;
                    imgChAnsRight->Visible = false;
                    imgBorder->Visible = false;
                    imgTimer->Visible = False;
                    lblTimer->Visible = False;
                    LabelMoney->Visible = False;
                    imgPulse->Visible = False;
                    imgTicker->Visible = false;
                    imgPulseBar->Visible = false;
                    imgTotalPrize->Visible = false;
                    imgQuestion->Picture->LoadFromFile("Data\\rr_quest.png");
                    imgQuestion->Visible = False;
                    LabelQuestion->Visible = False;
                    lblRightAnswer->Visible = False;
                    ModeOfGame = 7;
                    Wait = 23;
                } else {
                    PlaySound("rr_notfall.wav");
                    ModeOfGame = 6;
                    Wait = 30;
                }
            }
        } break;
    case 6: {
            if (Wait == 32) {
                imgPlace->Picture->LoadFromFile("Data\\Place.png");
                // PlaySound("rr_save.wav");
                LightHatchesW(1, 0);
                MechanizmSetHatchesStates();
                if (FinalRoundOfGame == 3) {
                    for (int i = 0; i < 5; i++)
                        if (ingame[i]) {
                            lblPlayer[i]->Visible = False;
                            lblMoney[i]->Visible = False;
                            LabelMoney->Caption = IntToStr(money[i] + 1000000);
                            imgChoosenAnswer->Visible = False;
                            imgTimer->Visible = False;
                            lblTimer->Visible = False;
                            LabelMoney->Visible = False;
                            imgTicker->Visible = false;
                            imgPulseBar->Visible = false;
                            imgTotalPrize->Visible = false;
                            imgBorder->Visible = false;
                            imgChAnsLeft->Visible = false;
                            imgChAnsRight->Visible = false;
                            imgPulse->Visible = False;
                            imgQuestion->Picture->LoadFromFile("Data\\rr_quest.png");
                            imgQuestion->Visible = False;
                            LabelQuestion->Visible = False;
                            lblRightAnswer->Visible = False;
                        }
                    Wait = 0;
                    ModeOfGame = 8;
                }
            }
            if (Wait == 35) {
                LightHatchesW(255, 1);
                MechanizmSetHatchesStates();
                Wait = 10;
                ModeOfGame = 0;
            }
        } break;
    case 7: {
            if (Wait == 30) {
                LightHatchesW(3, 0);
                imgTotalPrize->Top = imgBorder->Top + 30;
                LabelMoney->Top = imgTotalPrize->Top + 10;
                LabelMoney->Visible = True;
                LabelMoney->Left = imgTotalPrize->Left + 9;
                imgTotalPrize->Visible = True;
                imgBorder->Visible = true;
                MechanizmSetHatchesStates();
                PlayMusic("rr_closing.wav");
                tmrWaitingFinal->Enabled = False;
            }
        } break;
    case 8: {
            if (Wait == 8) {
                LightHatchesW(2, 3);
                imgTotalPrize->Top = imgBorder->Top + 30;
                LabelMoney->Top = imgTotalPrize->Top + 10;
                LabelMoney->Visible = True;
                LabelMoney->Left = imgTotalPrize->Left + 9;
                imgTotalPrize->Visible = True;
                imgBorder->Visible = true;
                MechanizmSetHatchesStates();
                PlayMusic("rr_closing.wav");
                tmrWaitingFinal->Enabled = False;
            }
        } break;
    }
}

// ---------------------------------------------------------------------------

void __fastcall TF::imgHatch0Click(TObject* Sender) {
    if (FinalRoundOfGame > 0 && CanChoose == 1) {
        CurrentHatch = 0;
        CanChoose = 0;
        UpdateHatches();
        tmrWaitingFinal->Enabled = True;
        for (int i = 0; i < 5; i++) {
            if (ingame[i]) {
                switch (i) {
                case 0: {
                        imgPlayer[0]->Top =
                            int(imgHatch[0]->Top + (imgHatch[0]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[0]->Left =
                            int(imgHatch[0]->Left + (imgHatch[0]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 1: {
                        imgPlayer[1]->Top =
                            int(imgHatch[0]->Top + (imgHatch[0]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[1]->Left =
                            int(imgHatch[0]->Left + (imgHatch[0]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 2: {
                        imgPlayer[2]->Top =
                            int(imgHatch[0]->Top + (imgHatch[0]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[2]->Left =
                            int(imgHatch[0]->Left + (imgHatch[0]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 3: {
                        imgPlayer[3]->Top =
                            int(imgHatch[0]->Top + (imgHatch[0]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[3]->Left =
                            int(imgHatch[0]->Left + (imgHatch[0]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                case 4: {
                        imgPlayer[4]->Top =
                            int(imgHatch[0]->Top + (imgHatch[0]->Height - imgNumber[0]->Height) / 2 - 5);
                        imgPlayer[4]->Left =
                            int(imgHatch[0]->Left + (imgHatch[0]->Width - imgNumber[0]->Width) / 2 - 5);
                    } break;
                }
            }
        }
    }
}

// ---------------------------------------------------------------------------
void __fastcall TF::edFinalAnswerKeyPress(TObject* Sender, wchar_t& Key) {
    if ((Key == 13) && (ModeOfGame == 2)) {
        tmrTime->Enabled = False;
        edFinalAnswer->Visible = False;
        Wait = 0;
        ModeOfGame = 3;
        tmrWaitingFinal->Enabled = True;
    }
}

// ---------------------------------------------------------------------------
void TF::TransferMoneyFinal() {
    int pos;
    for (int i = 0; i < 5; i++) {
        if (ingame[i]) {
            pos = i;
        }
    }
    if (Reward > 6666) {
        money[pos] += 6666;
        LabelMoney->Caption = IntToStr(money[pos]);
        lblMoney[pos]->Caption = LabelMoney->Caption;
        Reward -= 6666;
    } else {
        money[pos] += Reward;
        LabelMoney->Caption = IntToStr(money[pos]);
        lblMoney[pos]->Caption = LabelMoney->Caption;
        tmrMoney->Enabled = False;
    }
}

void __fastcall TF::btnContinueGameClick(TObject* Sender) {
    int pos;
    for (int i = 0; i < 5; i++) {
        if (ingame[i]) {
            pos = i;
        }
    }
    switch (FinalRoundOfGame) {
    case 1: {
            money[pos] -= 50000;
            lblMoney[pos]->Caption = IntToStr(money[pos]);
        } break;
    case 2: {
            money[pos] -= 100000;
            lblMoney[pos]->Caption = IntToStr(money[pos]);
        } break;
    }
    FinalRoundOfGame++ ;
    Wait = 10;
    LightHatchesW(255, 1);
    MechanizmSetHatchesStates();
    ModeOfGame = 0;
    RoundOfGame = -1;
    btnGetMoney->Visible = False;
    btnContinueGame->Visible = False;
    tmrWaitingFinal->Enabled = True;
}
// ---------------------------------------------------------------------------

void __fastcall TF::FormClose(TObject* Sender, TCloseAction& Action) {
    MenuForm->Show();

    for (int i = 0; i < 5; i++) {
        lblMoney[i]->Caption = "0";
        money[i] = 0;
        ingame[i] = true;
        lblPlayer[i]->Visible = True;
        lblMoney[i]->Visible = True;
    }

    imgNumber[0]->Enabled = False;
    imgNumber[1]->Enabled = False;
    imgNumber[2]->Enabled = False;
    imgNumber[3]->Enabled = False;
    imgNumber[4]->Enabled = False;

    RoundOfGame = -1;
    Wait = 0;
    ModeOfGame = 0;
    TransferAll = 1;
    FinalRoundOfGame = 0;
    LabelQuestion->Visible = False;
    LabelMoney->Visible = False;
    lblTimer->Visible = False;
    imgPulse->Visible = False;
    imgTimer->Visible = False;
    imgTicker->Visible = False;
    imgPulseBar->Visible = false;
    imgChAnsLeft->Visible = false;
    imgChAnsRight->Visible = false;
    imgChoosenAnswer->Visible = false;
    imgBorder->Visible = false;
    imgPlace->Picture->LoadFromFile("Data\\Place.png");
    imgSplash->Picture->LoadFromFile("Data\\Splash-1.png");
    imgPlayer[0]->Visible = True;
    imgPlayer[1]->Visible = True;
    imgPlayer[2]->Visible = True;
    imgPlayer[3]->Visible = True;
    imgPlayer[4]->Visible = True;
    imgMechanizm->Enabled = True;

    // ���������� �������� ��������� � �������� �����
    if (!Settings->Fullscreen) {
        Settings->FormsWidth = Width;
        Settings->FormsHeight = Height;
        Settings->FormsTop = Top;
        Settings->FormsLeft = Left;
    }

    tmrLog->Enabled = False;
    tmrMoney->Enabled = False;
    tmrPulseAnimation->Enabled = False;
    tmrRotator->Enabled = False;
    tmrTime->Enabled = False;
    tmrWaiting->Enabled = False;
    tmrWaitingFinal->Enabled = False;

    MediaPlayer1->Close();
    MediaPlayer2->Close();

}
// ---------------------------------------------------------------------------

void __fastcall TF::FormShow(TObject* Sender) {
    SetPlayers();

    if (Settings->Fullscreen) {
        BorderStyle = bsNone;
        Width = Screen->Width;
        Height = Screen->Height;
        Top = 0;
        Left = 0;
    } else {
        BorderStyle = bsSizeable;
        Width = Settings->FormsWidth;
        Height = Settings->FormsHeight;
        Top = Settings->FormsTop;
        Left = Settings->FormsLeft;
    }

    tmrPulseAnimation->Enabled = true;

    imgBorder->Left = (ClientWidth - imgBorder->Width) / 2;
    imgBorder->Top = ClientHeight - imgBorder->Height;

    imgTicker->Top = imgQuestion->Top - 59;
    imgTicker->Left = imgQuestion->Left + 30;

    LabelQuestion->Top = imgQuestion->Top + 47;
    LabelQuestion->Left = imgQuestion->Left + 149;

    lblTimer->Top = imgTicker->Top + 31;
    lblTimer->Left = imgTicker->Left + 17;

    imgTimer->Top = imgTicker->Top + 13;
    imgTimer->Left = imgTicker->Left + 21;

    imgTotalPrize->Top = imgQuestion->Top - 28;
    imgTotalPrize->Left = imgQuestion->Left + 163;

    LabelMoney->Top = imgTotalPrize->Top + 10;
    LabelMoney->Left = imgTotalPrize->Left + 9;

    imgPulseBar->Top = imgQuestion->Top - 58;
    imgPulseBar->Left = imgQuestion->Left + 704;

    imgPulse->Top = imgPulseBar->Top + 8;
    imgPulse->Left = imgPulseBar->Left + 7;

    imgSplash->Visible = True;
    tmrSplash->Enabled = True;
    PlayMusic("rr_round.wav");

    imgNumber[0]->Enabled = False;
    imgNumber[1]->Enabled = False;
    imgNumber[2]->Enabled = False;
    imgNumber[3]->Enabled = False;
    imgNumber[4]->Enabled = False;

    Hatches();
    LoadGraphic();
    Randomize();
    tmrRotator->Interval = SpeedOfRotation;
    switchoffquestion();

    for (int i = 0; i < 5; i++) {
        lblPlayer[i]->Caption = Settings->PlayerNames[i];
    }

    SetQuestionsMaximum(8, 7, 7, 4);

    imgPlayer[0]->Top = int(imgHatch[1]->Top + (imgHatch[1]->Height - imgNumber[0]->Height) / 2 - 5);
    imgPlayer[0]->Left = int(imgHatch[1]->Left + (imgHatch[1]->Width - imgNumber[0]->Width) / 2 - 5);

    imgPlayer[1]->Top = int(imgHatch[2]->Top + (imgHatch[2]->Height - imgNumber[1]->Height) / 2 - 5);
    imgPlayer[1]->Left = int(imgHatch[2]->Left + (imgHatch[2]->Width - imgNumber[1]->Width) / 2 - 5);

    imgPlayer[2]->Top = int(imgHatch[3]->Top + (imgHatch[3]->Height - imgNumber[2]->Height) / 2 - 5);
    imgPlayer[2]->Left = int(imgHatch[3]->Left + (imgHatch[3]->Width - imgNumber[2]->Width) / 2 - 5);

    imgPlayer[3]->Top = int(imgHatch[4]->Top + (imgHatch[4]->Height - imgNumber[3]->Height) / 2 - 5);
    imgPlayer[3]->Left = int(imgHatch[4]->Left + (imgHatch[4]->Width - imgNumber[3]->Width) / 2 - 5);

    imgPlayer[4]->Top = int(imgHatch[5]->Top + (imgHatch[5]->Height - imgNumber[4]->Height) / 2 - 5);
    imgPlayer[4]->Left = int(imgHatch[5]->Left + (imgHatch[5]->Width - imgNumber[4]->Width) / 2 - 5);

    tmrPulseAnimation->Enabled = True;
}
// ---------------------------------------------------------------------------

void __fastcall TF::btnGetMoneyClick(TObject* Sender) {
    Wait = 7;
    ModeOfGame = 8;
    btnGetMoney->Visible = False;
    btnContinueGame->Visible = False;
    tmrWaitingFinal->Enabled = True;
}
// ---------------------------------------------------------------------------

void __fastcall TF::FormResize(TObject* Sender) {
    static lock;
    if (lock) {
        return;
    }

    lock = true;

    if (Settings->Fullscreen) {
        Top = 0;
        Left = 0;
    }

    imgQuestion->Left = (ClientWidth - imgQuestion->Width) / 2;
    imgQuestion->Top = ClientHeight - imgQuestion->Height - 50;

    imgBorder->Left = (ClientWidth - imgBorder->Width) / 2;
    imgBorder->Top = ClientHeight - imgBorder->Height;

    imgPlace->Left = int((ClientWidth - imgPlace->Width) / 2 - 1 / Width * 80);
    imgPlace->Top = 50;

    imgPlayers->Top = 0;
    imgPlayers->Left = ClientWidth - imgPlayers->Width;

    imgTotalPrize->Top = imgQuestion->Top - 28;
    imgTotalPrize->Left = imgQuestion->Left + 163;
    if (FinalRoundOfGame >= 1 && (ModeOfFinalGame == 7 || ModeOfFinalGame == 8)) {
        imgTotalPrize->Top = imgBorder->Top + 30;
    }

    LabelMoney->Top = imgTotalPrize->Top + 10;
    LabelMoney->Left = imgTotalPrize->Left + 9;

    imgHatch[3]->Left = imgPlace->Left + 116;
    imgHatch[4]->Left = imgPlace->Left + 225;
    imgHatch[5]->Left = imgPlace->Left + 225;
    imgHatch[0]->Left = imgPlace->Left + 116;
    imgHatch[1]->Left = imgPlace->Left + 8;
    imgHatch[2]->Left = imgPlace->Left + 8;

    imgHatch[3]->Top = imgPlace->Top + 0;
    imgHatch[4]->Top = imgPlace->Top + 56;
    imgHatch[5]->Top = imgPlace->Top + 176;
    imgHatch[0]->Top = imgPlace->Top + 236;
    imgHatch[1]->Top = imgPlace->Top + 176;
    imgHatch[2]->Top = imgPlace->Top + 56;

    imgTicker->Top = imgQuestion->Top - 59;
    imgTicker->Left = imgQuestion->Left + 30;

    LabelQuestion->Top = imgQuestion->Top + 47;
    F->LabelQuestion->Left = (int)(F->imgQuestion->Left + (F->imgQuestion->Width - F->LabelQuestion->Width) / 2.);

    lblTimer->Top = imgTicker->Top + 31;
    lblTimer->Left = imgTicker->Left + 17;

    imgTimer->Top = imgTicker->Top + 13;
    imgTimer->Left = imgTicker->Left + 21;

    imgPulseBar->Top = imgQuestion->Top - 58;
    imgPulseBar->Left = imgQuestion->Left + 704;

    imgPulse->Top = imgPulseBar->Top + 8;
    imgPulse->Left = imgPulseBar->Left + 7;

    btnExit->Top = Height - btnExit->Height;
    btnExit->Left = Width - btnExit->Width;

    lblExit->Top = 5;
    lblExit->Left = 5;

    lblTimer->Top = imgTicker->Top + 31;
    lblTimer->Left = imgTicker->Left + 17;

    imgTimer->Top = imgTicker->Top + 13;
    imgTimer->Left = imgTicker->Left + 21;

    // ������� ��������� ��� ���� ������� � �����
    int offcet = 0;
    for (int i = 0; i < 5; ++i) {
        CreateLabel(lblPlayer, i, 15 + offcet, imgPlayers->Left + 67, 201, 20, Settings->PlayerNames[i]);
        CreateLabel(lblMoney, i, 43 + offcet, imgPlayers->Left + 80, 176, 25, money[i]);
        offcet += 83;
    }

    edFinalAnswer->Top = imgQuestion->Top + 214;
    edFinalAnswer->Left = imgQuestion->Left + 364;

    ResizeAnswers();
    Choosen_Answer_Change_Position();

    imgMechanizm->Left = 0;
    imgMechanizm->Top = 145;
    imgMechanizm->Picture->LoadFromFile("Data\\�����_" + IntToStr(MechState) + ".png");

    imgSplash->Left = int((F->ClientWidth - imgSplash->Width) / 2);
    imgSplash->Top = int((F->ClientHeight - imgSplash->Height) / 2);
    imgSplash->BringToFront();

    for (int i = 0; i < 5; ++i) {
        int j = i + 1;
        imgPlayer[i]->Top = int(imgHatch[j]->Top + (imgHatch[j]->Height - imgNumber[i]->Height) / 2 - 5);
        imgPlayer[i]->Left = int(imgHatch[j]->Left + (imgHatch[j]->Width - imgNumber[i]->Width) / 2 - 5);
        imgPlayer[i]->Visible = True;
    }

    imgSplash->Center = true;
    imgSplash->Width = (F->Width > F->Height) ? F->Width : F->Height;
    imgSplash->Height = imgSplash->Width;

    lock = false;
}

// ---------------------------------------------------------------------------
void __fastcall TF::tmrMechamizmTimer(TObject* Sender) {
    if (MechanizmOn == -1) {
        if (++MechState == 16) {
            tmrMechamizm->Enabled = False;
        }
    } else {
        if (--MechState == 1) {
            tmrMechamizm->Enabled = False;
        }
    }
    imgMechanizm->Picture->LoadFromFile("Data\\�����_" + IntToStr(MechState) + ".png");
}
// ---------------------------------------------------------------------------

void __fastcall TF::imgMechanizmClick(TObject* Sender) {
    if ((MechanizmOn == 0) || (MechanizmOn == 1)) {
        btnMechStartClick(F->btnMechStart);
        tmrMechamizm->Enabled = True;
    } else {
        btnMechStopClick(F->btnMechStop);
        tmrMechamizm->Enabled = True;
    }
}
// ---------------------------------------------------------------------------

void __fastcall TF::tmrSplashTimer(TObject* Sender) {
    Wait++ ;
    if (Wait == 5) {
        tmrSplash->Enabled = False;
        imgSplash->Visible = False;
        Wait = 0;
    }
}
// ---------------------------------------------------------------------------

void __fastcall TF::lblExitClick(TObject* Sender) { btnExitClick(btnExit); }

// ---------------------------------------------------------------------------
void ShowError(int errcode) {
    switch (errcode) {
    case 1:
        ShowMessage("������ �������� ���� ��������: ��� ���� �� �������!");
        exit(1);
    case 2:
        F->FatalError = 1;
        ShowMessage("������ �������� ���� ��������: ���� � ������ '" + Settings->LastBase + "' �� ����������!");
        exit(1);
    }
}

// ---------------------------------------------------------------------------
void DumpMemory(int errcode) {
    TFileStream* stream = new TFileStream("crash.dat", fmCreate);

    AnsiString str = "";

    str = "LastBase = " + Settings->LastBase + "\n\r";
    stream->Write(& str[1], str.Length());

    int n = F->NumberOfQuestion;

    str = "Number of question = " + IntToStr(n) + "\n\r";
    stream->Write(& str[1], str.Length());

    str = "Question = " + IntToStr(base[n].Round) + ". " + base[n].Question + "\n\r";
    stream->Write(& str[1], str.Length());

    str = "Ingame = [";
    for (int i = 0; i < 5; i++) {
        str += BoolToStr(F->ingame[i]) + ",";
    }
    str += "]\n\r";
    stream->Write(& str[1], str.Length());

    str = "opened_now = [";
    for (int i = 0; i < 6; i++) {
        str += BoolToStr(opened_now[i]) + ",";
    }
    str += "]\n\r";
    stream->Write(& str[1], str.Length());

    stream->Free();
}

void __fastcall TF::tmrDecidedTimer(TObject* Sender) {
    Wait++ ;
    if (Wait == TimeToDecide) {
        imgMechanizmClick(imgMechanizm);
        tmrDecided->Enabled = false;
        if (FinalRoundOfGame > 0) {
            Wait = 18;
        }
        if (RoundOfGame >= 1 && RoundOfGame <= 4) {
            Wait = 0;
        }
    }
}

// ---------------------------------------------------------------------------
void SetQuestionsMaximum(int FirstRound, int SecondRound, int ThirdRound, int FouthRound) {
    colquestions[0] = FirstRound;
    colquestions[1] = SecondRound;
    colquestions[2] = ThirdRound;
    colquestions[3] = FouthRound;
}

// ----------------------------------------------------------------------------
void __fastcall TF::tmrLightAnimationTimer(TObject* Sender) {
    int pos1[2], pos2[2], pos3[2], pos4[2], pos5[2], pos6[2];

    pos1[0] = imgPlace->Left + 8;
    pos1[1] = imgPlace->Top + 176;

    pos2[0] = imgPlace->Left + 8;
    pos2[1] = imgPlace->Top + 56;

    pos3[0] = imgPlace->Left + 116;
    pos3[1] = imgPlace->Top + 0;

    pos4[0] = imgPlace->Left + 225;
    pos4[1] = imgPlace->Top + 56;

    pos5[0] = imgPlace->Left + 225;
    pos5[1] = imgPlace->Top + 176;

    pos6[0] = imgPlace->Left + 116;
    pos6[1] = imgPlace->Top + 236;

    if (spin_round_mode) {
        if (imgHatch[1]->Top >= pos2[1]) {
            imgHatch[1]->Top -= 4;

            imgHatch[2]->Left += 4;
            imgHatch[2]->Top -= 2;

            imgHatch[3]->Left += 4;
            imgHatch[3]->Top += 2;

            imgHatch[4]->Top += 4;

            imgHatch[5]->Left -= 4;
            imgHatch[5]->Top += 2;

            imgHatch[0]->Left -= 4;
            imgHatch[0]->Top -= 2;
        } else {
            imgHatch[1]->Top = pos2[1];

            imgHatch[2]->Left = pos3[0];
            imgHatch[2]->Top = pos3[1];

            imgHatch[3]->Left = pos4[0];
            imgHatch[3]->Top = pos4[1];

            imgHatch[4]->Top = pos5[1];

            imgHatch[5]->Left = pos6[0];
            imgHatch[5]->Top = pos6[1];

            imgHatch[0]->Left = pos1[0];
            imgHatch[0]->Top = pos1[1];

            spin_round_mode = 0;
        }
    } else {
        if (imgHatch[1]->Top < pos1[1]) {
            imgHatch[1]->Top += 4;

            imgHatch[2]->Left -= 4;
            imgHatch[2]->Top += 2;

            imgHatch[3]->Left -= 4;
            imgHatch[3]->Top -= 2;

            imgHatch[4]->Top -= 4;

            imgHatch[5]->Left += 4;
            imgHatch[5]->Top -= 2;

            imgHatch[0]->Left += 4;
            imgHatch[0]->Top += 2;
        } else {
            imgHatch[1]->Top = pos1[1];

            imgHatch[2]->Left = pos2[0];
            imgHatch[2]->Top = pos2[1];

            imgHatch[3]->Left = pos3[0];
            imgHatch[3]->Top = pos3[1];

            imgHatch[4]->Top = pos4[1];

            imgHatch[5]->Left = pos5[0];
            imgHatch[5]->Top = pos5[1];

            imgHatch[0]->Left = pos6[0];
            imgHatch[0]->Top = pos6[1];

            tmrLightAnimation->Enabled = false;

            after_spin_lights();
        }
    }

}
// ----------------------------------------------------------------------------

void __fastcall TF::ControlLabelClick(TObject* Sender) {
    if (ModeOfGame == 3 && CanAnswer == 1 && Settings->PlayerType[chooseplayer - 1] == bbHuman) {
        switch (RoundOfGame) {
        case 1:
            F->Reward = 1000;
            break;
        case 2:
            F->Reward = 2000;
            break;
        case 3:
            F->Reward = 3000;
            break;
        case 4:
            F->Reward = 4000;
            break;
        }

        // ���������, ����� ������ ����� ��� ������
        for (int i = 0; i < 5; ++i) {
            if (Sender == lblAnswers[i]) {
                answer = i;
            }
        }

        // �������� ������� �������� ������ � ��������� ������
        Proverka();
        ModeOfGame = 4;
        tmrTime->Enabled = False;
    }
    if (ModeOfGame == 1 && CanChoose == 1 && Settings->PlayerType[CurrentHatch - 1] == bbHuman) {
        if (Sender == lblPlayer[0] && CurrentHatch != 1) {
            F->imgHatch1Click(NULL);
        }
        if (Sender == lblPlayer[1] && CurrentHatch != 2) {
            F->imgHatch2Click(NULL);
        }
        if (Sender == lblPlayer[2] && CurrentHatch != 3) {
            F->imgHatch3Click(NULL);
        }
        if (Sender == lblPlayer[3] && CurrentHatch != 4) {
            F->imgHatch4Click(NULL);
        }
        if (Sender == lblPlayer[4] && CurrentHatch != 5) {
            F->imgHatch5Click(NULL);
        }
        CanChoose == 0;
    }
}

// ---------------------------------------------------------------------------
void TF::ResizeAnswers() {
    if (RoundOfGame == 1) {
        int middle = (int)((imgQuestion->Width) / 2.);
        lblAnswers[0]->Top = imgQuestion->Top + 160;
        lblAnswers[1]->Top = imgQuestion->Top + 160;
        lblAnswers[0]->Left =
            (int)(imgQuestion->Left + middle - 50 - (lblAnswers[0]->Width + lblAnswers[1]->Width) / 2.);
        lblAnswers[1]->Left = (int)(lblAnswers[0]->Left + (lblAnswers[0]->Width) + 100);
        imgNumber[0]->Top = lblAnswers[0]->Top - 2;
        imgNumber[0]->Left = lblAnswers[0]->Left - 30;
        imgNumber[1]->Top = lblAnswers[1]->Top - 2;
        imgNumber[1]->Left = lblAnswers[1]->Left - 30;
    }
    if (RoundOfGame == 2) {
        lblAnswers[0]->Top = imgQuestion->Top + 150;
        lblAnswers[1]->Top = imgQuestion->Top + 150;
        lblAnswers[2]->Top = imgQuestion->Top + 175;
        int middle = (int)((imgQuestion->Width) / 2.);
        if (lblAnswers[0]->Width > lblAnswers[2]->Width) {
            lblAnswers[0]->Left =
                (int)(imgQuestion->Left + middle - 50 - (lblAnswers[0]->Width + lblAnswers[1]->Width) / 2.);
            lblAnswers[1]->Left = (int)(lblAnswers[0]->Left + (lblAnswers[0]->Width) + 100);
            lblAnswers[2]->Left = lblAnswers[0]->Left;
        } else {
            lblAnswers[2]->Left =
                (int)(imgQuestion->Left + middle - 50 - (lblAnswers[2]->Width + lblAnswers[1]->Width) / 2.);
            lblAnswers[1]->Left = (int)(lblAnswers[2]->Left + (lblAnswers[2]->Width) + 100);
            lblAnswers[0]->Left = lblAnswers[2]->Left;
        }
        imgNumber[0]->Top = lblAnswers[0]->Top - 2;
        imgNumber[0]->Left = lblAnswers[0]->Left - 30;
        imgNumber[1]->Top = lblAnswers[1]->Top - 2;
        imgNumber[1]->Left = lblAnswers[1]->Left - 30;
        imgNumber[2]->Top = lblAnswers[2]->Top - 2;
        imgNumber[2]->Left = lblAnswers[2]->Left - 30;
    }
    if (RoundOfGame == 3) {
        lblAnswers[0]->Top = imgQuestion->Top + 150;
        lblAnswers[1]->Top = imgQuestion->Top + 150;
        lblAnswers[2]->Top = imgQuestion->Top + 175;
        lblAnswers[3]->Top = imgQuestion->Top + 175;
        int middle = (int)((imgQuestion->Width) / 2.);
        if (lblAnswers[0]->Width > lblAnswers[2]->Width) {
            lblAnswers[0]->Left =
                (int)(imgQuestion->Left + middle - 50 - (lblAnswers[0]->Width + lblAnswers[1]->Width) / 2.);
            if (lblAnswers[1]->Width > lblAnswers[3]->Width) {
                lblAnswers[1]->Left = (int)(lblAnswers[0]->Left + (lblAnswers[0]->Width) + 100);
                lblAnswers[3]->Left = lblAnswers[1]->Left;
            } else {
                lblAnswers[3]->Left = (int)(lblAnswers[0]->Left + (lblAnswers[0]->Width) + 100);
                lblAnswers[1]->Left = lblAnswers[3]->Left;
            }
            lblAnswers[2]->Left = lblAnswers[0]->Left;
        } else {
            lblAnswers[2]->Left =
                (int)(imgQuestion->Left + middle - 50 - (lblAnswers[2]->Width + lblAnswers[1]->Width) / 2.);
            if (lblAnswers[1]->Width > lblAnswers[3]->Width) {
                lblAnswers[1]->Left = (int)(lblAnswers[2]->Left + (lblAnswers[2]->Width) + 100);
                lblAnswers[3]->Left = lblAnswers[1]->Left;
            } else {
                lblAnswers[3]->Left = (int)(lblAnswers[2]->Left + (lblAnswers[2]->Width) + 100);
                lblAnswers[1]->Left = lblAnswers[3]->Left;
            }
            lblAnswers[0]->Left = lblAnswers[2]->Left;
        }

        for (int i = 0; i < 4; ++i) {
            imgNumber[i]->Top = lblAnswers[i]->Top - 2;
            imgNumber[i]->Left = lblAnswers[i]->Left - 30;
        }
    }
    if (RoundOfGame == 4) {
        for (int i = 0; i < 5; ++i) {
            lblAnswers[i]->Top = imgQuestion->Top + 150 + 25 * (i / 3);
        }
        double middle = imgQuestion->Width / 2.;
        lblAnswers[0]->Left =
            (int)(imgQuestion->Left + middle - 100 - (lblAnswers[0]->Width + lblAnswers[1]->Width +
                lblAnswers[2]->Width) / 2.);
        lblAnswers[1]->Left = (int)(lblAnswers[0]->Left + (lblAnswers[0]->Width) + 100);
        lblAnswers[2]->Left = (int)(lblAnswers[1]->Left + (lblAnswers[1]->Width) + 100);
        lblAnswers[3]->Left =
            (int)(imgQuestion->Left + middle - 50 - (lblAnswers[3]->Width + lblAnswers[4]->Width) / 2.);
        lblAnswers[4]->Left = (int)(lblAnswers[3]->Left + (lblAnswers[3]->Width) + 100);

        for (int i = 0; i < 5; ++i) {
            imgNumber[i]->Top = lblAnswers[i]->Top - 2;
            imgNumber[i]->Left = lblAnswers[i]->Left - 30;
        }

    }
}

// ---------------------------------------------------------------------------
void TF::ShowAnswers() {
    if (RoundOfGame == 1) {
        CreateLabel(lblAnswers, 0, imgQuestion->Top + 160, imgQuestion->Left + 300,
            (base[NumberOfQuestion].Answers[variants[0]]).Length()* 12, 20,
            base[NumberOfQuestion].Answers[variants[0]]);
        CreateLabel(lblAnswers, 1, imgQuestion->Top + 160, imgQuestion->Left + 600,
            (base[NumberOfQuestion].Answers[variants[1]]).Length()* 12, 20,
            base[NumberOfQuestion].Answers[variants[1]]);
        imgNumber[0]->Visible = True;
        imgNumber[1]->Visible = True;
    }
    if (RoundOfGame == 2) {
        CreateLabel(lblAnswers, 0, imgQuestion->Top + 150, imgQuestion->Left + 300,
            (base[NumberOfQuestion].Answers[variants[0]]).Length()* 12, 20,
            base[NumberOfQuestion].Answers[variants[0]]);
        CreateLabel(lblAnswers, 1, imgQuestion->Top + 150, imgQuestion->Left + 600,
            (base[NumberOfQuestion].Answers[variants[1]]).Length()* 12, 20,
            base[NumberOfQuestion].Answers[variants[1]]);
        CreateLabel(lblAnswers, 2, imgQuestion->Top + 175, imgQuestion->Left + 300,
            (base[NumberOfQuestion].Answers[variants[2]]).Length()* 12, 20,
            base[NumberOfQuestion].Answers[variants[2]]);
        imgNumber[0]->Visible = True;
        imgNumber[1]->Visible = True;
        imgNumber[2]->Visible = True;
    }
    if (RoundOfGame == 3) {
        CreateLabel(lblAnswers, 0, imgQuestion->Top + 150, imgQuestion->Left + 300,
            (base[NumberOfQuestion].Answers[variants[0]]).Length()* 12, 20,
            base[NumberOfQuestion].Answers[variants[0]]);
        CreateLabel(lblAnswers, 1, imgQuestion->Top + 150, imgQuestion->Left + 600,
            (base[NumberOfQuestion].Answers[variants[1]]).Length()* 12, 20,
            base[NumberOfQuestion].Answers[variants[1]]);
        CreateLabel(lblAnswers, 2, imgQuestion->Top + 175, imgQuestion->Left + 300,
            (base[NumberOfQuestion].Answers[variants[2]]).Length()* 12, 20,
            base[NumberOfQuestion].Answers[variants[2]]);
        CreateLabel(lblAnswers, 3, imgQuestion->Top + 175, imgQuestion->Left + 600,
            (base[NumberOfQuestion].Answers[variants[3]]).Length()* 12, 20,
            base[NumberOfQuestion].Answers[variants[3]]);
        imgNumber[0]->Visible = True;
        imgNumber[1]->Visible = True;
        imgNumber[2]->Visible = True;
        imgNumber[3]->Visible = True;
    }
    if (RoundOfGame == 4) {
        CreateLabel(lblAnswers, 0, imgQuestion->Top + 150, imgQuestion->Left + 150,
            (base[NumberOfQuestion].Answers[variants[0]]).Length()* 12, 20,
            base[NumberOfQuestion].Answers[variants[0]]);
        CreateLabel(lblAnswers, 1, imgQuestion->Top + 150, imgQuestion->Left + 450,
            (base[NumberOfQuestion].Answers[variants[1]]).Length()* 12, 20,
            base[NumberOfQuestion].Answers[variants[1]]);
        CreateLabel(lblAnswers, 2, imgQuestion->Top + 150, imgQuestion->Left + 750,
            (base[NumberOfQuestion].Answers[variants[2]]).Length()* 12, 20,
            base[NumberOfQuestion].Answers[variants[2]]);
        CreateLabel(lblAnswers, 3, imgQuestion->Top + 175, imgQuestion->Left + 300,
            (base[NumberOfQuestion].Answers[variants[3]]).Length()* 12, 20,
            base[NumberOfQuestion].Answers[variants[3]]);
        CreateLabel(lblAnswers, 4, imgQuestion->Top + 175, imgQuestion->Left + 600,
            (base[NumberOfQuestion].Answers[variants[4]]).Length()* 12, 20,
            base[NumberOfQuestion].Answers[variants[4]]);
        imgNumber[0]->Visible = True;
        imgNumber[1]->Visible = True;
        imgNumber[2]->Visible = True;
        imgNumber[3]->Visible = True;
        imgNumber[4]->Visible = True;
    }
}

void TF::Choosen_Answer_Change_Position() {
    if (ModeOfGame == 4) {
        switch (answer) {
        case 0: {
                imgChAnsLeft->Top = imgNumber[0]->Top - 10;
                imgChAnsLeft->Left = imgNumber[0]->Left - 10;
                imgChoosenAnswer->Top = imgChAnsLeft->Top;
                imgChoosenAnswer->Left = imgChAnsLeft->Left + imgChAnsLeft->Width;
                imgChAnsRight->Top = imgChoosenAnswer->Top;
                imgChAnsRight->Left = imgChoosenAnswer->Left + imgChoosenAnswer->Width;
            } break;
        case 1: {
                imgChAnsLeft->Top = imgNumber[1]->Top - 10;
                imgChAnsLeft->Left = imgNumber[1]->Left - 10;
                imgChoosenAnswer->Top = imgChAnsLeft->Top;
                imgChoosenAnswer->Left = imgChAnsLeft->Left + imgChAnsLeft->Width;
                imgChAnsRight->Top = imgChoosenAnswer->Top;
                imgChAnsRight->Left = imgChoosenAnswer->Left + imgChoosenAnswer->Width;
            } break;
        case 2: {
                imgChAnsLeft->Top = imgNumber[2]->Top - 10;
                imgChAnsLeft->Left = imgNumber[2]->Left - 10;
                imgChoosenAnswer->Top = imgChAnsLeft->Top;
                imgChoosenAnswer->Left = imgChAnsLeft->Left + imgChAnsLeft->Width;
                imgChAnsRight->Top = imgChoosenAnswer->Top;
                imgChAnsRight->Left = imgChoosenAnswer->Left + imgChoosenAnswer->Width;
            } break;
        case 3: {
                imgChAnsLeft->Top = imgNumber[3]->Top - 10;
                imgChAnsLeft->Left = imgNumber[3]->Left - 10;
                imgChoosenAnswer->Top = imgChAnsLeft->Top;
                imgChoosenAnswer->Left = imgChAnsLeft->Left + imgChAnsLeft->Width;
                imgChAnsRight->Top = imgChoosenAnswer->Top;
                imgChAnsRight->Left = imgChoosenAnswer->Left + imgChoosenAnswer->Width;
            } break;
        case 4: {
                imgChAnsLeft->Top = imgNumber[4]->Top - 10;
                imgChAnsLeft->Left = imgNumber[4]->Left - 10;
                imgChoosenAnswer->Top = imgChAnsLeft->Top;
                imgChoosenAnswer->Left = imgChAnsLeft->Left + imgChAnsLeft->Width;
                imgChAnsRight->Top = imgChoosenAnswer->Top;
                imgChAnsRight->Left = imgChoosenAnswer->Left + imgChoosenAnswer->Width;
            } break;
        }
    }
    if (ModeOfGame == 5) {
        switch (RandomPlace) {
        case 0: {
                imgChAnsLeft->Top = imgNumber[0]->Top - 10;
                imgChAnsLeft->Left = imgNumber[0]->Left - 10;
                imgChoosenAnswer->Top = imgChAnsLeft->Top;
                imgChoosenAnswer->Left = imgChAnsLeft->Left + imgChAnsLeft->Width;
                imgChAnsRight->Top = imgChoosenAnswer->Top;
                imgChAnsRight->Left = imgChoosenAnswer->Left + imgChoosenAnswer->Width;
            } break;
        case 1: {
                imgChAnsLeft->Top = imgNumber[1]->Top - 10;
                imgChAnsLeft->Left = imgNumber[1]->Left - 10;
                imgChoosenAnswer->Top = imgChAnsLeft->Top;
                imgChoosenAnswer->Left = imgChAnsLeft->Left + imgChAnsLeft->Width;
                imgChAnsRight->Top = imgChoosenAnswer->Top;
                imgChAnsRight->Left = imgChoosenAnswer->Left + imgChoosenAnswer->Width;
            } break;
        case 2: {
                imgChAnsLeft->Top = imgNumber[2]->Top - 10;
                imgChAnsLeft->Left = imgNumber[2]->Left - 10;
                imgChoosenAnswer->Top = imgChAnsLeft->Top;
                imgChoosenAnswer->Left = imgChAnsLeft->Left + imgChAnsLeft->Width;
                imgChAnsRight->Top = imgChoosenAnswer->Top;
                imgChAnsRight->Left = imgChoosenAnswer->Left + imgChoosenAnswer->Width;
            } break;
        case 3: {
                imgChAnsLeft->Top = imgNumber[3]->Top - 10;
                imgChAnsLeft->Left = imgNumber[3]->Left - 10;
                imgChoosenAnswer->Top = imgChAnsLeft->Top;
                imgChoosenAnswer->Left = imgChAnsLeft->Left + imgChAnsLeft->Width;
                imgChAnsRight->Top = imgChoosenAnswer->Top;
                imgChAnsRight->Left = imgChoosenAnswer->Left + imgChoosenAnswer->Width;
            } break;
        case 4: {
                imgChAnsLeft->Top = imgNumber[4]->Top - 10;
                imgChAnsLeft->Left = imgNumber[4]->Left - 10;
                imgChoosenAnswer->Top = imgChAnsLeft->Top;
                imgChoosenAnswer->Left = imgChAnsLeft->Left + imgChAnsLeft->Width;
                imgChAnsRight->Top = imgChoosenAnswer->Top;
                imgChAnsRight->Left = imgChoosenAnswer->Left + imgChoosenAnswer->Width;
            } break;
        }
    }
}

void __fastcall TF::FormHide(TObject* Sender) { tmrPulseAnimation->Enabled = false; }
// ---------------------------------------------------------------------------
