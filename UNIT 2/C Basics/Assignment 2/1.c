#include <stdio.h> 
void main() {
	int a;
	printf("Enter an integer you want to check: "); 
	fflush(stdin); fflush(stdout);
	scanf("%d", &a);
	if (a%2==0) printf("%d is even\n", a);
	else printf("%d is odd\n",a);
}
