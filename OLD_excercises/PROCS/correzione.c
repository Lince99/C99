/*
* Correzione verifica
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	pid_t a, b;
	a = fork();
	b = fork();

	if(a == 0)
	{
		if(b == 0)
			printf("1\n");
		else if(b > 0)
			printf("2\n");
		else
			printf("Errore!\n");
	}
	else if(a > 0)
	{
		if(b == 0)
			printf("3\n");
		else if(b > 0)
			printf("4\n");
		else
			printf("Errore!\n");
	}
	else
		printf("Errore!\n");
	return 0;
}
