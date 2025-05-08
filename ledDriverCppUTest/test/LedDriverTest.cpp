#include "CppUTest/TestHarness.h"

extern "C"
{
#include "LedDriver.h"
}

#include "CppUTest/TestHarness.h"

extern "C"
{
#include "LedDriver.h"
}

TEST_GROUP(LedDriver){
	uint16_t virtualLeds;
    void setup()    {
      LedDriver_Create(&virtualLeds);
    }
    void teardown()    {
       LedDriver_Destroy();
    }
};

TEST(LedDriver, Create)
{
//  FAIL("Start here");
}

TEST(LedDriver, LedsOffAfterCreate)
{
	virtualLeds = 0xffff;
	LedDriver_Create(&virtualLeds);
	LONGS_EQUAL(0, virtualLeds);

}



