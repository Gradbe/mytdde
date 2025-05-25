#include "LightController.h"
#include "LightScheduler.h"

#include <stdlib.h>
#include <stdbool.h>

typedef struct{
	int id;
	int minuteOfDay;
	int event;
	Day day;
}ScheduledLightEvent;

static ScheduledLightEvent scheduledEvent;

static void scheduleEvent(int id, Day day, int minuteOfDay, int event){
	scheduledEvent.id = id;
	scheduledEvent.day = day;
	scheduledEvent.minuteOfDay = minuteOfDay;
	scheduledEvent.event = event;
}

static bool DoesLightRespondToday(Time* time, Day reactionDay){
	int today = time->dayOfWeek; 
	if (reactionDay == EVERYDAY) 
		return true;
	if (reactionDay == today)
		return true;
	if (reactionDay == WEEKEND && (today == SATURDAY || today==SUNDAY))
		return true;
	if (reactionDay == WEEKDAY && today < SATURDAY && today > SUNDAY)
		return true;
	return false;
}

static void operateLight(ScheduledLightEvent* event){
	if (event->event == LIGHT_ON)
		LightController_On(event->id);
	else if (event->event == LIGHT_OFF)
		LightController_Off(event->id);
}

static void processEventDueNow(Time* time, ScheduledLightEvent* lightEvent){
	if(lightEvent->id == UNUSED)
		return;
	if(!DoesLightRespondToday(time, lightEvent->day))
		return;
	if (time->minuteOfDay != lightEvent->minuteOfDay)
		return;
	operateLight(lightEvent);
}


void LightScheduler_Create(void){
	scheduledEvent.id = UNUSED; 
	TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
}

void LightScheduler_Destroy(){
}

void LightScheduler_WakeUp(){
	Time time;
	TimeService_GetTime(&time);
	processEventDueNow(&time, &scheduledEvent);
}

void LightScheduler_ScheduleTurnOn(int id, Day d, int minute){
	scheduleEvent(id, d, minute, LIGHT_ON);
}

void LightScheduler_ScheduleTurnOff(int id, Day d, int minute){
	scheduleEvent(id, d, minute, LIGHT_OFF);
}


