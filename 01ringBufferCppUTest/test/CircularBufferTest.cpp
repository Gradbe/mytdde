#include "CppUTest/TestHarness.h"

extern "C"
{
#include "CircularBuffer.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(CircularBuffer){
};

TEST(CircularBuffer, Create)
{
	CircularBuffer_t* buf = CircularBuffer_Create(10);
	CHECK_TRUE(buf != NULL);
}


