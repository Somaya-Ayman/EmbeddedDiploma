#include <stdio.h>
void main () {
	char a;
	printf("Enter an alphabet: ");
	fflush(stdin); fflush(stdout);
	scanf("%c", &a);
	if (a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u') printf("%c is a vowel\n",a);
	else printf("%c is a constant \n", a);
}
