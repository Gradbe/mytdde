#ifndef LIGHT_SCHEDULER_H
#define LIGHT_SCHEDULER_H
#include "TimeService.h"

typedef enum{
	EVERYDAY = 10, WEEKDAY, WEEKEND,
	SUNDAY = 1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
}Day;

enum {
	UNUSED = -1,
	MAX_EVENTS = 128,
};

enum { LS_OK, LS_TOO_MANY_EVENTS, LS_ID_OUT_OF_BOUNDS};

void LightScheduler_Create();
void LightScheduler_Destroy();
void LightScheduler_WakeUp();
int LightScheduler_ScheduleTurnOn(int id, Day d, int minute);
int LightScheduler_ScheduleTurnOff(int id, Day d, int minute);
void LightScheduler_Randomize(int id, Day d, int minute);
void LightScheduler_ScheduleRemove(int id, Day d, int minute);


#endif

