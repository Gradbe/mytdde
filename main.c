#include <stdio.h>

enum day{
	MONDAY=70, 
	TUESDAY, 
	THURSDAY
};

int main(){
	enum day today;
	today = TUESDAY;
	printf("N = %d\n", today);
}

