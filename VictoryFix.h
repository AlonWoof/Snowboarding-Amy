#pragma once

#ifndef _VICTORYFIX_H_
#define _VICTORYFIX_H_
#include <FunctionHook.h>

int SetAmyWinPose();
extern FunctionHook<void> SetFinishAction_h;
void SetFinishAction_r();
extern bool VictoryFixEnabled;

#endif // !_VICTORYFIX_H_
