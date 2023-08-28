#include <stdio.h>
int factorial (int x);
void main () {
	int a;
	printf("Enter an positive integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &a);
	printf("Factorial of %d = %d", a, factorial (a));
}
factorial (int x) { 
	if (x == 0) return 1;
	return x*factorial (x-1);
}
