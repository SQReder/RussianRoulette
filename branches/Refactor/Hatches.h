// ---------------------------------------------------------------------------

#ifndef HatchesH
#define HatchesH
// ---------------------------------------------------------------------------
#include "pch.h"
#include "MainForm.h"
// ---------------------------------------------------------------------------
void Hatches();
void MechanizmSetHatchesStates();
void ShiftHatches();

#define LIGHT_ALL_HATCHES_BLUE 255
void LightHatchesW(int, int);
void ZeroRoundRotating();
void FirstRoundRotating();
void ZeroRoundSpin();
void OpenRandomHatches(const int OpenHatches, int ModeOfGame);
void SecondRoundRotating();
void ThirdRoundRotating();
void FourthRoundRotating();
void FifthRoundRotating();
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
