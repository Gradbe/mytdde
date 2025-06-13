#ifndef FLASH_H
#define FLASH_H

#include "IO.h"

int Flash_Write(ioAddress offset, ioData data);

typedef enum{
	FLASH_SUCCESS = 0
} FlashStatus;

#endif
