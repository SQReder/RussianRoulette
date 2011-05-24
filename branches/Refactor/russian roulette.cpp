// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
// ---------------------------------------------------------------------------
USEFORM("uSettings.cpp", SettingsForm);
USEFORM("Splash.cpp", SplashForm);
USEFORM("MainMenu.cpp", MenuForm);
USEFORM("About.cpp", AboutForm);
USEFORM("MainForm.cpp", F);

// ---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
    try {
        Application->Initialize();
        Application->Title = "������� �������";
        Application->CreateForm(__classid(TSplashForm), & SplashForm);
        Application->CreateForm(__classid(TMenuForm), & MenuForm);
        Application->CreateForm(__classid(TSettingsForm), & SettingsForm);
        Application->CreateForm(__classid(TAboutForm), & AboutForm);
        Application->CreateForm(__classid(TF), & F);
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
