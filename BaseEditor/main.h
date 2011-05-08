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
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TEdit *edAnswer;
	TCheckListBox *lstAnswers;
	TButton *btnAddAnswer;
	TListBox *lstQuestions;
	TMemo *mQuestion;
	TButton *btnAddQuestionToBase;
	TSpinButton *SpinButton1;
	TEdit *edRound;
	TPanel *pTop;
	TPanel *pAnswers;
	TPanel *pQuestions;
	TEdit *edSearch;
	TPanel *pAddAnswer;
	void __fastcall btnAddAnswerClick(TObject *Sender);
	void __fastcall edAnswerKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall lstAnswersDblClick(TObject *Sender);
	void __fastcall lstAnswersClickCheck(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
