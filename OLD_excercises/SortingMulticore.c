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
time_t mergeSortSingle (int arr[], int temp[]);
void mergeSingle (int arr[], int left, int right, int end,int temp[]);

int main (int argc, char** argv)
{
	srand(time(NULL)); //time(NULL) = tempo
	int i = 0;
	time_t tot_single; //tempo impiegato dal merge sort singleproc
	time_t tot_multi; //tempo impiegato dal merge sort multiproc
	int arr[DIM]; //1 processo
	int arrTemp[DIM]; //array di supporto
	int n_proc = 0; //numero di processi

	//chiedo all'utente di inserire il numero di processi
	n_proc = input();

	//inserimento dell'array di dimensione DIM con valori random
	initRandom(arr, 100);
	//inizializza a random l'array da ordinare
	//copiaArray(arr, arrTemp);
	printf("Array di partenza:\n  ");
	stampa(arr);

	//mergesort singolo processo
	tot_single = mergeSortSingle(arr, arrTemp);
	//tot_multi = mergeSortMulti(arr, n_proc);
	printf("Array ordinata SINGLECORE:\n  ");
	stampa(arr);

	//mergesort multi processo crea max N processi definiti da MAX_PROCS
	//stampa i tempi
	printf("%lld\n", (long long) tot_single);
	return 0;
}

//richiede il numero di processi
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

//stampare a video un'array di dimensione DIM
void stampa (int arr[])
{
	int i = 0;
	for(i = 0; i < DIM; i++) {
		printf("%d", arr[i]);
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
time_t mergeSortSingle (int arr[], int temp[])
{
	int lung = 0;
	int i = 0;
	time_t diff;
	time_t now = time(NULL);
	//suddivide in array di dimensione = 2
	for(lung = 1; lung < DIM; lung = 2 * lung)
	{
		//richiama per i volte il merge
		for(i = 0; i < DIM; i = i + 2 * lung)
		{
			//unisce gli elementi di arr a 2 a 2 ordinandoli
			mergeSingle(arr, i, i+lung < DIM ? i+lung : DIM, 
					i+2*lung < DIM ? i+2*lung : DIM, temp);
		}
		//e ricopia temp in arr, ordinandola
		copiaArray(arr, temp);
	}
	//calcola il tempo impiegato
	diff = difftime(time(NULL), now);
	return diff;
}


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

