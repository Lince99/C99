/*
 * Basso Nicola
 * 4^AI
 */
/*
 * dedicated library that manage list of other items, like other lists.
 * all params need to be allocated before calling these functions
 */

#include <stdio.h>
#include <stdlib.h>
#include "colors.h"

//signatures
typedef struct voidNODE voidNode;
voidNode* init_voidNode(void* val);
void addTail_voidNode(voidNode* node, void* val);
voidNode* addHead_voidNode(voidNode* head, void* val);
void print_voidNode_int(voidNode* head);
int free_voidNodes(voidNode* head);



/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - VOID* LINKED LIST - - - - - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

//generic type (void*) list
struct voidNODE {
	void* value;
	voidNode* next;
};

/*
 * initialize a new node and return its pointer
 */
voidNode* init_voidNode(void* val) {
    voidNode* node = NULL; /* the new head of the list */

    //alloc the new node
    if( ( node = (voidNode*) malloc(sizeof(voidNode)) ) == NULL) {
            printf(ANSI_RED "Error on allocating new list node!"
                   ANSI_RESET "\n");
            return NULL;
    }
    //and assign values to the content of the node
    node->value = malloc(sizeof(val));
    node->value = val;
    node->next = NULL;

    //return the new allocated node
    return node;
}

/*
 * function that add an element at the tail of the linked list
 */
void addTail_voidNode(voidNode* node, void* val) {
    voidNode* new = NULL;

    //allocate the new node
    new = init_voidNode(val);
    //check if there is an old node to attach, if not "new" is the new node
    if(node == NULL) {
        node = new;
        return;
    }
    //the new node goes to the tail of the list
    while(node->next != NULL)
        node = node->next;
    //assign the pointer of the new node to the link of the old tail
    node->next = new;
}

/*
 * function that create a new head for the list
 */
voidNode* addHead_voidNode(voidNode* head, void* val) {
    voidNode* new = NULL;

    //allocate the new node
    new = init_voidNode(val);
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
void print_voidNode_int(voidNode* head) {
    int val = 0;

	//check if it's empty
	if(head == NULL) {
		printf(ANSI_RED "Empty list!" ANSI_RESET "\n");
		return;
	}

	//otherwise print in a formatted manner
	printf(ANSI_GREEN);
	while(head != NULL) {
        //hope that it contains an integer
        val = *(int*)(head->value);
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

/*
 * function that free the list from the head
 */
int free_voidNodes(voidNode* head) {
    voidNode* tmp = NULL; /* temp node for saving the next node on freeing */
    //scoll the list
    while(head != NULL) {
        //free the current node
        tmp = head;
        free(head);
        //and continue to the next
        head = tmp->next;
    }

}
