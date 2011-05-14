//---------------------------------------------------------------------------


#pragma hdrstop

#include "uHostMode.h"
#include "uSettings.h"
#include "MainForm.h"
#include "Hatches.h"
TF* FPlayerMode = new TF(F);
//---------------------------------------------------------------------------
void initialize_host_mode() {
	if (Screen->MonitorCount > 1) {
	   copy_stats();
	   FPlayerMode->DefaultMonitor = dmDesktop;
	   FPlayerMode->Show();
	   TRect Bounds2 = Screen->Monitors[1]->BoundsRect; // получаем границы
	   FPlayerMode->SetBounds(Bounds2.Left,Bounds2.Top,Bounds2.Width(),Bounds2.Height());
	   FPlayerMode->Left = Screen->Monitors[1]->Left;
	   FPlayerMode->Top = Screen->Monitors[1]->Top;
	}
}
//---------------------------------------------------------------------------
void copy_stats() {
	FPlayerMode->Settings = F->Settings;
	MechanizmSetHatchesStates();
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
