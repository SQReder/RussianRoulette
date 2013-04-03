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
#include "uHostMode.h"
#include "MainForm.h"

// ---------------------------------------------------------------------------
void initialize_host_mode() {
    if (Screen->MonitorCount > 1) {
        TForm *FPlayerMode = new TForm(F);
        FPlayerMode->DefaultMonitor = dmDesktop;
        TRect Bounds2 = Screen->Monitors[1]->BoundsRect; // получаем границы
        FPlayerMode->SetBounds(Bounds2.Left, Bounds2.Top, Bounds2.Width(), Bounds2.Height());
        FPlayerMode->Left = Screen->Monitors[1]->Left;
        FPlayerMode->Top = Screen->Monitors[1]->Top;
        FPlayerMode->Show();
    }
}
// ---------------------------------------------------------------------------

#pragma package(smart_init)
