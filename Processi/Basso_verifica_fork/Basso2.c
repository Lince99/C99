/*
 * Basso Nicola
 * 4^AI
 * 7/12/2018
 */
/*
 * Creare un programma che permette ad un processo figlio 
 * di passare al fratello un array di n elementi (n costante), 
 * popolato da tastiera.
 * Il fratello raddoppierà gli elementi dell'array
 * mentre il padre stamperà a video gli elementi modificati.
 */

#include <stdio.h> //printf, scanf
#include <unistd.h> //fork
#include <stdlib.h> //exit
#include <sys/wait.h> //wait
#include <sys/types.h> //pid_t

//dimensione massima dell'array
#ifndef N
	#define N 10
#endif

//firme
void init_arr(int* arr);
void writePipe(int* pipefd, int* arr);
void readPipe(int* pipefd, int* arr);
void fillArr(int* arr);
void multiply(int* arr, int factor);
void printArr(int* arr);

int main(void) {
	int pipefd[2]; //0 lettura, 1 scrittura
	int arr[N];
	pid_t pid = 0;
	pid_t pidBro = 0;
	
	init_arr(arr);
	
	//creo pipe
	if(pipe(pipefd) == -1) {
		printf("Errore nel creare pipe!");
		return -1;
	}
	
	//creo 3 processi
	pid = fork();
	if(pid < 0) {
		printf("Errore nel creare il processo!\n");
		return -1;
	}
	//padre crea il fratello del primo processo
	else if(pid > 0) {
		pidBro = fork();
		if(pidBro < 0) {
			printf("Errore nel creare il processo!\n");
		}
		//sono nel fratello
		else if(pidBro == 0) {
			waitpid(pid, NULL, 0);
			//legge dalla pipe
			readPipe(pipefd, arr);
			//moltiplica gli elementi
			multiply(arr, 2);
			printf("Array moltiplicata:\n");
			printArr(arr);
			//passa al padre
			writePipe(pipefd, arr);
			
			return 0;
		}
		//sono il padre originale
		else {
			waitpid(pidBro, NULL, 0);
			//ricevo l'array modificata da pipe
			printf("Array letta:\n");
			readPipe(pipefd, arr);
			//stampo a video l'array finale
			printArr(arr);
		}
	}
	//figlio popola l'array e la passa al fratello
	else {
		//richiede i valori dell'array
		printf("Inserisci gli elementi dell'array:\n");
		fillArr(arr);
		//la passa tramite pipe
		writePipe(pipefd, arr);
		
		return 0;
	}
	
	return 0;
}



/*
 * procedura che semplicemente pulisce l'array a 0
 */
void init_arr(int* arr) {
	register int i = 0;
	
	for(; i < N; i++) {
		arr[i] = 0;
	}

}

/*
 * procedura che scrive l'array nel pipe
 */
void writePipe(int* pipefd, int* arr) {
	close(pipefd[0]);
	write(pipefd[1], arr, sizeof(int)*N);
	close(pipefd[1]);
}

/*
 * procedura che legge e aggiorna l'array dal pipe
 */
void readPipe(int* pipefd, int* arr) {
	close(pipefd[1]);
	read(pipefd[0], arr, sizeof(int)*N);
	close(pipefd[0]);
}

/*
 * procedura che richiede di inserire N elementi nell'array
 */
void fillArr(int* arr) {
	register int i = 0;

	for(; i < N; i++) {
		printf("%d elemento:\t", i+1);
		scanf("%d", &arr[i]);
	}

}

/*
 * procedura che moltiplica ogni elemento dell'array per factor
 */
void multiply(int* arr, int factor) {
	register int i = 0;

	for(; i < N; i++) {
		arr[i] *= factor;
	}

}

/*
 * procedura che visualizza a video il contenuto dell'array
 */
void printArr(int* arr) {
	register int i = 0;

	for(; i < N; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

}


