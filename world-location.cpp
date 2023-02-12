
#include "pch.h"
#include "world-location.h"

bool isInLocation(WorldLocation* wl)
{
	if (CurrentLevel == wl->levelID && CurrentAct == wl->act)
	{

#ifdef DEBUG
		DrawCollisionSphere(&wl->position, wl->range);
#endif // DEBUG

		if (IsPlayerInsideSphere(&wl->position, wl->range))
		{
			return true;
		}

	}

	return false;
}