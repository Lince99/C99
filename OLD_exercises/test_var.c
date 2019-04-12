/*
* Basso Nicola
* 4^AI
* 13/10/2017
*/

//programma che testa l'incremento di una variabile da parte di più processi

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	int p = 0; //pid dei processi
	int i = 0; //numero da incrementare
	int n_proc = 0;

	printf("Quanti processi vuoi creare?\n--> ");
	do {
		scanf("%d", &n_proc);
		if(n_proc <= 0)
			printf("Deve essere maggiore di 0!\n");
	} while(n_proc <= 0);

	//crea n_proc processi
	for(; n_proc > 0; n_proc--) {
		//esegue il fork e controlla il valore di return
		if((p = fork()) < 0) {
			printf("Errore nel fork!\n");
			exit(1);
		}
		else if(p == 0) {
			//incremento e stampo
			i = i + 1;
			printf("Sono %d e ho incrementato la variabile (%d)\n", getpid(), i);
		}
		else
			printf("Sono %d\n", getpid());
	}

	return 0;
}
