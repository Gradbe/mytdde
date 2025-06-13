#include <stdio.h>

typedef struct point {
	int a;
	int b;
}point;

void printPoint(point* p){
	int a = 0;
	a = (*p).a;
	printf("A = %d\n", a);
	int b = p->b;
	printf("B = %d\n", b);
}

int main(){
	point p;
	p.a = 10;
	p.b = 12;
	printPoint(&p);
	return 0;
}

