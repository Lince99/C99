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
typedef struct ADJMATRIX_T adj_matrix_t;

strucy ADJMATRIX_T {
    graph_node_t* value;
    graph_node_t* row; //directly connected graph nodes (has next = NULL)
    adj_matrix_t* next; //list of nodes
};


/*
 * function that try to alloc one new node
 */
adj_matrix_t* init_adj_matrix_t(graph_node_t* val) {
    adj_matrix_t* node = NULL;

    node = (adj_matrix_t*) malloc(sizeof(adj_matrix_t));
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
adj_matrix_t* add_row_adj_matrix_t(graph_node_t* node, graph_node_t* val) {

}

#endif //G_MATRIX_ADJ_H
