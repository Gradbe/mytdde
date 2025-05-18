#include "LightControllerSpy.h"

#include "CppUTest/TestHarness_c.h"
#include <stdio.h>
#ifdef WIN32
#define vsnprintf _vsnprintf
#endif

static int lastId;
static int lastState;

void LigthController_Create(){
	lastId = LIGHT_ID_UNKNOWN;
	lastState = LIGHT_STATE_UNKNOWN;
}

void LightController_On(int lightNum){
	lastId = lightNum;
	lastState = LIGHT_ON;
}

int LightControllerSpy_GetLastId(){
	return lastId;
}

int LightControllerSpy_GetLastState(){
	return lastState;
}


