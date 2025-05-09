#include "CircularBuffer.h"
#include <stdlib.h>

CircularBuffer_t* CircularBuffer_Create(int capacity){
	CircularBuffer_t* buff = malloc(sizeof(int));
	if (buff==NULL){
		exit(0);
	}
	return buff;
}


