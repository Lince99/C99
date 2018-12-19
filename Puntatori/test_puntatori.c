/*
 * Basso Nicola
 */

#include <stdio.h>
#include <stdlib.h>

void somma(double* sum, double x, double y);
void init(float* arr, int dim);

int main(int argc, char** argv) {
    //parte 1
    double* s;
    double tmp = 0;
    double x, y;

	s = (double*) malloc(sizeof(double));
    x = 12.53;
    y = 30.2312;
    s = &tmp;

    somma(s, x, y);
    printf("somma di %lf + %lf = %lf\n", x, y, *s);



    //parte 2
    int dim = 10;
    int i;
    float numbers[dim];

    init(numbers, dim);
    float* nPtr;
	nPtr = (float*) malloc(sizeof(float)*dim);
	nPtr = &numbers;
    printf("array = ");
    for(i = 0; i < 10; i++) {
        printf("%f ", numbers[i]);
    }
    printf("\narray con puntatore = ");
    for(i = 0; i < 10; i++) {
        printf("%f ", *nPtr+i);
    }
    printf("\n");

	free(s);
	free(nPtr);

    return 0;
}

void somma(double* sum, double x, double y) {
    *sum = x+y;
}

void init(float* arr, int dim) {
	int i;

    for(i = 0; i < dim; i++) {
        arr[i] = i + (float)i/10;
    }
}
