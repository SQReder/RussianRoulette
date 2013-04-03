// ---------------------------------------------------------------------------

#ifndef HatchesH
#define HatchesH
// ---------------------------------------------------------------------------
#include "pch.h"
#include "MainForm.h"

typedef enum {
	Zero, First, Second, Third, Fourth, Final
} RoundEnum;
// ---------------------------------------------------------------------------
void InitializeHatches();
void ShiftHatches();

#define LIGHT_ALL_HATCHES_BLUE 255
void LightHatchesW(int, int);
void DoSpin(const RoundEnum round);
void ZeroRoundSpin();
void OpenRandomHatches(const int OpenHatches, int ModeOfGame);
void UpdateHatches();
void choosingplayer();
void Proverka2();
void OpenHatches();
void SwitchesLights();
void before_spin_lights();
void after_spin_lights();
void OpenRndHatches();

extern int AnimationFrame;
#endif
