//---------------------------------------------------------------------------


#pragma hdrstop

#include "uHostMode.h"
#include "MainForm.h"
//---------------------------------------------------------------------------
void initialize_host_mode() {
	if (Screen->MonitorCount > 1) {
	   TForm* FPlayerMode = new TForm(F);
	   FPlayerMode->DefaultMonitor = dmDesktop;
		TRect Bounds2 = Screen->Monitors[1]->BoundsRect; // получаем границы
	FPlayerMode->SetBounds(Bounds2.Left,Bounds2.Top,Bounds2.Width(),Bounds2.Height());
	   FPlayerMode->Left = Screen->Monitors[1]->Left;
	   FPlayerMode->Top = Screen->Monitors[1]->Top;
	   FPlayerMode->Show();
	}
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
