// ---------------------------------------------------------------------------

#ifndef SplashH
#define SplashH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <pngimage.hpp>
#include <StdCtrls.hpp>

// ---------------------------------------------------------------------------
class TSplashForm : public TForm {
__published: // IDE-managed Components

    TImage *imgSplash;
    TTimer *tmrSplash;
    TTimer *tmrOpenSplash;
    TProgressBar *PBLoad;
    TLabel *lblLoadState;

    void __fastcall FormCreate(TObject *Sender);
    void __fastcall tmrSplashTimer(TObject *Sender);
    void __fastcall tmrOpenSplashTimer(TObject *Sender);

public: // User declarations
    __fastcall TSplashForm(TComponent *Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TSplashForm *SplashForm;
// ---------------------------------------------------------------------------
#endif
