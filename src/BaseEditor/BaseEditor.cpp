// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
// ---------------------------------------------------------------------------
USEFORM("main.cpp", f);
USEFORM("frm_pass.cpp", fpass);
//---------------------------------------------------------------------------
HWND msg_hwnd;

// ---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
    try {
        Application->Initialize();
        Application->MainFormOnTaskBar = true;
        Application->Title = "Base editor for Russian Roulette";
        Application->CreateForm(__classid(Tf), &f);
         Application->CreateForm(__classid(Tfpass), &fpass);
         msg_hwnd = Application->Handle;
        Application->Run();
    }
    catch (Exception& exception) {
        Application->ShowException(& exception);
    }
    catch (...) {
        try {
            throw Exception("");
        }
        catch (Exception& exception) {
            Application->ShowException(& exception);
        }
    }
    return 0;
}
// ---------------------------------------------------------------------------
