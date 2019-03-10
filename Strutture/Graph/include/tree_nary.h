/*
 * Copyright 2019 Lince99
 * for the license refer to the prject's license
 */

#ifndef TREE_NARY_H
#define TREE_NARY_H

#include <stdio.h>
#include <stdlib.h>
#include "common/colors.h"
#include "common/node_value.h"

//signatures
typedef struct NARYNODE naryNode_t;

struct NARYNODE {
    nodeVal_t* value;
    int n_leaf; /* number of leaves of the current node */
    karyNode** leaf; /* dynamic array of leaves */
};

/*
 * function that try to alloc one new node
 */
naryNode_t* init_naryNode_int(int val) {
    karyNode* node = NULL;

    node = (karyNode*) malloc(sizeof(karyNode));
    if(node == NULL) {
        printf(ANSI_RED "Error on alloc new tree node!" ANSI_RESET "\n");
        return NULL;
    }
    node->value = init_nodeVal(&(void*)val, sizeof(int), sizeof(val));
    node->n_leaf = 0;
    node->leaf = NULL;

    return node;
}

/*
 * formatted print of 1 node and his leaves
 */
void print_naryNode(naryNode_t* node) {
    int i = 0;

    if(node == NULL) {
        printf(ANSI_YELLOW "Void node!" ANSI_RESET "\n");
        return;
    }
    //stampa il valore al centro e i figli sotto
    for(; i < node->n_leaf-1; i++)
        printf("  ");
    printf(ANSI_BLUE);
    print_nodeVal_int(node->value);
    printf(ANSI_RESET "\n");
    //se non ci sono foglie allora lo comunica
    if(node->n_leaf == 0) {
        printf(ANSI_CYAN "nil " ANSI_RESET "\n");
        return;
    }
    //se ci sono allora le stampa tutte
    for(i = 0; i < node->n_leaf; i++) {
        if(node->leaf[i] != NULL)
            printf(ANSI_CYAN "%d   ", node->leaf[i]->value);
        else
            printf(ANSI_CYAN "nil ");
    }
    printf(ANSI_RESET "\n");

}


#endif //TREE_NARY_H
