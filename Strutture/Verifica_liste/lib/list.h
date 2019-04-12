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

typedef struct LIST list;

struct LIST {
    char name;
    float lung;
    list* next;
};

list* init_node(char name, float lung) {
    list* new = NULL;

    //prova ad allocare il nuovo nodo
    new = (list*) malloc(sizeof(list));
    if(new == NULL) {
        perror("Errore di allocazione di un nuovo nodo!\n");
        return NULL;
    }
    //e gli assegna i valori
    new->name = name;
    new->lung = lung;
    new->next = NULL;

    return new;
}

void print_list(list* head) {
    if(head == NULL)
        printf("Lista vuota!\n");
    else {
        while(head->next != NULL) {
            printf("[%c] = %f metri\n", head->name, head->lung);
            head = head->next;
        }
    }
}

/*
 * funzione che aggiunge un/a atleta in ordine cresente di lungezza del salto
 */
list* add_node(list* head, char name, float lung) {
    list* new = NULL;
    list* tmp = head;
    list* prev = NULL;

    new = init_node(name, lung);
    if(tmp == NULL)
        return new;
    //se il nuovo atleta ha effettuato il salto peggiore diventa la nuova testa
    if(new->lung <= tmp->lung) {
        new->next = tmp;
        return new;
    }
    //altrimenti lo inserisce all'interno o alla fine della lista
    while(tmp->next != NULL) {
        prev = tmp;
        //se e' maggiore di quello corrente avanza
        if(new->lung > tmp->lung)
            tmp = tmp->next;
        //altrimenti collega il precedente al nuovo e questo al successivo
        else {
            prev->next = new;
            new->next = tmp;
            break;
        }
    }

    return head;
}

list* add_node_tail(list* head, char name, float lung) {
    list* new = NULL;
    list* tmp = head;

    new = init_node(name, lung);
    if(tmp == NULL)
        return new;
    while(tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;

    return head;
}

list* add_node_head(list* head, char name, float lung) {
    list* new = NULL;

    new = init_node(name, lung);
    if(head == NULL)
        return new;
    new->next = head;

    return new;
}

list* rem_node(list* head, float val) {
    list* tmp = head;
    list* prev = NULL;

    if(tmp == NULL)
        return NULL;

    while(tmp->next != NULL) {
        prev = tmp;
        if(tmp->lung == val) {
            prev->next = tmp->next;
            free(tmp);
        }
        tmp = tmp->next;
    }

    return head;
}

list* rem_node_tail(list* head) {
    list* tmp = head;

    if(tmp == NULL)
        return NULL;
    while(tmp->next != NULL)
        tmp = tmp->next;
    free(tmp);

    return head;
}

list* rem_node_head(list* head) {
    list* tmp = NULL;

    if(head == NULL)
        return NULL;
    tmp = head->next;
    free(head);

    return tmp;
}
