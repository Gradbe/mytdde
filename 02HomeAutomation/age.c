#include <stdio.h>

int main(){
	int age = 0;

	printf("Enter age\n");
	scanf("%d", &age);

	if (age > 18)
		printf("you can vote\n");
	else
		printf("you can not vote\n");
}
