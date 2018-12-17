/*
* Basso Nicola
* 4^AI
*/
/*
* creare 2 thread, funzione uguale che somma un intero, 
* il valore sarà il parametro
* stampa ad ogni passaggio
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void*
somma(void* var);

int
main(void)
{
	pthread_t t1, t2;
	int var = 5;

	printf("1- var = %d\n", var);

	//creo il primo thread
	if(pthread_create(&t1, NULL, &somma, (void*) &var) < 0) {
		printf("Errore nel creare il thread 1!\n");
		exit(-1);
	}
	pthread_join(t1, 0);

	//creo il secondo thread con la somma del precedente
	printf("2- var = %d\n", var);
	if(pthread_create(&t2, NULL, &somma, (void*) &var) < 0) {
		printf("Errore nel creare il thread 2!\n");
		exit(-1);
	}
	//termina i thread prima del processo padre
	pthread_join(t2, 0);

	return 0;
}

void*
somma(void* var)
{
	int* sum = (int*) var;
	*sum += *sum;
	printf("Thread %ld- var = %d\n", pthread_self(), *sum);

	pthread_exit(NULL);
}
