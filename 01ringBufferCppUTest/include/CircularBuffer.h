#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdbool.h>

typedef struct CircularBufferStruct CircularBuffer_t;

CircularBuffer_t* CircularBuffer_Create(int size);
void CircularBuffer_Destroy(CircularBuffer_t* self);
bool CircularBuffer_IsEmpty(CircularBuffer_t* self);
bool CircularBuffer_IsFull(CircularBuffer_t* self);
bool CircularBuffer_Put(CircularBuffer_t* buff, int val);
int CircularBuffer_Get(CircularBuffer_t* buff);
int CircularBuffer_Capacity(CircularBuffer_t* buff);
void CircularBuffer_Print(CircularBuffer_t* buff);

#endif

