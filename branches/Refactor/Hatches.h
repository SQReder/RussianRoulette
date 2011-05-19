// ---------------------------------------------------------------------------

#ifndef HatchesH
#define HatchesH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Graphics.hpp>
#include "Globals.h"
#include "MainForm.h"
// ---------------------------------------------------------------------------
void Hatches();
void MechanizmSetHatchesStates();
void ShiftHatches();
void LightHatchesW(int, int);
void ZeroRoundRotating();
void FirstRoundRotating();
void ZeroRoundSpin();
void OpenRandomHatches(const unsigned char);
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
