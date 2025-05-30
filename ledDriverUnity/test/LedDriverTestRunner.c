#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(LedDriver){
	RUN_TEST_CASE(LedDriver, LedsOffAfterCreate);
	RUN_TEST_CASE(LedDriver, TurnOnLedOne);
	RUN_TEST_CASE(LedDriver, TurnOffLedOne);
	RUN_TEST_CASE(LedDriver, TurnOnMultipleLeds);
	RUN_TEST_CASE(LedDriver, TurnOffAnyLed);
	RUN_TEST_CASE(LedDriver, TurnOffMultipleLEDS);
	RUN_TEST_CASE(LedDriver, TurnOnAllLeds);
	RUN_TEST_CASE(LedDriver, TurnOffAllLeds);
	RUN_TEST_CASE(LedDriver, LedMemoryIsNotReadable);
	RUN_TEST_CASE(LedDriver, UpperAndLowerBounds);
	RUN_TEST_CASE(LedDriver, OutOfBoundsTurnOnDoesNoHarm);
	RUN_TEST_CASE(LedDriver, OutOfBoundsTurnOffDoesNoHarm);
	RUN_TEST_CASE(LedDriver, OutOfBoundsProducesRuntimeError);
	RUN_TEST_CASE(LedDriver, OutOfBoundsToDo);
	RUN_TEST_CASE(LedDriver, IsOn);
	RUN_TEST_CASE(LedDriver, OutOfBoundsLedsAreOff);
	RUN_TEST_CASE(LedDriver, IsOff);
}
