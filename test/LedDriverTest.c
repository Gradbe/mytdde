#include "unity.h"
#include "unity_fixture.h"

#include "LedDriver.h"

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
