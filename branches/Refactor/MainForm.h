// ---------------------------------------------------------------------------
#ifndef MainFormH
#define MainFormH
// ---------------------------------------------------------------------------
#include "pch.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <MPlayer.hpp>
#include <pngimage.hpp>
#include <StdCtrls.hpp>

// -----------------------------------------------------------------------------
class TF : public TForm {
__published: // IDE-managed Components

    TImage *imgPlace;
    TImage *imgHatch0;
    TImage *imgHatch3;
    TImage *imgHatch1;
    TImage *imgHatch2;
    TImage *imgHatch5;
    TImage *imgHatch4;
    TImage *imgQuestion;
    TButton *btnMechStart;
    TButton *btnMechStop;
    TButton *btnGetMoney;
    TButton *btnContinueGame;
    TButton *btnExit;
    TTimer *tmrRotator;
    TMediaPlayer *MediaPlayer1;
    TLabel *LabelQuestion;
    TLabel *LabelMoney;
    TTimer *tmrWaiting;
    TTimer *tmrMoney;
    TImage *imgPlayers;
    TImage *imgNumber1;
    TImage *imgNumber2;
    TImage *imgNumber3;
    TImage *imgNumber4;
    TImage *imgNumber5;
    TImage *imgChoosenAnswer;
    TTimer *tmrTime;
    TLabel *lblTimer;
    TImage *imgTimer;
    TMemo *mlog;
    TTimer *tmrLog;
    TImage *imgPulse;
    TTimer *tmrWaitingFinal;
    TTimer *tmrPulseAnimation;
    TEdit *edFinalAnswer;
    TLabel *lblRightAnswer;
    TImage *imgTotalPrize;
    TImage *imgPlayer1;
    TImage *imgPlayer2;
    TImage *imgPlayer3;
    TImage *imgPlayer4;
    TImage *imgPlayer5;
    TImage *imgMechanizm;
    TTimer *tmrMechamizm;
    TImage *imgSplash;
    TTimer *tmrSplash;
    TLabel *lblExit;
    TButton *Button1;
    TImage *imgTicker;
    TImage *imgPulseBar;
    TImage *imgBorder;
    TTimer *tmrDecided;
    TTimer *tmrLightAnimation;
    TMediaPlayer *MediaPlayer2;
    TImage *imgChAnsLeft;
    TImage *imgChAnsRight;
    TLabel *ControlLabel;

    void __fastcall tmrPulseAnimationTimer(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall LoadGraphic();
    void __fastcall btnMechStartClick(TObject *Sender);
    void __fastcall btnExitClick(TObject *Sender);
    void __fastcall btnMechStopClick(TObject *Sender);
    void __fastcall tmrRotatorTimer(TObject *Sender);
    void __fastcall PlaySound(String path);
    void __fastcall PlayMusic(String path);
    void __fastcall tmrWaitingTimer(TObject *Sender);
    void __fastcall tmrMoneyTimer(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall tmrTimeTimer(TObject *Sender);
    void __fastcall tmrWaitingFinalTimer(TObject *Sender);
    void __fastcall edFinalAnswerKeyPress(TObject *Sender, wchar_t &Key);
    void __fastcall btnContinueGameClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall btnGetMoneyClick(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall tmrMechamizmTimer(TObject *Sender);
    void __fastcall imgMechanizmClick(TObject *Sender);
    void __fastcall tmrSplashTimer(TObject *Sender);
    void __fastcall tmrDecidedTimer(TObject *Sender);
    void __fastcall tmrLightAnimationTimer(TObject *Sender);
    void __fastcall ControlLabelClick(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall HatchClick(TObject *Sender);

private: // User declarations
    void CreateLabel(TLabel **, int, int, int, int, int, UnicodeString);

public: // User declarations
    __fastcall TF(TComponent *Owner);

    typedef enum {
        mRoundQuestion, // задаётся вопрос раунда
            mRoundChoosePlayer, // задающий участник должен выбрать отвечающего игрока
            mRoundPlayerChoosen, // отвечающий игрок выбран
            mRoundAnswering, // ответы показны, игрок даёт ответ
            mRoundAnswerLocked, // ответ принят, идёт проверка ответа
            mRoundShowCorrectAns, // показ верного ответа, перечисление денег
            mRoundMomentOfTruth = 7, // «момент истины» для игрока после остановки механизма
            mRoundNoQuestions, // вопросы раунда закончились, определяется явный лидер
            mRoundSuddenDeath, // один из игроков (кроме спасённого) покидает игру
            mRoundEndOfCurrRound, // конец текущего раунда
            mRoundNewRound, // объявление нового раунда
            mRoundStartNewRound, // начало нового раунда
        // состояния игры в финальном раунде
            mFinalStartNewRound = 20, // начало финального раунда или отрезка финала
            mFinalQuestion, // задаётся вопрос стоимостью $amount рублей
            mFinalAnswering, // игрок отвечает на вопрос финала
            mFinalAnswerLocked, // игрок даёт ответ на вопрос и он проверяется
            mFinalGiveMoney, // в случае верного ответа игрок получает деньги
            mFinalMomentOfTruth, // «%s люков из 6 открываются автоматически» ©
            mFinalPlayerSave, // игрок остался на площадке игры после открытия люков
            mFinalPlayerFall, // игрок провалился
            mFinalEndOfGame, // игра закончена; выигрыш игрока - $amount рублей
        }

    ModesOfGame;
    ModesOfGame ModeOfGame; // режимы игры (последовательность игровых действий)

    TLabel *lblMoney[5];
    // лейблы и конструктор для отображения денег на панели игроков.
    TLabel *lblPlayer[5];
    TLabel *lblAnswers[5];

    int answer;
    int Reward;

    void TransferMoney();

    int money[5]; // деньги игроков
    int pulse[5]; // Пульсации кровяного давления

    int NumberOfQuestion;
    int Wait;
    int RandomPlace;

    void ResetForm();

    bool _Parse(UnicodeString ans);
    void TransferMoneyFinal();

    bool ingame[5]; // массив, определяющий наличие игрока в игре
    char FinalRound; // указывается номер финальной части раунда
    int FinalRoundOfGame;
    // финальный раунд игры (определяет стоимость финального вопроса)

    String FillChars(String str, int count);
    String GetStr(String str, int begin, int size);
    String ClearStr(String str);

    bool FatalError;

    void ShowAnswers();
    void ResizeAnswers();
    void Choosen_Answer_Change_Position(int mode);
};

void LoadQuestionFromBase(String BaseName);
// ---------------------------------------------------------------------------
extern PACKAGE TF *F;
// ---------------------------------------------------------------------------

#endif
