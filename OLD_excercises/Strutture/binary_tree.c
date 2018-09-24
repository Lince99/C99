/*
 * Basso Nicola
 * 4^AI
 * 23/10/2017
*/

//test di struttore dinamiche: albero binario

#include <stdio.h>
#include <stdlib.h>

typedef struct node Leaf;

struct node {
	int val; //valore della foglia
	Leaf* sx; //foglia successiva a sinistra
	Leaf* dx; //foglia successiva a destra
};

//dichiarazione delle funzioni
Leaf* initialize (Leaf* leaf, int val);
void addLeaf (Leaf* dad, int val);

int main(int argc, char **argv)
{
	
	return 0;
}

Leaf* initialize (Leaf* leaf, int val)
{
	//alloca la memoria per una nuova foglia
	if((leaf = (Leaf*) malloc(sizeof(Leaf))) == NULL) {
		printf("Errore nell'allocare!\n");
		exit(1);
	}
	//inizializza il valore e le foglie
	leaf->val = val;
	leaf->sx = NULL;
	leaf->dx = NULL;
	return leaf; //ritorna il puntatore della foglia
}

void addLeaf (Leaf* dad, int val)
{
	int found = 0; //flag
	int lvl = 0;
	Leaf* son;
	//inizializza la foglia
	son = initialize(son, val);
	//assegna alla prima posizione disponibile la nuova foglia
	//scorrendo i rami dell'albero (prima a sinistra)
	//finchè non gli trova un posto
	while(!found) {
		//guarda i due rami se sono NULL (prima sx)
		if(dad->sx == NULL) {
			dad->sx = son;
			found = 1;
		}
		else if(dad->dx == NULL) {
			dad->dx = son;
			found = 1;
		}
		else
			dad = dad->sx;
		lvl++;
	}
}
