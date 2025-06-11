#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>

typedef uint32_t ioAddress;
typedef uint16_t ioData;

int Flash_Write(ioAddress offset, ioData data);

#endif
