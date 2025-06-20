#include "CppUTest/TestHarness.h"

extern "C"{
#include "Flash.h"
#include "MockIO.h"
#include "TargetFlash.h"
#include "FakeMicroTime.h"
}

TEST_GROUP(Flash){
	ioAddress address;
	ioData data;
	int result;

	void setup(){
		address = 0x1000;
		data = 0xFEED;
		result = -1;
		MockIO_Create(20);
		FakeMicroTime_Init(0,1);
		Flash_Create();
	}
	void teardown(){
		Flash_Destroy();
		MockIO_Verify_Complete();
		MockIO_Destroy();
	}
};

TEST(Flash, WriteSucceeds_ReadyImmediately){
	MockIO_Expect_Write(CommandRegister, ProgramCommand);
	MockIO_Expect_Write(address, data);
	MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
	MockIO_Expect_ReadThenReturn(address, data);
	result = Flash_Write(address, data);
	LONGS_EQUAL(FLASH_SUCCESS, result);
}

TEST(Flash, WriteSucceeds_NotImmediatelyReady){
	MockIO_Expect_Write(CommandRegister, ProgramCommand);
	MockIO_Expect_Write(address, data);
	MockIO_Expect_ReadThenReturn(StatusRegister, 0);
	MockIO_Expect_ReadThenReturn(StatusRegister, 0);
	MockIO_Expect_ReadThenReturn(StatusRegister, 0);
	MockIO_Expect_ReadThenReturn(StatusRegister, 0);
	MockIO_Expect_ReadThenReturn(StatusRegister, 0);
	MockIO_Expect_ReadThenReturn(StatusRegister, 0);
	MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
	MockIO_Expect_ReadThenReturn(address, data);
	result = Flash_Write(address, data);
	LONGS_EQUAL(FLASH_SUCCESS, result);
}

TEST(Flash, WriteFails_VppError){
	MockIO_Expect_Write(CommandRegister, ProgramCommand);
	MockIO_Expect_Write(address, data);
	MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit | VppErrorBit);
	MockIO_Expect_Write(CommandRegister, Reset);
	
	result = Flash_Write(address, data);
	LONGS_EQUAL(FLASH_VPP_ERROR, result);
}

TEST(Flash, WriteFails_EraseErorBit){
	MockIO_Expect_Write(CommandRegister, ProgramCommand);
	MockIO_Expect_Write(address, data);
	MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit | EraseErrorBit);
	MockIO_Expect_Write(CommandRegister, Reset);
	
	result = Flash_Write(address, data);
	LONGS_EQUAL(FLASH_ERASE_ERROR, result);
}

TEST(Flash, WriteFails_BlockProtectionErrorBit){
	MockIO_Expect_Write(CommandRegister, ProgramCommand);
	MockIO_Expect_Write(address, data);
	MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit | BlockProtectionErrorBit);
	MockIO_Expect_Write(CommandRegister, Reset);
	
	result = Flash_Write(address, data);
	LONGS_EQUAL(FLASH_BLOCK_ERROR, result);
}

TEST(Flash, WriteFails_FlashReadbackError){
	MockIO_Expect_Write(CommandRegister, ProgramCommand);
	MockIO_Expect_Write(address, data);
	MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
	MockIO_Expect_ReadThenReturn(address, data-1);
	
	result = Flash_Write(address, data);
	LONGS_EQUAL(FLASH_READ_BACK_ERROR, result);
}

TEST(Flash, WriteSucceeds_IgnoresOtherBitsUntilReady){
	MockIO_Expect_Write(CommandRegister, ProgramCommand);
	MockIO_Expect_Write(address, data);
	MockIO_Expect_ReadThenReturn(StatusRegister, ~ReadyBit);
	MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
	MockIO_Expect_ReadThenReturn(address, data);
	
	result = Flash_Write(address, data);
	LONGS_EQUAL(FLASH_SUCCESS, result);
}

TEST(Flash, WriteFails_Timeout){
	FakeMicroTime_Init(0,500);
	Flash_Create();
	MockIO_Expect_Write(CommandRegister, ProgramCommand);
	MockIO_Expect_Write(address, data);
	for(int i = 0; i<10; i++){
		MockIO_Expect_ReadThenReturn(StatusRegister, ~ReadyBit);
	}
	result = Flash_Write(address, data);
	LONGS_EQUAL(FLASH_TIMEOUT_ERROR, result);
}

