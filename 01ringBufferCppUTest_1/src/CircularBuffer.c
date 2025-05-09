#include "CircularBuffer.h"
#include <stdio.h>
#include <stdlib.h>

struct RingBuffer {
 	char* data;
	int size;
	int count;
	int head;
	int tail;
};


RingBuffer_t* RingBuffer_Create(int size){
	RingBuffer_t* rb = malloc(sizeof(RingBuffer_t));
	rb->data = malloc(size * sizeof(char));
	rb->size = size;
	rb->count = 0;
	rb->tail = 0;
	rb->head = 0;
	return rb;
}

void RingBuffer_Destroy(RingBuffer_t* buffer){
	free(buffer->data);
	free(buffer);
}

bool RingBuffer_IsEmpty(RingBuffer_t* buffer){
	return buffer->count == 0;
}

bool RingBuffer_Put(RingBuffer_t* buffer, char data){
	if(buffer->count < buffer->size){
		buffer->count++;
		buffer->data[buffer->head++ % buffer->size]=data;
		return true;
	}
	else
		return false;
}

char RingBuffer_Get(RingBuffer_t* buffer){
	if(buffer->count == 0) return 0;

	char data;
	data = buffer->data[buffer->tail++ % buffer->size];
	buffer->count--;
	return data;
}


bool RingBuffer_Peek(RingBuffer_t* buffer, char* c){
	if(buffer->count == 0) return false;
	*c = buffer->data[buffer->tail];
	return true;
}


	 
