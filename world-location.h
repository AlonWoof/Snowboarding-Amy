#pragma once

#include <SADXModLoader.h>

typedef struct
{
	STAGE levelID;
	int act;
	NJS_VECTOR position;
	float range;

} WorldLocation;

bool isInLocation(WorldLocation* wl);
