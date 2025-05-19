#ifndef FAKE_TIME_H
#define FAKE_TIME_H
	
typedef struct{
	int minuteOfDay;
	int dayOfWeek;
}Time;

enum {
	TIME_UNKNOWN = -1
};

typedef enum {
	MONDAY = 0,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY
}day_e;

void TimeService_Create();
void TimeService_GetTime(Time* time);
void FakeTimeService_SetMinute(int minute);
void FakeTimeService_SetDay(day_e day);

#endif
