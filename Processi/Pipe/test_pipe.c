/*
 * Basso Nicola
 * 4^AI
 */
/*
 * programma di test delle funzionalita' dei pipe
 */

#include <stdio.h>
#include "./lib/colors.h"
#include "./lib/manager_process.h"
#include "./lib/input_check.h"

int main(int argc, char** argv) {
	int fd[2]; //0 = read, 1 = write
	pid_t pid = 0;
	int a = 0;
	int b = 0;
	int c = 0;
	double ris = 0;
	
	printf(ANSI_BG_BLUE "    (a+b) " ANSI_RESET "\n"
		   ANSI_BG_BLUE "y =-------" ANSI_RESET "\n"
		   ANSI_BG_BLUE "    (b*c) " ANSI_RESET "\n");
	/* - - - - - - - - - - - RICHIESTA DATI - - - - - - - - - - - - - */
	printf(ANSI_BLUE "Inserisci il valore di a:" ANSI_RESET "\n");
	getInt(&a);
	printf(ANSI_CYAN "Inserisci il valore di b:" ANSI_RESET "\n");
	getInt(&b);
	printf(ANSI_BLUE "Inserisci il valore di c:" ANSI_RESET "\n");
	getInt(&c);
	
	/* - - - - - - - - CREAZIONE PROCESSI E PIPE - - - - - - - - - - -*/
	//creazione della pipe
	if(pipe(fd) == -1) {
		perror(ANSI_RED "Errore nel pipe!" ANSI_RESET "\n");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if(pid < 0) {
		perror(ANSI_RED "Errore nel fork!" ANSI_RESET "\n");
		exit(EXIT_FAILURE);
	}
	/* - - - - - - - - - - - ESEGUE OPERAZIONI - - - - - - - - - - - -*/
	//il figlio esegue i calcoli
	else if(pid == 0) {
		ris = (double)b*c;
		//e scrive il risultato nella pipe
		close(fd[0]); //chiude il read
		write(fd[1], &ris, sizeof(double)); //scrive nella pipe
		close(fd[1]); //chiude la scrittura
		exit(EXIT_SUCCESS);
	}
	//il padre riceve il risulato ed esegue la divisione
	else {
		close(fd[1]); //chiude la scrittura
		//legge dalla pipe
		if(read(fd[0], &ris, sizeof(double)) <= 0)
			printf(ANSI_YELLOW "Nessun valore letto dalla pipe!" 
				   ANSI_RESET "\n");
		close(fd[0]); //chiude la lettura
		/* - - - - - - - - - - STAMPA RISULTATO - - - - - - - - - - - */
		if(ris == 0)
			printf(ANSI_RED "Numero diviso 0!" ANSI_RESET "\n");
		else {
			ris = (double) (a+b)/ris;
			printf(ANSI_GREEN "Risultato = %f" ANSI_RESET "\n", ris);
		}
	}
	
	return 0;
}
