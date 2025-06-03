#include "LightController.h"
#include "LightScheduler.h"
#include <stdio.h>

#include <stdlib.h>
#include <stdbool.h>

typedef struct{
	int id;
	int minuteOfDay;
	int event;
	Day day;
}ScheduledLightEvent;

static ScheduledLightEvent scheduledEvents[MAX_EVENTS];

void LightScheduler_Create(void){
	for (int i = 0; i < MAX_EVENTS; i++){
		scheduledEvents[i].id = UNUSED;
		TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
	}
}

void LightScheduler_Destroy(){
	TimeService_CancelPeriodicAlarmInSecond(60, LightScheduler_WakeUp);
}

static int scheduleEvent(int id, Day day, int minuteOfDay, int event){
	int i;
	for (i = 0; i < MAX_EVENTS; i++){
		if (scheduledEvents[i].id == UNUSED){
			scheduledEvents[i].id = id;
			scheduledEvents[i].day = day;
			scheduledEvents[i].minuteOfDay = minuteOfDay;
			scheduledEvents[i].event = event;
			return LS_OK;
		}
	}
	return LS_TOO_MANY_EVENTS;
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

void LightScheduler_WakeUp(){
	Time time;
	TimeService_GetTime(&time);
	for (int i = 0; i < MAX_EVENTS; i++){
		processEventDueNow(&time, &scheduledEvents[i]);
	}
}

int LightScheduler_ScheduleTurnOn(int id, Day d, int minute){
	return scheduleEvent(id, d, minute, LIGHT_ON);
}

int LightScheduler_ScheduleTurnOff(int id, Day d, int minute){
	return scheduleEvent(id, d, minute, LIGHT_OFF);
}

void LightScheduler_ScheduleRemove(int id, Day d, int minute){
	int i;
	for (i = 0; i < MAX_EVENTS; i++){
		if (scheduledEvents[i].id == id && 
		   scheduledEvents[i].day == d &&
		   scheduledEvents[i].minuteOfDay == minute)	
			scheduledEvents[i].id = UNUSED;
	}
/*	for (int j = 0; j < 10; j++){
		printf("Event %d, On/Off %d\n", scheduledEvents[j].id, scheduledEvents[j].event);
	}*/
}
