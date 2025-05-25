#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H
enum {
	LIGHT_ID_UNKNOWN = -1,
	LIGHT_STATE_UNKNOWN = -1, 
	LIGHT_ON = 1,
	LIGHT_OFF = 0
};

void LightController_Create();
void LightController_Destroy();
void LightController_On(int lightNum);
void LightController_Off(int lightNum);

#endif
