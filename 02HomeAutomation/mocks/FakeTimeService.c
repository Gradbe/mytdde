#include "FakeTimeService.h"
#include "stddef.h"

static Time fakeTime;
static WakeupCallback callback;
static int period;

void TimeService_Create(){
	fakeTime.minuteOfDay = TIME_UNKNOWN;
	fakeTime.dayOfWeek = TIME_UNKNOWN;
	callback = NULL;
	period = -1;
}

void TimeService_GetTime(Time* time){
	*time = fakeTime;
}

void FakeTimeService_SetMinute(int minute){
	fakeTime.minuteOfDay = minute;
}

void FakeTimeService_SetDay(Day day){
	fakeTime.dayOfWeek = day;
}

void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeupCallback cb){
	callback = cb;
	period = seconds;
}
void TimeService_CancelPeriodicAlarmInSecond(int seconds, WakeupCallback cb){
	if (cb == callback && period == seconds){
		callback = NULL;
		period = 0;
	}
}

WakeupCallback FakeTimeService_GetAlarmCallback(void){
	return callback;
}

int FakeTimeService_GetAlarmPeriod(){
	return period;
}

