
#include "pch.h"
#include <SADXModLoader.h>
#include "helper-functions.h"

#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>   
#include <sstream>

using namespace std;

template <typename T> string tostr(const T& t) {
	ostringstream os;
	os << t;
	return os.str();
}


template <typename T> string tohexstr(const T& t) {
	ostringstream os;
	os << std::hex << t;
	return os.str();
}

float lerp(float a, float b, float f)
{
	return (a * (1.0 - f)) + (b * f);
}

NJS_VECTOR lerpVector(NJS_VECTOR a, NJS_VECTOR b, float f)
{
	NJS_VECTOR ret;

	ret.x = lerp(a.x, b.x, f);
	ret.y = lerp(a.y, b.y, f);
	ret.z = lerp(a.z, b.z, f);

	return ret;
}

float clamp(float tg, float min, float max)
{
	if (tg < min)
		return min;

	if (tg > max)
		return max;

	return tg;
}


NJS_VECTOR getPlayerSidePos(taskwk* twp, double dist, int angle_offset)
{
	double sin; // fp30

	NJS_VECTOR pos;

	pos.x = 0;
	pos.y = 0;
	pos.z = 0;

	if (twp)
	{
		sin = njSin(twp->ang.y + angle_offset);
		pos.x = -(float)((float)((float)njCos(twp->ang.y + angle_offset) * (float)dist) - twp->pos.x);
		pos.y = twp->pos.y;
		pos.z = -(float)((float)((float)sin * (float)dist) - twp->pos.z);
	}

	return pos;
}



float getVectorMagnitude(NJS_VECTOR vec)
{
	// Stores the sum of squares
	  // of coordinates of a vector
	float sum = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;

	// Return the magnitude
	return sqrt(sum);
}

float angleToFloat(Angle angle)
{
	//return ((float)angle / (360.0f)) * 2;

	return (360.0f / 65535.0f) * angle;
}

Angle floatToAngle(float degrees)
{
	return (65535.0f / 360.0f) * degrees;
}

void copyAction(PL_ACTION* original, PL_ACTION* copy)
{
	copy->actptr = original->actptr;
	copy->frame = original->frame;
	copy->mtnmode = original->mtnmode;
	copy->next = original->next;
	copy->objnum = original->objnum;
	copy->racio = original->racio;
}

void copyPlayerParameter(player_parameter* original, player_parameter* copy)
{
	copy->jump2_timer = original->jump2_timer;
	copy->pos_error = original->pos_error;
	copy->lim_h_spd = original->lim_h_spd;
	copy->lim_v_spd = original->lim_v_spd;
	copy->max_x_spd = original->max_x_spd;
	copy->max_psh_spd = original->max_psh_spd;
	copy->jmp_y_spd = original->jmp_y_spd;
	copy->nocon_speed = original->nocon_speed;
	copy->slide_speed = original->slide_speed;
	copy->jog_speed = original->jog_speed;
	copy->run_speed = original->run_speed;
	copy->rush_speed = original->rush_speed;
	copy->crash_speed = original->crash_speed;
	copy->dash_speed = original->dash_speed;
	copy->jmp_addit = original->jmp_addit;
	copy->run_accel = original->run_accel;
	copy->air_accel = original->air_accel;
	copy->slow_down = original->slow_down;
	copy->run_break = original->run_break;
	copy->air_break = original->air_break;
	copy->air_resist_air = original->air_resist_air;
	copy->air_resist = original->air_resist;
	copy->air_resist_y = original->air_resist_y;
	copy->air_resist_z = original->air_resist_z;
	copy->grd_frict = original->grd_frict;
	copy->grd_frict_z = original->grd_frict_z;
	copy->lim_frict = original->lim_frict;
	copy->rat_bound = original->rat_bound;
	copy->rad = original->rad;
	copy->height = original->height;
	copy->weight = original->weight;
	copy->eyes_height = original->eyes_height;
	copy->center_height = original->center_height;
}

const string CharNames[]
{
	"SONIC",
	"EGGMAN",
	"MILES",
	"KNUCKLES",
	"TIKAL",
	"AMY",
	"GAMMA",
	"BIG"
};

void writeParam(string paramName, float param, ofstream * outfile)
{
	string str = paramName + " = " + tostr(param) + "f;\n";
	outfile->write(str.c_str(), str.size());
}

void writeParam(string paramName, int param, ofstream* outfile)
{
	string str = paramName + " = " + tostr(param) + ";\n";
	outfile->write(str.c_str(), str.size());
}

void writeParamsToFile()
{
	taskwk* twp = playertwp[0];
	playerwk* pwp = playerpwp[0];

	string path = getenv("APPDATA");

	path += "\\..\\..\\Documents\\Alonwoof Productions\\" + CharNames[PLNO(twp)] +"_PARAM_DATA.txt";

	ofstream outfile;
	outfile.open(path, ios::out | ios::binary);

	if (!outfile)
	{
		printf("\n\n  FUCK  \n\n");
		return;
	}
	
	writeParam("param_offset", (int)&pwp->p, &outfile);
	writeParam("jump2_timer", pwp->p.jump2_timer, &outfile);
	writeParam("pos_error", pwp->p.pos_error, &outfile);
	writeParam("lim_h_spd", pwp->p.lim_h_spd, &outfile);
	writeParam("lim_v_spd", pwp->p.lim_v_spd, &outfile);
	writeParam("max_x_spd", pwp->p.max_x_spd, &outfile);
	writeParam("max_psh_spd", pwp->p.max_psh_spd, &outfile);
	writeParam("jmp_y_spd", pwp->p.jmp_y_spd, &outfile);
	writeParam("nocon_speed", pwp->p.nocon_speed, &outfile);
	writeParam("slide_speed", pwp->p.slide_speed, &outfile);
	writeParam("jog_speed", pwp->p.jog_speed, &outfile);

	writeParam("run_speed", pwp->p.run_speed, &outfile);
	writeParam("rush_speed", pwp->p.rush_speed, &outfile);
	writeParam("crash_speed", pwp->p.crash_speed, &outfile);
	writeParam("dash_speed", pwp->p.dash_speed, &outfile);
	writeParam("jmp_addit", pwp->p.jmp_addit, &outfile);
	writeParam("run_accel", pwp->p.run_accel, &outfile);
	writeParam("air_accel", pwp->p.air_accel, &outfile);
	writeParam("slow_down", pwp->p.slow_down, &outfile);
	writeParam("run_break", pwp->p.run_break, &outfile);
	writeParam("air_break", pwp->p.air_break, &outfile);
	writeParam("air_resist_air", pwp->p.air_resist_air, &outfile);
	writeParam("air_resist", pwp->p.air_resist, &outfile);
	writeParam("air_resist_y", pwp->p.air_resist_y, &outfile);
	writeParam("air_resist_z", pwp->p.air_resist_z, &outfile);
	writeParam("grd_frict", pwp->p.grd_frict, &outfile);
	writeParam("grd_frict_z", pwp->p.grd_frict_z, &outfile);
	writeParam("lim_frict", pwp->p.lim_frict, &outfile);
	writeParam("rat_bound", pwp->p.rat_bound, &outfile);

	writeParam("rad", pwp->p.rad, &outfile);
	writeParam("height", pwp->p.height, &outfile);
	writeParam("weight", pwp->p.weight, &outfile);
	writeParam("eyes_height", pwp->p.eyes_height, &outfile);
	writeParam("center_height", pwp->p.center_height, &outfile);

	outfile.close();

	printf(path.c_str());
}


void writeMixedParan(int plno_a, int plno_b)
{
	//playerwk_default


	string path = getenv("APPDATA");

	path += "\\..\\..\\Documents\\Alonwoof Productions\\" + CharNames[plno_a] + "_" + CharNames[plno_b] + "_PARAM_DATA.txt";

	ofstream outfile;
	outfile.open(path, ios::out | ios::binary);

	if (!outfile)
	{
		printf("\n\n  FUCK  \n\n");
		return;
	}

	//playerwk_default[plno_a]
	writeParam("pos_error", lerp(playerwk_default[plno_a].pos_error, playerwk_default[plno_b].pos_error, 0.5f), &outfile);
	writeParam("lim_h_spd", lerp(playerwk_default[plno_a].lim_h_spd, playerwk_default[plno_b].lim_h_spd, 0.5f), &outfile);
	writeParam("lim_v_spd", lerp(playerwk_default[plno_a].lim_v_spd, playerwk_default[plno_b].lim_v_spd, 0.5f), &outfile);
	writeParam("max_x_spd", lerp(playerwk_default[plno_a].max_x_spd, playerwk_default[plno_b].max_x_spd, 0.5f), &outfile);
	writeParam("max_psh_spd", lerp(playerwk_default[plno_a].max_psh_spd, playerwk_default[plno_b].max_psh_spd, 0.5f), &outfile);
	writeParam("jmp_y_spd", lerp(playerwk_default[plno_a].jmp_y_spd, playerwk_default[plno_b].jmp_y_spd, 0.5f), &outfile);
	writeParam("nocon_speed", lerp(playerwk_default[plno_a].nocon_speed, playerwk_default[plno_b].nocon_speed, 0.5f), &outfile);
	writeParam("slide_speed", lerp(playerwk_default[plno_a].slide_speed, playerwk_default[plno_b].slide_speed, 0.5f), &outfile);
	writeParam("jog_speed", lerp(playerwk_default[plno_a].jog_speed, playerwk_default[plno_b].jog_speed, 0.5f), &outfile);

	writeParam("run_speed", lerp(playerwk_default[plno_a].run_speed, playerwk_default[plno_b].run_speed, 0.5f), &outfile);
	writeParam("rush_speed", lerp(playerwk_default[plno_a].rush_speed, playerwk_default[plno_b].rush_speed, 0.5f), &outfile);
	writeParam("crash_speed", lerp(playerwk_default[plno_a].crash_speed, playerwk_default[plno_b].crash_speed, 0.5f), &outfile);
	writeParam("dash_speed", lerp(playerwk_default[plno_a].dash_speed, playerwk_default[plno_b].dash_speed, 0.5f), &outfile);
	writeParam("jmp_addit", lerp(playerwk_default[plno_a].jmp_addit, playerwk_default[plno_b].jmp_addit, 0.5f), &outfile);
	writeParam("run_accel", lerp(playerwk_default[plno_a].run_accel, playerwk_default[plno_b].run_accel, 0.5f), &outfile);
	writeParam("air_accel", lerp(playerwk_default[plno_a].air_accel, playerwk_default[plno_b].air_accel, 0.5f), &outfile);
	writeParam("slow_down", lerp(playerwk_default[plno_a].slow_down, playerwk_default[plno_b].slow_down, 0.5f), &outfile);
	writeParam("run_break", lerp(playerwk_default[plno_a].run_break, playerwk_default[plno_b].run_break, 0.5f), & outfile);
	writeParam("air_break", lerp(playerwk_default[plno_a].air_break, playerwk_default[plno_b].air_break, 0.5f), & outfile);
	writeParam("air_resist_air", lerp(playerwk_default[plno_a].air_resist_air, playerwk_default[plno_b].air_resist_air, 0.5f), & outfile);
	writeParam("air_resist", lerp(playerwk_default[plno_a].air_resist, playerwk_default[plno_b].air_resist, 0.5f), & outfile);
	writeParam("air_resist_y", lerp(playerwk_default[plno_a].air_resist_y, playerwk_default[plno_b].air_resist_y, 0.5f), & outfile);
	writeParam("air_resist_z", lerp(playerwk_default[plno_a].air_resist_z, playerwk_default[plno_b].air_resist_z, 0.5f), & outfile);
	writeParam("grd_frict", lerp(playerwk_default[plno_a].grd_frict, playerwk_default[plno_b].grd_frict, 0.5f), & outfile);
	writeParam("grd_frict_z", lerp(playerwk_default[plno_a].grd_frict_z, playerwk_default[plno_b].grd_frict_z, 0.5f), & outfile);
	writeParam("lim_frict", lerp(playerwk_default[plno_a].lim_frict, playerwk_default[plno_b].lim_frict, 0.5f), & outfile);
	writeParam("rat_bound", lerp(playerwk_default[plno_a].rat_bound, playerwk_default[plno_b].rat_bound, 0.5f), & outfile);

	writeParam("rad", lerp(playerwk_default[plno_a].rad, playerwk_default[plno_b].rad, 0.5f), & outfile);
	writeParam("height", lerp(playerwk_default[plno_a].height, playerwk_default[plno_b].height, 0.5f), & outfile);
	writeParam("weight", lerp(playerwk_default[plno_a].weight, playerwk_default[plno_b].weight, 0.5f), & outfile);
	writeParam("eyes_height", lerp(playerwk_default[plno_a].eyes_height, playerwk_default[plno_b].eyes_height, 0.5f), & outfile);
	writeParam("center_height", lerp(playerwk_default[plno_a].center_height, playerwk_default[plno_b].center_height, 0.5f), & outfile);

	outfile.close();

	printf(path.c_str());
}



DataArray(NJS_ACTION*, s_snowboard_action, 0x3C561B0, 23);

void writeAction(NJS_ACTION * action, ofstream* outfile)
{
	string str = "	{ " + tohexstr(&action->motion) + ", " + tohexstr(&action->object) + " }, \n";
	outfile->write(str.c_str(), str.size());
}

void writeActionData()
{
	string path = getenv("APPDATA");

	path += "\\..\\..\\Documents\\Alonwoof Productions\\SNOWBOARD_ACTION_DATA.txt";

	ofstream outfile;
	outfile.open(path, ios::out | ios::binary);

	if (!outfile)
	{
		printf("\n\n  FUCK  \n\n");
		return;
	}

	outfile.write("NJS_ACTION * a_sboard_action[] \n{\n",35);

	for (int i = 0; i < 23; i++)
	{
		writeAction(s_snowboard_action[i], &outfile);
	}

	outfile.write(" \n}\n", 5);

	outfile.close();

	printf(path.c_str());
}