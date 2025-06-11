#include "CppUTest/TestHarness.h"

extern "C"{
#include "Flash.h"
}

TEST_GROUP(Flash){
	void setup(){}
	void teardown(){}
};

TEST(Flash, WriteSucceeds_ReadyImmediately){
	int result = 0; 
	/*MockIO_Expect_Write(0, 0x40);
	MockIO_Expect_Write(0x1000, 0xBEEF);
	MockIO_Expect_ReadThenReturn(0, 1<<7);
	MockIO_Expect_ReadThenReturn(0x1000, 0xBEEF);
	result = Flash_Write(0x1000, 0xBEEF);
	LONGS_EQUAL(0, result);
	MockIO_Verif_Complete();
	*/
	result = Flash_Write(0x1000, 0xBEEF);
}
