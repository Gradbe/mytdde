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

