// ---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <pngimage.hpp>
#include <MPlayer.hpp>
#include <ComCtrls.hpp>
#include <GIFImg.hpp>
// ---------------------------------------------------------------------------
enum TBotType {
    bbHuman, bbFoooool, bbFooly, bbNormal, bbHard, bbVeryHard
} ;

class TSettings {
public:
    UnicodeString PlayerNames[5];
    TBotType PlayerType[5];
    bool Fullscreen;
    int FormsWidth;
    int FormsHeight;
    int FormsTop;
    int FormsLeft;
    int MinWidth;
    int MinHeight;
    bool SoundEnabled;
    int SoundVolume;
    bool MusicEnabled;
    int MusicVolume;
    bool Win7Features;
    bool HostMode;
    String LastBase;
    TStringList* BaseNames;

    TSettings() {
        PlayerNames[0] = "Игрок №1";
        PlayerType[0] = bbHuman;
        PlayerNames[1] = "Игрок №2";
        PlayerType[1] = bbHuman;
        PlayerNames[2] = "Игрок №3";
        PlayerType[2] = bbHuman;
        PlayerNames[3] = "Игрок №4";
        PlayerType[3] = bbHuman;
        PlayerNames[4] = "Игрок №5";
        PlayerType[4] = bbHuman;

        Fullscreen = True;

        FormsWidth = 1024;
        FormsHeight = 768;

        MinWidth = 1024;
        MinHeight = 768;

        SoundEnabled = True;
        SoundVolume = 100;
        MusicEnabled = True;
        MusicVolume = 100;

        Win7Features = False;

        LastBase = "main.dat";

        BaseNames = new TStringList;
    } ;

} ;
// -----------------------------------------------------------------------------
class QA {
public:
    char Round;
    UnicodeString Question;
    UnicodeString Answers[5];
    int TrueAnswer;

    QA() {
        TrueAnswer = -1;
        Round = -1;
    }
} ;
// -----------------------------------------------------------------------------
class TF: public TForm {
__published: // IDE-managed Components
    TImage* imgPlace;
    TImage* imgHatch0;
    TImage* imgHatch3;
    TImage* imgHatch1;
    TImage* imgHatch2;
    TImage* imgHatch5;
    TImage* imgHatch4;
    TImage* imgQuestion;
    TButton* btnMechStart;
    TButton* btnMechStop;
    TButton* btnGetMoney;
    TButton* btnContinueGame;
    TButton* btnExit;
    TTimer* tmrRotator;
    TMediaPlayer* MediaPlayer1;
    TLabel* LabelQuestion;
    TLabel* LabelMoney;
    TTimer* tmrWaiting;
    TTimer* tmrMoney;
    TImage* imgPlayers;
    TImage* imgNumber1;
    TImage* imgNumber2;
    TImage* imgNumber3;
    TImage* imgNumber4;
    TImage* imgNumber5;
    TImage* imgChoosenAnswer;
    TTimer* tmrTime;
    TLabel* lblTimer;
    TImage* imgTimer;
    TMemo* mlog;
    TTimer* tmrLog;
    TImage* imgPulse;
    TTimer* tmrWaitingFinal;
    TTimer* tmrPulseAnimation;
    TEdit* edFinalAnswer;
    TLabel* lblRightAnswer;
    TImage* imgTotalPrize;
    TImage* imgPlayer1;
    TImage* imgPlayer2;
    TImage* imgPlayer3;
    TImage* imgPlayer4;
    TImage* imgPlayer5;
    TImage* imgMechanizm;
    TTimer* tmrMechamizm;
    TImage* imgSplash;
    TTimer* tmrSplash;
    TLabel* lblExit;
    TButton* Button1;
    TImage* imgTicker;
    TImage* imgPulseBar;
    TImage* imgBorder;
    TTimer* tmrDecided;
    TTimer* tmrLightAnimation;
    TMediaPlayer* MediaPlayer2;
    TImage* imgChAnsLeft;
    TImage* imgChAnsRight;
    TLabel* ControlLabel;

    void __fastcall tmrPulseAnimationTimer(TObject* Sender);
    void __fastcall imgPlaceClick(TObject* Sender);
    void __fastcall Button1Click(TObject* Sender);
    void __fastcall FormCreate(TObject* Sender);
    void __fastcall LoadGraphic();
    void __fastcall Button2Click(TObject* Sender);
    void __fastcall btnMechStartClick(TObject* Sender);
    void __fastcall btnExitClick(TObject* Sender);
    void __fastcall btnMechStopClick(TObject* Sender);
    void __fastcall tmrRotatorTimer(TObject* Sender);
    void __fastcall PlaySound(String path);
    void __fastcall PlayMusic(String path);
    void __fastcall tmrWaitingTimer(TObject* Sender);
    void __fastcall tmrMoneyTimer(TObject* Sender);
    void __fastcall imgHatch4Click(TObject* Sender);
    void __fastcall imgHatch5Click(TObject* Sender);
    void __fastcall imgHatch3Click(TObject* Sender);
    void __fastcall imgHatch1Click(TObject* Sender);
    void __fastcall imgHatch2Click(TObject* Sender);
    void __fastcall FormKeyDown(TObject* Sender, WORD& Key, TShiftState Shift);
    void __fastcall tmrTimeTimer(TObject* Sender);
    void __fastcall tmrLogTimer(TObject* Sender);
    void __fastcall tmrWaitingFinalTimer(TObject* Sender);
    void __fastcall imgHatch0Click(TObject* Sender);
    void __fastcall edFinalAnswerKeyPress(TObject* Sender, wchar_t& Key);
    void __fastcall btnContinueGameClick(TObject* Sender);
    void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
    void __fastcall FormShow(TObject* Sender);
    void __fastcall btnGetMoneyClick(TObject* Sender);
    void __fastcall FormResize(TObject* Sender);
    void __fastcall tmrMechamizmTimer(TObject* Sender);
    void __fastcall imgMechanizmClick(TObject* Sender);
    void __fastcall tmrSplashTimer(TObject* Sender);
    void __fastcall lblExitClick(TObject* Sender);
    void __fastcall tmrDecidedTimer(TObject* Sender);
    void __fastcall tmrLightAnimationTimer(TObject* Sender);
    void __fastcall ControlLabelClick(TObject* Sender);

private: // User declarations
    void CreateLabel(int, int, int, int, int, int, UnicodeString);

public: // User declarations
    __fastcall TF(TComponent* Owner);

    int opened_now[6]; // указывает какие люки будут открыты после остановки механизма
    int CurrentHatch;
    char TempRoundOfGame;
    char mode;
    int ModeOfGame;
    int chooseplayer;
    int RndHatch;
    int CantFall;
    TLabel* lblMoney[5]; // лейблы и конструктор для отображения денег на панели игроков.
    TLabel* lblPlayer[5];
    TLabel* lblAnswers[5];
    int qcount;

    QA* base;
    int answer;
    int Reward;

    void LoadQuestionFromBase(String BaseName);
    void TF::TransferMoney();
    int money[5]; // деньги игроков
    int pulse[5]; // Пульсации кровяного давления

    int NumberOfQuestion;
    int Wait;
    int RandomPlace;

    void blabla();

    bool _Parse(UnicodeString ans);
    void TransferMoneyFinal();

    bool ingame[5]; // массив, определяющий наличие игрока в игре
    char RoundOfGame; // указывается номер текущего раунда (влияет на механизм)
    char FinalRound; // указывается номер финальной части раунда
    int FinalRoundOfGame; // финальный раунд игры (определяет стоимость финального вопроса)

    TSettings* Settings;

    void InitializeSettings();
    String FillChars(String str, int count);
    String GetStr(String str, int begin, int size);
    String ClearStr(String str);

    bool FatalError;
    void ShowAnswers();
    void ResizeAnswers();
    void Choosen_Answer_Change_Position();
} ;

void ShowError(int errcode);
void DumpMemory(int errcode);
// ---------------------------------------------------------------------------
extern PACKAGE TF* F;
// ---------------------------------------------------------------------------

#endif
