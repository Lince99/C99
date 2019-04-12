/*
 * Basso Nicola
 * 4^AI
 */
/*
 * prove varie con la creazione e il passaggio di parametri ai thread
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>
#include "lib/colors.h"
#include "lib/input_check.h"


//numero massimo di thread generabili
#ifndef MAX_THREAD
	#define MAX_THREAD 100
#endif

//struttura dati con variabili senza alcuno scopo utile
typedef struct DATI dati;

struct DATI {
	int a;
	int b;
	float c;
};

//firme
int init_dati(dati** things, int size);
void* routine(void* arg);



int main(int argc, char** argv) {
	pthread_t* ts = NULL;
	dati* things = NULL;
	int size = 0;
	int i = 0;
	
	//inizializzo i dati della struttura
	printf(ANSI_GREEN "Quanti dati vuoi modificare?" ANSI_RESET "\n");
	getLimitInt(&size, 0, MAX_THREAD);
	if(init_dati(&things, size)) {
		printf(ANSI_RED "Errore nell'inizializzare i dati!"
			   ANSI_RESET "\n");
		return 1;
	}
	//inizializzo l'array di thread
	if( (ts = (pthread_t*) malloc(sizeof(pthread_t)*size)) == NULL) {
		printf(ANSI_RED "Errore nell'allocazione dei thread!" 
			   ANSI_RESET "\n");
		return 1;
	}
	for(; i < size; i++) {
		//passo a size thread una struttura da modificare ognuno
		if(pthread_create(&ts[i], NULL, &routine, (void*) ts[i])) {
			printf(ANSI_RED "Errore nella creazione del thread %d!" 
			   ANSI_RESET "\n", i);
			return 1;
		}
		//e per ognuno, un thread in attesa stampa tutti i dati
		
	}
	
	//libera la memoria
		free(things);
		free(ts);
	
	return 0;
}



/*
 * funzione che inizializza i dati a 0 e ritorna 1 in caso di errore
 */
int init_dati(dati** things, int size) {
	int i = 0;
	
	if(!size) {
		printf(ANSI_YELLOW "Dimensione non valida!" ANSI_RESET "\n");
		return 1;
	}
	//prova ad allocare
	if( (*things = (dati*) malloc(sizeof(dati)*size)) == NULL) {
		printf(ANSI_RED "Errore nell'allocazione dei dati!" 
			   ANSI_RESET "\n");
		return 1;
	}
	//inizializza tutto a 0
	for(; i < size; i++) {
		(*things)->a = 0;
		(*things)->b = 0;
		(*things)->c = 0;
	}
	
	return 0;
}

/*
 * funzione che modifica i valori della struttura
 */
void* routine(void* arg) {
	//TODO stampa tid
	printf(ANSI_BLUE "Sono il thread %d" ANSI_RESET "\n", 
		   syscall(SYS_gettid));
	
	pthread_exit(NULL);
}
