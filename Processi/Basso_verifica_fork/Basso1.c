/*
 * Basso Nicola
 * 4^AI
 * 7/12/2018
 */
/*
 * Generare due processi padre/figlio in cui:
 * - Il processo padre scrive la sequenza di caratteri [A-Z][a-z] 
 *   in un file di testo (aperto prima di eseguire la fork) 
 *   e successivamente chiude file creato.
 *   Nel file verrà scritta, 
 *   sulla riga successiva alla sequenza di caratteri, 
 *   il pid del processo che ha eseguito il lavoro.
 * - Il processo figlio stamperà video il contenuto 
 *   del file precedentemente gestito dal processo padre e vi apporrà, 
 *   su un ulteriore nuova linea, il proprio pid.
 */

#include <stdio.h> //printf, scanf
#include <unistd.h> //fork
#include <stdlib.h> //exit
#include <sys/wait.h> //wait
#include <sys/types.h> //pid_t

//dimensione massima del nome del file
#ifndef MAX_CHAR
	#define MAX_CHAR 64
#endif

//firme
void printToFile(FILE* fp);
int readFromFile(char* fileName);
void addPid(char* fileName, char* who);


int main(void) {
	FILE* fp = NULL;
	char fileName[MAX_CHAR];
	pid_t pid = 0;
	
	printf("Inserisci il nome del file dove vuoi salvare i dati:\n");
	scanf("%s", fileName);
	//creo il file
	if((fp = fopen(fileName, "w+")) < 0) {
		printf("Impossibile creare il file!\nUscita...\n");
		return -1;
	}
	
	//creo 2 processi
	pid = fork();
	if(pid < 0) {
		printf("Errore nel creare il processo!\n");
		return -1;
	}
	//padre scrive su file
	else if(pid > 0) {
		printToFile(fp);
		//aggiunta pid del padre al file
		addPid(fileName, "PADRE");
	}
	//figlio stampa a video il contenuto del file
	else {
		wait(NULL);
		if(readFromFile(fileName) < 0) {
			printf("Errore nella lettura dal processo figlio...\n");
			exit(-1);
		}
		//aggiunta pid del figlio al file
		addPid(fileName, "FIGLIO");
	}
	
	return 0;
}



/*
 * procedura che aggiunge l'alfabeto al file, 
 * richiede un puntatore a file gia' aperto
 */
void printToFile(FILE* fp) {
	int i = 0;

	//A-Z 65, 90
	for(i = 65; i < 90; i++) {
		fprintf(fp, "%c ", (char)i);
	}
	fprintf(fp, ", ");
	//a-z 97, 122
	for(i = 97; i < 122; i++) {
		fprintf(fp, "%c ", (char)i);
	}
	fprintf(fp, "\n");

	fclose(fp);
}

/*
 * procedura che legge ogni carattere presente nel file 
 * precedentemente chiuso
 */
int readFromFile(char* fileName) {
	FILE* fp = NULL;
	char readC = 0;

	//apre il file in lettura
	if((fp = fopen(fileName, "r")) < 0) {
		printf("Impossibile leggere il file!\nUscita...\n");
		return -1;
	}
	//legge ogni carattere
	while((readC = getc(fp)) != EOF)
		printf("%c", readC);

	fclose(fp);
	return 0;
}

/*
 * aggiunge il pid nel file
 */
void addPid(char* fileName, char* who) {
	FILE* fp = NULL;

	if((fp = fopen(fileName, "a")) < 0) {
		printf("Impossibile appendersi il file!\nUscita...\n");
		exit(-1);
	}
	fprintf(fp, "PID %s = %d\n", who, getpid());

	fclose(fp);
}
