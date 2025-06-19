#include "Flash.h"
#include "TargetFlash.h"
#include "IO.h"
#include <stdio.h>

void Flash_Create(void){}
void Flash_Destroy(void){}

static FlashStatus writeError(ioData status){
		IO_Write(CommandRegister, Reset);

		if (status & VppErrorBit)
			return FLASH_VPP_ERROR;
		else if (status & EraseErrorBit)
			return FLASH_ERASE_ERROR;
		else if (status & BlockProtectionErrorBit)
			return FLASH_BLOCK_ERROR;
		else if (status & ProgramErrorBit)
			return FLASH_BLOCK_ERROR;
		else 
			return FLASH_UNKNOWN_ERROR;
	
}

int Flash_Write(ioAddress address, ioData data){
	ioData status = 0;

	IO_Write(CommandRegister, ProgramCommand);
	IO_Write(address, data);

	while ((status & ReadyBit) == 0){
		status = IO_Read(StatusRegister);
	}
	if (status != ReadyBit){
		return writeError(status);
	}
	if (data != IO_Read(address))
		return FLASH_READ_BACK_ERROR;

	return FLASH_SUCCESS;
}

