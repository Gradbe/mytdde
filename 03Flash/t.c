#include <stdio.h>

int main(){
	int a = 1<<7;
	int b = ~a;
	printf("0x%x 0x%x\n", a, b);
	return 0;
}
