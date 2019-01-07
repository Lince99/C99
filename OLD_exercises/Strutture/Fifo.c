/*
 * Basso Nicola
 * 4^AI
 * 05/01/2019
 */

/* test di strutture dinamiche : coda FIFO */


#include <stdio.h>
#include <stdlib.h>

typedef struct Tail Fifo;

struct Tail {
	int val; //valore salvato
	Fifo* next; //prossimo elemento della coda
};

//dichiarazione delle funzioni
//restituisce il puntatore all'ultimo elemento della coda
Fifo* push (Fifo* first, int val);
//elimina il primo elemento della coda
Fifo* pop (Fifo* first);
//stampa tutta la coda
void printFifo (Fifo* first);

int main(int argc, char **argv)
{
	Fifo* coda = NULL; //coda vuota
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
Fifo* push (Fifo* first, int val)
{
	Fifo* new;
	//alloca la dimensione della struttura (int + puntatore)
	if((new = (Fifo*) malloc(sizeof(Fifo))) == NULL) {
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
Fifo* pop (Fifo* first)
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

void printFifo (Fifo* first)
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
