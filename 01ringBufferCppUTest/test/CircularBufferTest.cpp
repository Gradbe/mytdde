#include "CppUTest/TestHarness.h"

extern "C"
{
#include "CircularBuffer.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(CircularBuffer){
	CircularBuffer buffer;
    	void setup()    {
     		buffer =  CircularBuffer_Create(10);
   	}
    	void teardown()    {
       		CircularBuffer_Destroy(buffer);
    	}
};

TEST(CircularBuffer, Create)
{
//  FAIL("Start here");
}

TEST(CircularBuffer, EmptyAfterCreation){
	CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, NotFullAfterCreation0){
	CHECK_FALSE(CircularBuffer_IsFull(buffer));
}

TEST(CircularBuffer, NotEmpty){
	CircularBuffer_Put(buffer, 1003);
	CHECK_FALSE(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, NotEmptyThenEmpty){
	CircularBuffer_Put(buffer, 416);
	CHECK_FALSE(CircularBuffer_IsEmpty(buffer));
	CircularBuffer_Get(buffer);
	CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, GetPutOneValue){
	CircularBuffer_Put(buffer, 416);
	LONGS_EQUAL(416, CircularBuffer_Get(buffer));
}

TEST(CircularBuffer, GetPutAFew){
	CircularBuffer_Put(buffer, 416);
	CircularBuffer_Put(buffer, 417);
	CircularBuffer_Put(buffer, 418);
	LONGS_EQUAL(416, CircularBuffer_Get(buffer));
	LONGS_EQUAL(417, CircularBuffer_Get(buffer));
	LONGS_EQUAL(418, CircularBuffer_Get(buffer));
}

TEST(CircularBuffer, Capacity){
	CircularBuffer b = CircularBuffer_Create(2);
	LONGS_EQUAL(2, CircularBuffer_Capacity(b));
	CircularBuffer_Destroy(b);
}
