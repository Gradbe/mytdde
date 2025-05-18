#include "CppUTest/TestHarness.h"

extern "C"
{
#include "LightControllerSpy.h"
}

TEST_GROUP(FakeTimeService){
	void	setup(){
		LigthController_Create();
	}
	void teardown(){
	}
};

TEST(FakeTimeService, Create){
}

