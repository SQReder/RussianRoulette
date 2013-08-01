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
#include "MainMenu.h"
#include "MainForm.h"
#include "fSettings.h"
#include "About.h"
#include "GfxCache.h"
#include "audio.h"
#include "base.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TMenuForm *MenuForm;

// ---------------------------------------------------------------------------
__fastcall TMenuForm::TMenuForm(TComponent *Owner) : TForm(Owner) { }

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::FormCreate(TObject *) {
    Color = clBlack;

    btnNewGame->Caption = "Новая игра";
    btnShowSettings->Caption = "Настройки";
    btnGameRules->Caption = "Правила игры";
    btnBblNTuHaxep->Caption = "Выйти";
    btnAbout->Caption = "About";
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::FormClose(TObject *, TCloseAction &) {
    delete TSettings::Instance();
    Application->Terminate();
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::btnBblNTuHaxepClick(TObject *) {
	memoRules->Visible = false;
	imgRulesBgUp->Visible = false;
	imgRulesBgDown->Visible = false;
	this->GlassFrame->SheetOfGlass = true;
	TCloseAction ca = caFree;
    FormClose(NULL, ca);
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::btnNewGameClick(TObject *) {
	memoRules->Visible = false;
	imgRulesBgUp->Visible = false;
	imgRulesBgDown->Visible = false;
	this->GlassFrame->SheetOfGlass = true;
	const shared_ptr<QuestionBase> base = QuestionBase::Instance();
	base->LoadFromFile(TSettings::Instance()->LastBase);

	// сохранение текущего положения и размеров формы
    SaveFormPosition(MenuForm);

    F->Show();
    Hide();
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::btnShowSettingsClick(TObject *) {
	memoRules->Visible = false;
	imgRulesBgUp->Visible = false;
	imgRulesBgDown->Visible = false;
	this->GlassFrame->SheetOfGlass = true;
	SettingsForm->ShowModal();

    LoadFormPosition(MenuForm);
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::btnAboutClick(TObject *) {
	memoRules->Visible = false;
	imgRulesBgUp->Visible = false;
	imgRulesBgDown->Visible = false;
	this->GlassFrame->SheetOfGlass = true;
	AboutForm->ShowModal();
}
// ---------------------------------------------------------------------------

void __fastcall TMenuForm::FormResize(TObject *) {
    static bool lock_form = false;
    if (lock_form) {
        return;
    }

    lock_form = true;
    CoolPositionFix(MenuForm);
    const spacer = 0;

	btnNewGame->Top = spacer;
	btnNewGame->Left = MenuForm->ClientWidth - btnNewGame->ClientWidth - spacer;
	btnNewGame->Transparent = true;

    btnShowSettings->Top = btnNewGame->Top + btnNewGame->ClientHeight + spacer;
	btnShowSettings->Left = MenuForm->ClientWidth - btnShowSettings->ClientWidth - spacer;
	btnShowSettings->Transparent = true;

    btnGameRules->Top = btnShowSettings->Top + btnShowSettings->ClientHeight + spacer;
	btnGameRules->Left = MenuForm->ClientWidth - btnGameRules->ClientWidth - spacer;
	btnGameRules->Transparent = true;

    btnBblNTuHaxep->Top = MenuForm->ClientHeight - btnBblNTuHaxep->ClientHeight - spacer;
	btnBblNTuHaxep->Left = MenuForm->ClientWidth - btnBblNTuHaxep->ClientWidth - spacer;
	btnBblNTuHaxep->Transparent = true;

    Background->Top = int((MenuForm->ClientHeight - Background->Height) / 2);
	Background->Left = int((MenuForm->ClientWidth - Background->Width) / 2);

	memoRules->Top = 150;
	memoRules->Left = 30;
	memoRules->Width = MenuForm->Width - btnGameRules->Width - 130;
	memoRules->Height = MenuForm->Height - 300;
	imgRulesBgUp->Top = 100;
	imgRulesBgUp->Left = memoRules->Left;
	imgRulesBgUp->Width = memoRules->Width;
	imgRulesBgDown->Top = 150 + memoRules->Height;
	imgRulesBgDown->Left = memoRules->Left;
	imgRulesBgDown->Width = memoRules->Width;

    btnAbout->Top = MenuForm->ClientHeight - btnBblNTuHaxep->ClientHeight - btnAbout->ClientHeight - spacer * 2;
	btnAbout->Left = MenuForm->ClientWidth - btnAbout->ClientWidth - spacer;
	btnAbout->Transparent = true;

    lock_form = false;
}
// ---------------------------------------------------------------------------

void __fastcall TMenuForm::FormShow(TObject *) {
    TSettings *Settings = TSettings::Instance();
    MenuForm->Constraints->MinWidth = Settings->MinWidth;
    MenuForm->Constraints->MinHeight = Settings->MinHeight;

	const shared_ptr<GfxCache> gfx = GfxCache::Instance();
	Background->Picture->Assign(gfx->Menu_bg.get());

    LoadFormPosition(MenuForm);
}

// ---------------------------------------------------------------------------
void __fastcall TMenuForm::FormKeyDown(TObject *, WORD &Key, TShiftState Shift) {
    if (Shift.Contains(ssAlt) && (Key == 13)) {
        SwitchFullscreen(MenuForm);
	} else if (Shift.Empty()) {
        switch (Key) {
        case 'N': btnNewGameClick(NULL);
            break;
        case 27: btnBblNTuHaxepClick(NULL);
			break;
		case 'R':
			btnGameRulesClick(NULL);
			break;
        case 'S': btnShowSettingsClick(NULL);
            break;
        case 'A': btnAboutClick(NULL);
            break;
        }
    }
}
// ---------------------------------------------------------------------------
void __fastcall TMenuForm::btnGameRulesClick(TObject *Sender)
{
	memoRules->Top = 150;
	memoRules->Left = 30;
	memoRules->Width = MenuForm->Width - btnGameRules->Width - 130;
	memoRules->Height = MenuForm->Height - 300;
	imgRulesBgUp->Top = 100;
	imgRulesBgUp->Left = memoRules->Left;
	imgRulesBgUp->Width = memoRules->Width;
	imgRulesBgDown->Top = 150 + memoRules->Height;
	imgRulesBgDown->Left = memoRules->Left;
	imgRulesBgDown->Width = memoRules->Width;
	this->GlassFrame->SheetOfGlass = false;
	LoadRulesText();
	memoRules->Visible = true;
	imgRulesBgUp->Visible = true;
	imgRulesBgDown->Visible = true;
}
//---------------------------------------------------------------------------
void TMenuForm::LoadRulesText() {
	array<const String, 86> rules =
	 { "Ведь это «Русская рулетка» — игра, сыграть в ",
	   "которую существует целый миллион причин. (© Валдис Пельш)\r\n\r\nПравила игры",
	   " целиком и полностью построены на оригинальных правилах телевизионной игры.",
	   "\r\n\r\nКаждый раз игра будет начинаться с пятью участниками. ",
	   "Именно они между собой должны бороться за выход в финал, где финалист и ",
	   "может заработать 1000000 виртуальных рублей.\r\n\r\n",
	   "= Правила основной игры =\r\n\r\n",
	   "Всего в игре четыре раунда. В начале первого из них ведущий с помощью ",
	   "механизма приведёт в действие механизм «Русской рулетки», который позволит",
	   " определить участника, задающего первый вопрос. После этого первый вопрос ",
	   "игры будет показан на экране, а также каждому игроку будет начислено по ",
	   "стартовой 1000 рублей для того, чтобы было, на что играть.\r\n\r\n",
	   "Основной принцип игры прост: участники в каждом из раундов будут адресовать",
	   " друг другу вопросы, заданные компьютером. Игрок, которому был передан вопрос, ",
	   "обязан в течение 20 секунд с момента начала отсчёта времени дать ответ на вопрос."
	   " Выбирать участнику придётся из нескольких вариантов ответа: в зависимости",
	   " от раунда, количество вариантов будет варьироваться от 2-х до 5-ти с шагом",
	   " в один вариант. Естественно, на заданный вопрос существует только один ",
	   "верный ответ.\r\n\r\n",
	   "Если игрок даёт верный ответ на вопрос, он получает на свой счёт ",
	   "вознаграждение в сумме от 1000 до 4000 виртуальных рублей (размер суммы ",
	   "зависит от номера раунда). Если же ошибается, то он теряет все заработанные",
	   " деньги (они переходят участнику, адресовавшему ему заданный вопрос), и в ",
	   "таком случае ему придётся привести в действие механизм «Русской рулетки».\r\n\r\n",
	   "В механизме шесть ячеек. В первом раунде игры лишь одна из них будет ",
	   "пустой, однако по мере прохождения игры количество пустых ячеек будет ",
	   "увеличиваться: в четвёртом раунде уже четыре из шести ячеек могут погубить"
	   " игрока. Если после остановки механизма под игроком оказывается ",
	   "спасительная ячейка, то он остаётся в игре и имеет право адресовать ",
	   "следующий вопрос кому-то из соперников. В противном случае количество ",
	   "игроков на площадке сокращается, и раунд считается завершённым.\r\n\r\n",
	   "Если вопросы раунда завершились, но никто из игроков не провалился, то ",
	   "лидер по количеству денег сможет привести в действие механизм ",
	   "«Русской рулетки», а один из его соперников покинет игру после остановки ",
	   "механизма. Но в случае, когда на площадке нет явного лидера (несколько ",
	   "участников имеют одинаковую наибольшую сумму), тогда механизм приводит в ",
	   "действие ведущий, а игру в итоге покинет один из всех оставшихся на ",
	   "площадке игроков.\r\n\r\n",
	   "Если на счету у участника, покинувшего игру в результате такой ситуации, ",
	   "были какие-либо деньги, то они делятся в равных долях между оставшимися ",
	   "игроками.\r\n\r\n",
	   "= Правила финального раунда =\r\n\r\n",
	   "Игрок, который смог обыграть своих соперников на протяжении всех четырёх ",
	   "раундов, становится финалистом игры.\r\n\r\n",
	   "Правила финала довольно просты. Вся финальная часть игры делится на три ",
	   "раунда, в каждом из которых будут задаваться вопросы разного уровня ",
	   "сложности на разную стоимость.\r\n\r\n",
	   "В начале каждого раунда участник после предупредительного сигнала должен ",
	   "привести в действие механизм «Русской рулетки», чтобы определить ",
	   "расстановку пустых ячеек в раунде. После остановки механизма игрок должен ",
	   "выбрать один из шести люков, который он и займёт.\r\n\r\n",
	   "В дальнейшем игрок увидит вопрос стоимостью 50000, 100000 или 1000000 ",
	   "виртуальных рублей (зависит от текущего раунда финала). Вариантов ответа ",
	   "к этому вопросу дано не будет, и у участника будет лишь 10 секунд на ответ.",
	   " За это время необходимо ввести ответ в появившееся поле и нажать клавишу ",
	   "Enter.\r\n\r\n",
	   "Если ответ окажется верным, раунд считается пройденным, а игрок получает ",
	   "стоимость вопроса к себе на счёт. После этого он сможет решить, продолжить ",
	   "игру и перейти к следующему раунду, или же забрать имеющуюся сумму и ",
	   "покинуть игру. Однако, если вопрос стоил 1000000 виртуальных рублей, ",
	   "игра заканчивается сразу же.\r\n\r\n",
	   "Если ответ окажется неверным, то три, четыре или пять люков из шести ",
	   "откроются автоматически. В случае, если игрок останется на площадке, он ",
	   "сможет увидеть новый вопрос той же стоимости, но перед этим ему придётся ",
	   "вновь привести в действие механизм. Если же игрок проваливается, игра ",
	   "завершается, а выигрышем участника становятся деньги, заработанные в ",
	   "основном этапе игры.\r\n\r\n",
	   "Если игрок останется спасённым в случае ошибки на вопросе стоимостью ",
	   "1000000 виртуальных рублей, то миллион прибавляется на счёт участника и ",
	   "игра на этом заканчивается. Игра также заканчивается в случае, если ",
	   "игрок забрал деньги на промежуточных этапах или провалился.\r\n\r\n",
	   "= Управление =\r\n\r\n",
	   "В момент выбора отвечающего игрока кнопками «1», «2», «3», «4» и «5» ",
	   "можно выбрать участника, отвечающего на вопрос. Также это можно сделать, ",
	   "щёлкнув по люку с игроком.\r\n\r\n",
	   "Ответ на вопрос фиксируется нажатием клавиш «1», «2», «3», «4» или «5», ",
	   "в соответствии с порядковым номером ответа. Также ответ фиксируется ",
	   "щелчком левой кнопкой мыши по варианту ответа.\r\n\r\n",
	   "Привести в действие, а также остановить механизм можно щелчком по рычагу, ",
	   "а также нажатием кнопки «Пробел».\r\n\r\n",
	   "Чтобы зафиксировать решение «забрать деньги» или «продолжить игру» ",
	   "в финальном раунде, необходимо щёлкнуть по кнопке с соответствующим ",
	   "решением левой кнопкой мыши.\r\n\r\n",
	   "Переключение между оконным и полноэкранным режимом в процессе игры ",
	   "осуществляется по нажатию сочетания клавиш «Alt»+«Enter».\r\n\r\n",
	   "Выход из игры — клавиша «Esc» или сочетание «Alt»+«F4», а также ",
	   "щелчок по кнопке «Выход из игры». Прогресс игры при этом теряется."};

	 String all_rules;

	 for (unsigned int i = 0; i < rules.size(); i++) {
		 all_rules += rules[i];
	 }
	 memoRules->Lines->Text = all_rules;
}
