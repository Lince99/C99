/*
 * Basso Nicola
 * aka Lince99
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/colors.h"
#include "lib/input_check.h"
#include "lib/k-ary_tree.h"


/*
            A
        B       C
     D  E  F
*/
void test_fill();

int main(int argc, char** argv) {
    karyNode* root = NULL;

    root = fill_tree_user(root, MAX_LEAFS);
    print_tree(root, 0);

    return 0;
}

void test_fill() {
    karyNode* root = NULL;
    karyNode* node0 = NULL;
    karyNode* node1 = NULL;

    root = init_node(0);
    node0 = init_node(1);
    add_leaf(root, node0);
    add_leaf(node0, init_node(3));
    //print_node(root);
    add_node(root, 2);
    add_node(root, 4);
    add_node(root, 5);
    add_node(root, 6);
    add_leaf(node0, init_node(7));
    node1 = get_leaf_node(node0, 1);
    printf("Node extracted:\n");
    print_node(node1);
    free_subtree(node0, 1);
    add_leaf(node0, init_node(8));
    //print_node(root);

    printf("\nTree:\n");
    print_tree(root, 0);

    printf("\n");
    free(root);
}
