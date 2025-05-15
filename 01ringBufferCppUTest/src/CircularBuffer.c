#include "CircularBuffer.h"
#include "Utils.h"
#include <stdlib.h>

struct CircularBufferStruct{
	int size;
	int count;
	int tail;
	int head;
	int* value;
};

CircularBuffer_t* CircularBuffer_Create(int size){
	CircularBuffer_t* buffer = (CircularBuffer_t*)malloc(sizeof(CircularBuffer_t));
	buffer->value = (int*)malloc(sizeof(int)*size);
	buffer->count = 0;
	buffer->tail = buffer->head = 0;
	buffer->size = size;
	return buffer;
}
void CircularBuffer_Destroy(CircularBuffer_t* self){
	free(self->value);
	free(self);
}

bool CircularBuffer_IsEmpty(CircularBuffer_t* self){
	if (self->count == 0)
		return true;
	else 
		return false;
}

bool CircularBuffer_IsFull(CircularBuffer_t* self){
	if(self->count == self->size)
		return true;
	else
		return false;
}

bool CircularBuffer_Put(CircularBuffer_t* self, int val){
	if (self->count < self->size){
		self->count++;
		int head = (self->head++)%self->size;
		self->value[head] = val;
		return true;
	}else
		return false;
}


int CircularBuffer_Get(CircularBuffer_t* self){
	if (self->count > 0){
		self->count--;
		int tail = (self->tail++)%self->size;
		int value = self->value[tail];
		return value;
	}else
		return 0;
}


int CircularBuffer_Capacity(CircularBuffer_t* self){
	return self->size;
}
void CircularBuffer_Print(CircularBuffer_t* self){
	    int i;
    int currentValue;

    currentValue = self->tail;

    FormatOutput("Circular buffer content:\n<");

    for (i = 0; i < self->count; i++) {
        if (i != 0)
            FormatOutput(", ");
        FormatOutput("%d", self->value[currentValue++]);
        if (currentValue >= self->size)
            currentValue = 0;
    }

    FormatOutput(">\n");
}

