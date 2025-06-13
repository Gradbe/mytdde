#include "IO.h"

ioData IO_Read(ioAddress offset){
	ioData* p = 0;
	return *(p + offset);
}

void IO_Write(ioAddress offset, ioData data){
	ioData* p = 0;
	*(p + addr) = data;
}
