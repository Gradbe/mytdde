#ifndef FLASH_H
#define FLASH_H

#include "IO.h"

void Flash_Create(void);
void Flash_Destroy(void);
int Flash_Write(ioAddress offset, ioData data);

typedef enum{
	FLASH_SUCCESS = 0, 
	FLASH_VPP_ERROR
} FlashStatus;

#endif
