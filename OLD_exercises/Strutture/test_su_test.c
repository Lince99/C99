/*
* Basso Nicola
* 4^AI
* 21/10/2017
*/

//test vari

#include <stdio.h>
#include <stdlib.h>

struct Test {
	int n;
	char c;
};
typedef struct Test TEST;

typedef struct Nodo Node;

struct Nodo {
	int val;
	Node* next;
};

typedef struct list List;

struct list {
	Node* start;
};

//functions definitions
void stampaVAL(Node* p);
void addNode (Node* old, int val);
void printNodes (Node* start);

int main(int argc, char **argv)
{
	//test puntatori
	int n;
	int* pN;
	pN = &n;
	*pN = 5;
	printf("n = %d\n", n);
	printf("-------------------------------------------------------\n");



	int* p;
	p = (int*) malloc(sizeof(int));
	*p = 10;
	printf("p = %d\n", *p);
	free(p);
	printf("(free) p = %d\n", *p);
	printf("-------------------------------------------------------\n");



	int* arr = NULL;
	arr = (int*) malloc(sizeof(int)*2);
	printf("arr = %d\n", *arr);
	free(arr);
	printf("-------------------------------------------------------\n");



	int dim = 10;
	int i = 0;
	arr = (int*) malloc(sizeof(int)*dim);
	for(i = 0; i < dim; i++)
		arr[i] = i;
	for(i = 0; i < dim; i++)
		printf("%d ", arr[i]);
	printf("\n");
	free(arr);
	printf("-------------------------------------------------------\n");



	//test strutture
	TEST testEz;
	testEz.n = 10;
	printf("TEST.n = %d\n",testEz.n);
	printf("-------------------------------------------------------\n");



	TEST* arrTest;
	printf("dim TEST = %ld byte\n", sizeof(TEST));
	arrTest = (TEST*) malloc(sizeof(TEST));
	arrTest->n = 10;
	(*arrTest).c = 'c'; //uguale a (*struct).var
	printf("TEST*\n\tn = %d\n\tc = %c\n", arrTest->n, arrTest->c);
	free(arrTest);
	printf("-------------------------------------------------------\n");



	Node* testa;
	testa = (Node*) malloc(sizeof(Node));
	testa->val = 1;
	testa->next = NULL;
	free(testa);
	if((*testa).next == NULL)
		printf("testa NULLA\n");
	printf("-------------------------------------------------------\n");



	Node* head;
	List* lista;
	head = (Node*) malloc(sizeof(Node));
	lista = (List*) malloc(sizeof(List));
	head->next = NULL;
	lista->start = head;
	lista->start->val = 10;
	printf("head.val = %d\n", head->val);
	free(head);
	free(lista);
	printf("-------------------------------------------------------\n");



	/*
	int tot = 10;
	Node** obj;
	*obj = (Node*) malloc(sizeof(Node)*tot);
	for(i = 0; i < tot; i++)
		obj[i] = (Node*) malloc(sizeof(Node));
	free(obj);
	printf("-------------------------------------------------------\n");
	*/



	Node* obj0;
	Node* obj1;
	obj0 = (Node*) malloc(sizeof(Node));
	obj1 = (Node*) malloc(sizeof(Node));
	obj0->val = 1;
	obj1->val = 2;
	obj0->next = NULL;
	obj1->next = obj0->next;
	obj0->next = obj1;
	printf("obj0 = %d\n", obj0->val);
	printf("obj1 = %d\n", obj1->val);
	free(obj0);
	free(obj1);
	printf("-------------------------------------------------------\n");



	Node* start;
	start = (Node*) malloc(sizeof(Node));
	start->val = 1;
	start->next = NULL;
	addNode(start, 10);
	addNode(start->next, 1);
	printf("start->next->val= %d\n", start->next->val);
	printNodes(start);
	free(start);
	printf("-------------------------------------------------------\n");



	Node* pTest;
	Node* pNext;
	pTest = (Node*) malloc(sizeof(Node));
	pNext = (Node*) malloc(sizeof(Node));
	pTest->next = pNext;
	pTest->val = 1;
	stampaVAL(pTest);
	free(pTest);
	printf("-------------------------------------------------------\n");

	return 0;
}

void stampaVAL(Node* p)
{
	int* ptr;
	ptr = (int*) p->next;
	int n = p->val;
	printf("stampaVAL = %d\n", n);
	printf("ptr = %p\n", ptr);
}

void addNode (Node* old, int val)
{
	Node* new;
	new = (Node*) malloc(sizeof(Node));
	new->next = old->next;
	new->val = val;
	old->next = new;
}

void printNodes (Node* start)
{
	Node* tmp;
	tmp = start;
	while(tmp != NULL) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	free(tmp);
	printf("\n");
}
