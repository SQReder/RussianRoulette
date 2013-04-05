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

#include "MainForm.h"
#include "mainmenu.h"
#include "Hatches.h"
#include "GameLogic.h"
#include "Splash.h"
#include "AI.h"
#include "fSettings.h"
#include "uHostMode.h"
#include "base.h"
#include "GfxCache.h"
#include "audio.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define _StartRotaingSpeed 50

TF *F;

enum {
	Off, Spining, Stoping
} MechanizmState;

int SpeedOfRotation = _StartRotaingSpeed;
bool SoundOn = true;
int TimeOfQuestion; // время, данное на ответ игроку
int MoneyTransferMode = 0;
// режим начисления денег (1 - 1-ому игроку, 2 - 2-ому и т.д.; a - всем)
int ModeOfFinalGame;
// режим финальной игры (опр. порядок действий в tmrWaitingFinal)
bool TransferAll = 1; // режим начисления денег всем игрокам
int WaitForFate;
// переменная, определяющая время ожидания "решения судьбы" (провал или нет)
bool CanAnswer = 0; // переменная, определяющая, может ли отвечать игрок
bool CanChoose = 1;
// переменная, определяющая, можно ли выбирать игрока/игровое место или нет
int QuestionsLeft;
// переменная, определяющая количество оставшихся вопросов в раунде
int colquestions[4];
// массив, определяющий максимальное количество вопросов по раундам
int MaximalSumm;
// переменная, определяющая максимальное значение среди сумм игроков
int MaximalSummCount;
// переменная, определяющая кол-во максимумов среди игроков
int indexes[COUNT_PLAYERS], variants[COUNT_PLAYERS];
// массивы, помогающие случайно распредлить варианты ответов
bool spin_round_mode;
// определяет анимацию (1 - по часовой, 0 - против часовой)
int TimeToDecide; // время, необходимое боту для принятия решения
int LeaderPlayerAtFinal;
// порядковый индекс игрока, прошедшего в финал (необходимо для принятия решений)
int RoundOfGame; // указывается номер текущего раунда (влияет на механизм)

int opened_now[6];
// указывает какие люки будут открыты после остановки механизма
int TempRoundOfGame;
int chooseplayer;
int CantFall;
bool DisableResizeEvent = false;

int curbot = -1; // переменная показывает порядковый номер бота среди игроков
TColor BgStateColor; // добавим маленько эпичности при проверке ответов: окраска окна

TImage *imgPlayer[COUNT_PLAYERS];
TImage *imgHatch[COUNT_HATCHES];
TImage *imgNumber[COUNT_ANSWERS];

array<TBot, 5> bot;
void SetQuestionsMaximum(int FirstRound, int SecondRound, int ThirdRound, int FouthRound);
// -----------------------------------------------------------------------------

void __fastcall TF::LoadGraphic() {
	const shared_ptr<GfxCache> gfx = GfxCache::Instance();
	imgPlace->Picture->Assign(gfx->Place.get());
	Wait = 0;

	imgSplash->Picture->Assign(gfx->GetSplash(1));

	hatches_enable_state(false);
	tmrWaiting->Enabled = false;
	imgTotalPrize->Visible = false;

	TSettings *Settings = TSettings::Instance();
	F->Constraints->MinWidth = Settings->MinWidth;
	F->Constraints->MinHeight = Settings->MinHeight;

	btnMechStart->Enabled = true;

	edFinalAnswer->Visible = false;

	for (int i = 0; i < COUNT_ANSWERS; ++i) {
		imgNumber[i]->Visible = false;
	}

	imgChoosenAnswer->Visible = false;

	imgQuestion->Picture->Assign(gfx->rr_quest.get());

	btnMechStop->Enabled = false;
	CantFall = -1;
	AnimationFrame = 1;
}

// ---------------------------------------------------------------------------
void TF::SetLabel(shared_ptr<TLabel> typedLabel, int top, int left, int width,
				  String caption, int height) {
	typedLabel->Top = top;
	typedLabel->Left = left;
	typedLabel->Width = width;
	typedLabel->Height = height;

	typedLabel->Caption = caption;

	typedLabel->Visible = true;
}

// ---------------------------------------------------------------------------
__fastcall TF::TF(TComponent *Owner) : TForm(Owner) { }

shared_ptr<TLabel> createLabel() {
	TLabel *instance = new TLabel(F);
	instance->Parent = F;
	instance->Font->Color = clWhite;
	instance->Font->Size = 12;
	instance->Font->Name = "ARIAL";
	instance->Font->Charset = TFontCharset(RUSSIAN_CHARSET);
	instance->AutoSize = true;
	instance->Font->Style = TFontStyles() << fsBold;
	return shared_ptr<TLabel>(instance);
}

// ---------------------------------------------------------------------------
void __fastcall TF::FormCreate(TObject *) {
	EZDBGONLYLOGGERSTREAM << _T("Created\n");
	// initialise control pointer arrays with visual components
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

	for(int i = 0; i < COUNT_PLAYERS; ++i) {
		lblMoney.at(i) = createLabel();
		lblMoney.at(i)->Alignment = taRightJustify;

		lblPlayer.at(i)  = createLabel();
		lblPlayer.at(i)->Alignment = taCenter;

		lblAnswers.at(i) = createLabel();
		lblAnswers.at(i)->Alignment = taLeftJustify;
		lblAnswers.at(i)->BringToFront();
	}

	for (int i = 0; i < 6; ++i) {
		imgHatch[i]->Width  = 160;
		imgHatch[i]->Height = 160;
	}
}

// ---------------------------------------------------------------------------

void __fastcall TF::tmrPulseAnimationTimer(TObject *) {
	static frame = 0;
	const shared_ptr<GfxCache> gfx = GfxCache::Instance();
	imgPulse->Picture->Assign(gfx->GetPulseFrame(frame));
	frame = ++frame % gfx->PulseFramesCount;
}

// ---------------------------------------------------------------------------

void __fastcall TF::btnMechStartClick(TObject *) {
	SpeedOfRotation = (ModeOfGame == mRoundNoQuestions) ? 75 : _StartRotaingSpeed;
	if (RoundOfGame == -1 || FinalRoundOfGame > 0) {
		SpeedOfRotation = 35;
	}
	tmrRotator->Interval = SpeedOfRotation;
	MechanizmState = Spining;
	const shared_ptr<GfxCache> gfx = GfxCache::Instance();
	imgPlace->Picture->Assign(gfx->PlaceRedMechActive.get());
	tmrRotator->Enabled = true;
	PlaySound(rr_mexopen);
	btnMechStart->Enabled = false;
	btnMechStop->Enabled = true;
}

// ---------------------------------------------------------------------------
void SwitchOffMech_WhiteLights() {
	F->tmrRotator->Enabled = false;
	LightHatchesW(LIGHT_ALL_HATCHES_BLUE, 4);
//    MechanizmSetHatchesStates();
}

// ---------------------------------------------------------------------------
void __fastcall TF::btnMechStopClick(TObject *) {
	const shared_ptr<GfxCache> gfx = GfxCache::Instance();

	MechanizmState = Stoping;
	if (RoundOfGame == -1) {
		RoundOfGame = 0;
	}
	PlaySound(rr_mexclose);
	randomize();
	WaitForFate = 5 + random(11);
	imgPlace->Picture->Assign(gfx->PlaceRedZero.get());
	if (RoundOfGame < 1) {
		imgPlace->Picture->Assign(gfx->Place.get());
	}

	if (FinalRoundOfGame > 0) {
		SwitchOffMech_WhiteLights();
		CanChoose = 1;
		OpenRandomHatches(FinalRoundOfGame + 2, ModeOfGame);
	}

	bool b2 = RoundOfGame >= 1 && ModeOfGame != mRoundNoQuestions;
	bool b3 = !b2 && ModeOfGame == mRoundNoQuestions;
	if (b2 || b3) {
		SwitchOffMech_WhiteLights();
	}
	// ------------------

	if (RoundOfGame == 0) {
		DoSpin(Zero);
	} else {
		if (ModeOfGame != mRoundNoQuestions) {
			OpenRandomHatches(RoundOfGame, ModeOfGame);
			ModeOfGame = mRoundMomentOfTruth;
			tmrWaiting->Enabled = true;
		} else {
			OpenRandomHatches(1, ModeOfGame);
			ModeOfGame = mRoundSuddenDeath;
		}
		tmrWaiting->Enabled = true;
	}

	imgLiver->Enabled = false;

	btnMechStart->Enabled = false;
	btnMechStop->Enabled = false;
}

// ---------------------------------------------------------------------------
void __fastcall TF::btnExitClick(TObject *) {
	int r;
	r = MessageDlg("Вы действительно хотите закончить игру?\n"
				   "Все данные об этой игре будут потеряны!", mtCustom,
		mbYesNo, 0);
	if (r == mrYes) {
		Close();
	}
}

// ---------------------------------------------------------------------------
void __fastcall TF::tmrRotatorTimer(TObject *) {
	if (ModeOfGame == mRoundNoQuestions) {
		SwitchesLights();
	} else {
		switch (RoundOfGame) {
		case -1: DoSpin(Zero);
			break;
		case 0: ShiftHatches();
			break;
		case 1: DoSpin(First);
			break;
		case 2: DoSpin(Second);
			break;
		case 3: DoSpin(Third);
			break;
		case 4: DoSpin(Fourth);
			break;
		case 5: DoSpin(Zero);
			break;
		}
	}

	if (FinalRoundOfGame > 0) {
		ZeroRoundSpin();
	}

	if (RoundOfGame < 1) {
		CurrentHatch = ++CurrentHatch % 6;
	}

	if (MechanizmState == Stoping) // если механизм в стадии отключения
	{

		SpeedOfRotation += 30; // замедляем вращение
		tmrRotator->Interval = SpeedOfRotation;
		if ((SpeedOfRotation > 450) && (CurrentHatch != 0) && (isPlayerInGame[CurrentHatch - 1]))
			// и если вращение очень уж медленное
		{
			tmrRotator->Enabled = false; // вырубаем таймер
			if (RoundOfGame == 0) {
				LightHatchesW(2, 4);
				if (TempRoundOfGame != 0) {
					RoundOfGame = TempRoundOfGame;
				} else {
					QuestionsLeft = colquestions[0];
					RoundOfGame = 1;
				}
			}
			PlaySound(rr_endround);
			switchonquestion();
			ModeOfGame = mRoundQuestion;
			if (TSettings::Instance()->HostMode == false) {
				tmrWaiting->Enabled = true;
				Wait = 0;
			}
		}
	}
}

// ---------------------------------------------------------------------------
int ChooseAnyPlayer() {
	TSettings* settings = TSettings::Instance();

	while (1) {
		int ChosenOne = random(COUNT_PLAYERS);

		bool isHuman = settings->PlayerType[ChosenOne] != bbHuman;
		// увеличение шанса того, что бот выберет человека, а не другого бота
		bool HumanLuck = random(100) < 10;
		if (!isHuman && HumanLuck) {
			continue;
		}

		bool notCurrentPlayer = ChosenOne != CurrentHatch - 1;
		bool isActualyInGame = F->isPlayerInGame[ChosenOne] != 0;
		if (notCurrentPlayer && isActualyInGame) {
			return ChosenOne + 1;
		}
	}
}
// ---------------------------------------------------------------------------

void __fastcall TF::tmrWaitingTimer(TObject *) {
	const shared_ptr<GfxCache> gfx = GfxCache::Instance();
	TSettings *Settings = TSettings::Instance();
	const shared_ptr<QuestionBase> base = QuestionBase::Instance();
	Wait++ ;
	switch (ModeOfGame) {
	case mRoundQuestion: // показ вопроса
		if (Wait == 5) {
			if (QuestionsLeft > 0) {
				for (int i = 0; i < 5; i++) { // magic constant
					indexes[i] = -1;
					variants[i] = -1;
					PlaySound(rr_nextq);
				}
				tmrWaiting->Enabled = false;
				showquestion();
				CanChoose = 0;
				hatches_enable_state(false);
				btnMechStart->Enabled = false;
				TimeOfQuestion = 20;
				lblTimer->Caption = IntToStr(TimeOfQuestion);
				Wait = 0;
				ModeOfGame = mRoundChoosePlayer;
				if (TransferAll == 1) {
					RoundOfGame = 1;
				}
			} else {
				imgQuestion->Visible = false;
				imgBorder->Visible = false;
				LabelMoney->Visible = false;
				imgPulse->Visible = false;
				ModeOfGame = mRoundNoQuestions;
			}
		}
		break;
	case mRoundChoosePlayer: // начисление стартовой суммы денег игрокам
		// и последующий выбор отвечающего
		if (Wait == 3) {
			tmrWaiting->Enabled = false;
			Wait = 2;
			if (TransferAll == 1) {
				Reward = 1000;
				tmrMoney->Enabled = true;
				MoneyTransferMode = 'a';
			} else {
				CanChoose = 1;
			}
			if (RoundOfGame != 4) {
				if (Settings->PlayerType[CurrentHatch - 1] == bbHuman) {
					GiveHumanChooseOpponent();
				} else {
					chooseplayer = ChooseAnyPlayer();
					choosingplayer();
					ModeOfGame = mRoundPlayerChoosen;
					if (!Settings->HostMode) {
						tmrWaiting->Enabled = true;
					}
				}
			} else {
				hatches_enable_state(false);
				CanChoose = 0;
				for (int i = 0; i < COUNT_PLAYERS; i++) {
					if ((isPlayerInGame[i]) && (CurrentHatch != i + 1)) {
						chooseplayer = i + 1;
					}
				}
				choosingplayer();
				ModeOfGame = mRoundPlayerChoosen;
				if (!Settings->HostMode) {
					tmrWaiting->Enabled = true;
				}
			}
		}
		break;
	case mRoundPlayerChoosen: // выбор игрока
		if (Wait == 3) {
			if (RoundOfGame != 4) {
				spin_round_mode = 1;
				PlaySound(rr_choosen);
			}
			MoneyTransferMode = 'c';
			LabelMoney->Caption = lblMoney[chooseplayer - 1]->Caption;
			LabelMoney->Visible = true;
			imgTotalPrize->Visible = true;
			if (Settings->PlayerType[chooseplayer - 1] != bbHuman) {
#ifdef _DEBUG
				TimeToDecide = 1;
#else
				switch (Settings->PlayerType[chooseplayer - 1]) {
				case bbFoooool: TimeToDecide = 2 + random(20);
					break;
				case bbFooly: TimeToDecide = 7 + random(13);
					break;
				case bbNormal: TimeToDecide = 7 + random(9);
					break;
				case bbHard: TimeToDecide = 5 + random(6);
					break;
				case bbVeryHard: TimeToDecide = 1 + random(4);
					break;
				}
#endif
			}
		}
		if (Wait == 4) {
			tmrWaiting->Enabled = false;
			if (RoundOfGame != 4) {
				before_spin_lights();
				tmrLightAnimation->Enabled = true;
			}
			ModeOfGame = mRoundAnswering;
			Wait = 0;
			tmrWaiting->Enabled = true;
		}
		break;
	case mRoundAnswering: // показ ответов и таймера
		if (Wait == 7) {
			// -=[Случайное распределение вариантов ответа]=-
			// --[ 1. Наполнение массива индексами ]--
			for (int i = 0; i < RoundOfGame + 1; i++) {
				indexes[i] = i;
			}
			// --[ 2. Случайное распределение индексов ]--
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

			// --[ 3. Запись вариантов ответа, согласно индексам]--
			TimeOfQuestion = 20;
			imgPulse->Visible = true;
			tmrPulseAnimation->Enabled = true;
			imgPulseBar->Visible = true;
			imgTicker->Visible = true;
			imgTimer->Picture->Assign(gfx->GetTickFrame(TimeOfQuestion));
			ShowAnswers();
			ResizeAnswers();
			// --[ 4. Финальное: определение надписи, в которой лежит правильный ответ ]--
			int trueans;
			trueans = base->GetTrueAnswer(NumberOfQuestion);
			for (int i = 0; i < RoundOfGame + 1; i++) {
				if (variants[i] == trueans) {
					RandomPlace = i;
				}
			}
			// -=[ Окончание алгоритма распределения ]=-
			lblTimer->Visible = true;
			imgTimer->Visible = true;
			break;
		}
		// Wait=0;

		if (Wait == 12) {
			tmrWaiting->Enabled = false;
			if (!Settings->HostMode) {
				// сброс последнего выбранного ответа
				answer = 255;
				// и включение возможности ответить
				CanAnswer = 1;
				PlaySound(rr_20sec);
				tmrTime->Enabled = true;
			}
			Wait = 0;
		}
		break;
	case mRoundAnswerLocked: // проверка ответа
		if (Wait == 2) {
			CanAnswer = 0;
			StopSound(rr_20sec);
			if (answer == RandomPlace) {
				imgQuestion->Picture->Assign(gfx->quest_correct.get());
				FlashBackground(clLime);
				if (!Settings->HostMode) {
					tmrWaiting->Enabled = true;
				}
				imgChoosenAnswer->Visible = true;
				imgChAnsLeft->Visible = true;
				imgChAnsRight->Visible = true;
				imgChoosenAnswer->AutoSize = false;
				imgChoosenAnswer->Stretch = true;
				imgChoosenAnswer->Height = imgNumber[0]->Height + 20;
				imgChoosenAnswer->Width = 20 + lblAnswers[answer]->Width - 5;
				Choosen_Answer_Change_Position(answer);
				CurrentHatch = chooseplayer;
				chooseplayer = 255;
				QuestionsLeft-- ;
			} else {
				imgQuestion->Picture->Assign(gfx->quest_incorrect.get());
				FlashBackground(clRed);
				if (answer != -1) {
					imgChoosenAnswer->Visible = true;
					imgChAnsLeft->Visible = true;
					imgChAnsRight->Visible = true;
				}
				imgChoosenAnswer->AutoSize = false;
				imgChoosenAnswer->Stretch = true;
				imgChoosenAnswer->Height = imgNumber[0]->Height + 20;
				imgChoosenAnswer->Width = 20 + lblAnswers[answer]->Width - 5;
				Choosen_Answer_Change_Position(answer);
				Proverka2();
				Reward = money[chooseplayer - 1];
				QuestionsLeft-- ;
			}
		}
		if (Wait == 8) {
			if (answer != RandomPlace) {
				PlaySound(rr_bg1);
			} else {
				PlaySound((rrSoundEvent)((int)rr_bg1 + (2 + random(4))));
			}
			if (!Settings->HostMode) {
				tmrWaiting->Enabled = true;
			} else {
				tmrWaiting->Enabled = false;
			}
			ModeOfGame = mRoundShowCorrectAns;
			Wait = 0;
		}
		TransferAll = 0;
		break;
	case mRoundShowCorrectAns: // начисление денег и отображение правильного ответа
		if (Wait == 2) {
			imgChoosenAnswer->Visible = true;
			imgChAnsLeft->Visible = true;
			imgChAnsRight->Visible = true;
			imgChoosenAnswer->Width = 20 + lblAnswers[RandomPlace]->Width - 5;
			Choosen_Answer_Change_Position(RandomPlace);
			MoneyTransferMode = chooseplayer;
			tmrMoney->Enabled = true;
			PlaySound(rr_money);
		}
		if (Wait == 7) {
			tmrWaiting->Enabled = false;
			if (Settings->PlayerType[chooseplayer - 1] == bbHuman) {
				btnMechStart->Enabled = 1;
				imgLiver->Enabled = 1;
			} else {
#ifdef _DEBUG
				TimeToDecide = 1;
#else
				switch (Settings->PlayerType[chooseplayer - 1]) {
				case bbFoooool: TimeToDecide = 10 + random(31);
					break;
				case bbFooly: TimeToDecide = 10 + random(21);
					break;
				case bbNormal: TimeToDecide = 5 + random(16);
					break;
				case bbHard: TimeToDecide = 5 + random(11);
					break;
				case bbVeryHard: TimeToDecide = 1 + random(11);
					break;
				}
#endif
				imgLiverClick(imgLiver);
				curbot = chooseplayer - 1;
				tmrDecided->Enabled = true;
			}
			Wait = 0;
		}
		break;
	case mRoundMomentOfTruth: // проверка подлинности провала ошибившегося игрока
		{
			if (Wait == WaitForFate) {
				if (opened_now[chooseplayer] == 1) {
					OpenHatches();
					PlaySound(rr_fall);
					int chooseplayer_debug_index = chooseplayer - 1;
					EZDBGONLYLOGGERSTREAM << "mRoundMomentOfTruth: chooseplayer = " << chooseplayer <<
						"; isPlayerInGame[" << chooseplayer_debug_index << "] " << isPlayerInGame[chooseplayer - 1]
						<< "->0" << endl;
					isPlayerInGame[chooseplayer - 1] = 0;

					for (int i = 0; i < COUNT_PLAYERS; i++) {
						if (isPlayerInGame[i]) {
							EZDBGONLYLOGGERSTREAM << "isPlayerInGame: " << i << endl;
						}
					}

					imgPulse->Visible = false;
					tmrPulseAnimation->Enabled = false;
					LabelMoney->Visible = false;
					lblPlayer[chooseplayer - 1]->Visible = false;
					lblMoney[chooseplayer - 1]->Visible = false;
					money[chooseplayer - 1] = 0;
					imgQuestion->Visible = false;
					imgBorder->Visible = false;
					imgTicker->Visible = false;
					imgPulseBar->Visible = false;
					imgTotalPrize->Visible = false;
					for (int i = 0; i < COUNT_ANSWERS; i++) {
						/* is it necessary? may be we are wrote wrong arcitecture? */
						if (lblAnswers[i] != NULL) {
							lblAnswers[i]->Visible = false;
						}
					}
					imgPlayer[chooseplayer - 1]->Visible = false;
					for (int i = 0; i < COUNT_ANSWERS; ++i) {
						imgNumber[i]->Visible = false;
					}
					imgChoosenAnswer->Visible = false;
					imgChAnsLeft->Visible = false;
					imgChAnsRight->Visible = false;
					imgTimer->Visible = false;
					lblTimer->Visible = false;
					imgQuestion->Picture->Assign(gfx->rr_quest.get());
					LabelQuestion->Visible = false;
					if (!Settings->HostMode) {
						tmrWaiting->Enabled = true;
						Wait = 0;
					} else {
						tmrWaiting->Enabled = false;
						Wait = 9;
					}
					ModeOfGame = mRoundEndOfCurrRound;
				} else {
					PlaySound(rr_save);
					CurrentHatch = chooseplayer;
					chooseplayer = 255;
					imgPlace->Picture->Assign(gfx->Place.get());
					ResetForm();
				}
			}
			if (Wait == (WaitForFate + 3)) {
				if (!Settings->HostMode) {
					tmrWaiting->Enabled = true;
					Wait = 0;
				} else {
					tmrWaiting->Enabled = false;
					Wait = 4;
				}
				ModeOfGame = mRoundQuestion;
				PlaySound((rrSoundEvent)(rr_bg1 + 4 + random(2)));
			}
			break;
		}
	case mRoundNoQuestions: // определение лидера в случае окончания вопросов
		{
			if (Wait == 8) {
				MaximalSumm = 0;
				MaximalSummCount = 0;
				for (int i = 0; i < COUNT_PLAYERS; i++) {
					if (money[i] > MaximalSumm) {
						MaximalSumm = money[i];
					}
				}
				for (int i = 0; i < COUNT_PLAYERS; i++) {
					if (money[i] == MaximalSumm) {
						MaximalSummCount++ ;
						CantFall = i;
					}
				}
				if (MaximalSummCount > 1 || RoundOfGame == 4) {
					CantFall = -1;
				}
				tmrWaiting->Enabled = false;
				if (Settings->PlayerType[CantFall] == bbHuman) {
					btnMechStart->Enabled = 1;
					imgLiver->Enabled = 1;
				} else {
#ifdef _DEBUG
					TimeToDecide = 1;
#else
					switch (Settings->PlayerType[CantFall]) {
						case bbFoooool: TimeToDecide = 10 + random(31);
							break;
						case bbFooly: TimeToDecide = 10 + random(21);
							break;
						case bbNormal: TimeToDecide = 5 + random(16);
							break;
						case bbHard: TimeToDecide = 5 + random(11);
							break;
						case bbVeryHard: TimeToDecide = 1 + random(11);
							break;
					}
#endif
					imgLiverClick(imgLiver);
					curbot = CantFall;
					if (curbot < 0) {
						curbot = -1;
						TimeToDecide = 5 + random(6);
					}
					tmrDecided->Enabled = true;
				}
				Wait = 0;
			}
		} break;
	case mRoundSuddenDeath: // ситуация, когда один из игроков неминуемо должен покинуть игру
		{
			if (Wait == WaitForFate) {
				int NumberOfPlayers = 0;
				OpenRndHatches();
				PlaySound(rr_fall);
				int chooseplayer_debug_index = chooseplayer - 1;
				EZDBGONLYLOGGERSTREAM << "mRoundSuddenDeath: chooseplayer = " << chooseplayer << "; isPlayerInGame[" <<
					chooseplayer_debug_index << "] " << isPlayerInGame[chooseplayer - 1] << "->0" << endl;
				isPlayerInGame[chooseplayer - 1] = 0;
				MoneyTransferMode = 'a';
				for (int i = 0; i < COUNT_PLAYERS; i++) {
					if (isPlayerInGame[i]) {
						EZDBGONLYLOGGERSTREAM << "isPlayerInGame: " << i << endl;
						NumberOfPlayers++ ;
					}
				}
				Reward = money[chooseplayer - 1] / NumberOfPlayers / 1.;
				tmrMoney->Enabled = true;
				money[chooseplayer - 1] = 0;
				lblPlayer[chooseplayer - 1]->Visible = false;
				lblMoney[chooseplayer - 1]->Visible = false;
				imgPlayer[chooseplayer - 1]->Visible = false;
			}
			if (Wait == (WaitForFate + 7)) {
				PlaySound(rr_bg1);
				if (!Settings->HostMode) {
					tmrWaiting->Enabled = true;
					Wait = 0;
				} else {
					Wait = 5;
					tmrWaiting->Enabled = false;
				}
				ModeOfGame = mRoundEndOfCurrRound;
			}
		} break;
	case mRoundEndOfCurrRound: {
			if (Wait == 10) {
				PlaySound(rr_endround);
				LightHatchesW(2, 0);
				Wait = 0;
				RoundOfGame++ ;
				if (RoundOfGame != 5) {
					QuestionsLeft = colquestions[RoundOfGame - 1];
					ModeOfGame = mRoundNewRound;
					imgSplash->Picture->Assign(gfx->GetSplash(RoundOfGame));
				} else {
					ModeOfGame = mFinalStartNewRound;
					tmrWaiting->Enabled = false;
					tmrWaitingFinal->Enabled = true;
				}
			}
		} break;
	case mRoundNewRound: {
			if (Wait == 5) {
				PlaySound(rr_round);
				imgSplash->Visible = true;
				LightHatchesW(LIGHT_ALL_HATCHES_BLUE, 2);
				imgPlace->Picture->Assign(gfx->Place.get());
			}
			if (Wait == 12) {
				imgSplash->Visible = false;
				PlaySound(rr_openround);
				Wait = 0;
				ModeOfGame = mRoundStartNewRound;
			}
		} break;
	case mRoundStartNewRound: {
			MaximalSumm = 0;
			MaximalSummCount = 0;
			switch (RoundOfGame) {
			case 2: QuestionsLeft = colquestions[1];
				break;
			case 3: QuestionsLeft = colquestions[2];
				break;
			case 4: QuestionsLeft = colquestions[3];
				break;
			}
			if (Wait == 5) {
				for (int i = 0; i < COUNT_PLAYERS; i++) {
					if (money[i] > MaximalSumm) {
						MaximalSumm = money[i];
						CurrentHatch = i + 1;
						chooseplayer = 255;
					}
				}
				for (int i = 0; i < COUNT_PLAYERS; i++) {
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
					imgLiver->Enabled = 1;
					tmrWaiting->Enabled = false;
				} else {
					UpdateHatches();
				}
				switchonquestion();
			}
			if (Wait == 12) {
				PlaySound(rr_bg4);
				if (!Settings->HostMode) {
					Wait = 0;
					tmrWaiting->Enabled = true;
				} else {
					Wait = 4;
					tmrWaiting->Enabled = false;
				}
				ModeOfGame = mRoundQuestion;
			}
		} break;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TF::tmrMoneyTimer(TObject *) {
	if (MoneyTransferMode == 'a') {
		int control = 0;
		if (ModeOfGame != mRoundSuddenDeath) // стартовое начисление по 1000 игрокам
		{
			for (int i = 0; i < COUNT_PLAYERS; i++) { // начисление денег игрокам
#define slowest_money 4
				if (((Reward - money[slowest_money]) / 66) > 0) {
					if (isPlayerInGame[i]) {
						money[i] += 66;
					} // цикл, ибо пишем одно и то-же в несколько лейблов
					control = control + 66;
				} else {
					if (isPlayerInGame[i]) {
						money[i] += (Reward - money[slowest_money]) % 66;
					}
					control = Reward;
				} // -> if (((Reward - money[slowest_money]) / 66) > 0)
				lblMoney[i]->Caption = IntToStr(money[i]);
			}
			if (control == Reward) {
				tmrMoney->Enabled = false;
				CanChoose = 1;
				GiveHumanChooseOpponent();
			}
		} else { // по идее, это начисление игрокам денег...
			for (int i = 0; i < COUNT_PLAYERS; i++)
				if (isPlayerInGame[i]) {
					money[i] = money[i] + Reward;
					lblMoney[i]->Caption = IntToStr(money[i]);

					int inaccuracy = money[i] % 100;
					if (inaccuracy == 99 || inaccuracy == 98) {
						money[i] += 100 - inaccuracy;
					}
					lblMoney[i]->Caption = IntToStr(money[i]);
				}
			tmrMoney->Enabled = false;
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

// ---------------------------------------------------------------------------
void __fastcall TF::HatchClick(TObject *Sender) {
	int id = -1;

	for (int i = 0; i < COUNT_HATCHES; ++i) {
		if (Sender == imgHatch[i]) {
			id = i;
			break;
		}
	}

	if (FinalRoundOfGame > 0 && CanChoose == 1) {
		CurrentHatch = id;
		UpdateHatches();
		tmrWaitingFinal->Enabled = true;
		for (int i = 0; i < COUNT_PLAYERS; i++) {
			if (isPlayerInGame[i]) {
				/* and here */
				imgPlayer[i]->Top = int(imgHatch[id]->Top + (imgHatch[id]->Height - imgNumber[0]->Height) / 2 - 5);
				imgPlayer[i]->Left = int(imgHatch[id]->Left + (imgHatch[id]->Width - imgNumber[0]->Width) / 2 - 5);
			}
		}
	} else if (ModeOfGame == mRoundChoosePlayer) {
		chooseplayer = id;
		choosingplayer();
		ModeOfGame = mRoundPlayerChoosen;
		tmrWaiting->Enabled = true;
	}
	CanChoose = 0;
}

// 'a' + n === VK_NUMPAD1 + n
const char *KeyCode[6] = { "6f", "1a", "2b", "3c", "4d", "5e" };

void __fastcall TF::FormKeyDown(TObject *, WORD &Key, TShiftState Shift) {
	TSettings *Settings = TSettings::Instance();

	TCHAR ch[] = "\0\0";
	ch[0] = Key;

	if (Shift.Contains(ssAlt) && (Key == 13)) {
		EZDBGONLYLOGGERSTREAM << "Switch fullscreen mode" << endl;
		SwitchFullscreen(F);
	} else if (Shift.Empty() && (Key == 27)) {
		EZDBGONLYLOGGERSTREAM << "Exit form" << endl;
		btnExitClick(NULL);
	}

	/* if (Screen->MonitorCount > 1 && Key == 'H') {
	 initialize_host_mode();
	 } */

	if (Key == VK_RIGHT && Settings->HostMode == true) {
		if (RoundOfGame >= 1 && RoundOfGame <= 4) {
			if (ModeOfGame == 3) {
				CanAnswer = 1;
				PlaySound(rr_20sec);
				tmrTime->Enabled = true;
			} else {
				tmrWaiting->Enabled = true;
			}
		}
		if (FinalRoundOfGame > 0) {
			tmrWaitingFinal->Enabled = true;
		}
	}
	if ((imgLiver->Enabled) && (Key == 32)) {
		imgLiverClick(imgLiver);
	}
	// выбор игрового места в финале
	if (FinalRoundOfGame > 0 && ModeOfGame == mFinalStartNewRound && CanChoose == 1 && Settings->PlayerType
		[LeaderPlayerAtFinal] == bbHuman) {

		EZDBGONLYLOGGERSTREAM << "Choosing hatch at final" << endl;
		EZDBGONLYLOGGERSTREAM << _T("Key ") << Key << _T("(") << ch << _T(") pressed\n");

		for (int i = 0; i < COUNT_HATCHES; ++i) {
			if (strchr(KeyCode[i], Key) && imgHatch[i]->Enabled) {
				EZDBGONLYLOGGERSTREAM << "strchr(" << KeyCode[i] << ", " << ch << ")" << endl;
				EZDBGONLYLOGGERSTREAM << "HatchClick -> " << i << endl;
				HatchClick(imgHatch[i]);
			}
		}
	}

	// выбор отвечающего игрока (1-4 раунды)
	if (ModeOfGame == mRoundChoosePlayer && Settings->PlayerType[CurrentHatch - 1] == bbHuman && CanChoose == 1) {
		EZDBGONLYLOGGERSTREAM << "Choose player for answer" << endl;
		EZDBGONLYLOGGERSTREAM << _T("Key ") << Key << _T("(") << ch << _T(") pressed\n");
		EZDBGONLYLOGGERSTREAM << "Current hatch = " << CurrentHatch << endl;
		for (int i = 1; i < COUNT_HATCHES; ++i) {
			int j = i - 1;
			EZDBGONLYLOGGERSTREAM << "isPlayerInGame[" << j << "] = " << isPlayerInGame[i - 1] << endl;
			if (strchr(KeyCode[i], Key) && isPlayerInGame[i - 1] == true && CurrentHatch != i) {
				EZDBGONLYLOGGERSTREAM << "HatchClick -> " << i << endl;
				HatchClick(imgHatch[i]);
			}
		}
	}

	// ответ на вопрос (1-4 раунды)
	if (ModeOfGame == mRoundAnswering && CanAnswer == 1 && Settings->PlayerType[chooseplayer - 1] == bbHuman) {
		EZDBGONLYLOGGERSTREAM << "Answer at round " << RoundOfGame << endl;
		EZDBGONLYLOGGERSTREAM << _T("Key ") << Key << _T("(") << ch << _T(") pressed\n");
		for (int i = 1; i < 6; ++i) { // magic constant
			// ShowMessage(answer);
			int AnswersIndexMax = RoundOfGame + 1;
			if (strchr(KeyCode[i], Key) && i <= AnswersIndexMax) {
				answer = i - 1;
				EZDBGONLYLOGGERSTREAM << "answer[0.." << AnswersIndexMax << "] -> " << answer << endl;
				CanAnswer = 0;
			}
		}

		if (answer <= RoundOfGame) {
			Proverka();
			ModeOfGame = mRoundAnswerLocked;
			tmrTime->Enabled = false;
		}

		Reward = RoundOfGame * 1000;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TF::tmrTimeTimer(TObject *) {
	const shared_ptr<GfxCache> gfx = GfxCache::Instance();
	const shared_ptr<QuestionBase> base = QuestionBase::Instance();
	TimeOfQuestion-- ;
	if (RoundOfGame < 5) {
		if (TimeOfQuestion == (20 - TimeToDecide)
		 && TSettings::Instance()->PlayerType[chooseplayer - 1] != bbHuman) {
			if (bot[chooseplayer - 1].Get_Answer()) {
				answer = RandomPlace;
				Reward = RoundOfGame * 1000;
			} else {
				do {
					answer = random(RoundOfGame + 1);
				}
				while (answer == RandomPlace);
			}
			Proverka();
			ModeOfGame = mRoundAnswerLocked;
			tmrTime->Enabled = false;
		}
	} else {
		if (TimeOfQuestion == (10 - TimeToDecide)
		&& TSettings::Instance()->PlayerType[LeaderPlayerAtFinal] != bbHuman) {
			if (bot[LeaderPlayerAtFinal].Get_Answer()) {
				String q = base->GetAnswer(NumberOfQuestion, 0);;
				edFinalAnswer->Text = q;
			}
			ModeOfGame = mFinalAnswerLocked;
			tmrWaitingFinal->Enabled = true;
			Reward = StrToInt(LabelMoney->Caption);
			tmrTime->Enabled = false;
		}
	}
	if (TimeOfQuestion >= 0) {
		lblTimer->Caption = IntToStr(TimeOfQuestion);
		imgTimer->Picture->Assign(gfx->GetTickFrame(TimeOfQuestion));
	}
	if (TimeOfQuestion < 0) {
		if (TimeOfQuestion == -3) {
			tmrTime->Enabled = false;
			if (FinalRoundOfGame < 1) {
				answer = -1;
				Proverka();
				ModeOfGame = mRoundAnswerLocked;
			} else {
				tmrTime->Enabled = false;
				ModeOfGame = mFinalAnswerLocked;
				edFinalAnswer->Visible = false;
				tmrWaitingFinal->Enabled = true;
			}
		}
	}
}

// ---------------------------------------------------------------------------
void TF::TransferMoney() {
	if (chooseplayer != 255) {
		money[chooseplayer - 1] -= (Reward >= 100) ? 100 : Reward;
		lblMoney[chooseplayer - 1]->Caption = IntToStr(money[chooseplayer - 1]);
		LabelMoney->Caption = IntToStr(money[chooseplayer - 1]);
	}

	if (Reward > 0) {
		money[CurrentHatch - 1] += (Reward >= 100) ? 100 : Reward;
		lblMoney[CurrentHatch - 1]->Caption = IntToStr(money[CurrentHatch - 1]);
		LabelMoney->Caption = IntToStr(money[CurrentHatch - 1]);
	} else {
		int dt = money[CurrentHatch - 1] % 100;
		if (dt > 97) {
			money[chooseplayer - 1] += 100 - dt;
			money[CurrentHatch - 1] += 100 - dt;
		}
		dt = money[CurrentHatch - 1] % 10;
		if (dt > 7) {
			money[chooseplayer - 1] += 10 - dt;
			money[CurrentHatch - 1] += 10 - dt;
		}
		tmrMoney->Enabled = false;
		lblMoney[CurrentHatch - 1]->Caption = IntToStr(money[CurrentHatch - 1]);
		LabelMoney->Caption = IntToStr(money[CurrentHatch - 1]);
	}

	if (Reward >= 100) {
		Reward -= 100;
	} else {
		Reward = 0;
		if (answer == RandomPlace) {
			ModeOfGame = mRoundQuestion;
			if (!TSettings::Instance()->HostMode) {
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
void TF::ResetForm() // возвращает форму в исходное положение
{
	const shared_ptr<GfxCache> gfx = GfxCache::Instance();
	for (int i = 0; i <= RoundOfGame; ++i) {
		lblAnswers[i]->Visible = false;
	}

	for (int i = 0; i < COUNT_ANSWERS; ++i) {
		imgNumber[i]->Visible = false;
	}

	F->imgChoosenAnswer->Visible = false;
	F->imgChAnsLeft->Visible = false;
	F->imgChAnsRight->Visible = false;
	F->imgTimer->Visible = false;
	F->lblTimer->Visible = false;
	F->imgTicker->Visible = false;
	F->imgPulse->Visible = false;
	F->imgTotalPrize->Visible = false;
	F->imgPulseBar->Visible = false;
	F->imgQuestion->Picture->Assign(gfx->rr_quest.get());
	F->LabelQuestion->Visible = false;
	F->LabelMoney->Visible = false;
	hatches_enable_state(false);
	UpdateHatches();
}

void __fastcall TF::tmrWaitingFinalTimer(TObject *) {
	// финальный раунд игры "Русская рулетка"
	TSettings *Settings = TSettings::Instance();
	const shared_ptr<GfxCache> gfx = GfxCache::Instance();
	const shared_ptr<QuestionBase> base = QuestionBase::Instance();

	Wait++ ;
	switch (ModeOfGame) {
	case mFinalStartNewRound: {
			if (Wait == 5) {
				for (int i = 0; i < COUNT_ANSWERS; ++i) {
					imgNumber[i]->Enabled = false;
				}
				CanChoose = 0;
				for (int i = 0; i < COUNT_PLAYERS; i++) {
					if (isPlayerInGame[i]) {
						LeaderPlayerAtFinal = i;
					}
				}
				PlaySound(rr_final);
				hatches_enable_state(false);
				imgSplash->Picture->Assign(gfx->FinalSplash.get());
				imgSplash->Visible = true;
				CantFall = -1;
				LightHatchesW(LIGHT_ALL_HATCHES_BLUE, 2);
				imgPlace->Picture->Assign(gfx->Place.get());
				FinalRoundOfGame = 1;
			}
			if (Wait == 11) {
				imgSplash->Visible = false;
				hatches_enable_state(false);
				for (int i = 0; i < COUNT_PLAYERS; i++) {
					if (isPlayerInGame[i]) {
						imgPlayer[i]->Top = int(imgPlace->Top + (imgPlace->Height - imgPlayer[i]->Height) / 2);
						imgPlayer[i]->Left = int(imgPlace->Left + (imgPlace->Width - imgPlayer[i]->Width) / 2);
					}
				}
			}
			if (Wait == 18) {
				imgChoosenAnswer->Visible = false;
				imgTimer->Visible = false;
				lblTimer->Visible = false;
				LabelMoney->Visible = false;
				imgPulse->Visible = false;
				imgPulseBar->Visible = false;
				imgTotalPrize->Visible = false;
				imgTicker->Visible = false;
				imgChAnsLeft->Visible = false;
				imgChAnsRight->Visible = false;
				imgQuestion->Picture->Assign(gfx->rr_quest.get());
				imgQuestion->Visible = false;
				LabelQuestion->Visible = false;
				lblRightAnswer->Visible = false;
				PlaySound(rr_nextq);
				if (Settings->PlayerType[LeaderPlayerAtFinal] == bbHuman) {
					btnMechStart->Enabled = true;
					imgLiver->Enabled = true;
					hatches_enable_state(true);
				} else {
					switch (Settings->PlayerType[LeaderPlayerAtFinal]) {
					case bbFoooool: TimeToDecide = 5 + random(41);
						break;
					case bbFooly: TimeToDecide = 5 + random(31);
						break;
					case bbNormal: TimeToDecide = 5 + random(21);
						break;
					case bbHard: TimeToDecide = 1 + random(16);
						break;
					case bbVeryHard: TimeToDecide = 1 + random(11);
						break;
					}
#ifdef _DEBUG
					TimeToDecide = 1;
#endif

					imgLiverClick(imgLiver);
					curbot = LeaderPlayerAtFinal;
					bot[curbot].bAction = baStoppingMech;
					Wait = 0;
					tmrDecided->Enabled = true;
					hatches_enable_state(false);
				}
				RoundOfGame = -1;
				chooseplayer = 255;
				tmrWaitingFinal->Enabled = false;
			}
			if (Wait == 19) {
				ModeOfGame = mFinalQuestion;
				Wait = 0;
				hatches_enable_state(false);
			}
		} break;
	case mFinalQuestion: {
			if (Wait == 5) {
				RoundOfGame = 5;
				imgQuestion->Visible = true;
				imgBorder->Visible = true;
				imgPulseBar->Visible = true;
				imgTicker->Visible = true;
				imgPulse->Visible = true;
				imgTotalPrize->Visible = true;
				if (FinalRoundOfGame == 1) {
					LabelMoney->Caption = "50000";
				}
				if (FinalRoundOfGame == 2) {
					LabelMoney->Caption = "100000";
				}
				if (FinalRoundOfGame == 3) {
					LabelMoney->Caption = "1000000";
				}
				LabelMoney->Visible = true;
			}
			if (Wait == 8) {
				PlaySound(rr_question);
				TimeOfQuestion = 10;
				load_final_question();
				lblTimer->Caption = IntToStr(TimeOfQuestion);
				lblTimer->Visible = true;
				imgTimer->Picture->Assign(gfx->GetTickFrame(TimeOfQuestion));
				imgTimer->Visible = true;
				edFinalAnswer->Top = imgQuestion->Top + imgQuestion->Height - 30 - edFinalAnswer->Height;
				edFinalAnswer->Left = (int)(imgQuestion->Left + (imgQuestion->Width - edFinalAnswer->Width) / 2.);
				edFinalAnswer->Visible = true;
				if (TSettings::Instance()->PlayerType[LeaderPlayerAtFinal] == bbHuman) {
					edFinalAnswer->Enabled = true;
				} else {
					edFinalAnswer->Enabled = false;
				}
				edFinalAnswer->Text = "";
			}
			if (Wait == 13) {
				tmrTime->Enabled = true;
				PlaySound(rr_20sec);
				ModeOfGame = mFinalAnswering;
				tmrWaitingFinal->Enabled = false;
			}
		} break;
	case mFinalAnswerLocked: { // игрок даёт ответ
			edFinalAnswer->Visible = false;
			StopSound(rr_20sec);
			if (CheckAnswerAtFinalRound(edFinalAnswer->Text, NumberOfQuestion)) {
				PlaySound(rr_true);
				lblRightAnswer->Top = imgQuestion->Top + 160;
				lblRightAnswer->Height = 19;
				lblRightAnswer->AutoSize = true;
				lblRightAnswer->Caption = base->GetAnswer(NumberOfQuestion, 0);
				lblRightAnswer->Left =
					(int)(imgQuestion->Left + (imgQuestion->Width / 2.) - (lblRightAnswer->Width / 2.));
				lblRightAnswer->Visible = true;
				imgChoosenAnswer->Width = lblRightAnswer->Width;
				imgChoosenAnswer->Top = lblRightAnswer->Top - 10;
				imgChoosenAnswer->Left = lblRightAnswer->Left;
				imgChAnsLeft->Top = imgChoosenAnswer->Top;
				imgChAnsLeft->Left = imgChoosenAnswer->Left - imgChAnsLeft->Width;
				imgChAnsRight->Left = imgChoosenAnswer->Left + imgChoosenAnswer->Width;
				imgChAnsRight->Top = imgChoosenAnswer->Top;
				imgChoosenAnswer->Visible = true;
				imgChAnsLeft->Visible = true;
				imgChAnsRight->Visible = true;
				Reward = StrToInt(LabelMoney->Caption);
				imgQuestion->Picture->Assign(gfx->quest_correct.get());
				LightHatchesW(LIGHT_ALL_HATCHES_BLUE, 4);
				ModeOfGame = mFinalGiveMoney;
			} else {
				PlaySound(rr_false);
				lblRightAnswer->Top = imgQuestion->Top + 160;
				lblRightAnswer->Height = 19;
				lblRightAnswer->AutoSize = true;
				lblRightAnswer->Caption = base->GetAnswer(NumberOfQuestion, 0);
				lblRightAnswer->Left =
					(int)(imgQuestion->Left + (imgQuestion->Width / 2.) - (lblRightAnswer->Width / 2.));
				lblRightAnswer->Visible = true;
				imgChoosenAnswer->Width = lblRightAnswer->Width;
				imgChoosenAnswer->Top = lblRightAnswer->Top - 10;
				imgChoosenAnswer->Left = lblRightAnswer->Left;
				imgChAnsLeft->Top = imgChoosenAnswer->Top;
				imgChAnsLeft->Left = imgChoosenAnswer->Left - imgChAnsLeft->Width;
				imgChAnsRight->Left = imgChoosenAnswer->Left + imgChoosenAnswer->Width;
				imgChAnsRight->Top = imgChoosenAnswer->Top;
				imgChoosenAnswer->Visible = true;
				imgChAnsLeft->Visible = true;
				imgChAnsRight->Visible = true;
				LightHatchesW(3, 4);
				ModeOfGame = mFinalMomentOfTruth;
				WaitForFate = 10 + random(11);
				imgQuestion->Picture->Assign(gfx->quest_incorrect.get());
				imgPlace->Picture->Assign(gfx->PlaceRedZero.get());
			}
			Wait = 0;
		} break;
	case mFinalGiveMoney: {
			if (Wait == 8) {
				PlaySound(rr_bg3);
				MoneyTransferMode = 0;
				tmrMoney->Enabled = true;
			}
			if (Wait == 18) {
				if (FinalRoundOfGame < 3) {
					imgContGame->Top = imgBorder->Top + 15;
					imgTakeAMoney->Top = imgBorder->Top + 15;
					imgContGame->Left = imgTotalPrize->Left - 75;
					imgTakeAMoney->Left = imgTotalPrize->Left + imgTotalPrize->Width - (imgTakeAMoney->Width / 2.) - 75;
					imgTakeAMoney->Visible = true;
					imgContGame->Visible = true;
				}
				tmrWaitingFinal->Enabled = false;
				imgChoosenAnswer->Visible = false;
				imgChAnsLeft->Visible = false;
				imgChAnsRight->Visible = false;
				imgTimer->Visible = false;
				lblTimer->Visible = false;
				LabelMoney->Visible = false;
				imgPulse->Visible = false;
				imgQuestion->Picture->Assign(gfx->rr_quest.get());
				imgQuestion->Visible = false;
				LabelQuestion->Visible = false;
				lblRightAnswer->Visible = false;
				imgTicker->Visible = false;
				imgPulseBar->Visible = false;
				imgTotalPrize->Visible = false;
				// если в финале бот, то блокируем кнопки, а иначе - наоборот
				bool LockedDecisionBtns = (bool)(Settings->PlayerType[LeaderPlayerAtFinal] != bbHuman);
				imgContGame->Enabled = !LockedDecisionBtns;
				imgTakeAMoney->Enabled = !LockedDecisionBtns;
				if (LockedDecisionBtns) {
					bot[LeaderPlayerAtFinal].bAction = baDecideStayOrLeave;
					switch (Settings->PlayerType[LeaderPlayerAtFinal]) {
					case bbFoooool: TimeToDecide = 1 + random(15);
						break;
					case bbFooly: TimeToDecide = 1 + random(12);
						break;
					case bbNormal: TimeToDecide = 1 + random(10);
						break;
					case bbHard: TimeToDecide = 1 + random(7);
						break;
					case bbVeryHard: TimeToDecide = 1 + random(4);
						break;
					}
#ifdef _DEBUG
					TimeToDecide = 3;
#endif
					tmrDecided->Enabled = true;
					Wait = 0;
				}
				if (FinalRoundOfGame == 3) {
					Wait = 0;
					tmrDecided->Enabled = false;
					ModeOfGame = mFinalEndOfGame;
					tmrWaitingFinal->Enabled = true;
				}
			}
		} break;
	case mFinalMomentOfTruth: { // игрок в ожидании решения судьбы
			if (Wait == WaitForFate) {
				OpenRndHatches();
				if (opened_now[CurrentHatch] == 1) {
					PlaySound(rr_fall);
					for (int i = 0; i < COUNT_PLAYERS; i++)
						if (isPlayerInGame[i]) {
							lblPlayer[i]->Visible = false;
							lblMoney[i]->Visible = false;
							LabelMoney->Caption = IntToStr(money[i]);
							imgPlayer[i]->Visible = false;
						}
					imgChoosenAnswer->Visible = false;
					imgChAnsLeft->Visible = false;
					imgChAnsRight->Visible = false;
					imgBorder->Visible = false;
					imgTimer->Visible = false;
					lblTimer->Visible = false;
					LabelMoney->Visible = false;
					imgPulse->Visible = false;
					imgTicker->Visible = false;
					imgPulseBar->Visible = false;
					imgTotalPrize->Visible = false;
					imgQuestion->Picture->Assign(gfx->rr_quest.get());
					imgQuestion->Visible = false;
					LabelQuestion->Visible = false;
					lblRightAnswer->Visible = false;
					ModeOfGame = mFinalPlayerFall;
					Wait = 23;
				} else {
					PlaySound(rr_notfall);
					ModeOfGame = mFinalPlayerSave;
					Wait = 30;
				}
			}
		} break;
	case mFinalPlayerSave: {
			if (Wait == 35) {
				imgPlace->Picture->Assign(gfx->Place.get());
				LightHatchesW(1, 0);
				imgChoosenAnswer->Visible = false;
				imgTimer->Visible = false;
				lblTimer->Visible = false;
				LabelMoney->Visible = false;
				imgTicker->Visible = false;
				imgPulseBar->Visible = false;
				imgTotalPrize->Visible = false;
				imgBorder->Visible = false;
				imgChAnsLeft->Visible = false;
				imgChAnsRight->Visible = false;
				imgPulse->Visible = false;
				imgQuestion->Picture->Assign(gfx->rr_quest.get());
				imgQuestion->Visible = false;
				LabelQuestion->Visible = false;
				lblRightAnswer->Visible = false;
				// если игрок спасся на вопросе стоимостью в 1 000 000 рублей,
				// то игра завершается
				if (FinalRoundOfGame == 3) {
					for (int i = 0; i < COUNT_PLAYERS; i++)
						if (isPlayerInGame[i]) {
							lblPlayer[i]->Visible = false;
							lblMoney[i]->Visible = false;
							LabelMoney->Caption = IntToStr(money[i] + 1000000);
						}
					Wait = 0;
					ModeOfGame = mFinalEndOfGame;
				} else {
					LightHatchesW(LIGHT_ALL_HATCHES_BLUE, 1);
					Wait = 10;
					PlaySound(rr_bg5);
					ModeOfGame = mFinalStartNewRound;
				}
			}
			if (Wait == 35) {
				LightHatchesW(LIGHT_ALL_HATCHES_BLUE, 1);
				Wait = 10;
				ModeOfGame = mFinalStartNewRound;
			}
		} break;
	case mFinalPlayerFall:
	case mFinalEndOfGame: {
			if (Wait == 30 && ModeOfGame == mFinalPlayerFall) {
				LightHatchesW(3, 0);
			} else if (Wait == 8 && ModeOfGame == mFinalEndOfGame) {
				LightHatchesW(2, 3);
			}
			imgTotalPrize->Top = imgBorder->Top + 30;
			LabelMoney->Top = imgTotalPrize->Top + 10;
			LabelMoney->Visible = true;
			LabelMoney->Left = imgTotalPrize->Left + 9;
			imgTotalPrize->Visible = true;
			imgBorder->Visible = true;
			PlaySound(rr_closing);
			tmrWaitingFinal->Enabled = false;
		} break;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TF::edFinalAnswerKeyPress(TObject *, wchar_t &Key) {
	if ((Key == 13) && (ModeOfGame == mFinalAnswering)) {
		tmrTime->Enabled = false;
		edFinalAnswer->Visible = false;
		Wait = 0;
		ModeOfGame = mFinalAnswerLocked;
		tmrWaitingFinal->Enabled = true;
	}
}

// ---------------------------------------------------------------------------
void TF::TransferMoneyFinal() {
	int pos;
	for (int i = 0; i < COUNT_PLAYERS; i++) {
		if (isPlayerInGame[i]) {
			pos = i;
		}
	}
	if (Reward > 6666) {
		money[pos] += 6666;
		Reward -= 6666;
	} else {
		money[pos] += Reward;
		tmrMoney->Enabled = false;
	}

	LabelMoney->Caption = IntToStr(money[pos]);
	lblMoney[pos]->Caption = LabelMoney->Caption;
}

void __fastcall TF::btnContinueGameClick(TObject *) {
	int pos;
	for (int i = 0; i < COUNT_PLAYERS; i++) {
		if (isPlayerInGame[i]) {
			pos = i;
			break;
		}
	}

	switch (FinalRoundOfGame) {
	case 1:
	case 2:
		lblMoney[pos]->Caption = IntToStr(money[pos]);
		money[pos] -= 50000 * FinalRoundOfGame;
	}

	FinalRoundOfGame++ ;
	Wait = 10;
	LightHatchesW(LIGHT_ALL_HATCHES_BLUE, 1);
	ModeOfGame = mFinalStartNewRound;
	RoundOfGame = -1;
	btnGetMoney->Visible = false;
	btnContinueGame->Visible = false;
	tmrWaitingFinal->Enabled = true;
}
// ---------------------------------------------------------------------------

void __fastcall TF::FormClose(TObject *, TCloseAction &) {
	const shared_ptr<GfxCache> gfx = GfxCache::Instance();
	// сохранение текущего положения и размеров формы
	SaveFormPosition(F);
	MenuForm->Show();

	for (int i = 0; i < COUNT_PLAYERS; i++) {
		isPlayerInGame[i] = true;
		lblPlayer[i]->Visible = true;

		money[i] = 0;
		lblMoney[i]->Caption = "0";
		lblMoney[i]->Visible = true;
	}

	for (int i = 0; i < COUNT_ANSWERS; ++i) {
		imgNumber[0]->Enabled = false;
	}

	RoundOfGame = -1;
	Wait = 0;
	ModeOfGame = mRoundQuestion;
	TransferAll = 1;
	FinalRoundOfGame = 0;
	LabelQuestion->Visible = false;
	LabelMoney->Visible = false;
	lblTimer->Visible = false;
	imgPulse->Visible = false;
	imgTimer->Visible = false;
	imgTicker->Visible = false;
	imgPulseBar->Visible = false;
	imgChAnsLeft->Visible = false;
	imgChAnsRight->Visible = false;
	imgChoosenAnswer->Visible = false;
	imgBorder->Visible = false;
	imgPlace->Picture->Assign(gfx->Place.get());
	imgSplash->Picture->Assign(gfx->GetSplash(1));
	for (int i = 0; i < COUNT_PLAYERS; ++i) {
		imgPlayer[i]->Visible = true;
	}
	imgLiver->Enabled = true;

	tmrLog->Enabled = false;
	tmrMoney->Enabled = false;
	tmrPulseAnimation->Enabled = false;
	tmrRotator->Enabled = false;
	tmrTime->Enabled = false;
	tmrWaiting->Enabled = false;
	tmrWaitingFinal->Enabled = false;
}

// ---------------------------------------------------------------------------
void ResetPlayers() {
	CurrentHatch = 0;
	for (int i = 0; i < COUNT_PLAYERS; i++) {
		F->isPlayerInGame[i] = 1;
	}
	RoundOfGame = -1; // указывается номер текущего раунда (влияет на механизм)

	for (int i = 0; i < COUNT_PLAYERS; i++) {
		bot[i].SetBotType(TSettings::Instance()->PlayerType[i]);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TF::FormShow(TObject *) {
	ResetPlayers();

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

	imgContGame->Top = imgBorder->Top + 15;
	imgTakeAMoney->Top = imgBorder->Top + 15;
	imgContGame->Left = imgTotalPrize->Left - 75;
	imgTakeAMoney->Left = imgTotalPrize->Left + imgTotalPrize->Width - (imgTakeAMoney->Width / 2.) - 75;

	imgSplash->Visible = true;
	tmrSplash->Enabled = true;
	PlaySound(rr_round);

	for (int i = 0; i < COUNT_ANSWERS; ++i) {
		imgNumber[i]->Enabled = false;
	}

	InitializeHatches();
	LoadGraphic();
	Randomize();
	tmrRotator->Interval = SpeedOfRotation;
	switchoffquestion();

	for (int i = 0; i < COUNT_PLAYERS; i++) {
		lblPlayer[i]->Caption = TSettings::Instance()->PlayerNames[i];
	}

#ifdef _DEBUG
	SetQuestionsMaximum(1, 1, 1, 1);
#else
	SetQuestionsMaximum(8, 7, 7, 4);
#endif

	tmrPulseAnimation->Enabled = true;
	DisableResizeEvent = true;
	LoadFormPosition(F);
	DisableResizeEvent = false;
	F->Resize();
}
// ---------------------------------------------------------------------------

void __fastcall TF::btnGetMoneyClick(TObject *) {
	Wait = 7;
	ModeOfGame = mFinalEndOfGame;
	btnGetMoney->Visible = false;
	btnContinueGame->Visible = false;
	tmrWaitingFinal->Enabled = true;
}
// ---------------------------------------------------------------------------

void __fastcall TF::FormResize(TObject *) {
	if (DisableResizeEvent) {
		return;
	}
	const shared_ptr<GfxCache> gfx = GfxCache::Instance();

	CoolPositionFix(F);

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
	static int labelQuestionOffcet = (F->imgQuestion->Width - F->LabelQuestion->Width) / 2;
	F->LabelQuestion->Left = F->imgQuestion->Left + labelQuestionOffcet;

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

	// Создаем лейблочки для имен игроков и денег
	int offcet = 0;
	for (int i = 0; i < COUNT_PLAYERS; ++i) {
		SetLabel(lblPlayer[i], 15 + offcet, imgPlayers->Left + 67, 201, TSettings::Instance()->PlayerNames[i]);
		SetLabel(lblMoney[i], 43 + offcet, imgPlayers->Left + 80, 176, money[i], 25);
		offcet += 83;
	}

	edFinalAnswer->Top = imgQuestion->Top + 214;
	edFinalAnswer->Left = imgQuestion->Left + 364;

	ResizeAnswers();
	if (ModeOfGame == mRoundAnswerLocked) {
		Choosen_Answer_Change_Position(answer);
	} else if (ModeOfGame == mRoundShowCorrectAns) {
		Choosen_Answer_Change_Position(RandomPlace);
	}

	imgLiver->Left = 0;
	imgLiver->Top = 145;
	imgLiver->Picture->Assign(gfx->GetLiverFrame(0));

	imgSplash->Left = int((F->ClientWidth - imgSplash->Width) / 2);
	imgSplash->Top = int((F->ClientHeight - imgSplash->Height) / 2);
	imgSplash->BringToFront();

	TPoint offset((imgHatch[0]->Width - imgPlayer[0]->Width) / 2,
				  (imgHatch[0]->Height - imgPlayer[0]->Height) / 2);
	for (int i = 0; i < COUNT_PLAYERS; ++i) {
		imgPlayer[i]->Top = imgHatch[i + 1]->Top + offset.y;
		imgPlayer[i]->Left = imgHatch[i + 1]->Left + offset.x;
	}

	imgSplash->Center = true;
	imgSplash->Width = (F->Width > F->Height) ? F->Width : F->Height;
	imgSplash->Height = imgSplash->Width;
}

// ---------------------------------------------------------------------------
void __fastcall TF::tmrMechamizmTimer(TObject *) {
	static int MechState = 1;
	if (MechanizmState == Spining) {
		if (++MechState == 15) {
			tmrMechamizm->Enabled = false;
		}
	} else {
		if (--MechState == 0) {
			tmrMechamizm->Enabled = false;
		}
	}
	const shared_ptr<GfxCache> gfx = GfxCache::Instance();
	imgLiver->Picture->Assign(gfx->GetLiverFrame(MechState));
}
// ---------------------------------------------------------------------------

void __fastcall TF::imgLiverClick(TObject *) {
	if (MechanizmState != Spining) {
		btnMechStartClick(NULL);
		tmrMechamizm->Enabled = true;
	} else {
		btnMechStopClick(NULL);
		tmrMechamizm->Enabled = true;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TF::tmrSplashTimer(TObject *) {
	Wait++ ;
#ifdef _DEBUG
#define ROUND_SPLASH_OUTTIME 1
#else
#define ROUND_SPLASH_OUTTIME 5
#endif
	if (Wait == ROUND_SPLASH_OUTTIME) {
		tmrSplash->Enabled = false;
		imgSplash->Visible = false;
		Wait = 0;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TF::tmrDecidedTimer(TObject *) {
	Wait++ ;
	if (Wait == TimeToDecide) {
		if (curbot == -1) {
			imgLiverClick(imgLiver);
			tmrDecided->Enabled = false;
			if (RoundOfGame >= 1 && RoundOfGame <= 4) {
				Wait = 0;
			}
		}
		else {
			if (bot[curbot].bAction == baStoppingMech) {
				imgLiverClick(imgLiver);
				if (FinalRoundOfGame > 0) {
					Wait = 0;
					TimeToDecide = 2 + random(3);
					bot[curbot].bAction = baChoosingHatch;
				}
				if (RoundOfGame >= 1 && RoundOfGame <= 4) {
					Wait = 0;
					tmrDecided->Enabled = false;
				}
			}
			else if (bot[curbot].bAction == baChoosingHatch) {
				Wait = 18;
				tmrDecided->Enabled = false;
				HatchClick(imgHatch[random(6)]);
			}
			else if (bot[curbot].bAction == baDecideStayOrLeave) {
				if (bot[curbot].Get_Answer()) { imgContGameClick(imgContGame); }
				else { imgTakeAMoneyClick(imgTakeAMoney); }
			}
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
void __fastcall TF::tmrLightAnimationTimer(TObject *) {
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

void __fastcall TF::ControlLabelClick(TObject *Sender) {
	TSettings *Settings = TSettings::Instance();

	if (ModeOfGame == mRoundAnswering && CanAnswer == 1 && Settings->PlayerType[chooseplayer - 1] == bbHuman) {
		F->Reward = 1000 * RoundOfGame;

		// проверяем, какой именно ответ был выбран
		for (int i = 0; i < COUNT_ANSWERS; ++i) {
			if (Sender == lblAnswers[i].get()) {
				answer = i;
			}
		}

		// включаем функцию проверки ответа и отключаем таймер
		Proverka();
		ModeOfGame = mRoundAnswerLocked;
		tmrTime->Enabled = false;
	}
	if (ModeOfGame == mRoundChoosePlayer && CanChoose == 1 && Settings->PlayerType[CurrentHatch - 1] == bbHuman) {
		for (int i = 0; i < COUNT_PLAYERS; ++i) {
			if (Sender == lblPlayer[i].get() && CurrentHatch != i + 1) {
				HatchClick(imgHatch[i + 1]);
			}
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
	}
	if (RoundOfGame == 2) {
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
	}
	if (RoundOfGame == 3) {
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

	}
	if (RoundOfGame == 4) {
		double middle = imgQuestion->Width / 2.;
		lblAnswers[0]->Left =
			(int)(imgQuestion->Left + middle - 100 - (lblAnswers[0]->Width + lblAnswers[1]->Width +
				lblAnswers[2]->Width) / 2.);
		lblAnswers[1]->Left = (int)(lblAnswers[0]->Left + (lblAnswers[0]->Width) + 100);
		lblAnswers[2]->Left = (int)(lblAnswers[1]->Left + (lblAnswers[1]->Width) + 100);
		lblAnswers[3]->Left =
			(int)(imgQuestion->Left + middle - 50 - (lblAnswers[3]->Width + lblAnswers[4]->Width) / 2.);
		lblAnswers[4]->Left = (int)(lblAnswers[3]->Left + (lblAnswers[3]->Width) + 100);
	}

	int d = (RoundOfGame < 4) ? 2 : 3;
	for (int i = 0; i < COUNT_ANSWERS && RoundOfGame > 1; ++i) {
		lblAnswers[i]->Top = imgQuestion->Top + 150 + 25 * (i / d);
	}

	for (int i = 0; i < RoundOfGame + 1; ++i) {
		if (lblAnswers[i]) {
			imgNumber[i]->Top = lblAnswers[i]->Top - 2;
			imgNumber[i]->Left = lblAnswers[i]->Left - 30;
		}
	}
}

// ---------------------------------------------------------------------------
void TF::ShowAnswers() {
	const shared_ptr<QuestionBase> base = QuestionBase::Instance();
	if (RoundOfGame == 1) {
		static const array<int, 2> left = {imgQuestion->Left + 300, imgQuestion->Left + 600};
		static top = imgQuestion->Top + 160;
		SetLabel(lblAnswers[0], top, left[0],
			base->GetAnswer(NumberOfQuestion, variants[0]).Length() * 12, base->GetAnswer(NumberOfQuestion, variants[0]));
		SetLabel(lblAnswers[1], top, left[1],
			base->GetAnswer(NumberOfQuestion, variants[1]).Length() * 12, base->GetAnswer(NumberOfQuestion, variants[1]));
	}
	if (RoundOfGame == 2) {
		static const array<int, 2> left = {imgQuestion->Left + 300, imgQuestion->Left + 600};
		static const array<int, 2> top =  {imgQuestion->Top  + 150, imgQuestion->Top  + 175};
		SetLabel(lblAnswers[0], top[0], left[0],
			base->GetAnswer(NumberOfQuestion, variants[0]).Length() * 12, base->GetAnswer(NumberOfQuestion, variants[0]));
		SetLabel(lblAnswers[1], top[0], left[1],
			base->GetAnswer(NumberOfQuestion, variants[1]).Length() * 12, base->GetAnswer(NumberOfQuestion, variants[1]));
		SetLabel(lblAnswers[2], top[1], left[0],
			base->GetAnswer(NumberOfQuestion, variants[2]).Length() * 12, base->GetAnswer(NumberOfQuestion, variants[2]));
	}
	if (RoundOfGame == 3) {
		static const array<int, 2> left = {imgQuestion->Left + 300, imgQuestion->Left + 600};
		static const array<int, 2> top =  {imgQuestion->Top  + 150, imgQuestion->Top  + 175};
		SetLabel(lblAnswers[0], top[0], left[0],
			base->GetAnswer(NumberOfQuestion, variants[0]).Length() * 12, base->GetAnswer(NumberOfQuestion, variants[0]));
		SetLabel(lblAnswers[1], top[0], left[2],
			base->GetAnswer(NumberOfQuestion, variants[1]).Length() * 12, base->GetAnswer(NumberOfQuestion, variants[1]));
		SetLabel(lblAnswers[2], top[1], left[0],
			base->GetAnswer(NumberOfQuestion, variants[2]).Length() * 12, base->GetAnswer(NumberOfQuestion, variants[2]));
		SetLabel(lblAnswers[3], top[1], left[2],
			base->GetAnswer(NumberOfQuestion, variants[3]).Length() * 12, base->GetAnswer(NumberOfQuestion, variants[3]));
	}
	if (RoundOfGame == 4) {
		static const array<int, 5> left = {
										imgQuestion->Left + 150, imgQuestion->Left + 450,
										imgQuestion->Left + 750, imgQuestion->Left + 300,
										imgQuestion->Left + 600
									};
		static const array<int, 2> top =  {imgQuestion->Top  + 150, imgQuestion->Top  + 175};
		SetLabel(lblAnswers[0], top[0], left[0],
			base->GetAnswer(NumberOfQuestion, variants[0]).Length() * 12, base->GetAnswer(NumberOfQuestion, variants[0]));
		SetLabel(lblAnswers[1], top[0], left[1],
			base->GetAnswer(NumberOfQuestion, variants[1]).Length() * 12, base->GetAnswer(NumberOfQuestion, variants[1]));
		SetLabel(lblAnswers[2], top[0], left[2],
			base->GetAnswer(NumberOfQuestion, variants[2]).Length() * 12, base->GetAnswer(NumberOfQuestion, variants[2]));
		SetLabel(lblAnswers[3], top[1], left[3],
			base->GetAnswer(NumberOfQuestion, variants[3]).Length() * 12, base->GetAnswer(NumberOfQuestion, variants[3]));
		SetLabel(lblAnswers[4], top[1], left[4],
			base->GetAnswer(NumberOfQuestion, variants[4]).Length() * 12, base->GetAnswer(NumberOfQuestion, variants[4]));
	}

	for (int i = 0; i <= RoundOfGame; ++i) {
		imgNumber[i]->Visible = true;
	}
}

void TF::Choosen_Answer_Change_Position(int mode) {
	imgChAnsLeft->Top = imgNumber[mode]->Top - 10;
	imgChAnsLeft->Left = imgNumber[mode]->Left - 10;
	imgChoosenAnswer->Top = imgChAnsLeft->Top;
	imgChoosenAnswer->Left = imgChAnsLeft->Left + imgChAnsLeft->Width;
	imgChAnsRight->Top = imgChoosenAnswer->Top;
	imgChAnsRight->Left = imgChoosenAnswer->Left + imgChoosenAnswer->Width;
}

void __fastcall TF::FormHide(TObject *) {
	tmrPulseAnimation->Enabled = false;
	SaveFormPosition(F);
	StopSoundAll();
}
// ---------------------------------------------------------------------------

void __fastcall TF::tmrAnimateBackgroundTimer(TObject *)
{
	switch (BgStateColor) {
		case clLime:
		{
			int green = GetGValue(F->Color);
			green = (green <= 255 - 51) ? green + 51 : 255;
			F->Color = (TColor)RGB(0, green, 0);
			if (F->Color == BgStateColor) {
				BgStateColor = clBlack;
			}
		}
		break;
		case clRed:
		{
			int red = GetRValue(F->Color);
			red = (red <= 255 - 51) ? red + 51 : 255;
			F->Color = (TColor)RGB(red, 0, 0);
			if (F->Color == BgStateColor) {
				BgStateColor = clBlack;
			}
		}
		break;
		case clBlack:
		{
			int green = GetGValue(F->Color);
			int red   = GetRValue(F->Color);
			green = (green >= 15) ? green - 15 : 0;
			red   = (red   >= 15) ? red   - 15 : 0;
			F->Color = (TColor)RGB(red, green, 0);
			if (F->Color == BgStateColor) {
				tmrAnimateBackground->Enabled = false;
			}
		}
		break;
	}
}
//---------------------------------------------------------------------------
void TF::FlashBackground(TColor NewStateColor)
{
	BgStateColor = NewStateColor;
	tmrAnimateBackground->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TF::imgContGameClick(TObject *)
{
	btnContinueGameClick(btnContinueGame);
	imgTakeAMoney->Visible = false;
	imgContGame->Visible = false;
	imgBorder->Visible = false;
	tmrDecided->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TF::imgTakeAMoneyClick(TObject *)
{
	btnGetMoneyClick(btnGetMoney);
	imgTakeAMoney->Visible = false;
	imgContGame->Visible = false;
	imgBorder->Visible = false;
	tmrDecided->Enabled = false;
}
//---------------------------------------------------------------------------
