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
// ---------------------------------------------------------------------------




USEFORM("MainMenu.cpp", MenuForm);
USEFORM("Splash.cpp", SplashForm);
USEFORM("MainForm.cpp", F);
USEFORM("About.cpp", AboutForm);
USEFORM("fSettings.cpp", SettingsForm);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
    try {
        Application->Initialize();
        Application->Title = "Русская рулетка";
        Application->CreateForm(__classid(TSplashForm), &SplashForm);
		Application->CreateForm(__classid(TMenuForm), &MenuForm);
		Application->CreateForm(__classid(TSettingsForm), &SettingsForm);
		Application->CreateForm(__classid(TAboutForm), &AboutForm);
		Application->CreateForm(__classid(TF), &F);
		Application->Run();
    }
    catch (Exception &exception) {
        Application->ShowException(&exception);
    }
    catch (...) {
        try {
            throw Exception("");
        }
        catch (Exception &exception) {
            Application->ShowException(&exception);
        }
    }

    return 0;
}
// ---------------------------------------------------------------------------
