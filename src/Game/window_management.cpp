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
#include "window_management.h"
#include "pch.h"
#pragma package(smart_init)

// ---------------------------------------------------------------------------
void LoadFormPosition(TForm *form) {
    TSettings *Settings = TSettings::Instance();

    if (Settings->Fullscreen) {
        form->BorderStyle = bsNone;
        form->Width = Screen->Width;
        form->Height = Screen->Height;
        form->Top = 0;
        form->Left = 0;
    } else {
        form->BorderStyle = bsSizeable;
        form->Width = Settings->FormsWidth;
        form->Height = Settings->FormsHeight;
        form->Left = Settings->FormsLeft;
        form->Top = Settings->FormsTop;
    }
}

void SaveFormPosition(TForm *form) {
    TSettings *Settings = TSettings::Instance();

    if (!Settings->Fullscreen) {
        Settings->FormsWidth = form->Width;
        Settings->FormsHeight = form->Height;
        Settings->FormsTop = form->Top;
        Settings->FormsLeft = form->Left;
    }
}
// ---------------------------------------------------------------------------

void CoolPositionFix(TForm *form) {
    /* ј÷÷ »…  ќ—“џЋ№
     суть в том, что после перевода формы в состо€ние Borderless
     она самопроизвольно сдвигаетс€ влево, что не есть гут
     при этом контролировать это смещение из LoadFormPosition()
     не представл€етс€ возможным =(
     */
    if (form->Top < 0) {
        form->Top = 0;
    }
    if (form->Left < 0) {
        form->Left = 0;
    }
}
// ---------------------------------------------------------------------------

void SwitchFullscreen(TForm *form) {
    TSettings *Settings = TSettings::Instance();

    Settings->Fullscreen = !Settings->Fullscreen;
    LoadFormPosition(form);
}
