#include <stdio.h>
void main () {
	char c;
	printf("Enter operator either + or - or * or devide: ");
	fflush(stdin); fflush(stdout);
	scanf("%c", &c);
	float opl, op2;
	printf("Enter two operands: "); 
	fflush(stdin); fflush(stdout); 
	scanf("%f%f",&op1, &op2);
	switch (c) {
	case '+': 
		printf("%f", op1+op2); 
		break;
	case '-': 
		printf("%f", opl-op2);
	    break;
	case '*': 
		printf("%f", opl*op2); 
		break;
	case '/': 
		printf("%f", opl/op2); 
		break;

	}
}
