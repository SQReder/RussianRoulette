// ---------------------------------------------------------------------------

#ifndef SplashH
#define SplashH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <pngimage.hpp>

// ---------------------------------------------------------------------------
class TSplashForm : public TForm {
__published: // IDE-managed Components

    TImage* imgSplash;
    TTimer* tmrSplash;
    TTimer* tmrOpenSplash;

    void __fastcall FormCreate(TObject* Sender);
    void __fastcall FormClick(TObject* Sender);
    void __fastcall tmrSplashTimer(TObject* Sender);
    void __fastcall imgSplashClick(TObject* Sender);
    void __fastcall tmrOpenSplashTimer(TObject* Sender);

public: // User declarations
    __fastcall TSplashForm(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TSplashForm* SplashForm;
// ---------------------------------------------------------------------------
#endif
