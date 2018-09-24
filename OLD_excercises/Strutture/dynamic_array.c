/*
* Basso Nicola
* 4^AI
* 21/10/2017
*/

//test di strutture dinamiche : array a dimensione variabile

#include <stdio.h>
#include <stdlib.h>

int* addArray (int arr[], int dim); //aggiunge un valore all'array
int* remArray (int* arr, int dim, int pos); //rimuove l'ultimo valore
void initArray (int arr[], int dim); //inizializza l'array
void printArray (int arr[], int dim); //stampa l'array

int main (int argc, char **argv)
{
	int dim = 10;
	int *pArray;

	pArray = (int*) malloc(sizeof(int)*dim);
	printf("Array:\nvalore:%d\npunta a:%p\npuntatore:%p\n", *pArray, &pArray, pArray);
	initArray(pArray, dim);
	printArray(pArray, dim);
	
	//add
	dim++;
	pArray = (int*) realloc(pArray, sizeof(int)*dim);
	initArray(pArray, dim);
	printArray(pArray, dim);
	
	dim = dim + 2;
	pArray = (int*) realloc(pArray, sizeof(int)*dim);
	initArray(pArray, dim);
	printArray(pArray, dim);
		
	/*for(; dim > 1; dim--)
	{
		pArray = (int*) realloc(pArray, sizeof(int)*dim);
		initArray(pArray, dim);
		printArray(pArray, dim);
	}*/

	printf("\nTest n*2:");
	pArray = addArray(pArray, dim);
	pArray[dim] = 100;
	dim = dim + 1;
	printArray(pArray, dim);

	printf("\nTest n*3:");
	pArray = remArray(pArray, dim, 3);
	dim = dim - 1;
	printArray(pArray, dim);
	free(pArray);
	return 0;
}

int* addArray (int* arr, int dim)
{
	return (int*) realloc(arr, sizeof(int)*(dim+1));
}

int* remArray (int* arr, int dim, int pos)
{
	int i = 0;
	int* pTemp;
	//array temporanea
	pTemp = (int*) malloc(sizeof(int)*(dim-1));
	//copia la prima parte
	for(i = 0; i < pos; i++)
		pTemp[i] = arr[i];
	//copia la seconda parte saltando POS
	for(; i < dim-1; i++)
		pTemp[i] = arr[i+1];

	//ricrea arr con la dimensione esatta
	free(arr);
	arr = (int*) malloc(sizeof(int)*(dim-1));
	for(i = 0; i < dim-1; i++)
		arr[i] = pTemp[i];
	free(pTemp);
	return arr;
}

void initArray (int arr[], int dim)
{
	int i = 0;
	for(; i < dim; i++)
		arr[i] = i;
}

void printArray (int arr[], int dim)
{
	int i = 0;

	printf("\n\t");
	for(i = 0; i < dim; i++)
		printf("[%d] ", i);
	printf("\n\t");
	for(i = 0; i < dim; i++)
		printf(" %d  ", arr[i]);
	printf("\n");
}
