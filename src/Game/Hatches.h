#pragma once
#include "pch.h"
#include "MainForm.h"

typedef enum {
	Zero, First, Second, Third, Fourth, Final
} RoundEnum;

typedef enum {
		lcBlack  = 0,
		lcBase   = 1,
		lcBlue   = 2,
		lcRed    = 3,
		lcWhite  = 4,
} LightColorsEnum;

// этот класс написан, что-бы нельзя было задавать подсветку числом
class HatchLightState {
	LightColorsEnum state;
public:
	HatchLightState()
	: state(LightColorsEnum()) { };

	HatchLightState(const LightColorsEnum& s)
	: state(s) { }

	bool operator==(const LightColorsEnum& h) const
	{ return state == h; }

	bool operator!=(const HatchLightState& h) const
	{ return state != h.state; }

	bool operator<(const HatchLightState& h) const
	{ return state < h.state; }

	operator LightColorsEnum()
	{ return state; }
};

// ---------------------------------------------------------------------------
void InitializeHatches();
void ShiftHatches();

void DoRotating(const RoundEnum round);
void ZeroRoundSpin();
void ZeroRoundRotating();
void OpenRandomHatches(const int OpenHatches, int ModeOfGame);
void UpdateHatches();
void choosingplayer();
void Proverka2();
void OpenHatchNow(int hatchToOpen);
void SwitchesLights();
void before_spin_lights();
void after_spin_lights();
void OpenHatches();
void LightAllHatchesWith(HatchLightState light);
void ChangeHatchesLight(HatchLightState exclude, HatchLightState to);

extern int AnimationFrame;
