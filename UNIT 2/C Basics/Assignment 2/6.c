#include <stdio.h>
void main () {
	int x;
	printf("Enter an integer: "); 
	fflush(stdin); fflush(stdout); 
	scanf("%d", &x);
	int sum = 0;
	for (int i=1; i<= x; i++) { 
    sum += i;
  }
	printf("Sum = %d", sum );
	}
