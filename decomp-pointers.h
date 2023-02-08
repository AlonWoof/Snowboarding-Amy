#pragma once

#include <SADXModLoader.h>
#include "decomp-structs.h"



TaskFunc(Miles2PControl, 0x0047E8F0);
TaskFunc(NpcMilesControlDestructor, 0x0047DB10);

TaskFunc(CalcTotalScore,0x0042BEE0);

FunctionPointer(int, NpcGetAngleToTarget, (NJS_POINT3* ps, NJS_POINT3* pd, float* dist, float* distxz), 0x47DD90);
FunctionPointer(int, EV_CheckExec, (int num), 0x0042FB10);
FunctionPointer(void, PGetAccelerationSnowBoard, (taskwk* twp, motionwk2* mwp, playerwk* pwp, double Max_Speed), 0x448550);
FunctionPointer(void, PGetAccelerationSnowBoardAir, (taskwk* twp, motionwk2* mwp, playerwk* pwp), 0x448AF0);
FunctionPointer(void, PGetAccelerationSnowBoardAirSpecial, (taskwk* twp, motionwk2* mwp, playerwk* pwp), 0x448D10);
FunctionPointer(bool, PCheckPower, (taskwk* twp, Angle* angle, float* magnitude), 0x43BDC0);
FunctionPointer(int, AddScore, (int score), 0x00491530);
FunctionPointer(void, CameraSnowboardSpecial1, (_OBJ_CAMERAPARAM* pParam), 0x468EC0);
FunctionPointer(void, CameraSnowboardSpecial2, (_OBJ_CAMERAPARAM* pParam), 0x469080);
FunctionPointer(void, PSetSnowEffect, (taskwk* twp, motionwk2* mwp, playerwk* pwp), 0x440930);

FunctionPointer(void, PResetPosition, (taskwk* twp, motionwk2* mwp, playerwk* pwp), 0x43EE70);

DataArray(colaround, around_enemy_list_p0, 0x03B259C0, 657);
DataArray(colaround, around_enemy_list_p1, 0x03B242F8, 656);
DataPointer(unsigned short, ael_num0, 0x3B23288);
DataPointer(unsigned short, ael_num1, 0x3B240A8);

//FunctionPointer(void, KillHimP, (int pno), 0x00440CD0);
