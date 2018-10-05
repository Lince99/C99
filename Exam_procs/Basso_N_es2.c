/*
 * Basso Nicola
 * 4^AI
 * 3/11/2017 
*/

//programma 2: ricerca di elemento su array con 2 processi

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

#define DIM 30 //dimensione dell'array

//dichiarazione funzioni
void initArray(int arr[], int max);
void stampaArray(int arr[]);
int trovaElem(int arr[], int start, int end, int elem);
int ricerca(int arr[], int elem);

int main(int argc, char **argv)
{
	srand(time(NULL));
	int arr[DIM];
	int elem = 0; //elemento da cercare
	int found = 0;

	//creazione array DIM interi casuali positivi (0-20)
	initArray(arr, 20);
	stampaArray(arr);
	//richiesta di un elemento
	printf("Inserisci l'elemento che vuoi cercare:\n--> ");
	scanf("%d", &elem);

	//stampe finali se i processi hanno trovato o no l'elemento
	found = ricerca(arr, elem);
	if(found == -1)
		printf("Elemento non trovato!\n");
	else
		printf("Elemento %d trovato alla posizione %d!\n", elem, found);

	return 0;
}



//inizializza l'array con numeri random da 0 a max
void initArray(int arr[], int max)
{
	int i;

	for(i = 0; i < DIM; i++)
		arr[i] = rand()%max;
}

//visualizza a video l'array
void stampaArray(int arr[])
{
	int i;

	for(i = 0; i < DIM; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

//trova nell'array passata l'elemento, se non lo trova ritorna -1
int trovaElem(int arr[], int start, int end, int elem)
{
	//scorre da start a end e non supera mai la dimensione totale
	for(; start < end && start < DIM; start++) {
		if(arr[start] == elem) //se lo trova ritorna la posizione
			return start;
	}

	return -1;
}

//usa 2 processi per trovare l'elemento (ritorna la posizione)
int ricerca(int arr[], int elem)
{
	pid_t pid;
	int pos = -1;

	//divisione array in 2 processi
	pid = fork();
	wait(0);
	if(pid == 0) { //il figlio prende la prima parte
		printf("FIGLIO: ");
		//se non è ancora stato trovato l'elemento lo cerca
		if(pos == -1)
			pos = trovaElem(arr, 0, (int)DIM/2, elem);
		else //se è già stato trovato esce
			exit(0);
	}
	else if(pid > 0) { //il padre prende la seconda parte
		printf("PADRE: ");
		//se il figlio non ha trovato nulla allora ci pensa il padre
		if(pos == -1)
			pos = trovaElem(arr, (int)DIM/2, DIM, elem);
		else //se è già stato trovato esce
			exit(0);
	}
	else {
		printf("ERRORE!\n");
		exit(1);
	}

	return pos;
}
