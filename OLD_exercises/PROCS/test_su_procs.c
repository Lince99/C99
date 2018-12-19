/*
* Basso Nicola
* 4^AI
* 22/10/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

//crea un numero random in base al tempo
void initRandom (int arr[], int dim, int max)
{
	int i = 0;
	for(i = 0; i < dim; i++)
		arr[i] = (int)(rand()%max);
}

//stampa a video un'array di dimensione DIM
void stampa (int arr[], int dim)
{
	int i = 0;
	for(i = 0; i < dim; i++) {
		printf("%d", arr[i]);
		//fino al penultimo elemento stampa il divisore
		if(i < dim-1)
			printf(" ");
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	int dim = 10;
	//crea array
	int arr[dim];
	//inizializza random
	initRandom(arr, dim, 100);
	//visualizza
	stampa(arr, dim);
}
