#ifndef C_BUFF_
#define C_BUFF_

#include <stdbool.h>

typedef struct RingBuffer RingBuffer_t;

RingBuffer_t* RingBuffer_Create(int size);
void RingBuffer_Destroy(RingBuffer_t* buffer);
bool RingBuffer_IsEmpty(RingBuffer_t* buffer);
bool RingBuffer_Put(RingBuffer_t* buffer, char c);
char RingBuffer_Get(RingBuffer_t* buffer);

#endif
