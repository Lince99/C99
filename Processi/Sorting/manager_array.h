/*
 * Basso Nicola
 * 4^AI
 * 26/10/2018
 */
/*
 * Libreria utile a gestire tutti gli aspetti delle array
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

//definizioni


// - - - - - - - - - - - FUNZIONI PER INIZIALIZZARE ARRAY - - - - - - - - - - //

/*
 * accetta un puntatore ad un'array di interi,
 * il numero massimo generabile dal random,
 * e la dimensione dell'array da allocare
 */
int* initRandom(int* arr, int min, int max, int dim) {
    int i;
    srand((unsigned) time(NULL));

    if( !(arr = (int*) malloc(sizeof(int)*dim)) ) {
        printf("Spazio Insufficiente per allocare l'array!\n");
        return NULL;
    }
    //ad ogni elemento viene assegnato un numero random in base al tempo
    for(i = 0; i < dim; i++) {
        *(arr+i) = min + (int)(rand()%max);
    }

    return arr;
}

int* initZeroes(int* arr, int dim) {

    if( !(arr = (int*) calloc(dim, sizeof(int))) ) {
        printf("Spazio Insufficiente per allocare l'array!\n");
        return NULL;
    }

    return arr;
}



// - - - - - - - - - - - - FUNZIONI PER ORDINARE ARRAY - - - - - - - - - - - -//
//fonte: https://it.wikibooks.org/wiki/Implementazioni_di_algoritmi

/*
 * funzione di ordinamento seguendo l'algoritmo del BUBBLE sort
 */

int* bubbleSort(int* arr, int dim) {
    int i = 0;
    int j = 0;
    int tmp = 0;

    for(i = 0; i < dim; i++) {
        for(j = 0; j < dim-i-1; j++) {
            //se l'elemento corrente e' maggiore allora effettua lo scambio
            if(*(arr+j) > *(arr+j+1)) {
                //caabbc
                tmp = *(arr+j);
                *(arr+j) = *(arr+j+1);
                *(arr+j+1) = tmp;
            }
        }
    }

    return arr;
}



/*
 * funzione di ordinamento seguendo l'algoritmo del SELECTION sort
 */

int* selectionSort(int* arr, int dim) {
    int i = 0;
    int j = 0;
    int min = 0;
    int minInd = 0;
    int tmp = 0;

    //cerca il numero minore nell'array per i*j volte
    for(i = 0; i < dim-1; i++) {
        min = *(arr+i);
        minInd = i;
        for(j = i+1; j < dim; j++) {
            if(*(arr+j) < min) {
                min = *(arr+j);
                minInd = j;
            }
        }
        *(arr+minInd) = *(arr+i);
        *(arr+i) = min;
    }
}

/*
 * funzione di ordinamento seguendo l'algoritmo del INSERTION sort
 */

int* insertionSort(int* arr, int dim) {
    int i = 0;
    int j = 0;
    int tmp = 0;

    for(i = 0; i < dim; i++) {
        tmp = *(arr+i);
        for(j = j-1; (j >= 0) && (tmp < *(arr+j)); j--) {
            *(arr+j+1) = *(arr+j);
        }
        *(arr+j+1) = tmp;
    }
}



/*
 * funzione di ordinamento seguendo l'algoritmo del MERGE sort
 */

int* mergeSort(int* arr, int dim) {
    return arr;
}



/*
 * funzione di ordinamento seguendo l'algoritmo del QUICK sort
 */

int* quickSort(int* arr, int dim) {

    return arr;
}



// - - - - - - - - - - - - - FUNZIONI SPECIFICHE - - -  - - - - - - - - - - - //

/*
 * scambio dei valori contenuti nei due puntatori
 */

/*
void excg(void* a, void* b) {
    void* tmp;

    //TODO
    *tmp = *a;
    *a = *b;
    *b = *tmp;
}*/


// - - - - - - - - - - - - - FUNZIONI PER LA STAMPA - - - - - - - - - - - - - //

/*
 * accetta un'array di interi e la sua dimensione
 * stampa in stdout l'array formattata in una sola riga
 * oltre gli 80 caratteri va a capo //TODO
 */
void printArr(int* arr, int dim) {
	int i;

	for(i = 0; i < dim; i++) {
		printf("%d", *(arr+i));
		//stampa una virgola dopo ogni elemento fino al penultimo
		if(i < dim-1) {
			printf(", ");
		}
		//all'ultimo valore va a capo
		else {
			printf(".\n");
		}
	}
}
