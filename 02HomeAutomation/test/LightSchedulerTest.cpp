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
};


TEST(LightScheduler, NoScheduleNothingHappens){
	FakeTimeService_SetDay(MONDAY);
	FakeTimeService_SetMinute(100);
	LightScheduler_WakeUp();
	LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
	LONGS_EQUAL(LIGHT_STATE_UNKNOWN,LightControllerSpy_GetLastState());
}

TEST(LightScheduler, ScheduleOnEveryDayNotTimeYet){
	LightScheduler_TurnOn(3, EVERYDAY, 1200);
	FakeTimeService_SetDay(MONDAY);
	FakeTimeService_SetMinute(1199);
	LightScheduler_WakeUp();
	LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
	LONGS_EQUAL(LIGHT_STATE_UNKNOWN,LightControllerSpy_GetLastState());
}

