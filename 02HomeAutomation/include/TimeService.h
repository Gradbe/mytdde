#ifndef TIME_SERVICE_H
#define TIME_SERVICE_H

typedef struct{
	int minuteOfDay;
	int dayOfWeek;
}Time;

typedef enum{
	EVERYDAY = 10, 
	SUNDAY = 1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
}Day;

#endif

