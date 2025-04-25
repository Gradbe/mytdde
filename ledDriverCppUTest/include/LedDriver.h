#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>
typedef int BOOL;
enum {FALSE=0, TRUE=1};

void LedDriver_Create(uint16_t* address);
void LedDriver_Destroy(void);
void LedDriver_TurnOn(int ledNumber);

// Other C declarations...

#endif

