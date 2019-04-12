/*
 * Basso Nicola
 * 4^AI
 */
/*
 * utilizzo del mutex in un esempio
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include "lib/colors.h"
#include "lib/input_check.h"

//numero massimo di thread generabili
#ifndef MAX_THREAD
	#define MAX_THREAD 100
#endif

#define N_CARICHI_OP 10
#define MAX_PESO_OP 20
#define MAX_PESO_CARICO 100

pthread_mutex_t mutex;

void* fill(void* arg);

int main(int argc, char** argv) {
	srand(time(NULL));
	pthread_t* operai = NULL;
	int peso = 0;
	int n_operai = 0;
	int i = 0;
	
	//chiedo il numero di lavoratori presenti nell'area carico
	printf(ANSI_GREEN "Quanti operai ci sono?" ANSI_RESET "\n");
	getLimitInt(&n_operai, 0, MAX_THREAD);
	//inizializzo l'array di thread
	ts = (pthread_t*) malloc(sizeof(pthread_t)*n_operai);
	if(ts == NULL) {
		printf(ANSI_RED "Errore nell'allocazione dei thread!" 
			   ANSI_RESET "\n");
		return 1;
	}
	//usa i thread per incrementare il peso
	for(i = 0; i < n_operai; i++) {
		if(pthread_create(&ts[i], NULL, &fill, (void*) n_operai)) {
			printf(ANSI_RED "Errore nella creazione del thread %d!" 
			   ANSI_RESET "\n", i);
			return 1;
		}
		pthread_join(ts[i], (int*) peso);
	}

	return 0;
}


void* fill(void* arg) {
	int* peso = (int*) arg;
	int i = 0;
	int gen = 0;
	
	for(i = 0; i < N_CARICHI_OP; i++) {
		do {
			gen = 1+rand()%(MAX_PESO_OP-1);
		} while((*peso+gen) >= MAX_PESO_CARICO);
		//sezione critica
		pthread_mutex_lock(&mutex);
		peso += gen;
		pthread_mutex_unlock(&mutex);
		printf("Caricato %d\n", *peso);
	}
	
	pthread_exit((void*) peso);
}
