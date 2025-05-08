#include "CircularBuffer.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct CircularBufferStruct{
	int count;
	int index;
	int outdex;
	int capacity;
	int* value;
}CircularBufferStruct;


CircularBuffer CircularBuffer_Create(int capacity){
	CircularBuffer self = calloc(capacity, sizeof(CircularBufferStruct));
	self->capacity = capacity;
	self->value = calloc(capacity, sizeof(int));
	self->count = 0;
	self->index = 0;
	self->outdex = 0;
	return self;
}

void CircularBuffer_Destroy(CircularBuffer self){

}

BOOL CircularBuffer_IsEmpty(CircularBuffer self){
	return self->count == 0;
}

BOOL CircularBuffer_IsFull(CircularBuffer self){
	return self->count == self->capacity;
}

void CircularBuffer_Put(CircularBuffer self, int value){
	self->count+=1;
	self->value[self->index++] = value;
}

int CircularBuffer_Get(CircularBuffer self){
	int value = self->value[self->outdex++];
	self->count-=1;
	return value;
}

int CircularBuffer_Capacity(CircularBuffer self){
	return self->capacity;
}

