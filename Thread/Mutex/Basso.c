/*
 * Basso Nicola
 * 4^AI
 * 19/02/19
 * Verifica sui thread in C
 */
/*
 * Sfruttare i thread per ordinare un array [1] di dimensione qualsiasi 
 * in modo concorrente.
 * [ ] OPZIONE 1 (voto max 8) : utilizzare due thread. [2]
 * [x] OPZIONE 2 (voto max 10): il numero di thread da impiegare sarà 
 * 								deciso dall'utente. [4]
 * L'array verrà popolato con elementi casuali interi positivi [1] 
 * e dovranno essere fatte le opportune stampe [1]
 * per verificare il corretto funzionamento del programma.
 * Come al solito verranno valutati la puntualità, 
 * il rispetto della consegna, l'indentazione e i commenti [1], 
 * l'uso dei sottoprogrammi;
 * come al solito prestare attenzione agli errori 
 * e ai casi particolari [1].
 * Consegnare il file ProprioCognome.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <limits.h>
#include <string.h>

//numero massimo di caratteri inseribili dall'utente per riga
#ifndef MAX_CHAR
	#define MAX_CHAR 50
#endif

#ifndef MAX_RAND_INT
	#define MAX_RAND_INT 100
#endif

pthread_mutex_t mutex;

//struttura di appoggio per i parametri da passare ai singoli thread
typedef struct PARAMSTHREAD paramsThread;
struct PARAMSTHREAD {
	int* arr;
	int dim;
	int round;
};

//firme
int* sortArr(int* arr, int dim, pthread_t* ts, int n_thread);
void* ordinaPart(void* arg);
void printArr(int* arr, int dim);
int* initRandom(int size, int max);
int getInt();



int main(int argc, char** argv) {
	srand(time(NULL));
	int* arr = NULL;
	int dim = 0;
	int n_thread = 0;
	pthread_t* ts = NULL;
	
	//richiede la dimensione dell'array
	printf("Inserisci la dimensione dell'array da ordinare:\n");
	dim = getInt();
	//inizializza a random l'array
	arr = initRandom(dim, MAX_RAND_INT);
	//stampa l'array disordinata
	printf("- - - Array disordinata - - -\n");
	printArr(arr, dim);
	//chiede il numero di thread da utilizzare per ordinare
	printf("Quanti thread vuoi utilizzare per l'ordinamento?\n");
	n_thread = getInt();
	//crea i thread
	ts = (pthread_t*) malloc(sizeof(pthread_t)*n_thread);
	if(ts == NULL) {
		perror("Impossibile continuare senza thread!\n");
		return 1;
	}
	//ordina l'array con n_thread
	arr = sortArr(arr, dim, ts, n_thread);
	//stampa l'array ordinata
	printf("- - - Array ordinata - - -\n");
	printArr(arr, dim);

	return 0;
}

int* sortArr(int* arr, int dim, pthread_t* ts, int n_thread) {
	int i = 0;
	int j = 0;
	int check = 0;
	paramsThread* params;
	
	params = (paramsThread*) malloc(sizeof(paramsThread));
	//controllo generico
	if(ts == NULL || arr == NULL || dim == 0 || 
	   n_thread == 0 || params == NULL)
		return NULL;
	//salvo i dati per i parametri del thread
	params->arr = arr;
	params->dim = dim;
	
	//per ogni thread esegue l'ordinamento bubble sort
	for(; i < n_thread; i++) {
		params->round = i;
		for(j = 0; j < dim; i++) {
			check = pthread_create(&ts[i], NULL, 
								   &ordinaPart, (void*)params);
			if(check != 0) {
				perror("Errore nel creare il thread!");
				return NULL;
			}
		}
		pthread_join(ts[i], (void*)arr);
	}
	
	return arr;
}

/*
 * procedura usata dal thread per ordinare un solo giro dell'array
 */
void* ordinaPart(void* arg) {
	//riceve i parametri dalla struttura
	paramsThread* params = (paramsThread*)arg;
	int* arr = params->arr;
	int dim = params->dim;
	int i = params->round; //ciclo superiore del bubble sort
	int j = 0;
	int tmp = 0;
	
	for(j = 0; j < dim-i-1; j++) {
		//la lettura e lo scambio sono la sezione critica
		pthread_mutex_lock(&mutex);
		//se l'elemento corrente e' maggiore allora scambia
		if(*(arr+j) > *(arr+j+1)) {
			tmp = *(arr+j);
			*(arr+j) = *(arr+j+1);
			*(arr+j+1) = tmp;
		}
		pthread_mutex_unlock(&mutex);
	}
	
	pthread_exit((void*)arr);
}

/*
 * funzione che stampa il contenuto dell'array
 */
void printArr(int* arr, int dim) {
	int i = 0;
	
	for(; i < dim; i++) {
		printf("%d", arr[i]);
		if(i == dim-1)
			printf(".\n");
		else
			printf(", ");
	}

}

/*
 * funzione alloca e inizializza a random un'array di size interi
 * con il valore massimo passato da parametro
 */
int* initRandom(int size, int max) {
	int* arr = NULL;
	int i = 0;
	
	if(size <= 0)
		return NULL;
	arr = (int*) malloc(sizeof(int)*size);
	if(arr == NULL) {
		perror("Impossibile allocare l'array!\n");
		return NULL;
	}
	for(; i < size; i++) {
		arr[i] = rand()%max;
	}
	
	return arr;
}

/*
 * funzione che chiede all'utente un intero, con relativi controlli 
 */
int getInt() {
	int n = 0;
	int valid = 0;
	
	do {
		printf("->");
		valid = scanf("%d", &n);
		if(valid == EOF)
			valid = 0;
		if(n <= 0) {
			printf("-Numero inserito non valido! Deve essere > 0!");
			valid = 0;
		}
	} while(!valid);
	
	return n;
}
