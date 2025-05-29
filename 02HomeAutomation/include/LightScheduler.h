#ifndef LIGHT_SCHEDULER_H
#define LIGHT_SCHEDULER_H
#include "TimeService.h"

typedef enum{
	EVERYDAY = 10, WEEKDAY, WEEKEND,
	SUNDAY = 1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
}Day;

enum {
	UNUSED = -1,
	MAX_EVENTS = 16
};

void LightScheduler_Create();
void LightScheduler_Destroy();
void LightScheduler_WakeUp();
void LightScheduler_ScheduleTurnOn(int id, Day d, int minute);
void LightScheduler_ScheduleTurnOff(int id, Day d, int minute);


#endif

