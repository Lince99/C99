/*
 * Basso Nicola
 * 4^AI
 * 3/11/2017 
 */

//programma 1: operazioni su float con processi

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	float a = 0;
	float b = 0;
	pid_t prod, diff, sum;

	//input di 2 valori
	printf("Inserire due valori:\n");
	printf("A = ");
	scanf("%f", &a);
	printf("B = ");
	scanf("%f", &b);

	//creo 4 processi (/ * - +)
	/*                   |
	           .-----divisione------.
	           |                    |
	  .---divisione---.      .---prodotto---.
	  |               |      |              |
	divisione  differenza   prodotto      somma
	*/
	prod = fork();
	wait(0); //ordino le stampe

	if(prod == 0) { //prodotto
		printf("Sono il processo %d il prodotto tra %f e %f : %f\n", 
				getpid(), a, b, a*b);

		diff = fork();
		if(diff == 0) //differenza
			printf("Sono il processo %d la differenza tra %f e %f : %f\n",
				getpid(), a, b, a-b);
		else if(diff > 0)
			exit(0);
		else {
			printf("ERRORE!\n");
			exit(1);
		}
	}
	else if(prod > 0) { //divisione
		if(b == 0)
			printf("Divisione per 0!\n");
		else
			printf("Sono il processo %d la divisione tra %f e %f: %f\n", 
				getpid(), a, b, a/b);

		sum = fork();
		if(sum == 0) //somma
			printf("Sono il processo %d la somma tra %f e %f : %f\n", 
				getpid(), a, b, a+b);
		else if(sum > 0)
			exit(0);
		else {
			printf("ERRORE!\n");
			exit(1);
		}
	}
	else {
		printf("ERRORE!\n");
		exit(1);
	}

	return 0;
}

