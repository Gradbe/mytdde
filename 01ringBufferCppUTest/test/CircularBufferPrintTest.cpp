#include "CppUTest/TestHarness.h"

extern "C"
{
#include "CircularBuffer.h"
//#include "util.h"
#include "FormatOutputSpy.h"
}

TEST_GROUP(CircularBufferPrint){
	CircularBuffer_t* buffer;
	const char* expectedOutput;
	const char* actualOutput;
	void setup(){
		UT_PTR_SET(FormatOutput, FormatOutputSpy);
		FormatOutputSpy_Create(100);
		actualOutput = FormatOutputSpy_GetOutput();
		buffer = CircularBuffer_Create(10);
	}
	void teardown(){
		CircularBuffer_Destroy(buffer);
		FormatOutputSpy_Destroy();
	}
};

TEST(CircularBufferPrint, PrintEmpty){
	expectedOutput = "Circular buffer content:\n<>\n";
	CircularBuffer_Print(buffer);
	STRCMP_EQUAL(expectedOutput, actualOutput);
	CircularBuffer_Put(buffer, 10);
	//STRCMP_EQUAL(expectedOutput, actualOutput);
	CircularBuffer_Put(buffer, 8);
	CircularBuffer_Put(buffer, 10);
	CircularBuffer_Put(buffer, 22);
	CircularBuffer_Print(buffer);

}

TEST(CircularBufferPrint, PrintAfterOneIsPut){
	expectedOutput = "Circular buffer content:\n<17>\n";
	CircularBuffer_Put(buffer, 17);
	CircularBuffer_Print(buffer);
	STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintNotYetWrappedOrFull){
	expectedOutput = "Circular buffer content:\n<10, 20, 30>\n";
	CircularBuffer_Put(buffer, 10);
	CircularBuffer_Put(buffer, 20);
	CircularBuffer_Put(buffer, 30);
	CircularBuffer_Print(buffer);
	STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintNotYetWrappedButFull){
	expectedOutput = "Circular buffer content:\n<31, 41, 59, 26, 53>\n";
	CircularBuffer_t* b = CircularBuffer_Create(5);
	CircularBuffer_Put(b, 31);
	CircularBuffer_Put(b, 41);
	CircularBuffer_Put(b, 59);
	CircularBuffer_Put(b, 26);
	CircularBuffer_Put(b, 53);
	CircularBuffer_Print(b);
	STRCMP_EQUAL(expectedOutput, actualOutput);
	CircularBuffer_Destroy(b);
}

TEST(CircularBufferPrint, PrintOldAndNewWhenWrappedAndFull){
	expectedOutput = "Circular buffer content:\n<41, 59, 26, 53, 999>\n";
	CircularBuffer_t* b = CircularBuffer_Create(5);
	CircularBuffer_Put(b, 31);
	CircularBuffer_Put(b, 41);
	CircularBuffer_Put(b, 59);
	CircularBuffer_Put(b, 26);
	CircularBuffer_Put(b, 53);
	CircularBuffer_Get(b);
	CircularBuffer_Put(b, 999);
	CircularBuffer_Print(b);
	STRCMP_EQUAL(expectedOutput, actualOutput);
	CircularBuffer_Destroy(b);
}


