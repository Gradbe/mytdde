#include "CppUTest/TestHarness.h"

extern "C"
{
#include "CircularBuffer.h"
#include "FormatOutputSpy.h"
}

TEST_GROUP(CircularBuffer){
	CircularBuffer_t* buffer;
	void	setup(){
		buffer = CircularBuffer_Create(10);
	}
	void teardown(){
		CircularBuffer_Destroy(buffer);
	}
	void putManyInTheBuffer(int seed, int howMany){
		for (int i = 0; i < howMany; i++)
			CircularBuffer_Put(buffer, i+seed);
	}
};

TEST(CircularBuffer, Create){
	CHECK(CircularBuffer_Create(1));
}

TEST(CircularBuffer, EmptyAfterCreate){
	CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, NotFullAfterCreate){
	CHECK_FALSE(CircularBuffer_IsFull(buffer));
}

TEST(CircularBuffer, NotEmptyAfterPut){
	CircularBuffer_Put(buffer, 13);
	CHECK_FALSE(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, NotEmptyThenEmpty){
	CircularBuffer_Put(buffer, 12);
	CHECK_FALSE(CircularBuffer_IsEmpty(buffer));
	CircularBuffer_Get(buffer);
	CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, Capacity){
	CircularBuffer_t* buff = CircularBuffer_Create(8);
	LONGS_EQUAL(8, CircularBuffer_Capacity(buff));
	CircularBuffer_Destroy(buff);
}


TEST(CircularBuffer, CircularBufferFullAfterPuts){
	for (int i = 0; i < CircularBuffer_Capacity(buffer); i++){
		CircularBuffer_Put(buffer, i);
	}
	CHECK_TRUE(CircularBuffer_IsFull(buffer));
}

TEST(CircularBuffer, PutGetOne){
	CircularBuffer_Put(buffer, 12);
	LONGS_EQUAL(12,  CircularBuffer_Get(buffer));
	CircularBuffer_Put(buffer, 143);
	LONGS_EQUAL(143,  CircularBuffer_Get(buffer));
}

TEST(CircularBuffer, PutGetAFew){
	CircularBuffer_Put(buffer, 1);
	CircularBuffer_Put(buffer, 2);
	CircularBuffer_Put(buffer, 12);
	LONGS_EQUAL(1,  CircularBuffer_Get(buffer));
	LONGS_EQUAL(2,  CircularBuffer_Get(buffer));
	LONGS_EQUAL(12,  CircularBuffer_Get(buffer));
}

TEST(CircularBuffer, EmptyToFullToEmpty){
	for (int i = 0; i < CircularBuffer_Capacity(buffer); i++){
		CircularBuffer_Put(buffer, i+100);
	}
	CHECK_TRUE(CircularBuffer_IsFull(buffer));
	for (int j = 0; j < CircularBuffer_Capacity(buffer); j++){
		CircularBuffer_Get(buffer);
	}
	CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
	CHECK_FALSE(CircularBuffer_IsFull(buffer));
}

TEST(CircularBuffer, WrapAround){
	int capacity = CircularBuffer_Capacity(buffer);
	for (int i = 0; i < capacity; i++)
		CircularBuffer_Put(buffer, 100+i);
	CHECK_TRUE(CircularBuffer_IsFull(buffer));
	LONGS_EQUAL(100, CircularBuffer_Get(buffer));
	CHECK_FALSE(CircularBuffer_IsFull(buffer));
	CircularBuffer_Put(buffer, 1000);
	CHECK_TRUE(CircularBuffer_IsFull(buffer));
	
	for (int j = 1; j < capacity; j++){
		CircularBuffer_Get(buffer);
	}
	LONGS_EQUAL(1000, CircularBuffer_Get(buffer));
	CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
	

}

TEST(CircularBuffer, PutToFullFails){
	putManyInTheBuffer(900, CircularBuffer_Capacity(buffer));
	CHECK_FALSE(CircularBuffer_Put(buffer, 999));
}

TEST(CircularBuffer, PutToFullDoesNOtDamageContents){
	putManyInTheBuffer(900, CircularBuffer_Capacity(buffer));
	CircularBuffer_Put(buffer, 9999);
	for(int i=0; i<CircularBuffer_Capacity(buffer); i++)
		LONGS_EQUAL(900+i, CircularBuffer_Get(buffer));
	CHECK_TRUE(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, GetFromEmptyReturns0){
	LONGS_EQUAL(0,	CircularBuffer_Get(buffer));
}

TEST(CircularBuffer, PrintEmpty){
	const char* expectedOutput = "Circular buffer content:\n<>\n";
	FormatOutputSpy_Create(100);
	UT_PTR_SET(FormatOutput, FormatOutputSpy);
	CircularBuffer_Print(buffer);
	STRCMP_EQUAL(expectedOutput, FormatOutputSpy_GetOutput());
	FormatOutputSpy_Destroy();	
}	

TEST(CircularBuffer, PrintAfterOneIsPut){
	const char* expectedOutput = "Circular buffer content:\n<17>\n";
	FormatOutputSpy_Create(100);
	UT_PTR_SET(FormatOutput, FormatOutputSpy);

	CircularBuffer_Put(buffer, 17);
	CircularBuffer_Print(buffer);

	STRCMP_EQUAL(expectedOutput, FormatOutputSpy_GetOutput());
	FormatOutputSpy_Destroy();	
}	
