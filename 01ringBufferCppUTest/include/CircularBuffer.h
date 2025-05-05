#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>
typedef int BOOL;
enum {FALSE = 0, TRUE = 1};

struct buffer{
	int capacity;
};

typedef struct buffer CircularBuffer;


CircularBuffer CircularBuffer_Create(CircularBuffer buffer);
void CircularBuffer_Destroy(void);
BOOL CircularBuffer_IsEmpty(CircularBuffer buf);

// Other C declarations...

#endif

