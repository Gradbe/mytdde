#include "CppUTest/TestHarness.h"
#include <iostream>

extern "C"
{
#include "FakeTimeService.h"
#include "LightScheduler.h"
#include "LightControllerSpy.h"
}

TEST_GROUP(LightScheduler){
	void	setup(){
		LightController_Create();
		LightScheduler_Create();
	}
	void teardown(){
		LightController_Destroy();
		LightScheduler_Destroy();
	}
	void setTimeTo(Day day, int minute){
		FakeTimeService_SetDay(day);
		FakeTimeService_SetMinute(minute);
	}
	void checkLightState(int id, int level){
		if (id == LIGHT_ID_UNKNOWN){
			LONGS_EQUAL(id, LightControllerSpy_GetLastId());
			LONGS_EQUAL(level, LightControllerSpy_GetLastState());
		}
		else
			LONGS_EQUAL(level, LightControllerSpy_GetLightState(id));
	}
		
};


TEST(LightScheduler, NoScheduleNothingHappens){
	setTimeTo(MONDAY, 100);
	LightScheduler_WakeUp();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnEveryDayNotTimeYet){
	LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
	setTimeTo(MONDAY, 1199);
	LightScheduler_WakeUp();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnEverydayItsTime){
	LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
	setTimeTo(MONDAY, 1200);

	LightScheduler_WakeUp();
	checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOffEverydayItsTime){
	LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);
	setTimeTo(MONDAY, 1200);

	LightScheduler_WakeUp();
	checkLightState(3, LIGHT_OFF);
}

TEST(LightScheduler, ScheduleTuesdayButItsMonday){
	LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
	setTimeTo(MONDAY, 1200);
	LightScheduler_WakeUp();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleTuesdayAndItsTuesday){
	LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
	setTimeTo(TUESDAY, 1200);
	LightScheduler_WakeUp();
	checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekendAndItsFriday){
	LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
	setTimeTo(FRIDAY, 1200);
	LightScheduler_WakeUp();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleWeekendAndItsSaturday){
	LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
	setTimeTo(SATURDAY, 1200);
	LightScheduler_WakeUp();
	checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekendAndItsSunday){
	LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
	setTimeTo(SUNDAY, 1200);
	LightScheduler_WakeUp();
	checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekendAndItsMonday){
	LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
	setTimeTo(MONDAY, 1200);
	LightScheduler_WakeUp();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleWeekdayAndItsSunday){
	LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
	setTimeTo(SUNDAY, 1200);
	LightScheduler_WakeUp();
	checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}


TEST(LightScheduler, ScheduleWeekdayAndItsMonday){
	LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
	setTimeTo(MONDAY, 1200);
	LightScheduler_WakeUp();
	checkLightState(3, LIGHT_ON);
}

TEST_GROUP(LightSchedulerInitAndCleanup){
};

TEST(LightSchedulerInitAndCleanup, CreateStartsOneMinuteAlarm){
	LightScheduler_Create();
	POINTERS_EQUAL((void*)LightScheduler_WakeUp,
			(void*)FakeTimeService_GetAlarmCallback());
	
	LONGS_EQUAL(60, FakeTimeService_GetAlarmPeriod());
	LightScheduler_Destroy();
}

TEST(LightSchedulerInitAndCleanup, DestroyCancelesOneMinuteAlarm){
	LightScheduler_Create();
	LightScheduler_Destroy();
	POINTERS_EQUAL(NULL,(void*)FakeTimeService_GetAlarmCallback());
}

TEST(LightScheduler, ScheduleTwoEventsAtTheSameTime){
	LightScheduler_ScheduleTurnOn(3, SUNDAY, 1200);
	LightScheduler_ScheduleTurnOn(12, SUNDAY, 1200);
	setTimeTo(SUNDAY, 1200);
	LightScheduler_WakeUp();
	checkLightState(3, LIGHT_ON);
	checkLightState(12, LIGHT_ON);
}

TEST(LightScheduler, RejectTooManyEvents){
	int i;
	for(i = 0; i < 128; i++){
		LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
	}
	LONGS_EQUAL(LS_TOO_MANY_EVENTS, LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
}

TEST(LightScheduler, RemoveRecyclesScheduleSlot){
	int i;
	for(i = 0; i < 128; i++){
		LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
	}
	LightScheduler_ScheduleRemove(6, MONDAY, 600);
	LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
}

TEST(LightScheduler, RemoveMultipeSchecduleEvent){
	LightScheduler_ScheduleTurnOn(9, MONDAY, 500);
	LightScheduler_ScheduleTurnOn(7, MONDAY, 500);
	LightScheduler_ScheduleRemove(9, MONDAY, 500);


	setTimeTo(MONDAY, 500);
	LightScheduler_WakeUp();
	checkLightState(7, LIGHT_ON);
	checkLightState(9, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, AcceptsValidLightIds){
	LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(9, MONDAY, 500));
	LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(27, MONDAY, 200));
	LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(12, MONDAY, 500));
}

TEST(LightScheduler, rejectsInvalidLightIds){
	LONGS_EQUAL(LS_ID_OUT_OF_BOUNDS, LightScheduler_ScheduleTurnOn(-1, MONDAY, 500));
	LONGS_EQUAL(LS_ID_OUT_OF_BOUNDS, LightScheduler_ScheduleTurnOn(132, MONDAY, 200));
}
