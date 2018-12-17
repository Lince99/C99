/*
 * Basso Nicola
 * 4^AI
 */
/*
 * dedicated library that manage only stack structures aka LIFO
 * https://it.wikipedia.org/wiki/FIFO#/media/File:FIFO-LIFO.svg
 */
/*TODO
#ifndef _STDIO_H
    #define _STDIO_H
*/
#include <stdio.h>
#include <stdlib.h>
#include "colors.h"

//signatures
typedef struct LIFO lifo;



/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* - - - - - - - - - - - GENERAL PORPOUSE STACK - - - - - - - - - - - - - - - */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

//this struct accept any type of data and represent a single node of the stack
struct LIFO {
    void* val;
    lifo* next;
}

/*
 * function that alloc and initialize one integer node of the list
 */
lifo* init_element()
