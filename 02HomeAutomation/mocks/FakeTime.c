#include "FakeTime.h"

static Time t;

void TimeService_Create(){
	t.minuteOfDay = TIME_UNKNOWN;
	t.dayOfWeek = TIME_UNKNOWN;
}

void TimeService_GetTime(Time* time){
	*time = t;
}

void FakeTimeService_SetMinute(int minute){
	t.minuteOfDay = minute;
}

void FakeTimeService_SetDay(day_e day){
	t.dayOfWeek = day;
}
