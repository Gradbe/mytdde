#include "CircularBuffer.h"
#include <stdio.h>


CircularBuffer CircularBuffer_Create(CircularBuffer newBuff){
	newBuff.capacity = 0;
	return newBuff;
}

void CircularBuffer_Destroy(void){
}

BOOL CircularBuffer_IsEmpty(CircularBuffer buff){
	if(buff.capacity == 0)
		return TRUE;
	else
		return FALSE;
}

