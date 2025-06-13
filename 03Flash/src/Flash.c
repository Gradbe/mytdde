#include "Flash.h"

int Flash_Write(ioAddress offset, ioData data){
	IO_Write(0, 0x40);
	IO_Write(offset, data);
	IO_Read(0);
	IO_Read(offset);

	return FLASH_SUCCESS;
}

