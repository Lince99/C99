/*
 * Basso Nicola
 * 4^AI
 */
/*
 * dedicated library that gives to you the power of the dynamic lists
 */


#include <stdio.h>
#include <stdlib.h>
#include "colors.h"

//linked list
//LIFO
//FIFO

//double-linked list
//ordered list
//matrix list



//linked list
typedef struct LNODE lNode;

struct LNODE {
	void* value;
	lNode* next;
};

/*
 * initialize a new node and return its pointer
 */
lNode* init_lNode(void* val) {
    lNode* node = NULL;

    //alloc the new node
    if( ( node = (lNode*) malloc(sizeof(lNode)) ) == NULL) {
            printf(ANSI_RED "Error on allocating new list node!\n"
                   ANSI_RESET);
            return NULL;
    }
    //and assign values to the content of the node
    printf("alloching\n");
    node->value = malloc(sizeof(val));
    node->value = val;
    node->next = NULL;
    printf("alloching end\n");

    //return the new allocated node
    return node;
}

/*
 * function that add an element at the tail of the linked list
 */
void addTail_lNode(lNode* node, void* val) {
    lNode* new = NULL;

    //allocate the new node
    new = init_lNode(val);
    //it goes to the tail of the list
    while(node != NULL) {
        node = node->next;
    }
    //assign the pointer of the new node to the link of the old tail
    if(node != NULL)
        node->next = new;
}

/*
 * function that create a new head for the list
 */
lNode* addHead_lNode(lNode* head, void* val) {
    lNode* new = NULL;

    //allocate the new node
    new = init_lNode(val);
    if(head != NULL) {
        //link the new node to the next node of the old head
        new->next = head->next;
        //free the old head, not returning or other things
        free(head);
    }

    return new;
}

/*
 * function that print all integer elements on "head" list
 */
void print_lNode_int(lNode* head) {
    int val = 0;

    //printf("in print\n");
	//check if it's empty
	if(head == NULL) {
		printf(ANSI_RED "Empty list!\n" ANSI_RESET);
		return;
	}

    printf("in 2 print\n");
	//otherwise print in a formatted manner
	printf(ANSI_GREEN);
	while(head != NULL) {
        printf("in 3 print\n");
        //hope that it contains an integer
        val = *(int*)head->value;
		printf("%d", val);
        //print commas while it's the last node
		if(head->next != NULL)
			printf(", ");
		else
			printf(".\n");
		head = head->next;
	}
	printf(ANSI_RESET);

}
