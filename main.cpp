// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <SADXModLoader.h>

#include "snowboarding.h"
#include "helper-functions.h"

int testMotion = 0;
extern NJS_ACTION* a_snowboard_action[23];
extern NJS_OBJECT a_sboard_snowboard;

void testDrawBoard()
{
	taskwk* twp = playertwp[0];

	if (playerpwp[0]->mj.action < 72 || playerpwp[0]->mj.action > 94)
		return;

	NJS_ACTION * action = a_snowboard_action[playerpwp[0]->mj.action - 72];

	if(FrameCounter % 60 == 0)
		testMotion++;

	if (testMotion >= 22)
		testMotion = 0;

	njTranslateV(0, &twp->pos);
	ROTATEZ(0, twp->ang.z);
	ROTATEX(0, twp->ang.x);
	ROTATEY(0, twp->ang.y);

	njEasyDrawObject((NJS_OBJECT*)twp->timer.l);
	njPopMatrix(1);

	if (action)
	{
		DebugFontSize = 64.0f;
		njPrint(NJM_LOCATION(32, 32), "Board Action: %i", playerpwp[0]->mj.action - 72);

		NJS_MOTION* motion = action->motion;

		if (twp->flag & 2)
			njTranslate(0, 0.0, -5.2199998, 0.0);
		njEasyDrawMotion(&a_sboard_snowboard, motion, playerpwp[0]->mj.nframe);
		njPopMatrix(1);
	}
	else
	{
		if (twp->flag & 2)
			njTranslate(0, 0.0, -5.2199998, 0.0);
		njEasyDrawObject(&a_sboard_snowboard);
		njPopMatrix(1);
	}
}

void setAmyPhysics_SonAmy()
{
	playerwk_default[Characters_Amy].max_x_spd = 1.525f;
	playerwk_default[Characters_Amy].max_psh_spd = 0.55f;
	playerwk_default[Characters_Amy].jmp_y_spd = 1.48f;
	playerwk_default[Characters_Amy].nocon_speed = 3.0f;
	playerwk_default[Characters_Amy].slide_speed = 0.23f;
	playerwk_default[Characters_Amy].jog_speed = 0.46f;
	playerwk_default[Characters_Amy].run_speed = 1.39f;
	playerwk_default[Characters_Amy].rush_speed = 2.3f;
	playerwk_default[Characters_Amy].crash_speed = 3.7f;
	playerwk_default[Characters_Amy].dash_speed = 5.09f;
	playerwk_default[Characters_Amy].jmp_addit = 0.0445f;
	playerwk_default[Characters_Amy].run_accel = 0.0475f;
	playerwk_default[Characters_Amy].air_accel = 0.031f;
	playerwk_default[Characters_Amy].slow_down = -0.06f;
	playerwk_default[Characters_Amy].run_break = -0.18f;
	playerwk_default[Characters_Amy].air_break = -0.17f;
	playerwk_default[Characters_Amy].air_resist_air = -0.028f;
	playerwk_default[Characters_Amy].air_resist = -0.008f;
	playerwk_default[Characters_Amy].air_resist_y = -0.01f;
	playerwk_default[Characters_Amy].air_resist_z = -0.4f;
	playerwk_default[Characters_Amy].grd_frict = -0.1f;
	playerwk_default[Characters_Amy].grd_frict_z = -0.6f;
	playerwk_default[Characters_Amy].lim_frict = -0.31f;
}

void setAmyPhysics_SonTails()
{
	playerwk_default[Characters_Amy].max_x_spd = 2.5f;
	playerwk_default[Characters_Amy].max_psh_spd = 0.6f;
	playerwk_default[Characters_Amy].jmp_y_spd = 1.66f;
	playerwk_default[Characters_Amy].nocon_speed = 3.0f;
	playerwk_default[Characters_Amy].slide_speed = 0.23f;
	playerwk_default[Characters_Amy].jog_speed = 0.475f;
	playerwk_default[Characters_Amy].run_speed = 1.39f;
	playerwk_default[Characters_Amy].rush_speed = 2.55f;
	playerwk_default[Characters_Amy].crash_speed = 3.7f;
	playerwk_default[Characters_Amy].dash_speed = 5.09f;
	playerwk_default[Characters_Amy].jmp_addit = 0.076f;
	playerwk_default[Characters_Amy].run_accel = 0.055f;
	playerwk_default[Characters_Amy].air_accel = 0.031f;
	playerwk_default[Characters_Amy].slow_down = -0.06f;
	playerwk_default[Characters_Amy].run_break = -0.18f;
	playerwk_default[Characters_Amy].air_break = -0.17f;
	playerwk_default[Characters_Amy].air_resist_air = -0.028f;
	playerwk_default[Characters_Amy].air_resist = -0.008f;
	playerwk_default[Characters_Amy].air_resist_y = -0.01f;
	playerwk_default[Characters_Amy].air_resist_z = -0.4f;
	playerwk_default[Characters_Amy].grd_frict = -0.1f;
	playerwk_default[Characters_Amy].grd_frict_z = -0.6f;
	playerwk_default[Characters_Amy].lim_frict = -0.31f;
}

TrialLevelListEntry newAmyTrialListEntry[]
{
	{STAGE_TWINKLEPARK, 2},
	{STAGE_SNOW, 2},
	{STAGE_SHELTER, 0},
	{STAGE_FINAL, 0}
};

TrialLevelList NewAmyTrialList =
{
	newAmyTrialListEntry, 4
};

LevelClearFlagData AmyLevelclearflags[] = {
	{ STAGE_TWINKLEPARK, EventFlags_Amy_TwinkleParkClear },
	{ STAGE_SHELTER, EventFlags_Amy_HotShelterClear },
	{ STAGE_FINAL, EventFlags_Amy_FinalEggClear },
	{ STAGE_SNOW, EventFlags_Amy_TwinkleParkClear },
	{ STAGE_EGGMANROBO, EventFlags_Amy_ZeroClear },
	{ -1}
};

DataArray(LevelClearFlagData*, LevelClearFlagOffsets_correct, 0x90A3FC, 8);
DataPointer(Uint8, CharacterSelectionNumber, 0x3B2A2FD);
DataPointer(ADVERTISE_WORK, AdvertiseWork_c, 0x3B2A2F0); // General menu information

Uint16 PlayerNoTbl[]
{
	0,
	2,
	3,
	5,
	7,
	6
};

StartPosition AmySnowStartPos = { STAGE_SNOW, 2, {120,375,-40}, 8800 };

extern "C"
{
	__declspec(dllexport) void Init(const char* path, const HelperFunctions& helperFunctions)
	{
		helperFunctions.RegisterStartPosition(Characters_Amy, AmySnowStartPos);
		InitSnowboarding();

	}

	

	__declspec(dllexport) void OnFrame()
	{

		TrialLevels[3] = NewAmyTrialList;
		LevelClearFlagOffsets_correct[Characters_Amy] = AmyLevelclearflags;


		if (!LevelClearCounts[PlayerNoTbl[AdvertiseWork_c.PlayerChar] * 43 + STAGE_SNOW])
			LevelClearCounts[PlayerNoTbl[AdvertiseWork_c.PlayerChar] * 43 + STAGE_SNOW] = 1;



		if (playertp[0])
		{
			if (playertwp[0])
			{
				if (CurrentCharacter == Characters_Amy)
				{
					AmySnowboardingExec(playertp[0], playermwp[0], playerpwp[0]);
					//TrialLevels
					testDrawBoard();
				}

				if (Controllers[0].PressedButtons & Buttons_Down)
				{
					writeParamsToFile();
					writeMixedParan(Characters_Sonic, Characters_Tails);
					writeMixedParan(Characters_Sonic, Characters_Amy);
					writeActionData();
					PrintDebug("\n\nA\n\n");
				}
			}
		}
	}

	__declspec(dllexport) ModInfo SADXModInfo = { 11 };
}