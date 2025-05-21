#include "LightController.h"
#include "LightScheduler.h"

#include <stdlib.h>

typedef struct{
	int id;
	int minuteOfDay;
}ScheduledLightEvent;

static ScheduledLightEvent scheduledEvent;

void LightScheduler_Create(void){
	scheduledEvent.id = UNUSED; 
}

void LightScheduler_Destroy(){
}

void LightScheduler_WakeUp(){
	Time time;
	TimeService_GetTime(&time);
	if(scheduledEvent.id == UNUSED)
		return;
	if (time.minuteOfDay != scheduledEvent.minuteOfDay)
		return;
	LightController_On(scheduledEvent.id);
}

void LightScheduler_TurnOn(int id, Day d, int minute){
}

void LightScheduler_ScheduleTurnOn(int id, Day d, int minute){
	scheduledEvent.id = id;
	scheduledEvent.minuteOfDay = minute;
}


