#include "CppUTest/TestHarness.h"

extern "C"
{
#include "LightControllerSpy.h"
#include "FakeTimeService.h"
#include "LightScheduler.h"
}

TEST_GROUP(LightControllerSpy){
	void	setup(){
		LightController_Create();
	}
	void teardown(){
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

TEST(LightControllerSpy, Create){
	LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
	LONGS_EQUAL(LIGHT_STATE_UNKNOWN,LightControllerSpy_GetLastState());
}

TEST(LightControllerSpy, RememberLastIdAndState){
	LightController_On(10);
	LONGS_EQUAL(10, LightControllerSpy_GetLastId());
	LONGS_EQUAL(LIGHT_ON,LightControllerSpy_GetLastState());
}

TEST(LightControllerSpy, RememberAllLightStates){
	LightController_On(0);
	LightController_Off(31);
	LONGS_EQUAL(LIGHT_ON, LightControllerSpy_GetLightState(0));
	LONGS_EQUAL(LIGHT_OFF, LightControllerSpy_GetLightState(31));
}



