#include <SADXModLoader.h>
#include "pch.h"
#include "decomp-pointers.h"
#include "decomp-structs.h"

#include <FunctionHook.h>

FunctionHook<void> SetFinishAction_h(0x415540);

bool VictoryFixEnabled = true;

typedef struct stageAndAct
{
	short stage; 
	short act;
};

stageAndAct AMY_NORMAL_STAGES[]
{
	{STAGE_TWINKLEPARK,1},
	{STAGE_SHELTER,1},
	{STAGE_FINAL,0}
};


//Thanks MainMemory, you're a sweetheart~
int SetAmyWinPose()
{
	if (CurrentCharacter != Characters_Amy || (CurrentLevel >= LevelIDs_Chaos0 && CurrentLevel != LevelIDs_SandHill))
		return 42;
	else
		return 32;
}

void SetLocalPathCamera(pathtag* ptp, int mode, int timer)
{
	unsigned __int8 v4; // r30

	v4 = mode;
	CameraSetEventCameraFunc(CameraLocalPath, 0, 2);
	camera_twp->value.l = (int)ptp;
	camera_twp->counter.b[0] = v4;
	camera_twp->timer.l = timer;
	camera_twp->counter.w[1] = 0;
}

void WaitLandPlayer_Amy(task* tp)
{
	taskwk* twp;
	
	//if (playertwp[0] && IsReleaseBoxActive() && GetReleaseBoxOpenID() == 1)
		twp = playertwp[0];



	if ((twp->flag & PL_FLAG_FLOOR) != 0)
	{
		//SetInputP(0, 19);
		twp->mode = MD_AMY_PLON;
		playerpwp[0]->mj.reqaction = 42;
		SetLocalPathCamera(&pathtag_a_camera0, 3, 720);
		//GM_SECall(SE_AV_CARTGOAL);
		GM_SECall(SE_AV_CLEAR);
		//InitDisplayGoal();
		pdVibMxStop(0);
		CreateElementalTask(2u, 5, CalcTotalScore);
		GM_BGM_Play(75);
		FreeTask(tp);
		return;
	}

}

void SetFinishAction_r()
{
	if (usPlayer != PLNO_AMY)
	{
		SetFinishAction_h.Original();
		return;
	}

	bool isNormalStage = false;

	for (int i = 0; i < 3; i++)
	{
		if (ssStageNumber == AMY_NORMAL_STAGES[i].stage && ssActNumber == AMY_NORMAL_STAGES[i].act)
			isNormalStage = true;
	}

	if (isNormalStage)
	{
		//Do normal stage things.
		SetFinishAction_h.Original();
		return;
	}
	
	PadReadOffP(0);
	ssPauseEnable = FALSE;
	SleepTimer();

	if (ulGlobalMode == 10)
		InitMissionCtrl();

	CreateElementalTask(0, LEV_3, WaitLandPlayer_Amy);
}

void SetFinishAction_aa()
{
	PadReadOffP(0);
	ssPauseEnable = FALSE;
	SleepTimer();

	if (ulGlobalMode == 10)
		InitMissionCtrl();

	switch (usPlayer)
	{
	case PLNO_TAILS:

		if (RaceWinnerPlayer == 1)
		{
			CreateElementalTask(0, LEV_3, WaitLandPlayer);
			return;
		}

		SetInputP(0, 19);
		SetMilesFinishAction();
		pdVibMxStop(0);
		CreateElementalTask(2u, 5, CalcTotalScore);
		break;

	case PLNO_KNUCKLES:
		SetInputP(0, 19);
		SetLocalPathCamera(&pathtag_k_camera0, 3, 720);
		pdVibMxStop(0);
		CreateElementalTask(2u, 5, CalcTotalScore);
		if ((ssActNumber | (ssStageNumber << 8)) >= 3840)
		{
			ADX_Close();
			GM_SECall(1448);
			GM_BGM_Play(75);
		}
		else
		{
			ADX_Close();
			GM_SECall(1445);
			GM_BGM_Play(75);

		}
	case PLNO_AMY:

		CreateElementalTask(0, LEV_3, WaitLandPlayer_Amy);
		SetAmyWinPose();
		/*
		if ((ssActNumber | (ssStageNumber << 8)) >= 3840)
		{
			CreateElementalTask(0, LEV_3, WaitLandPlayer);
		}
		else
		{
			SetInputP(0, 19);
			pdVibMxStop(0);
			CreateElementalTask(2u, 5, CalcTotalScore);
			ADX_Close();
			GM_SECall(1388);
			GM_BGM_Play(75);
		}*/
		break;

	case PLNO_BIG:
		SetInputP(0, 19);
		NJS_POINT3 camVec;
		camVec.x = -36.072899f;
		camVec.y = 5.7132001f;
		camVec.z = -1.5176001f;
		PConvertVector_P2G(playertwp[0], &camVec);
		//externCameraParam.yDirPos = playertwp[0]->cwp->info->center.y;
		//externCameraParam.zDirPos = playertwp[0]->cwp->info->center.z;
		//externCameraParam.xDirPos = playertwp[0]->cwp->info->center.x;
		//njSubVector(&playertwp[0]->cwp->info->center, &camVec);
		//externCameraParam.xCamPos = playertwp[0]->cwp->info->center.x;
		//externCameraParam.yCamPos = playertwp[0]->cwp->info->center.y;
		//externCameraParam.zCamPos = playertwp[0]->cwp->info->center.z;
		//CameraSetEventCameraFunc(CameraEventPointToPoint, 1u, 2);
		//InitDisplayGoal();
		//CreateElementalTask(2u, 5, CalcTotalScore);
		if ((ssActNumber | (ssStageNumber << 8)) >= 3840)
		{
			ADX_Close();
		}
		GM_BGM_Play(75);
		break;

	default:
		CreateElementalTask(0, LEV_3, WaitLandPlayer);
		ADX_Close();
		break;
	}
}