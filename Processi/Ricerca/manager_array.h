/*
 * Basso Nicola
 * 4^AI
 * 26/10/2018
 */
/*
 * Libreria utile a gestire tutti gli aspetti delle array
 */

#include <stdio.h> //printf
#include <stdlib.h> //random
#include <time.h> //random
#include "colors.h" //print colors

//firme
int* newArr(int* arr, int dim);
int* newArrZeroes(int* arr, int dim);
int* initRand(int* arr, int min, int max, int dim);
int* initExcludeRand(int* arr, int dim, int min, int max, int exc);
int* initLimitRand(int* arr, int dim, int min, int max, int flag);

int* bubbleSort(int* arr, int dim);
int* selectionSort(int* arr, int dim);
int* insertionSort(int* arr, int dim);

int searchElem(int* arr, int start, int end, int x);
int searchPrintElem(int* arr, int start, int end, int x);

int addElem(int** arr, int dim, int x);
void printArr(int* arr, int dim);



// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
// - - - - - - - - - - - FUNZIONI PER INIZIALIZZARE ARRAY - - - - - - - - - - //
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -//

/*
 * funzione che alloca un'array data la sua dimensione
 * con tutti i valori a 0 e ritorna il suo nuovo puntatore
 * params: puntatore dell'array da allocare
 *         la dimensione dell'array
 * return: il nuovo puntatore all'array
 */
int* newArr(int* arr, int dim) {

    if(!(arr = (int*)calloc(dim, sizeof(int))) ) {
        printf(ANSI_RED "Impossibile allocare l'array!\n" ANSI_RESET);
        return NULL;
    }

    return arr;
}

/*
 * alloca e inizializza un'array a 0
 * params: puntatore dell'array da allocare
 *         la dimensione dell'array
 * return: il nuovo puntatore all'array
 */
int* newArrZeroes(int* arr, int dim) {

    if( !(arr = (int*) calloc(dim, sizeof(int))) ) {
        printf(ANSI_RED "Spazio Insufficiente per allocare l'array!\n"
               ANSI_RESET);
        return NULL;
    }

    return arr;
}

/*
 * accetta un puntatore ad un'array di interi,
 * il numero massimo generabile dal random,
 * e la dimensione dell'array da allocare
 * params: puntatore dell'array da allocare
 *         il valore minimo da genarare
 *         il valore massimo generabile
 *         la dimensione dell'array
 * return: il nuovo puntatore all'array
 */
int* initRand(int* arr, int min, int max, int dim) {
    int i = 0;
    srand((unsigned) time(NULL));

    if( !(arr = (int*) malloc(sizeof(int)*dim)) ) {
        printf(ANSI_RED "Spazio Insufficiente per allocare l'array!\n"
               ANSI_RESET);
        return NULL;
    }
    //ad ogni elemento viene assegnato un numero random in base al tempo
    for(i = 0; i < dim; i++) {
        *(arr+i) = min + (int)(rand()%max);
    }

    return arr;
}

/*
 * funzione che inizializza con dei valori random l'array, tranne il
 * valore passato per parametro che non verra' mai inserito
 * params: puntatore dell'array da allocare
 *         la dimensione dell'array
 *         il valore minimo da genarare
 *         il valore massimo generabile
 *         il valore da escludere
 * return: il nuovo puntatore all'array
 */
int* initExcludeRand(int* arr, int dim, int min, int max, int exc) {
    int i = 0;
    int gen = 0;
    srand((unsigned) time(NULL));

    if( !(arr = (int*) malloc(sizeof(int)*dim)) ) {
        printf(ANSI_RED "Spazio Insufficiente per allocare l'array!\n"
               ANSI_RESET);
        return NULL;
    }
    //ad ogni elemento viene assegnato un numero random in base al tempo
    for(i = 0; i < dim; i++) {
		//controllato per evitare di includere il valore non desiderato
		do {
			gen = (int)(rand()%max);
		} while(gen != exc);
        *(arr+i) = min + gen;
    }

    return arr;
}

/*
 * funzione che imposta i valori dell'array in valori random dati i due estremi,
 * se flag = 1 allora evita di ripetere i numeri
 * params: puntatore dell'array da allocare
 *         la dimensione dell'array
 *         il valore minimo da genarare
 *         il valore massimo generabile
 * return: il nuovo puntatore all'array
 */
int* initLimitRand(int* arr, int dim, int min, int max, int flag) {
    int i = 0;
    int gen = 0;
    int isPresent = 0; //flag di controllo se esiste gia' il numero
    int excZero = 0; //flag per escludere lo zero dalla ricerca
    srand((unsigned) time(NULL));

    for(i = 0; i < dim; i++) {
        /* per evirare il ripetersi dei valori generati allora deve essere
         * rispettata la condizione che il massimo meno il minimo
         * deve risultare minore della dimensione dell'array
         */
        if(flag && ((max-min) < dim) ) {
            do {
                isPresent = 0;
                gen = min+( (int)rand()%(max-min+1) );
                //esclude man mano gli estremi per velocizzare la generazione
                if(gen == max)
                    max--;
                if(gen == min)
                    min++;
                //accetta lo zero 1 sola volta
                //poiche' tutta l'array e' inizializzata a 0
                if(gen == 0)
                    excZero = 1;
                else if(searchElem(arr, 0, dim, gen) != -1)
                    isPresent = 1;
            } while(isPresent);
        }
        //altrimenti crea numeri random ripetuti
        else {
            //numero random da min a max
            gen = min+( (int)rand()%(max-min) );
        }
        *(arr+i) = gen;
    }

    return arr;
}



// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
// - - - - - - - - - - - - FUNZIONI PER ORDINARE ARRAY - - - - - - - - - - - -//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
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

    return arr;
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

    return arr;
}

/*
 * funzione di ordinamento seguendo l'algoritmo del MERGE sort
 */
/*TODO
int* mergeSort(int* arr, int dim) {
    return arr;
}*/

/*
 * funzione di ordinamento seguendo l'algoritmo del QUICK sort
 */
/*TODO
int* quickSort(int* arr, int dim) {

    return arr;
}*/


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
// - - - - - - - - - - - FUNZIONI PER RICERCA DI ELEMENTI - - - - - - - - - - //
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -//


/*
 * funzione di ricerca lineare in una porzione di array
 * params: puntatore all'array in cui ricercare
 *         posizione iniziale da dove cercare
 *         posizione finale dove fermarsi
 *         valore da cercare
 * return: int della prima posizione dell'elemento
 */
/*TODO
int* searchPosElem(int* arr, int start, int end, int x) {
	int* found = NULL; //array di elementi trovati
	int dimFound = 0;
	int i = 0;

	if(end > start) {
		//scorre l'array dal punto iniziale a quello finale indicati
		//POTREBBE DARE SEGMENTATION FAULT! TODO risolvere
		for(i = start; i < end; i++) {
			if(*(arr+i) == x) {
				//aggiunge l'elemento all'array dei risultati
				dimFound = addElem(&found, end-start, i);
			}
		}
	}

	addElemStart(&found, dimFound, dimFound);

	return found;
}*/

/*
 * funzione che ritorna la posizione del primo elemento
 * trovato nella parte di array
 */
int searchElem(int* arr, int start, int end, int x) {

	if(end > start) {
		//scorre l'array dal punto iniziale a quello finale indicati
		for(; start < end; start++) {
            //POTREBBE DARE SEGMENTATION FAULT! TODO risolvere
			if(*(arr+start) == x)
                return start;
		}
	}

	//se non trova nulla ritorna l'indice -1
	return -1;
}

/*
 * funzione che stampa ogni corrispondenza trovata
 * e ritorna 1 se ha trovato qualcosa, 0 se non ha trovato nulla
 */
int searchPrintElem(int* arr, int start, int end, int x) {
    int found = 0;

	if(end > start) {
		//scorre l'array dal punto iniziale a quello finale indicati
		for(; start < end; start++) {
            //POTREBBE DARE SEGMENTATION FAULT! TODO risolvere
			if(*(arr+start) == x) {
                printf(ANSI_GREEN "Elemento %d trovato in posizione %d\n"
                       ANSI_RESET, x, start);
				found = 1;
			}
		}
	}

	return found;
}



// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
// - - - - - - - - - - - - - FUNZIONI SPECIFICHE - - -  - - - - - - - - - - - //
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -//

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

/*
 * aggiunge un elemento ad un'array ritornando la nuova dimensione
 */
int addElem(int** arr, int dim, int x) {

    //incrementa la dimensione di 1
    dim++;
    //realloca la memoria per aggiungergli il valore x
	*arr = (int*)realloc(*arr, dim);
	*(*(arr+dim-1)) = x;

    return dim;
}



// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
// - - - - - - - - - - - - - FUNZIONI PER LA STAMPA - - - - - - - - - - - - - //
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -//

/*
 * accetta un'array di interi e la sua dimensione
 * stampa in stdout l'array formattata in una sola riga
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

/*
 * dato un'array e la sua dimensione
 * stampa in stdout l'array formattata
 * e oltre gli 80 caratteri va a capo
 */
 /*TODO
void printLimitArr(int* arr, int dim, int colMax) {
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
*/
