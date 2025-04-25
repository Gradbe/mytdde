#include "LedDriver.h"
#include "RuntimeError.h"
#include <stdio.h>

enum {ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON};
enum {FIRST_LED = 1 , LAST_LED = 16};

static uint16_t* ledsAddress;
static uint16_t ledsImage;

static uint16_t convertLedNumberToBit(int LedNumber){
	return 1 << (LedNumber - 1);
}

static void setLedImageBit(int LedNumber){
	ledsImage |= convertLedNumberToBit(LedNumber);
}

static void clearLedImageBit(int LedNumber){
	ledsImage &= ~convertLedNumberToBit(LedNumber);
}

static void updateHardware(void){
	*ledsAddress = ledsImage;
}

static BOOL isLedOutOfBounds(int LedNumber){
	if (LedNumber > LAST_LED || LedNumber < FIRST_LED){
		RUNTIME_ERROR("LED Driver: out-of-bounds LED", LedNumber);
		return 1;
	}
	else
		return 0;
}

void LedDriver_Create(uint16_t* address){
	ledsAddress = address;
	ledsImage = 0;
	updateHardware();
}

void LedDriver_Destroy(void){
}

void LedDriver_TurnOn(int LedNumber){
	if (isLedOutOfBounds(LedNumber))
		return;
	setLedImageBit(LedNumber);
	updateHardware();
}

void LedDriver_TurnOff(int LedNumber){
	if (isLedOutOfBounds(LedNumber))
		return;
	clearLedImageBit(LedNumber);
	updateHardware();
}

void LedDriver_TurnAllOn(void){
	ledsImage = ALL_LEDS_ON;
	updateHardware();
}

void LedDriver_TurnAllOff(void){
	ledsImage = ALL_LEDS_OFF;
	updateHardware();
}

BOOL LedDriver_IsOn(int ledNumber){
	if (isLedOutOfBounds(ledNumber))
		return FALSE;
	return 0 != (convertLedNumberToBit(ledNumber) & ledsImage);
}

BOOL LedDriver_IsOff(int ledNumber){
	return !LedDriver_IsOn(ledNumber);
}

