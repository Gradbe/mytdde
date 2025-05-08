#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>
typedef int BOOL;
enum {FALSE = 0, TRUE = 1};

typedef struct CircularBufferStruct* CircularBuffer;


CircularBuffer CircularBuffer_Create(int capacity);
void CircularBuffer_Destroy(CircularBuffer self);
BOOL CircularBuffer_IsEmpty(CircularBuffer buf);
BOOL CircularBuffer_IsFull(CircularBuffer buf);
void CircularBuffer_Put(CircularBuffer buf, int value);
int CircularBuffer_Get(CircularBuffer buf);
int CircularBuffer_Capacity(CircularBuffer buf);

// Other C declarations...

#endif

