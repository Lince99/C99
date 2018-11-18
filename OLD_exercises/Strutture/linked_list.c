/*
* Basso Nicola
* 4^AI
* 21/10/2017
*/

//test di strutture dinamiche : lista (linked list)

#include <stdio.h> //printf...
#include <stdlib.h> //malloc...

//tipo Node dichiarato per comodità
typedef struct LNode Node;

struct LNode {
	int val; //valore dell'elemento corrente
	Node* next; //link all'elemento successivo
};

//dichiarazione delle funzioni
Node* initialize (Node* nodo, int val);
void addNode (Node* old, int val);
void remNode (Node* start, int pos);
void freeNodes (Node* start);
void printNodes (Node* nodo);
int findNode (Node* start, int key);

int main (int argc, char **argv)
{
	int i = 0;
	int key = 4; //chiave da cercare nella lista
	Node* start;

	//crea il nodo di partenza
	start = initialize(start, 0);
	//creo altri 5 nodi
	for(i = 0; i < 5; i++)
		addNode(start, i+1);
	//ne tolgo 1
	remNode(start, 0);
	//stampa per vedere se tutto è ok
	printNodes(start);
	//trova il valore key
	if((i = findNode(start, key)) != -1)
		printf("%d trovato in posizione %d\n", key, i);
	else
		printf("%d NON trovato!\n", key);
	//libero tutti i nodi
	freeNodes(start);
	printf("Nodi liberati dalla memoria!\n");

	return 0;
}

//inizializza un nodo a val e NULL
Node* initialize (Node* nodo, int val)
{
	//alloca la dimensione della struttura (int + puntatore)
	if((nodo = (Node*) malloc(sizeof(Node))) == NULL) {
		printf("Errore nell'allocare!\n");
		exit(1);
	}
	//e gli assegna il valore
	nodo->val = val;
	//setta il puntatore al prossimo nodo a NULL
	nodo->next = NULL;
	//ritorna il puntatore alla struttura inizializzata
	return nodo;
}

//aggiunge un nodo alla lista
void addNode (Node* old, int val)
{
	//crea e inizializza il nuovo nodo
	Node* new;
	new = initialize(new, val);
	//scorre tutti i nodi finchè non trova la coda
	while(old->next != NULL)
		old = old->next;
	//assegna l'indirizzo di new a old
	old->next = new;
}

//rimuove il nodo alla posizione pos collegando i suoi vicini
void remNode (Node* start, int pos)
{
	int i = 0;

	//se non ha alcun elemento ritorna
	if(start == NULL)
		return;
	//scorre la lista finchè i non arriva alla posizione
	//del nodo prima di quello da eliminare
	while(start != NULL && i < pos-1) {
		start = start->next;
		i++;
	}
	//arrivato a pos-1 collega il pos-1 al pos+1
	start->next = start->/*salta questo*/next->next;
}

//libera tutta la memoria occupata dalla lista
void freeNodes (Node* start)
{
	//scorre la lista
	while(start != NULL) {
		//libera il nodo
		free(start);
		//e passa al successivo
		start = start->next;
	}
}

//stampa la lista scorrendola totalmente
void printNodes (Node* nodo)
{
	//stampa fino alla fine della lista
	while(nodo != NULL) {
		printf("%d ", nodo->val);
		//avanza di puntatore
		nodo = nodo->next;
	}
	printf("\n");
}

int findNode (Node* start, int key)
{
	int n = 0;
	Node* tmp;

	//nodo di supporto per la stampa
	tmp = start;
	//stampa fino alla coda
	while(tmp != NULL) {
		//ritorna il nodo dove ha trovato la key
		if(tmp->val == key)
			return n;
		//passa al prossimo nodo
		tmp = tmp->next;
		n++;
	}
	//se non ha trovato nulla ritorna -1
	return -1;
}
