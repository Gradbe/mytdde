#include <stdio.h>
#include <stdlib.h>

struct my{
	int count;
};

typedef struct my* s;

int main(){
	s myS = malloc(sizeof(s));
	myS->count = 0;
	myS->count++;
	myS->count++;
	myS->count++;
	myS->count++;
	myS->count++;
	printf("Test count - %d\n", myS->count);
	return 0;
}


