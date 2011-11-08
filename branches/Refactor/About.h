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
#ifndef AboutH
#define AboutH
// ---------------------------------------------------------------------------
#include "pch.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>

// ---------------------------------------------------------------------------
class TAboutForm : public TForm {
__published: // IDE-managed Components

    TLabel *lblProjTitle;
    TLabel *lblLicence;
    TLabel *Label22;
    TLabel *Label1;

    void __fastcall FormCreate(TObject *Sender);
    void __fastcall lblLicenceClick(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

public: // User declarations
    __fastcall TAboutForm(TComponent *Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TAboutForm *AboutForm;
// ---------------------------------------------------------------------------
#endif
