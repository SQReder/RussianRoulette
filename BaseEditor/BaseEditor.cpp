// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
// ---------------------------------------------------------------------------
USEFORM("main.cpp", f);
//---------------------------------------------------------------------------
HWND msg_hwnd;

// ---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
    try {
        Application->Initialize();
        Application->MainFormOnTaskBar = true;
        Application->Title = "Base editor for Russian Roulette";
        Application->CreateForm(__classid(Tf), &f);
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
