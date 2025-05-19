#ifndef D_LightControllerSpy_H
#define D_LightControllerSpy_H

#include "LightControllerSpy.h"

enum {
	LIGHT_ID_UNKNOWN = -1,
	LIGHT_STATE_UNKNOWN = -1, 
	LIGHT_ON = 1,
	LIGHT_OFF = 0
};

void LigthController_Create();
void LightController_On(int lightNum);

int LightControllerSpy_GetLastId();
int LightControllerSpy_GetLastState();


#endif
