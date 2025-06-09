#include "CppUTest/TestHarness.h"

extern "C"
{
#include "FormatOutputSpy.h"
}

TEST_GROUP(FormatOutputSpy){
	void setup(){
		UT_PTR_SET(FormatOutput, FormatOutputSpy);
	}
	void teardown(){
		FormatOutputSpy_Destroy();
	}
};
TEST(FormatOutputSpy, HelloWorld){
	FormatOutputSpy_Create(20);
	FormatOutput("Hello, world\n");
	STRCMP_EQUAL("Hello, world\n", FormatOutputSpy_GetOutput());
}

TEST(FormatOutputSpy, LimitTheOutputBufferSize){
	FormatOutputSpy_Create(2);
	FormatOutputSpy("Hello, world\n");
	STRCMP_EQUAL("He", FormatOutputSpy_GetOutput());
}

TEST(FormatOutputSpy, PrintMultipleTimes){
	FormatOutputSpy_Create(20);
	FormatOutput("Hello, ");
	FormatOutput("world\n");
	STRCMP_EQUAL("Hello, world\n", FormatOutputSpy_GetOutput());
}

TEST(FormatOutputSpy, PrintMultipleOutputsPastFull){
	FormatOutputSpy_Create(12);
	FormatOutputSpy("12345");
	FormatOutputSpy("abcde");
	FormatOutputSpy("67890");
	STRCMP_EQUAL("12345abcde67", FormatOutputSpy_GetOutput());
}



