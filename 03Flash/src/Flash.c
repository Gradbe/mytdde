#include "Flash.h"
#include "TargetFlash.h"
#include "IO.h"
#include <stdio.h>

void Flash_Create(void){}
void Flash_Destroy(void){}

int Flash_Write(ioAddress address, ioData data){
	ioData status = 0;

	IO_Write(CommandRegister, ProgramCommand);
	IO_Write(address, data);

	while ((status & ReadyBit) == 0){
		status = IO_Read(StatusRegister);
	}
	if (status != ReadyBit){
		IO_Write(CommandRegister, Reset);

		if (status & VppErrorBit)
			return FLASH_VPP_ERROR;
	}

	IO_Read(address);

	return FLASH_SUCCESS;
}

