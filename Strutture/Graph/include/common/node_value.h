/*
 * Copyright 2019 Lince99
 * for the license refer to the prject's license
 */

#ifndef NODE_VALUE_H
#define NODE_VALUE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//signatures
typedef struct NODEVALUE nodeVal_t;

struct NODEVALUE {
    void* value;
    size_t n_value_size;
    size_t value_size;
};

/*
 *
 */
nodeVal_t* init_nodeVal(void* val, size_t size_n_val, size_t size_val) {
    nodeVal_t* node = NULL;

    node = (nodeVal_t*) malloc(sizeof(nodeVal_t));
    if(node == NULL) {
        printf(ANSI_RED "Error on alloc new tree node!" ANSI_RESET "\n");
        return NULL;
    }
    node->value = val;
    node->value_size = size_n_val;
    node->n_value_size = size_val;

    return node;
}

/*
 * function that print the integer value of the struct
 * the return value is only for check porpouses:
 * 0 = all ok, -1 = NULL found, -2 = wrong data type, -3 = error by fprintf
 *
 */
int print_nodeVal_int(nodeVal_t* val) {
    int i = 0;
    int arr_dim = 0;

    if(val == NULL) {
        printf("No value!");
        return -1;
    }
    if(val->n_value_size != sizeof(int)) {
        printf("Not an integer!");
        return -2;
    }
    //if the void* point to an array, print all of its elements
    arr_dim = (int)(val->value_size)/(val->n_value_size)
    for(i = 0; i < arr_dim; i++) {
        if(!fprintf(stdout, "%d", val->value))
            return -3;
        //beautified print with commas and periods :)
        (i < arr_dim-1) ? fprintf(stdout, ".") : fprintf(stdout, ", ");
    }

    return 0;
}

//TODO add gets & set and print value


#endif /NODE_VALUE_H
