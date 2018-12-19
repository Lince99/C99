/*
* Basso Nicola
* 4^AI
* 27/10/2017
*/

//sorting multiprocesso con vari algoritmi di ordinamento

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DIM 50 //dimensione fissa dell'array
#define MAX_PROCS 4 //numero massimo di processi
#define NOME_FILE "array.txt" //nome del file contenente l'array

//genera numeri random da 0 a max e li mette nell'array
void initRandom (int arr[], int max);
//scrive l'array nel file
void scriviFile (int a[]);
//stampa il contenuto del file
void stampaFile ();
//richiede il numero di processi da eseguire (con controlli)
int input ();
//ordinamento dell'array nel file
void sort(int start, int end);

int main (int argc, char** argv)
{
	//crea l'array di dimensione DIM
	int arr[DIM];
	//la inizializza con numeri random
	initRandom(arr, 100);
	// e la scrive sul file
	scriviFile(arr);
	//per controllo rilegge dal file
	stampaFile();

	//chiedo il numero di processi da usare
	int n_proc = 0;
	n_proc = input();

	//suddivide l'array
	int div = 0;
	int resto = 0;
	int flag = 0;
	div = (int) (DIM / n_proc);
	//parte restante dell'array accodata all'ultimo processo
	resto = DIM - (div * n_proc);
	if(resto > 0)
		flag = 1;

	//crea n_proc processi
	pid_t lista_array[n_proc];
	int i = 0;
	int pos = 0;

	//crea n_proc processi
	while(i < n_proc) {
		//controllo nella creazione dei fork
		if((lista_array[i] = fork()) < 0) {
			printf("Errore nel creare un fork!\n");
			exit(1);
		}
		else if(lista_array[i] == 0) {
			//se è l'ultimo processo e c'è una parte restante se ne occupa
			if(flag && i == n_proc-1)
				div += resto;
			if(div > 1) //se ha qualcosa da ordinare
				sort(pos, div -1); //ordina da 0 a A, da A a B, ....
			pos += div; //sposta la posizione
			exit(0);
		}
		else //il padre riordina l'array finale
			sort(0, DIM);
		i++;
	}

	//stampa l'array ordinata
	printf("Array ordinata:\n\t");
	stampaFile();

	return 0;
}



//crea un numero random in base al tempo
void initRandom (int arr[], int max)
{
	int i = 0;
	for(i = 0; i < DIM; i++)
		arr[i] = (int)(rand()%max);
}

//scrive sul file l'array
void scriviFile (int a[])
{
	FILE *fp; //puntatore al file
	int i = 0;

	//crea il file
	if ((fp = fopen(NOME_FILE, "w+")) == NULL)
	{
		printf("Impossibile aprire il file!\n");
		exit(1);
	}
	//salva l'array nel file
	for(i = 0; i < DIM; i++)
		fprintf(fp, "%d ", a[i]);
	fclose(fp);
}

//stampa il contenuto del file
void stampaFile ()
{
	FILE *fp;
	//apre il file
	if ((fp = fopen(NOME_FILE, "r")) == NULL)
	{
		printf("Impossibile aprire il file!\n");
		exit(1);
	}
	//e stampa
	char c;
	while(1) {
		c = fgetc(fp);
		if(feof(fp))
			break;
		printf("%c", c);
	}
	fclose(fp);

	printf("\n");
}

//richiede il numero di processi
int input ()
{
	int n = 0;
	printf("Inserisci il numero di processi che vuoi usare:\n--> ");
	do {
		scanf("%d", &n);
		if(n <= 0 || n > MAX_PROCS)
			printf("Numero non valido! (min = 1, max = %d)\n--> ", MAX_PROCS);
	} while(n <= 0 || n > MAX_PROCS);
	return n;
}

//applica il sorting all'array salvata nel file da start a end
void sort(int start, int end)
{
}
