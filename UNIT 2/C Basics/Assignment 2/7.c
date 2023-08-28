void main () {
	int a;
	printf("Enter an integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &a);
	if (a>=0) {
		int fact = 1;
		for (int i =1; i< a; i++) {
			fact *= i;
		}
		printf("Factorial = %d", fact);
	}
	else {
		printf("Error!! Factorial of negative number doesnt exist");
	}
}
