#include <stdio.h>
#include <stdlib.h>

struct node{
	int value;
	struct node* left;
	struct node* right;
};

typedef struct cbuffer{
	int count;
	int index;
	int outdex;
	int* values;
} cbuffer;


typedef struct node* ntp;

ntp root;

ntp createNode(){}

ntp insertNode(ntp* tp, int val){
}	

void printTree(ntp tp){
}

int main(int argc, char** argv){
	root = 0;
	for (int i = 1; i < argc; i++){
		insertNode(&root, atoi(argv[0]));
	}
	printTree(root);
	printf("\nSize is %ld\n", sizeof(cbuffer));
	cbuffer* myBuff = calloc(10, sizeof(cbuffer));
	printf("\nSize is %ld\n", sizeof(myBuff));
	myBuff->values = calloc(100, sizeof(int));
	printf("\nSize is %ld\n", sizeof(myBuff));
	return 0;
}
