#ifndef MOCK_IO_H
#define MOCK_IO_H

#include "IO.h"

void MockIO_Create(int maxExpectations);
void MockIO_Destroy(void);
void MockIO_Expect_Write(ioAddress offset, ioData data);
void MockIO_Expect_ReadThenReturn(ioAddress  offset, ioData returnData);
void MockIO_Verify_Complete(void);

#endif
