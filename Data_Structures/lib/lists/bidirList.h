/*
 * Basso Nicola
 * 4^AI
 */
/*
 * dedicated library that manage only list that contains integers as values
 */

#include <stdio.h>
#include <stdlib.h>
#include "colors.h"

//signatures
typedef struct bidListNODE bidListNode;

bidListNode* init_bidList(int n);
bidListNode* addTail_bidList(bidListNode* node, int n);
bidListNode* addHead_bidList(bidListNode* head, int n);
int length_bidList(bidListNode* node);
void print_bidList(bidListNode* head);
void printNear_bidList(bidListNode* head);
void printNode_bidList(bidListNode* node);
//TODO
bidListNode* findNode_bidList(bidListNode* head, int val);
bidListNode* getNode_bidList(bidListNode* head, int pos);
bidListNode* remNode_bidList(bidListNode* head, int n);
bidListNode* free_bidList(bidListNode* head);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* - - - - - - - - INTEGER BIDIRECTIONAL LINKED LIST - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

//this single-way linked list accept only intgers (or chars) as value
struct bidListNODE {
    int value;
    bidListNode* next;
    bidListNode* prev;
};

/*
 * function that alloc and initialize the node of the list
 */
bidListNode* init_bidList(int n) {
    bidListNode* node = NULL; /* the new node of the list */

    //alloc the new node
    node = (bidListNode*) malloc(sizeof(bidListNode));
    if(node == NULL) {
            printf(ANSI_RED "Error on allocating new list node!\n"
                   ANSI_RESET);
            return NULL;
    }
    //and assign the arg value to the content of the node
    node->value = n;
    node->next = NULL;
    node->prev = NULL;

    //return the new allocated node
    return node;
}

/*
 * function that add an element at the tail of the bidirectional linked list
 */
bidListNode* addTail_bidList(bidListNode* node, int n) {
    bidListNode* new = NULL; /* the new node will be stored here */
    bidListNode* start = NULL; /* start node that is useful for void lists */
    bidListNode* previous = NULL; /* the last node that has to be linked to  */

    //save the head
    start = node;
    //allocate the new node
    new = init_bidList(n);
    //check if there is an old node to attach else "new" is the new node
    if(node == NULL)
        return new;
    //the new node goes to the tail of the list, while saving the previous node
    while(node->next != NULL) {
        node = node->next;
        previous = node;
    }
    //assign the pointer of the new node to the link of the old tail
    node->next = new;
    //and assign the last node saved while scrolling the list to the node
    node->prev = previous;

    //return the head of the list
    return start;
}

/*
 * function that create a new head for the list
 */
bidListNode* addHead_bidList(bidListNode* head, int n) {
    bidListNode* new = NULL; /* this will be the node that has to be linked */

    //allocate the new node
    new = init_list(n);
    //if the head wasn't initialized before, new is the new list
    if(head == NULL)
        return new;
    //check if head is the real one
    if(head->prev != NULL) {
        //if not, reach the real head
        while(head->prev != NULL)
            head = head->prev;
    }
    //link the new node to the next node of the old head
    new->next = head;

    //the new node is the new head
    return new;
}

/*
 * recursive function that return the length of the list
 */
int length_bidList(bidListNode* node) {
    //if it has reached the end of list, start the recursion
    if(node == NULL)
        return 0;
    //else increase the counter
    else
        return length_list(node->next)+1;
}

/*
 * function that print all integer elements in the list
 */
void print_bidList(bidListNode* head) {

	//check if it's empty
	if(head == NULL) {
		printf(ANSI_RED "Empty list!" ANSI_RESET"\n");
		return;
	}

    //return to the real head
    if(head->prev != NULL) {
        //if not, reach the real head
        while(head->prev != NULL)
            head = head->prev;
    }
	//than print in a formatted manner
	printf(ANSI_GREEN);
	while(head != NULL) {
		printf("%d", head->value);
        //print commas until the last point
        (head->next != NULL) ? printf(", ") : printf(".\n");
		head = head->next;
	}
	printf(ANSI_RESET);

}

/*
 * function that print all integer elements in the list
 * and one by one print the current node, its previous and its next
 */
void printNear_bidList(bidListNode* head) {

	//check if it's empty
	if(head == NULL) {
		printf(ANSI_RED "Empty list!" ANSI_RESET"\n");
		return;
	}

    //check if head is the real head
    if(head->prev != NULL) {
        //if not, reach the real head
        while(head->prev != NULL)
            head = head->prev;
    }
	//than print in a formatted manner
	while(head != NULL) {
        printf(ANSI_GREEN);
        //print the value of the previous node if exixts
        if(head->prev != NULL) {
            printf(ANSI_BG_BLUE "Previous Node:" ANSI_BG_BLACK "\n");
            printf("%d", head->prev->value);
        }
        //print the value of the current node
        printf(ANSI_REVERSE "Node:" ANSI_REVERSE "\n");
		printf("%d", head->value);
        //print the value of the next node
        if(head->next != NULL) {
            printf(ANSI_BG_CYAN "Next Node:" ANSI_BG_BLACK "\n");
            printf("%d", head->next->value);
        }
        printf(ANSI_RESET "\n");
        //goes to the next point
		head = head->next;
	}

}

/*
 * function that print only the passed node
 */
void printNode_bidList(bidListNode* node) {

	//check if it's empty
	if(node == NULL) {
		printf(ANSI_RED "Nothing found!" ANSI_RESET "\n");
		return;
	}
	//otherwise print in a formatted manner
	printf(ANSI_GREEN "Value of this node: %d" ANSI_RESET "\n", node->value);

    if(node->next != NULL)
        printf(ANSI_CYAN ANSI_UNDERLINE "Has a NEXT node" ANSI_RESET "\n");
    else
        printf(ANSI_YELLOW ANSI_UNDERLINE "No NEXT node" ANSI_RESET "\n");
    if(node->prev != NULL)
        printf(ANSI_CYAN ANSI_UNDERLINE "Has a PREV node" ANSI_RESET "\n");
    else
        printf(ANSI_YELLOW ANSI_UNDERLINE "No PREV node" ANSI_RESET "\n");
}
