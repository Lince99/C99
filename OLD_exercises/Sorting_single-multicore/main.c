/*
* Basso Nicola
* 4^AI
*/
/*
* ordinamento di un'array tramite thread
* con confronto
*/

//libreria per ottenere il numero di core disponibili con getCores()
#include "getCores.h"
#include "arrayUtils.h"



int main(void)
{
	int* arrSingle; //array ordinata singleCore
	int* arrMulti; //array ordinata multiCore
	int n_cores = 0; //numero di core
	
	srand(time(NULL)); //time(NULL) = tempo
	time_t tot_single; //tempo impiegato dal sort sequenziale
	time_t tot_multi; //tempo impiegato dal sort multithread

	//creazione array disordinata
	initRandom(&arrSingle, ARR_DIM); //numeri random da 0 a ARR_DIM
	arrMulti = copyArray(&arrSingle);

	printf("Array iniziale:\n");
	stampa(arrSingle);

	//richiesta al sistema operativo del numero di processori
	n_cores = getCores();

	//ordinamento sequenziale cronometrato
	
	//ordinamento multithread cronometrato

	//stampa risultati

	return 0;
}
