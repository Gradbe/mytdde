#include "CppUTest/TestHarness.h"

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
		LONGS_EQUAL(id, LightControllerSpy_GetLastId());
		LONGS_EQUAL(level, LightControllerSpy_GetLastState());
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





