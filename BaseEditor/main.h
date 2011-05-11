//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <CheckLst.hpp>
#include "Spin.hpp"
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tf : public TForm
{
__published:	// IDE-managed Components
	TEdit *edAnswer;
	TCheckListBox *lstAnswers;
	TButton *btnAddAnswer;
	TListBox *lstQuestions;
	TMemo *mQuestion;
	TButton *btnAddQuestionToBase;
	TSpinButton *SpinRound;
	TEdit *edRound;
	TPanel *pTop;
	TPanel *pAnswers;
	TPanel *pQuestions;
	TEdit *edSearch;
	TPanel *pAddAnswer;
	TStatusBar *StatusBar;
	TMemo *mComment;
	TPanel *Panel1;
	TButton *btnClearSearchField;
	TMainMenu *MainMenu;
	TMenuItem *mmFile;
	TMenuItem *mmAbout;
	TMenuItem *mmNewBase;
	TMenuItem *mmOpenBase;
	TMenuItem *mmSaveBase;
	TMenuItem *mmSaveBaseAs;
	TMenuItem *mmExit;
	void __fastcall btnAddAnswerClick(TObject *Sender);
	void __fastcall edAnswerKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall lstAnswersDblClick(TObject *Sender);
	void __fastcall lstAnswersClickCheck(TObject *Sender);
	void __fastcall edRoundChange(TObject *Sender);
	void __fastcall SpinRoundDownClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall SpinRoundUpClick(TObject *Sender);
	void __fastcall btnAddQuestionToBaseClick(TObject *Sender);
	void __fastcall lstQuestionsDblClick(TObject *Sender);
	void __fastcall edSearchChange(TObject *Sender);
	void __fastcall btnClearSearchFieldClick(TObject *Sender);
	void __fastcall mQuestionEnter(TObject *Sender);
	void __fastcall mQuestionExit(TObject *Sender);
	void __fastcall mCommentEnter(TObject *Sender);
	void __fastcall mCommentExit(TObject *Sender);
	void __fastcall edAnswerEnter(TObject *Sender);
	void __fastcall edAnswerExit(TObject *Sender);
	void __fastcall edSearchEnter(TObject *Sender);
	void __fastcall edSearchExit(TObject *Sender);
	void __fastcall mmExitClick(TObject *Sender);
	void __fastcall mmNewBaseClick(TObject *Sender);
	void __fastcall mmSaveBaseClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tf(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tf *f;
//---------------------------------------------------------------------------
#endif
