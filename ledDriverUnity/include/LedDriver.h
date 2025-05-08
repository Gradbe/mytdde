#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>
typedef int BOOL;
enum {FALSE=0, TRUE=1};

void LedDriver_Create(uint16_t* address);
void LedDriver_TurnOn(int ledNumber);
void LedDriver_TurnOff(int ledNumber);
void LedDriver_TurnAllOn(void);
void LedDriver_TurnAllOff(void);
BOOL LedDriver_IsOn(int ledNumber);
BOOL LedDriver_IsOff(int ledNumber);

#endif
