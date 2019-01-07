/*
 * Basso Nicola
 * 4^AI
 */
/*
 * dedicated library that manage only stack structures aka LIFO
 * https://it.wikipedia.org/wiki/FIFO#/media/File:FIFO-LIFO.svg
 */

#include <stdio.h>
#include <stdlib.h>
#ifndef _COLORS_H
    #include "colors.h"
#endif

/* signatures */
typedef struct LIFO lifo;



/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* - - - - - - - - - - - GENERAL PORPOUSE STACK - - - - - - - - - - - - - - - */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/*
 * this struct accept any type of data
 * and represent a single node of the stack
 */
struct LIFO {
    void* val;
    lifo* next;
};

/*
 * function that alloc and initialize one integer node of the list
 */
lifo* init_element(void* n) {
    lifo* new = NULL; /* the new node of the list */

    /* alloc the new node */
    new = (lifo*) malloc(sizeof(lifo));
    if(new == NULL) {
        printf(ANSI_RED "Error on allocating new stack node!\n"
               ANSI_RESET);
        return NULL;
    }
    /* and assign the arg value to the content of the node */
    new->val = n;
    new->next = NULL;

    return new;
}

lifo* push(lifo* head, void* n) {
    lifo* new = NULL; /* this will be the new node that has to be linked */

    /* allocate the new node */
    new = init_element(n);
    /*
     * if the head is already initialized,
     * link the new node to the next node of the old head
     */
    if(head != NULL)
        new->next = head;

    /* the new node is the new head */
    return new;
}
