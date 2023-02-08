
#include "pch.h"

#include <SADXModLoader.h>
#include <UsercallFunctionHandler.h>
#include "helper-functions.h"
#include "decomp-pointers.h"
#include "decomp-structs.h"

#include "a_sbfront0.h"
#include "a_sbfront1.h"
#include "a_sblstop0.h"
#include "a_sbrstop0.h"

#include "a_sbjump0.h"
#include "a_sbjump1.h"
#include "a_sbright0.h"
#include "a_sbleft0.h"
#include "a_sbldamege0.h"
#include "a_sbrdamege0.h"

#include "a_sbdown0.h"
#include "a_sbdown1.h"
#include "a_sbdown2.h"

#include "a_sbwait0.h"
#include "a_sbwait1.h"

#include "a_sbsa0.h"
#include "a_sbsa1.h"
#include "a_sbsa2.h"
#include "a_sbsb0.h"
#include "a_sbss0.h"
#include "a_sbss1.h"
#include "a_sbss2.h"

#include "a_sboard_snowboard.h"


PL_ACTION AmySnowboard[] =
{
	{ &action_a_sbfront0, 78, MD_MTN_LOOP, 72, 0.0625f, 1.0f }, //72
	{ &action_a_sblstop0, 78, MD_MTN_STOP, 73, 0.12f, 1.0f }, //a_sblstop0 - 73
	{ &action_a_sbrstop0, 78, MD_MTN_STOP, 74, 0.12f, 1.0f }, //a_sbrstop0 - 74
	{ &action_a_sbjump1, 78, MD_MTN_NEXT, 81, 0.0625f, 1.0f }, //a_sbjump1 - 75
	{ &action_a_sbjump0, 78, MD_MTN_LOOP, 75, 0.25f, 1.0f }, //a_sbjump0 - 76
	{ &action_a_sbright0, 78, MD_MTN_MANU, 77, 1.0f, 1.0f }, //s_sbright0 - 77
	{ &action_a_sbleft0, 78, MD_MTN_MANU, 78, 1.0f, 1.0f }, //s_sbleft0 - 78
	{ &action_a_sbldamege0, 78, MD_MTN_NEXT, 84, 1.0f, 1.0f }, //s_sbldamege0 - 79
	{ &action_a_sbrdamege0, 78, MD_MTN_NEXT, 84, 1.0f, 1.0f }, //s_sbrdamege0 - 80
	{ &action_a_sbdown0, 78, MD_MTN_NEXT, 82, 0.5f, 1.0f }, //s_sbdown0 - 81 
	{ &action_a_sbdown1, 78, MD_MTN_LOOP, 82, 0.50f, 0.30f }, //s_sbdown1 - 82
	{ &action_a_sbdown2, 78, MD_MTN_NEXT, 72, 0.5f, 1.0f }, //s_sbdown2 - 83
	{ &action_a_sbwait0, 78, MD_MTN_LOOP, 84, 0.0625f, 1.0f }, //s_sbwait0 - 84
	{ &action_a_sbwait1, 78, MD_MTN_NEXT, 72, 0.0625f, 1.0f }, //s_sbwait1 - 85
	{ &action_a_sbsa0, 78, MD_MTN_NEXT, 72, 0.0625f, 0.85f }, //s_sbsa0 - 86
	{ &action_a_sbsa1, 78, MD_MTN_NEXT, 72, 0.0625f, 0.85f }, //s_sbsa1 - 87
	{ &action_a_sbss2, 78, MD_MTN_NEXT, 72, 0.0625f, 0.85f }, //s_sbss2 - 88
	{ &action_a_sbss2, 78, MD_MTN_TXEN, 72, 0.0625f, 0.85f }, //s_sbss2 - 89
	{ &action_a_sbsa2, 78, MD_MTN_NEXT, 91, 1.0f, 1.0f }, //s_sbsa2.nam - 90
	{ &action_a_sbss0, 78, MD_MTN_NEXT, 72, 1.0f, 1.0f }, //s_sbss0 - 91
	{ &action_a_sbss1, 78, MD_MTN_NEXT, 72, 0.25f, 1.0f }, //s_sbss1 - 92
	{ &action_a_sbsb0, 78, MD_MTN_NEXT, 82, 1.0f, 1.0f }, //s_sbsb0 - 93
	{ &action_a_sbfront1, 78, MD_MTN_LOOP, 94, 0.25f, 1.50f } //s_sbfront1 - 94
};

NJS_ACTION* a_snowboard_action[23];

PL_ACTION originalActions[23]
{
	{ NULL, 0, 0, 0, 0, 0 }
};

player_parameter originalAmyParams;
player_parameter AmySnowboardingParams = { 60, 1.75f, 16.0f, 16.0f, 1.525f, 0.55f, 1.48f, 3.0f, 0.23f, 
0.46f, 1.39f, 2.3f, 3.7f, 5.09f, 0.0445f, 0.0475f, 0.031f, -0.06f, -0.18f, -0.17f, -0.028f, -0.008f, 
-0.01f, -0.4f, -0.1f, -0.6f, -0.31f, 0.3f, 3.5f, 10.0f, 0.06f, 7.0f, 5.0f };

enum
{
	MD_AMY_S8A2_WAIT = 0x40,
	MD_AMY_S8A2_SLIP,
	MD_AMY_S8A2_LROT,
	MD_AMY_S8A2_RROT,
	MD_AMY_S8A2_JUMP,
	MD_AMY_S8A2_CLMB,
	MD_AMY_S8A2_FLY_,
	MD_AMY_S8A3_SLID,
	MD_AMY_S8A3_FSLD,
	MD_AMY_S8A3_BRAK,
	MD_AMY_S8A3_FALL,
	MD_AMY_S8A3_JUMP,
	MD_AMY_S8A3_SPEC,
	MD_AMY_S8A3_CRSH,
};

static NJS_TEXNAME textures_a_sboard_snowboard[] = { {(void*)"atx_board0",0,0} };

NJS_TEXLIST texlist_a_sboard_snowboard = { textures_a_sboard_snowboard, 1};

UsercallFunc(int, AmyCheckInput, (playerwk* pwp, motionwk2* mwp, taskwk* twp), (pwp, mwp, twp), 0x00487810, rEAX, rECX, rEDI, rESI);

const int listStart = 72;
const int listSize = 23;

bool checky = false;

int lastreq = 0;
int nextreq = 0;

void __cdecl init_amy_snowboard_action()
{
	a_snowboard_action[1] = SONIC_ACTIONS[77];
	a_snowboard_action[2] = SONIC_ACTIONS[78];
	a_snowboard_action[3] = SONIC_ACTIONS[80];
	a_snowboard_action[4] = SONIC_ACTIONS[79];
	a_snowboard_action[5] = SONIC_ACTIONS[73];
	a_snowboard_action[6] = SONIC_ACTIONS[74];
	a_snowboard_action[7] = SONIC_ACTIONS[75];
	a_snowboard_action[8] = SONIC_ACTIONS[76];
	a_snowboard_action[9] = SONIC_ACTIONS[81];
	a_snowboard_action[10] = SONIC_ACTIONS[82];
	a_snowboard_action[11] = 0;
	a_snowboard_action[12] = 0;
	a_snowboard_action[13] = 0;
	a_snowboard_action[14] = SONIC_ACTIONS[83];
	a_snowboard_action[15] = SONIC_ACTIONS[84];
	a_snowboard_action[16] = SONIC_ACTIONS[112];
	a_snowboard_action[17] = SONIC_ACTIONS[112];
	a_snowboard_action[18] = SONIC_ACTIONS[85];
	a_snowboard_action[19] = SONIC_ACTIONS[110];
	a_snowboard_action[20] = SONIC_ACTIONS[111];
	a_snowboard_action[21] = SONIC_ACTIONS[86];
	a_snowboard_action[22] = 0;

	for (int i = 0; i < 23; i++)
	{
		if(a_snowboard_action[i])
			a_snowboard_action[i]->object = &a_sboard_snowboard;
	}
}

void DisplayAmySnowBoard(task * tp)
{
	taskwk* twp = tp->twp;
	playerwk * ppwp = playerpwp[twp->counter.b[0]];

	if (dsCheckViewV(&twp->pos, 12.0f))
	{
		njSetTexture((NJS_TEXLIST*)twp->value.l);
		njPushMatrix(0);

		if (ppwp->mj.action < 72 || ppwp->mj.action > 94)
		{
			njTranslateV(0, &twp->pos);

			ROTATEZ(0, twp->ang.z);
			ROTATEX(0, twp->ang.x);
			ROTATEY(0, twp->ang.y);
			njTranslate(0, 0.0, -5.2199998, 0.0);
			njEasyDrawModel(*(NJS_MODEL**)(twp->timer.l + 4));
			njPopMatrix(1);
		}
		else
		{ 
	
			NJS_ACTION * action = a_snowboard_action[ppwp->mj.action - 72];

			njTranslateV(0, &twp->pos);
			ROTATEZ(0, twp->ang.z);
			ROTATEX(0, twp->ang.x);
			ROTATEY(0, twp->ang.y);

			
			if (action)
			{
				DebugFontSize = 64.0f;
				njPrint(NJM_LOCATION(32, 32), "Board Action: %i", ppwp->mj.action - 72);

				NJS_MOTION * motion = action->motion;
				if (twp->flag & 2)
					njTranslate(0, 0.0, -5.2199998, 0.0);

				njEasyDrawMotion(&a_sboard_snowboard, motion, ppwp->mj.nframe);
				njPopMatrix(1);
			}
			else
			{
				if (twp->flag & 2)
					njTranslate(0, 0.0, -5.2199998, 0.0);
				njEasyDrawObject((NJS_OBJECT*)twp->timer.l);
				njPopMatrix(1);
			}
		}
	}
}

void ExecuteAmySnowBoard(task* tp)
{
	taskwk* twp = tp->twp;
	motionwk * mwp = tp->mwp;

	taskwk* ptwp = playertwp[twp->counter.b[0]];
	motionwk2 * pmwp = playermwp[twp->counter.b[0]];

	Uint16 act = playerpwp[twp->counter.b[0]]->mj.action;

	if (act < 72 || act > 94)
	{
		if ((twp->flag & 8) == 0)
		{
			twp->pos.y = twp->pos.y - 5.2199998;
			//ObjectMovableSRegularExecute(a1);
			twp->pos.y = twp->pos.y - -5.2199998;
		}
		DisplayAmySnowBoard(tp);
	}
	else
	{
		twp->pos = ptwp->cwp->info->center;
		twp->pos.y += 0.2f;
		twp->ang.x = ptwp->ang.x;
		twp->ang.y = 0x8000 - ptwp->ang.y;
		twp->ang.z = ptwp->ang.z;
		mwp->spd = pmwp->spd;
		twp->flag &= 0xF7u;
		DisplayAmySnowBoard(tp);
	}

	//DisplayAmySnowBoard(tp);
}

void KilledAmySnowBoard(task* tp)
{

}

void AmySnowBoard(task* tp)
{

	taskwk* twp = tp->twp;

	twp->value.l = (int)&texlist_a_sboard_snowboard;
	twp->timer.l = (int)SONIC_OBJECTS[71];
	tp->mwp->weight = 0.02;
	//NeonuLoadTexture(&texlist_a_sboard_snowboard);
	LoadPVM("ATX_BOARD0", &texlist_a_sboard_snowboard);
	tp->dest = KilledAmySnowBoard;
	tp->exec = ExecuteAmySnowBoard;
	tp->disp = DisplayAmySnowBoard;

}

void replacePhysics(int pnum)
{
	copyPlayerParameter(&playerwk_default[Characters_Amy], &originalAmyParams);
	
	copyPlayerParameter(&AmySnowboardingParams, &playerwk_default[Characters_Amy]);
	copyPlayerParameter(&AmySnowboardingParams, &playerpwp[pnum]->p);
}

void restorePhysics(int pnum)
{
	copyPlayerParameter(&originalAmyParams, &playerwk_default[Characters_Amy]);
	copyPlayerParameter(&originalAmyParams, &playerpwp[pnum]->p);
}

void replaceActions()
{

	for (int i = 0; i < listSize; i++)
	{
		copyAction(&amy_action[listStart + i], &originalActions[i]);
	}

	for (int i = 0; i < listSize; i++)
	{
		copyAction(&AmySnowboard[i], &amy_action[listStart + i]);
		AmySnowboard[i].actptr->object = amy_action[0].actptr->object;

	}

	
}

void restoreActions()
{
	for (int i = 0; i < listSize; i++)
	{
		copyAction(&originalActions[i], &amy_action[listStart + i]);
	}

	originalActions[0].actptr = NULL;
}

int AmyCheckInput_r(playerwk* pwp, motionwk2* mwp, taskwk* twp)
{

	switch (twp->smode)
	{

	case PL_OP_SNOWBOARDING:
		PrintDebug("\n\n LETS FUCKIN GOOOOOO \n\n");
		twp->mode = MD_AMY_S8A3_FALL;
		pwp->mj.reqaction = 75;

		twp->flag = twp->flag & 0xFAFF;
		twp->flag = twp->flag & 0xDFFF;


		CreateElementalTask(3u, 2, AmySnowBoard);

		if (originalActions[0].actptr == NULL)
		{
			replaceActions();
			replacePhysics(0);
		}

		return TRUE;
	}

	if (twp->mode > MD_AMY_S8A3_SLID && twp->mode > MD_AMY_S8A3_CRSH)
	{
		if (amy_action[listStart].actptr != originalActions[0].actptr)
		{
			restoreActions();
			restorePhysics(0);
		}
	}


	return AmyCheckInput.Original(pwp, mwp, twp);
}




void InitSnowboarding()
{
	AmyCheckInput.Hook(AmyCheckInput_r);
	init_amy_snowboard_action();
}

Sint32 AmyCheckBeInTheAir(taskwk* twp, playerwk* pwp)
{

	if ((twp->flag & PL_FLAG_FLOOR) != 0)
		return FALSE;

	if ((twp->flag & PL_FLAG_BALL))
	{
		twp->mode = MD_AMY_JUMP;
		return TRUE;
	}

	if ((twp->flag & PL_FLAG_HOLD))
	{

		if ((PCheckHoldObject(twp) & 0x200) != 0)
		{
			twp->mode = MD_AMY_HFLL;
			pwp->mj.reqaction = 65;
			return 1;
		}
		//AmyThrowTheObjectOut(twp, pwp);

	}

	twp->mode = MD_AMY_FALL;
	pwp->mj.reqaction = 18;
	return TRUE;
}


int AmyCheckInputInSnowBoard(taskwk* twp, motionwk2* mwp, playerwk* pwp)
{

	if ((twp->flag & 0x1000) == 0)
		return FALSE;

	if (twp->smode == PL_OP_LETITGO)
	{
		twp->mode = 12;
		pwp->mj.reqaction = 18;
		return TRUE;
	}

	if (twp->smode != PL_OP_PLACEWITHKIME)
		return FALSE;

	//AmyThrowTheObjectOut(twp, (motionwk2*)pwp, pwp);
	twp->mode = 20;
	pwp->mj.reqaction = 75;
	twp->ang.z = 0;
	twp->ang.x = 0;
	PClearSpeed(mwp, pwp);
	twp->flag &= 0xDFFFu;

	return TRUE;
}

void AmySnowboardingCheckMode(taskwk * twp, motionwk2 * mwp, playerwk * pwp)
{
	DebugFontSize = 40.0f;
	njPrint(NJM_LOCATION(30, 30), "AMY REQACTION: %i", pwp->mj.reqaction);
	njPrint(NJM_LOCATION(30, 31), "AMY SPEED X: %f", pwp->spd.x);
	

		if (nextreq != pwp->mj.reqaction)
		{
			lastreq = nextreq;
			nextreq = pwp->mj.reqaction;
			PrintDebug("\n REQACTION AFTER %i: %i", lastreq, nextreq);

		}

	NJS_POINT3 vs, vd, pos;

	switch (twp->mode)
	{
	case MD_AMY_S8A3_SLID:

		if (AmyCheckInputInSnowBoard(twp, mwp, pwp))
			return;

		if (AmyCheckBeInTheAir(twp, pwp))
		{
			twp->mode = MD_AMY_S8A3_FALL;
			pwp->mj.reqaction = 81;
			return;
		}

		if ((perG[twp->counter.b[0]].release & jump_button) != 0)
		{
			twp->mode = MD_AMY_S8A3_JUMP;

			pwp->spd.y = pwp->p.jmp_y_spd;
			if (pwp->spd.x < pwp->p.rush_speed)
				pwp->spd.x = pwp->p.jog_speed + pwp->spd.x;

			if (pwp->ttp)
			{
				if (pwp->ttp->fwp)
				{
					SetAccelerationP(twp->counter.b[0],
						pwp->ttp->fwp->pos_spd.x,
						pwp->ttp->fwp->pos_spd.y,
						pwp->ttp->fwp->pos_spd.z);
				}
				
				if (pwp->ttp->twp->id == 9)
				{
					twp->mode = MD_AMY_S8A3_SPEC;
					dsPlay_oneshot(230, 0, 0, 0);


					vs.x = 0.0;
					vs.y = 1.7;
					vs.z = 3.0;
					vd.x = 0.0f;
					vd.y = 0.0f;
					vd.z = 0.0f;
					pos.x = 0.0f;
					pos.y = 0.0f;
					pos.z = 0.0f;

					njPushMatrix(_nj_unit_matrix_);
					ROTATEX(0, pwp->ttp->twp->ang.x);
					ROTATEY(0, pwp->ttp->twp->ang.y);
					ROTATEZ(0, pwp->ttp->twp->ang.z);

					njRotateY(0, 0x8000);
					njCalcVector(0, &vs, &pos);
					vs.z = 0.0;
					vs.x = 0.0;
					vs.y = 1.0;
					njCalcVector(0, &vs, &vd);

					SetRotationP(
						twp->counter.b[0],
						(asin(vd.z) * (65536.0f * 0.1591549762f)),
						(atan2(pos.x, pos.z) * (65536.0f * 0.15915497620f)),
						(asin(vd.x) * (65536.0f * -0.15915497620f)));
					njPopMatrix(1u);
					SetAccelerationP(twp->counter.b[0], pos.x, pos.y, pos.z);

					if (pwp->spd.x <= 4.14f)
					{
						if (pwp->spd.x <= 2.76f)
						{
							if (pwp->spd.x <= 1.84f)
							{
								twp->mode = MD_AMY_S8A3_JUMP;
								pwp->mj.reqaction = 76;
								//AddScore(10);
							}
							else
							{
								pwp->mj.reqaction = 93;
								//AddScore(30);
							}
						}
						else
						{
							pwp->mj.reqaction = 90;
							//AddScore(50);
						}
					}
					else
					{

						int randResult = rand();

						if (randResult * 0.000030517578 <= 0.66000003)
						{
							randResult = rand();
							pwp->mj.reqaction = 88;
							dsPlay_oneshot(SE_AV_CLEAR, 0, 0, 0);
						}
						else
						{
							pwp->mj.reqaction = 87;
							if (!gu8flgPlayingMetalSonic)
							{
								dsPlay_oneshot(SE_AV_CARTJUMP, 0, 0, 0);
							}
						}

						randResult = rand();

						if (randResult * 0.000030517578 < 0.5)
						{
							CameraSetEventCameraFunc(CameraSnowboardSpecial1, 0, 2);
						}
						else
						{
							CameraSetEventCameraFunc(CameraSnowboardSpecial2, 0, 2);
						}

						cameraControlWork.xspd = 0.0;
						AddScore(100);
					}
					return;
				}
			}



			pwp->mj.reqaction = 76;
			twp->flag &= 0xFFFDu;
			pwp->jumptimer = 0;
			dsPlay_oneshot(17, 0, 0, 0); //Also play Amy jump noise here?
		}
		else if (PCheckBreak(twp) && pwp->spd.x >= (double)pwp->p.jog_speed)
		{
			Angle ang;
			PCheckPower(twp, &ang, 0);

			if (SubAngle(twp->ang.y, ang) <= 0)
				pwp->mj.reqaction = 74;
			else
				pwp->mj.reqaction = 73;
		}
		else
		{
			//twp->mode = MD_AMY_S8A3_SLID;
			//pwp->mj.reqaction = 72;
			//SonicSBoardSlideSECall(twp, (motionwk2*)pwp, v201);
		}

		return;
	case MD_AMY_S8A3_BRAK:
		return;
	case MD_AMY_S8A3_FALL:

		if (!AmyCheckInputInSnowBoard(twp, mwp, pwp) && (twp->flag & PL_FLAG_FLOOR) != 0)
		{
			if (!twp->counter.b[0])
			{
				if (gu8flgPlayingMetalSonic)
				{
					dsPlay_oneshot(778, 0, 0, 0);
				}
				else
				{
					dsPlay_oneshot(33, 0, 0, 0);
				}
			}

			twp->mode = MD_AMY_S8A3_SLID;

			if (pwp->spd.y > -3.0)
			{
	
				pwp->mj.reqaction = 72;
				if (pwp->spd.x <= 0.30000001)
				{
					pwp->spd.x = 1.0;
				}
			}
			else
			{
				pwp->mj.reqaction = 83;
			}
			twp->ang.x = mwp->ang_aim.x;
			twp->ang.z = mwp->ang_aim.z;
			//MilesSBoardSlideSECall(v113, twp);
		}

		return;
	case MD_AMY_S8A3_JUMP:
		//dsPlay_oneshot(33, 0, 0, 0);
		if (AmyCheckInputInSnowBoard(twp, mwp, pwp) || (twp->flag & PL_FLAG_FLOOR) == 0)
			return;

		twp->mode = MD_AMY_S8A3_SLID;

		if (pwp->spd.y > -3.0)
		{
			pwp->mj.reqaction = 72;
			if (pwp->spd.x <= 0.30000001)
			{
				pwp->spd.x = 1.0;
			}
		}
		else
		{
			pwp->mj.reqaction = 83;
		}

		twp->ang.x = mwp->ang_aim.x;
		twp->ang.z = mwp->ang_aim.z;
		//MilesSBoardSlideSECall(_pwp, twp);
		return;

	case MD_AMY_S8A3_SPEC:

		if (AmyCheckInputInSnowBoard(twp, mwp, pwp) || (twp->flag & PL_FLAG_FLOOR) == 0)
			return;

		twp->mode = MD_AMY_S8A3_SLID;

		if (pwp->spd.y > -3.0)
		{
			pwp->mj.reqaction = 72;
		}
		else
		{
			pwp->mj.reqaction = 83;
		}

		twp->ang.x = mwp->ang_aim.x;
		twp->ang.z = mwp->ang_aim.z;
		//MilesSBoardSlideSECall(_pwp, twp);
		return;

	case MD_AMY_S8A3_CRSH:

		if (!AmyCheckInputInSnowBoard(twp, mwp, pwp))
		{

			if (pwp->mj.reqaction != 79 && pwp->mj.reqaction != 80)
			{
				twp->mode = MD_AMY_S8A3_SLID;
				pwp->mj.reqaction = 72;
				//MilesSBoardSlideSECall(v100, twp);
			}
		}
		return;
	}

}

void AmySnowboardForceAnimation(playerwk* pwp, motionwk2 * mwp, float force)
{
	if (force >= pwp->mj.nframe)
	{
		if (force <= pwp->mj.nframe)
			return;

		if (force - pwp->mj.nframe > 1.0f)
		{
			if (fabs(mwp->force) > 0.5f)
			{
				pwp->mj.nframe = (float)fabs(mwp->force) + pwp->mj.nframe;
				return;
			}
			force = pwp->mj.nframe + 0.5f;
		}
	}
	else
	{
		if (force == 0.0)
		{
			pwp->mj.nframe -= 2.0f;
			if (pwp->mj.nframe < 0.0f)
			{
				pwp->mj.nframe = 0.0;
			}
			return;
		}

		if (pwp->mj.nframe - force > 1.0f)
		{
			if (fabs(mwp->force) <= 0.5f)
			{
				pwp->mj.nframe = pwp->mj.nframe - 0.5f;
			}
			else
			{
				pwp->mj.nframe = pwp->mj.nframe - (float)fabs(mwp->force);
			}
			return;
		}

	}
	pwp->mj.nframe = force;
	return;
}

void AmyChangeSnowBoardMotion(taskwk * twp, motionwk2 * mwp, playerwk * pwp)
{
	Uint16 act = pwp->mj.reqaction;
	float force = 0.0f;

	if (act != 72 && act != 94 && act != 78 && act != 77 && act != 84 && act != 85)
		return;

	if (PCheckPower(twp, 0, 0))
	{
		if (mwp->force < 0.0)
		{
			if (act == 72 || act == 94 || act == 84 || act == 85)
			{
				pwp->mj.reqaction = 78;
				pwp->mj.nframe = 0.0;
				force = 4.0f - mwp->force * 12.0f;
				AmySnowboardForceAnimation(pwp, mwp, force);
				return;
			}

			if (act != 77)
			{

				force = 4.0f - mwp->force * 12.0f;
				AmySnowboardForceAnimation(pwp, mwp, force);
				return;
			}
			if (pwp->mj.nframe == 0.0f)
			{
				pwp->mj.reqaction = 78;
				force = 4.0f - mwp->force * 12.0f;
				AmySnowboardForceAnimation(pwp, mwp, force);
				return;
			}
			force = 0.0f;
			AmySnowboardForceAnimation(pwp, mwp, force);
			return;
		}


		if (mwp->force <= 0.0)
		{
			if (act == 72 || act == 94 || act == 84 || act == 85)
			{
				if ((perG[twp->counter.b[0]].on & (jump_button | action_button)) != 0)
				{
					pwp->mj.reqaction = 94;
				}
			}
			else
			{
				pwp->mj.nframe -= 1.0f;
				if (pwp->mj.nframe <= 0.0)
				{
					pwp->mj.nframe = 0.0;
					pwp->mj.reqaction = ((jump_button | action_button) & perG[twp->counter.b[0]].on) != 0 ? 94 : 72;
				}
			}
			force = pwp->mj.nframe;
		}
		else
		{
			if (act != 72 && act != 94 && act != 84 && act != 85)
			{
				if (act == 78)
				{
					if (pwp->mj.nframe != 0.0)
					{
						force = 0.0;
						AmySnowboardForceAnimation(pwp, mwp, force);
						return;
					}
					pwp->mj.reqaction = 77;
				}
				force = mwp->force * 12.0f + 4.0f;
				AmySnowboardForceAnimation(pwp, mwp, force);
				return;
			}
			pwp->mj.reqaction = 77;
			pwp->mj.nframe = 0.0f;
			force = mwp->force * 12.0f + 4.0f;
		}

		AmySnowboardForceAnimation(pwp, mwp, force);
		return;
	}

	if (act == 78 || act == 77)
	{
 
		pwp->mj.nframe -= 1.0f;
		if (pwp->mj.nframe <= 0.0f)
		{
			pwp->mj.reqaction = ((jump_button | action_button) & perG[twp->counter.b[0]].on) != 0 ? 94 : 72;
			pwp->mj.nframe = 0.0;
		}
	}
	else if ((perG[twp->counter.b[0]].on & (jump_button | action_button)) != 0)
	{
		pwp->mj.reqaction = 94;
	}
	else if (act == 72 && pwp->spd.x < 1.38f)
	{
		pwp->mj.reqaction = 84;
	}
	else if (act == 84 && pwp->spd.x < 1.38f)
	{
		pwp->mj.reqaction = 85;
	}

}

void AmySnowboardingExec(task * tp, motionwk2 * mwp, playerwk * pwp)
{

	if (ChkPause())
		return;

	taskwk* twp = tp->twp;

	AmySnowboardingCheckMode(twp, mwp, pwp);

	switch (twp->mode)
	{

	case MD_AMY_S8A3_SLID:
		PGetAccelerationSnowBoard(twp, mwp, pwp, 5.98);
		PGetSpeed(twp, mwp, pwp);
	
		if (PSetPosition(twp, mwp, pwp) == PSG_TYPE_CRASH)
		{
			dsPlay_oneshot(1222, 0, 0, 0);
			twp->mode = MD_AMY_S8A3_CRSH;

			if(VectorAngle(&mwp->spd, &pwp->wall_normal, &pwp->cstsp->tnorm) <= 0x8000)
				pwp->mj.reqaction = 79; // Sonic's 109

			PSetCrashEffect(twp);

			if (((ssStageNumber << 8) | ssActNumber) == 2050)
			{
				dsPlay_oneshot(235, 0, 0, 0);
				//PSetSnowEffect(twp, mwp, pwp);
				//goto LABEL_230;
			}
		}
		else
		{
			PResetPosition(twp, mwp, pwp);
			AmyChangeSnowBoardMotion(twp, mwp, pwp); //Implement later
		}
		PSetSnowEffect(twp, mwp, pwp);
		break;
	case MD_AMY_S8A3_CRSH:
		//PGetBreakSnowBoard(twp, mwp, pwp);
		PGetSpeed(twp, mwp, pwp);
		PSetPosition(twp, mwp, pwp);
		PResetPosition(twp, mwp, pwp);
		PSetSnowEffect(twp, mwp, pwp);
		break;
	case MD_AMY_S8A3_FALL:
	case MD_AMY_S8A3_JUMP:
		PResetAngle(twp, mwp, pwp);
		PGetAccelerationSnowBoardAir(twp, mwp, pwp);
		PGetSpeed(twp, mwp, pwp);
		PSetPosition(twp, mwp, pwp);
		PResetPosition(twp, mwp, pwp);
		break;
	case MD_AMY_S8A3_SPEC:
		PResetAngle(twp, mwp, pwp);
		PGetAccelerationSnowBoardAirSpecial(twp, mwp, pwp);
		PGetSpeed(twp, mwp, pwp);

		if (PSetPosition(twp, mwp, pwp))
		{
			pwp->mj.reqaction = 82;
		}

		PResetPosition(twp, mwp, pwp);
		break;
	}
}