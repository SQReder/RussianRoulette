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
#ifndef MainFormH
#define MainFormH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
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
	TImage *imgLiver;
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
	TImage *imgChAnsLeft;
	TImage *imgChAnsRight;
	TLabel *ControlLabel;
	TTimer *tmrAnimateBackground;
	TImage *imgContGame;
	TImage *imgTakeAMoney;

	void __fastcall tmrPulseAnimationTimer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall LoadGraphic();
	void __fastcall btnMechStartClick(TObject *Sender);
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall btnMechStopClick(TObject *Sender);
	void __fastcall tmrRotatorTimer(TObject *Sender);
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
	void __fastcall imgLiverClick(TObject *Sender);
	void __fastcall tmrSplashTimer(TObject *Sender);
	void __fastcall tmrDecidedTimer(TObject *Sender);
	void __fastcall tmrLightAnimationTimer(TObject *Sender);
	void __fastcall ControlLabelClick(TObject *Sender);
	void __fastcall FormHide(TObject *Sender);
	void __fastcall HatchClick(TObject *Sender);
	void __fastcall tmrAnimateBackgroundTimer(TObject *Sender);
	void __fastcall imgContGameClick(TObject *Sender);
	void __fastcall imgTakeAMoneyClick(TObject *Sender);

private: // User declarations
	void SetLabel(shared_ptr<TLabel>, int, int, int, String, int = 20);

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

    int answer;
    int Reward;

    void TransferMoney();

    int money[COUNT_PLAYERS]; // деньги игроков
    int pulse[COUNT_PLAYERS]; // Пульсации кровяного давления

    int NumberOfQuestion;
    int Wait;
    int RandomPlace;

    void ResetForm();

    void TransferMoneyFinal();

    array<bool, COUNT_PLAYERS> isPlayerInGame; // массив, определяющий наличие игрока в игре
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
	void FlashBackground(TColor NewStateColor);

	// лейблы для отображения денег на панели игроков.
	array<shared_ptr<TLabel>, COUNT_PLAYERS> lblMoney;
	array<shared_ptr<TLabel>, COUNT_PLAYERS> lblPlayer;
	array<shared_ptr<TLabel>, COUNT_PLAYERS> lblAnswers;
};

// ---------------------------------------------------------------------------
extern PACKAGE TF *F;
// ---------------------------------------------------------------------------

#endif
