#include "unity_fixture.h"

#include "LedDriver.h"
#include "RuntimeErrorStub.h"

static uint16_t virtualLeds;

TEST_GROUP(LedDriver);

TEST_SETUP(LedDriver){
	LedDriver_Create(&virtualLeds);
}
TEST_TEAR_DOWN(LedDriver){}

TEST(LedDriver, LedsOffAfterCreate){
//	TEST_FAIL_MESSAGE("Start here");
	uint16_t virtualLeds = 0xffff;
	LedDriver_Create(&virtualLeds);
	TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, TurnOnLedOne){
	LedDriver_TurnOn(1);
	TEST_ASSERT_EQUAL_HEX16(1, virtualLeds);
//	TEST_IGNORE_MESSAGE("Ignore message works!");
}

TEST(LedDriver, TurnOffLedOne){
	LedDriver_TurnOn(1);
	LedDriver_TurnOff(1);
	TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, TurnOnMultipleLeds){
	LedDriver_TurnOn(8);
	LedDriver_TurnOn(9);
	TEST_ASSERT_EQUAL_HEX16(0x180, virtualLeds);
}	

TEST(LedDriver, TurnOffAnyLed){
	LedDriver_TurnAllOn();
	LedDriver_TurnOff(7);
	TEST_ASSERT_EQUAL_HEX16(0xffbf, virtualLeds);
}

TEST(LedDriver, TurnOnAllLeds){
	LedDriver_TurnAllOn();
	TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}

TEST(LedDriver, LedMemoryIsNotReadable){
	virtualLeds = 0xffff;
	LedDriver_TurnOn(8);
	TEST_ASSERT_EQUAL_HEX16(0x80, virtualLeds);
}

TEST(LedDriver, UpperAndLowerBounds){
	LedDriver_TurnOn(1);
	LedDriver_TurnOn(16);
	TEST_ASSERT_EQUAL_HEX16(0x8001, virtualLeds);
}

TEST(LedDriver, OutOfBoundsTurnOnDoesNoHarm){
	LedDriver_TurnOn(-1);
	LedDriver_TurnOn(0);
	LedDriver_TurnOn(17);
	LedDriver_TurnOn(3141);
	TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}


TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm){
	LedDriver_TurnAllOn();
	LedDriver_TurnOff(-1);
	LedDriver_TurnOff(0);
	LedDriver_TurnOff(17);
	LedDriver_TurnOff(3141);
	TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}

TEST(LedDriver, OutOfBoundsProducesRuntimeError){
	LedDriver_TurnOn(-1);
	TEST_ASSERT_EQUAL_STRING("LED Driver: out-of-bounds LED", RuntimeErrorStub_GetLastError());
	TEST_ASSERT_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}

IGNORE_TEST(LedDriver, OutOfBoundsToDo){
	//things to do 
}

TEST(LedDriver, IsOn){
	TEST_ASSERT_FALSE(LedDriver_IsOn(11));
	LedDriver_TurnOn(11);
	TEST_ASSERT_TRUE(LedDriver_IsOn(11));
}

TEST(LedDriver, OutOfBoundsLedsAreOff){
	TEST_ASSERT_FALSE(LedDriver_IsOn(0));
	TEST_ASSERT_FALSE(LedDriver_IsOn(17));
	TEST_ASSERT_TRUE(LedDriver_IsOff(784));
	TEST_ASSERT_FALSE(LedDriver_IsOn(3471));
}

TEST(LedDriver, IsOff){
	TEST_ASSERT_TRUE(LedDriver_IsOff(2));
	LedDriver_TurnOn(2);
	TEST_ASSERT_FALSE(LedDriver_IsOff(2)); 
}

TEST(LedDriver, TurnOffMultipleLEDS){
	LedDriver_TurnAllOn();
	LedDriver_TurnOff(8);
	LedDriver_TurnOff(9);
	TEST_ASSERT_EQUAL_HEX16(0xfe7f, virtualLeds);
	TEST_ASSERT_EQUAL_HEX16(~(0x180)&0xffff, virtualLeds);
	LedDriver_TurnAllOn();
	LedDriver_TurnOff(1);
	LedDriver_TurnOff(5);
	LedDriver_TurnOff(9);
	TEST_ASSERT_EQUAL_HEX16(~(0x111)&0xffff, virtualLeds);
}

TEST(LedDriver, TurnOffAllLeds){
	LedDriver_TurnAllOn();
	LedDriver_TurnAllOff();
	TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}
