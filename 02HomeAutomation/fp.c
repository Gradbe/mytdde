#include <stdio.h>

typedef int (*operation)(int, int);

void my_operation(operation op, int a, int b){
	printf("%d\n", op(a,b));
}

int add(int a, int x){return a + x;}
int multiply(int a, int x){return a * x;}

int main(){
	printf("Let's add\n");
	my_operation(add, 15,15);
	printf("Let's multiply\n");
	my_operation(multiply, 15,15);
	return 0;
}
