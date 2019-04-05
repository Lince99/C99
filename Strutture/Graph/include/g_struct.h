/*
 * Copyright 2019 Lince99
 * for the license refer to the prject's license
 */

#ifndef G_STRUCT_H
#define G_STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "common/colors.h"
#include "common/string_manager.h"

//signatures
typedef struct GRAPH_NODE_T graph_node_t;
typedef struct GRAPH_ARC_T graph_arc_t;



struct GRAPH_NODE_T {
    int value;
    graph_arc_t* arc; //list of adiacent nodes (with weight per-arc)
    int visit; //0 = white, 1 = gray, 2 = black
};

struct GRAPH_ARC_T {
    int weight;
    graph_node_t* adiacent; //adjacent node
    graph_arc_t* next; //next arc of this node
};

/*
 * initialize 1 node
 */
graph_node_t* init_graph_node(int val) {
    graph_node_t* node = NULL;

    node = (graph_node_t*) malloc(sizeof(graph_node_t));
    if(node == NULL) {
        perror("Error on allocation graph_node_t!\n");
        return NULL;
    }
    node->value = val;
    node->arc = NULL;
    node->visit = 0;

    return node;
}

/*
 * initialize 1 arc
 */
graph_arc_t* init_graph_arc(int val) {
    graph_arc_t* arc = NULL;

    arc = (graph_arc_t*) malloc(sizeof(graph_arc_t));
    if(arc == NULL) {
        perror("Error on allocation graph_arc_t!\n");
        return NULL;
    }
    arc->weight = val;
    arc->adiacent = NULL;
    arc->next = NULL;

    return arc;
}

/*
 * add a directly connected node to another node
 */
graph_node_t* graph_add_adiacent(graph_node_t* root, graph_node_t* ad, int wg) {
    graph_arc_t* new_arc = init_graph_arc(wg);
    graph_arc_t* curr_arc = NULL;

    if(node == NULL)
        root = init_graph_node(0);
    if(ad == NULL)
        ad = init_graph_node(0);

    new_arc->adiacent = ad;

    if(root->arc == NULL)
        root->arc = new_arc;
    else {
        curr_arc = root->arc;
        while(curr_arc->next != NULL)
            curr_arc = curr_arc->next;
        curr_arc->next = new_arc;
    }

    return node;
}

//TODO implement graph functions

/*
 *
 */
char* graph_get_type(graph_node_t* node) {
    char* str = NULL;

    return str;
}

/*
 *
 */
int graph_get_distance(graph_node_t* start, graph_node_t* end) {
    int pass = 0;

    return pass;
}

/*
 *
 */
int graph_get_max_distance(graph_node_t* node) {
    int dist = 0;

    return dist;
}

/*
 *
 */
int graph_get_n_node(graph_node_t* node) {
    int count = 0;

    return count;
}

/*
 *
 */
int graph_get_n_arc(graph_node_t* node) {
    int count = 0;

    return count;
}


#endif //G_STRUCT_H
