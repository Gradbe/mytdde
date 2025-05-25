#ifndef FAKE_TIME_H
#define FAKE_TIME_H
#include "TimeService.h"
#include "LightScheduler.h"
	
enum {
	TIME_UNKNOWN = -1
};

void FakeTimeService_SetMinute(int minute);
void FakeTimeService_SetDay(Day day);
int FakeTimeService_GetAlarmPeriod();
WakeupCallback FakeTimeService_GetAlarmCallback(void);
#endif
