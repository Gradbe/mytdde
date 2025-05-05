#include "CppUTest/TestHarness.h"

extern "C"
{
#include "CircularBuffer.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(CircularBuffer){
	CircularBuffer buffer;
    	void setup()    {
     		buffer =  CircularBuffer_Create(buffer);
   	}
    	void teardown()    {
       		CircularBuffer_Destroy();
    	}
};

TEST(CircularBuffer, Create)
{
//  FAIL("Start here");
}

TEST(CircularBuffer, EmptyAfterCreation){
	CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
}




