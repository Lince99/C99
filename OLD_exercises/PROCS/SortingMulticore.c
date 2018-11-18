/*
* Basso Nicola
* 4^AI
* 13/10/2017
*/
//merge sort multiprocesso a confronto con merge sort singolo processo

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DIM 50
#define MAX_PROCS 4

//richiede il numero di processi da eseguire (con controlli)
int input ();
//genera numeri random da 0 a max e li mette nell'array
void initRandom (int arr[], int max);
//stampa array
void stampa (int arr[]);
//copia in B l'array A
void copiaArray (int a[], int b[]);
//merge sort singleproc che restituisce il tempo d'esecuzione
time_t mergeSortSingle (int arr[]);
//void mergeSingle (int arr[], int left, int right, int end,int temp[]);
//merge sort multiprocesso che restituisce il tempo d'esecuzione
time_t mergeSortMulti (int arr[], int n_proc);

int main (int argc, char** argv)
{
	srand(time(NULL)); //time(NULL) = tempo
	time_t tot_single = 0; //tempo impiegato dal merge sort singleproc
	time_t tot_multi = 0; //tempo impiegato dal merge sort multiproc
	int n_proc = 0; //numero di processi
	int arr[DIM]; //1 processo
	int arrMulti[DIM]; //n_proc processi

	//chiedo all'utente di inserire il numero di processi
	n_proc = input();

	//inserimento dell'array di dimensione DIM con valori random
	initRandom(arr, 100);
	//inizializza a random l'array da ordinare
	copiaArray(arr, arrMulti);
	printf("Array di partenza:\n  ");
	stampa(arr);

	//mergesort singolo processo
	tot_single = mergeSortSingle(arr);
	tot_multi = mergeSortMulti(arrMulti, n_proc);
	printf("Array ordinata con 1 SOLO PROCESSO:\n  ");
	stampa(arr);
	printf("Array ordinata con %d PROCESSI:\n  ", n_proc);
	stampa(arrMulti);

	//mergesort multi processo crea max N processi definiti da MAX_PROCS
	//stampa i tempi
	printf("Tempo impiegato da:\n");
	printf("\tSINGOLO: %lld ms\n", (long long) tot_single);
	printf("\t%d PROCESSI: %lld ms\n", n_proc, (long long) tot_multi);
	return 0;
}

//funzione che richiede all'utente di inserire il numero di processi da
//usare e fa i controlli
int input ()
{
	int n = 0;
	printf("Inserisci il numero di processi che vuoi usare:\n--> ");
	do {
		scanf("%d", &n);
		if(n <= 0 || n > MAX_PROCS)
			printf("Numero non valido! (min = 1, max = %d", MAX_PROCS);
	} while(n <= 0 || n > MAX_PROCS);
	return n;
}

//crea un numero random in base al tempo
void initRandom (int arr[], int max)
{
	int i = 0;
	for(i = 0; i < DIM; i++)
		arr[i] = (int)(rand()%max);
}

//stampa a video un'array di dimensione DIM
void stampa (int arr[])
{
	int i = 0;
	for(i = 0; i < DIM; i++) {
		printf("%d", arr[i]);
		//fino al penultimo elemento stampa il divisore
		if(i < DIM-1)
			printf(" ");
	}
	printf("\n");
}

//copia in B l'array A
void copiaArray (int a[], int b[])
{
	int i = 0;
	for(i = 0; i < DIM; i++)
		b[i] = a[i];
}

//mergesort 1 processo
time_t mergeSortSingle (int arr[])
{
	//int lung = 0;
	//int i = 0;
	time_t diff;
	time_t now = time(NULL);

	/*
	//suddivide in array di dimensione = 2
	for(lung = 1; lung < DIM; lung = 2 * lung)
	{
		//richiama per i volte il merge
		for(i = 0; i < DIM; i = i + 2 * lung)
		{
			//unisce gli elementi di arr a 2 a 2 ordinandoli
			mergeSingle(arr, i, min(i+lung, DIM), 
						min(i+2*lung, DIM), temp);
		}
		//e ricopia temp in arr, ordinandola
		copiaArray(arr, temp);
	}
	*/
	//calcola il tempo impiegato
	diff = difftime(time(NULL), now);
	return diff;
}

/*
//ordina gli elementi da left a right
void mergeSingle (int arr[], int left, int right, int end, int temp[])
{
	int i = left;
	int j = right;
	int k = 0;
	//finchè ci sono elementi a destra e a sinistra
	for(k = left; k < end; k++) {
		//se l'elemento di sinistra è minore di quello di destra
		//allora lo assegna a temp
		if(i < right && (j >= end || arr[i] <= arr[j])) {
			temp[k] = arr[i];
			i = i + 1;
		}
		//altrimenti lo scambia nell'array temp
		else {
			temp[k] = arr[j];
			j = j + 1;
		}
	}
}
*/

time_t mergeSortMulti (int arr[], int n_proc)
{
	time_t diff;
	time_t now = time(NULL);
	//crea n_proc processi

	//calcola il tempo impiegato
	diff = difftime(time(NULL), now);
	return diff;
}
