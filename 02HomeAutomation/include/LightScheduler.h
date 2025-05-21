#ifndef LIGHT_SCHEDULER_H
#define LIGHT_SCHEDULER_H
#include "TimeService.h"

enum {UNUSED = -1};

void LightScheduler_Create();
void LightScheduler_Destroy();
void LightScheduler_WakeUp();
void LightScheduler_TurnOn(int id, Day d, int minute);
void LightScheduler_ScheduleTurnOn(int id, Day d, int minute);

#endif

