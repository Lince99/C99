#include <stdio.h>
#include <stdlib.h>

void somma(double a, double b, double* s);

int main() {
	//test 0
	double a = 10;
	double b = 5;
	double* s;

	s = malloc(sizeof(double));
	somma(a, b, s);

	printf("a= %lf\tb= %lf\ts = %lf\n", a, b, *s);



	//test 1
	int* p;
	int d;
	int i;

	printf("Inserisci la dimensione dell'array\n--> ");
	scanf("%d", &d); //l'utente inserisce la dim dell'array
	p = (int*) malloc(sizeof(int)*d);
	for(i = 0; i < d; i++) {
		printf("Inserisci il %d° valore:\t", i+1);
		scanf("%d", (p+i));
	}
	printf("array inserita:\n");
	for(i = 0; i < d; i++) {
		printf("%d ", *(p+i));
	}
	printf("\n");
	free(p);

	return 0;
}

void somma(double a, double b, double* s) {
	*s = a+b;
}
