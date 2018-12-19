#include <stdio.h>

int main (int argc, char** argv)
{
	int n_nodi = 0;
	int start = 0;
	int end = 0;
	int i = 0; //indice asse y
	int j = 0; //indice asse x
	int x = 0; //numero inserito dall'utente
	//chiedo il numero di nodi presenti nel grafo
	printf("Quanti nodi sono presenti nel grafo?\n");
	scanf("%d", &n_nodi);
	//creo la matrice di adiacenza
	int matrice[n_nodi][n_nodi];
	for(i = 0; i < n_nodi; i++)
	{
		for(j = 0; j < n_nodi; j++)
			matrice[i][j] = 0;
	}
	//chiedo per ogni nodo a cosa è collegato
	for(i = 0; i < n_nodi; i++)
	{
		printf("Il nodo %d è collegato:\n", i);
		for(j = 0; j < n_nodi; j++)
		{
			printf("\tal nodo %d? (n=0 = no, n>0 = si)-->", j);
			scanf("%d", &x);
			matrice[i][j] = x;
		}
	}
	//stampa di controllo
	for(i = 0; i < n_nodi; i++)
	{
		for(j = 0; j < n_nodi; j++)
			printf("%d ", matrice[i][j]);
		printf("\n");
	}
	//chiedo qual è il nodo di partenza e quello di arrivo
	printf("Qual è il nodo di partenza?\n-->");
	scanf("%d", &start);
	printf("E dove vuoi arrivare?\n-->");
	scanf("%d", &end);
	//chiedo quale algoritmo vuole applicare per la visita
	//bfs(matrice, start, end);
	//applico l'algoritmo e stampo il path più breve
	
	return 0;
}
