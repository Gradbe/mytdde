#include <stdio.h>
static int events[10];
static void printme(int a){
	int i;
	for (i = 0; i < 10; i++){
		if(events[i]==0){
			printf("I'm called and i is %d\n", i);
			events[i]=a;
			break;
		}
	}
}

int main(){
	printme(2);
	printme(4);
	printme(5);
	for (int i = 0; i < 10; i++){
		printf("Events[%d] = %d\n", i, events[i]);
	}
	return 0;
}
