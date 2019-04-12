/*
 * Basso Nicola
 * 4^AI
 * 05/01/2019
 */

/* test di strutture dinamiche : coda LIFO */



#include <stdio.h>
#include <stdlib.h>

typedef struct Tail Lifo;

struct Tail {
	int val; //valore salvato
	Lifo* next; //prossimo elemento della coda
};

//dichiarazione delle funzioni
//restituisce il puntatore all'ultimo elemento della coda
Lifo* push (Lifo* first, int val);
//elimina il primo elemento della coda
Lifo* pop (Lifo* first);
//stampa tutta la coda
void printLifo (Lifo* first);

int main(int argc, char **argv)
{
	Lifo* coda = NULL; //coda vuota
	printFifo(coda);
	coda = push(coda, 1);
	printFifo(coda);
	coda = push(coda, 2);
	printFifo(coda);
	coda = push(coda, 4);
	coda = push(coda, 4);
	coda = push(coda, 4);
	coda = push(coda, 4);
	printFifo(coda);
	coda = pop(coda);
	printFifo(coda);
	coda = pop(coda);
	printFifo(coda);
	coda = pop(coda);
	printFifo(coda);
	coda = pop(coda);
	coda = pop(coda);
	coda = pop(coda);
	coda = pop(coda);
	return 0;
}



//inserisce un elemento all'ultima posizione
Lifo* push (Lifo* first, int val)
{
	Lifo* new;
	//alloca la dimensione della struttura (int + puntatore)
	if((new = (Lifo*) malloc(sizeof(Lifo))) == NULL) {
		printf("Errore nell'allocare!\n");
		exit(1);
	}
	//assegna val
	new->val = val;
	//mette in coda il nuovo elemento
	new->next = first;
	//e sposta il puntatore all'ultimo
	first = new;
	//ritorna il nuovo puntatore della coda
	return first;
}

//libera il primo elemento della coda ritornando la coda aggiornata
Lifo* pop (Lifo* first)
{
	//puntatori temporanei
	Fifo* tmp;
	Fifo* ret; //nel caso la coda fosse più grande

	tmp = ret = first;
	//se è già vuota non deve eliminare nulla
	if(first == NULL)
		return NULL;

	//se ha un solo elemento lo elimina
	if(first->next == NULL) {
		free(first);
		return NULL;
	}

	//scorre la coda dall'ultimo fino al primo
	while(first->next != NULL) {
		tmp = first; //salva la posizione corrente
		first = first->next; //e procede
	}
	//arrivato al primo assegna al secondo NULL
	tmp->next = NULL;
	//e libera il primo
	free(first);

	return ret;
}

void printLifo (Lifo* first)
{
	//se la coda è vuota lo comunica
	if(first == NULL) {
		printf("Coda vuota!\n");
		return;
	}
	//scorre tutti gli elementi dall'ultimo al primo
	while(first != NULL) {
		printf("%d ", first->val);
		//avanza di puntatore
		if(first->next != NULL)
			first = first->next;
		else break;
	}
	printf("\n");
}
