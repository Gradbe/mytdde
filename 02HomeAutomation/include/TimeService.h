#ifndef TIME_SERVICE_H
#define TIME_SERVICE_H

typedef struct{
	int minuteOfDay;
	int dayOfWeek;
}Time;

typedef void(*WakeupCallback)(void);

void TimeService_GetTime(Time*);
void TimeService_Create();
void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeupCallback);
void TimeService_CancelPeriodicAlarmInSecond(int seconds, WakeupCallback cb);

#endif

