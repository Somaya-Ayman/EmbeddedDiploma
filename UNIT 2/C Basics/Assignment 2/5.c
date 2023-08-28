#include <stdio.h>
void main () {
	char x;
	printf("Enter a character: ");
	fflush(stdin); fflush(stdout);
	scanf("%c", &x);
	if( ( x >= 'a') && (x<='z') || ( (x>= 'A') && (x<= 'Z')))printf("%c is a charachter", x); 
	else printf("%c is not a charachter", x);
}
