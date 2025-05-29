#include "LightControllerSpy.h"

#include "CppUTest/TestHarness_c.h"
#include <stdio.h>
#ifdef WIN32
#define vsnprintf _vsnprintf
#endif

static int lastId;
static int lastState;
static int lights[MAX_LIGHTS];

void LightController_Create(){
	lastId = LIGHT_ID_UNKNOWN;
	lastState = LIGHT_STATE_UNKNOWN;
}

void LightController_Destroy(){
}

void LightController_On(int lightNum){
	lastId = lightNum;
	lastState = LIGHT_ON;
	lights[lightNum] = LIGHT_ON;
}

void LightController_Off(int lightNum){
	lastId = lightNum;
	lastState = LIGHT_OFF;
	lights[lightNum] = LIGHT_OFF;
}

int LightControllerSpy_GetLastId(){
	return lastId;
}

int LightControllerSpy_GetLastState(){
	return lastState;
}


int LightControllerSpy_GetLightState(int id){
	return lights[id];
}
