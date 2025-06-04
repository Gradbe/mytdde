#include "CppUTest/TestHarness.h"

extern "C"
{
#include "FakeRandomMinute.h"
#include "LightScheduler.h"
#include "FakeTimeService.h"
#include "LightControllerSpy.h"
#include <stdio.h>
}

TEST_GROUP(LightSchedulerRandomize){
	void setup(){
	}
	void teardown(){
	}
	void setTimeTo(Day day, int minute){
		FakeTimeService_SetDay(day);
		FakeTimeService_SetMinute(minute);
	}
	void checkLightState(int id, int level){
	}
};

TEST(LightSchedulerRandomize, TurnsOnEarly){
	FakeRandomMinute_SetFirstAndIncrement(-10, 5);
	LightScheduler_ScheduleTurnOn(4, EVERYDAY, 600);
	LightScheduler_Randomize(4, EVERYDAY, 600);
	setTimeTo(MONDAY, 600-10);
	LightScheduler_WakeUp();
	checkLightState(4, LIGHT_ON);
}

