/*
 * Copyright 2019 Lince99
 * for the license refer to the prject's license
 */

#ifndef G_MATRIX_ADJ_H
#define G_MATRIX_ADJ_H

#include "stdio.h"
#include "stdlib.h"
#include "g_struct.h"
#include "common/colors.h"

//TODO implements all functions and structure about adjacents' matrix
typedef struct ADJNODE AdjNode_t;

strucy ADJNODE {
    int value;
    AdjNode_t* row; //directly connected graph nodes (has next = NULL)
    AdjNode_t* next; //list of nodes
};


/*
 * function that try to alloc one new node
 */
AdjNode_t* init_AdjNode_t(int val) {
    AdjNode_t* node = NULL;

    node = (AdjNode_t*) malloc(sizeof(AdjNode_t));
    if(node == NULL) {
        printf(ANSI_RED "Error on alloc new adjacent node!" ANSI_RESET "\n");
        return NULL;
    }
    node->value = val;
    node->row = NULL;
    node->next = NULL;

    return node;
}

/*
 * add to root->row
 */
AdjNode_t* addNeighbour_AdjNode_t(AdjNode_t* root, AdjNode_t* neigh)

#endif //G_MATRIX_ADJ_H
