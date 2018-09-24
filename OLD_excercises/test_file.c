/*
* Basso Nicola
* 4^AI
* 13/10/2017
*/

//programma che testa l'incremento di una variabile da parte di più processi
//salvata in un file

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define nome_file "var.txt"

int main(int argc, char** argv)
{
	int p = 0; //pid dei processi
	int i = 0; //numero da leggere, incrementare e scrivere
	int n_proc = 0;
	FILE *fp; //puntatore del file

	//crea il file
	if ((fp = fopen(nome_file, "w+")) == NULL) {
		printf("Impossibile creare il file! Uscita...\n");
		return(1);
	}
	else {
		printf("File creato!\n");
		fprintf(fp, "%d", 0);
	}
	fclose(fp);
	/*
	if(fp = fopen(string,"mode")) == NULL)
		errore
	else
		//fscanf(fp, "%d", &i);
		fprintf(fp, "%d", i);
		if(!feof(fp)) //se ha superato la fine del file prevista
	fclose(fp); //chiude il file
	*/

	printf("Quanti processi vuoi creare?\n--> ");
	do {
		scanf("%d", &n_proc);
		if (n_proc <= 0)
			printf("Deve essere maggiore di 0!\n");
	} while (n_proc <= 0);

	//crea n_proc processi
	for (; n_proc > 0; n_proc--) {
		//esegue il fork e controlla il valore di return
		if ((p = fork()) < 0) {
			printf("Errore nel fork!\n");
			exit(1);
		}
		else if (p == 0) {
			//leggo dal file
			if ((fp = fopen(nome_file, "r")) == NULL) { //controllo all'apertura
				printf("Errore nel leggere il file!\n");
				exit(0);
			}
			else { //legge dal file la variabile
				if (fscanf(fp, "%d", &i) == 1) {//se riesce a leggere
					i = i + 1; //e la incrementa
					printf("Sono %d e ho incrementato la variabile (%d)\n", getpid(), i);
				}	
				else {
					printf("Impossibile leggere dal file!\n");
					exit(1);
				}
			}
			fclose(fp);
			//e la riscrivo sul file
			if ((fp = fopen(nome_file, "w")) == NULL) { //controllo all'apertura
				printf("Errore nello scrivere nel file!\n");
				exit(0);
			}
			else { //scrive la variabile
				fprintf(fp, "%d", i);
				printf("Variabile scritta!\n");
			}
			fclose(fp);
		}
		else
			printf("Sono %d\n", getpid());
	}

	return 0;
}
