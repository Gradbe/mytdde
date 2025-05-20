#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H

#include "TimeService.h"


void LightScheduler_Create();
void LightScheduler_Destroy();
void LightScheduler_WakeUp();
void LightScheduler_TurnOn(int id, Day d, int minute);

#endif

