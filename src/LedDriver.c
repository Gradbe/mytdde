#include "LedDriver.h"

enum {ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON};

static uint16_t* ledsAddress;
static uint16_t ledsImage;

static uint16_t convertLedNumberToBit(int LedNumber){
	return 1 << (LedNumber - 1);
}

void LedDriver_Create(uint16_t* address){
	ledsAddress = address;
	ledsImage = 0;
	*ledsAddress = ledsImage;
}

void LedDriver_TurnOn(int LedNumber){
	ledsImage |= convertLedNumberToBit(LedNumber);
	*ledsAddress = ledsImage;
}

void LedDriver_TurnOff(int LedNumber){
	ledsImage &= ~convertLedNumberToBit(LedNumber);
	*ledsAddress = ledsImage;
}

void LedDriver_TurnAllOn(void){
	ledsImage = ALL_LEDS_ON;
	*ledsAddress = ledsImage;
}



