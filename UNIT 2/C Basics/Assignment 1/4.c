#include <stdio.h>
void main () {
	float x,y;
	printf("Enter two numbers: "); 
	fflush(stdin); fflush(stdout); 
	scanf("%f%f",&x, &y); 
	printf("Product: %f",x*y);
}
