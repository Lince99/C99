#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int i = 0;
	pid_t dad_pid;
	pid_t child_pid;
	pid_t son_pid;

	//for(i = 0; i < 2; i++) {
		//fork
		printf(" DAD ---Sono %d figlio di %d.\n", getpid(), getppid());
		dad_pid = fork();
		printf(" FORKED ---Sono %d figlio di %d.\n", getpid(), getppid());

		//errore
		if(dad_pid < 0) {
			printf("ERRORE!\n");
			return 0;
		}
		//sono il figlio
		else if(dad_pid == 0)
		{
			//fork2
			son_pid = fork();
			printf(" FIGLIO ---Sono %d figlio di %d.\n", getpid(), getppid());
			exit(0);
		}
		//sono il padre con almeno un figlio
		else
		{
			printf(" UNCLE-GRANPA ---Sono %d figlio di %d.\n", getpid(), getppid());
		}
		//fine 1 ciclo
		wait(NULL);
		sleep(1);
	//}
	printf("FINE\n");
	return 0;
}
