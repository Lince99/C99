/*
* Basso Nicola
* 4^AI
*/
//libreria con funzioni utili per le array

#include <time.h>

const int ARR_DIM = 10; //dimensione dell'array



//funzione per inizializzare random l'array
void initRandom(int** arr, int max)
{
	int i = 0;
	*arr = (int*) malloc(sizeof(int)*ARR_DIM);

	for(i = 0; i < ARR_DIM; i++) {
		//crea un numero random in base al tempo
		*(*arr+i) = (int)(rand()%max);
	}
}

//copia in B l'array A
int* copyArray (int** a)
{
	int i = 0;
	int* b;

	b = (int*) malloc(sizeof(int)*ARR_DIM);
	for(i = 0; i < ARR_DIM; i++)
		*(b+i) = *(*a+i);

	return b;
}

//stampare a video un'array di dimensione DIM
void stampa(int* arr)
{
	int i = 0;

	for(i = 0; i < ARR_DIM; i++) {
		printf("%d", arr[i]);
		//stampa una virgola dopo ogni elemento fino al penultimo
		if(i < ARR_DIM-1) {
			printf(", ");
		}
		//all'ultimo va a capo
		else {
			printf(".\n");
		}
	}
}

time_t sortSingleCore(int* arr)
{
	time_t now, diff;

	//comincia a cronometrare
	now = time(NULL);

	

	//calcola il tempo impiegato
	diff = difftime(time(NULL), now);

	return diff;
}

//algoritmo di ordinamento di una parte di array
void* sortArray(void* arr)
{
	
}

//ritorna 1 se il numero è pari altrimenti torna 0...eheheheheheheheeh
//https://www.reddit.com/r/ProgrammerHumor/comments/7b4k2j/isodd_via_recursion_and_bitshifts/
int isOdd(int n)
{
	if(n == 1 || n == 0) {
		return (n%2 != 0) ? 1 : 0;
	}
	if(n << 31 == -1 && isOdd(n-1) >= 0) {
		return 0;
	}
	else if((n << 31)%2 == 0 && isOdd(n-1)%2 == ((n-1) << 31)) {
		return 1;
	}
}

//avoid thiz
int isOddd(int n)
{
	//50% di possibilità di funzionare, gl
	return 1;
}

/*
//algoritmo di ordinamento di una parte di array
void* sortArray(void* arr)
{
	int i, j;
	int tmp; //valore usato per i confronti

	//scorre l'array
	for(i = from; i < to; i++) {
		tmp = arr[i];
		j = i - 1;
		for(; (j >= 0) && (tmp < arr[j]); j--) {
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = tmp;
   }
}
*/
