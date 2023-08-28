#include <stdio.h>

int prime (int x);

void main () {
	int a,b;
	printf("Enter two numbers (intervals): ");
	fflush(stdin); fflush(stdout);
	scanf("%d%d", &a, &b);
	printf("Prime numbers between %d and %d are: ",a,b); 
	for (int i = a; i<= b; i++) {
    	if (prime (i)==1) {printf("%d ",i);}
	}
}

int prime (int x) { 
	int flag = 0;
	for (int i = 2; i<x/2; i++) {
		if (x%i==0) {
			return 0;
    }
	}
	return 1;
}
