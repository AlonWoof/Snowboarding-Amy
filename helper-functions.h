#pragma once


#include <SADXModLoader.h>

float lerp(float a, float b, float f);
float clamp(float tg, float min, float max);
NJS_VECTOR lerpVector(NJS_VECTOR a, NJS_VECTOR b, float f);
NJS_VECTOR getPlayerSidePos(taskwk* twp, double dist, int angle_offset = 0);
float getVectorMagnitude(NJS_VECTOR vec);
float angleToFloat(Angle angle);
Angle floatToAngle(float degrees);
void copyAction(PL_ACTION* original, PL_ACTION* copy);
void copyPlayerParameter(player_parameter* original, player_parameter* copy);
void writeParamsToFile();
void writeMixedParan(int plno_a, int plno_b);
void writeActionData();

#define SHORT_ANG(ang) ((ang) & 0xFFFF)
#define ROTATEX(m, ang) if (ang != 0) njRotateX(m, SHORT_ANG(ang));
#define ROTATEY(m, ang) if (ang != 0) njRotateY(m, SHORT_ANG(ang));
#define ROTATEZ(m, ang) if (ang != 0) njRotateZ(m, SHORT_ANG(ang));

#define PNUM(twp) twp->counter.b[0]
#define PLNO(twp) twp->counter.b[1]
