#pragma once

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>


class TF : public TForm
{
__published:	// IDE-managed Components
	TPanel *PanelContent;
	TPanel *PanelBottom;
	TMainMenu *menuMain;
	TMenuItem *mFile;
	TMenuItem *mExit;
	TComboBox *cbRound;
	TSplitter *Splitter1;
	TListBox *lstLog;
	TEdit *edQuestionFilter;
	TListBox *ListBox1;
	TPanel *PanelEditor;
	TLabel *Label2;
	TMemo *mQuestion;
	TMemo *mAnswers;
	TLabel *Label1;
	TPanel *PanelQuestions;
	TLabel *Label3;
	TLabel *Label4;
	TSplitter *Splitter2;
	TLabel *Label5;
private:	// User declarations
public:		// User declarations
	__fastcall TF(TComponent* Owner);
};


extern PACKAGE TF *F;
