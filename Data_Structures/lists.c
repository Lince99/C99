/*
 * Basso Nicola
 * 4^AI
 */
/*
 * Programma di test delle funzioni dedicate alla gestione delle liste
 */

#include <stdio.h>
#include "lib/list.h"
#include "lib/colors.h"
#include "lib/input_check.h"

int main() {
    lNode* head = NULL;
    int* n = NULL;

    n = (int*)malloc(sizeof(int));
    *n = 2;
    //HHEEEEEEELLLLLLLLLLL
    /*void* test = NULL;
    test = malloc(sizeof(int));


    *(int*)test = *n;
    printf("test = %d\n", *(int*)test);
    free(test);*/
    //END HHEEEEEEELLLLLLLLLLL

    head = init_lNode(n);

    *n += 1;
    addTail_lNode(head, n);

    print_lNode_int(head);

    return 0;
}
