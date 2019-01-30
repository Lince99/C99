/*
 * Basso Nicola
 * 4^AI
 * 21/01/2019
 */

/*
 * Libreria utile all'esercizio n^1 graduatoria
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct PILA pila;

struct PILA {
    int val;
    pila* next;
};

pila* init_node(int val) {
    pila* new = NULL;

    //prova ad allocare il nuovo nodo
    new = (pila*) malloc(sizeof(pila));
    if(new == NULL) {
        perror("Errore di allocazione di un nuovo nodo!\n");
        return NULL;
    }
    //e gli assegna i valori
    new->val = val;
    new->next = NULL;

    return new;
}

void print_list(pila* head) {

    if(head == NULL)
        printf("Pila vuota!\n");
    while(head != NULL) {
        printf("%d", head->val);
        head = head->next;
        if(head->next == NULL)
            printf(".\n");
        else
            printf(", ");
    }

}

pila* add_node_head(pila* head, int val) {
    pila* new = NULL;

    new = init_node(val);
    if(head == NULL)
        return new;
    new->next = head;

    return new;
}

pila* push(pila* head, int val) {
    pila* new = NULL;
    pila* tmp = head;

    new = init_node(val);
    if(tmp == NULL)
        return new;
    while(tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;

    return head;
}

pila* push_node(pila* head, pila* new) {
    pila* tmp = head;

    if(tmp == NULL)
        return new;
    while(tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;

    return head;
}

pila* pop(pila* head) {
    pila* tmp = head;

    if(tmp == NULL)
        return NULL;
    while(tmp->next != NULL) {
        if(head->next != NULL) {
            if(head->next->next != NULL)
                head = head->next;
        }
        tmp = tmp->next;
    }
    head->next = NULL;

    return tmp;
}
