#ifndef FAKE_TIME_H
#define FAKE_TIME_H
#include "TimeService.h"
	

enum {
	TIME_UNKNOWN = -1
};

void TimeService_Create();
void TimeService_GetTime(Time* time);
void FakeTimeService_SetMinute(int minute);
void FakeTimeService_SetDay(Day day);

#endif
