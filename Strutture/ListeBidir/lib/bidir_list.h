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

//signatures
typedef struct listNODE listNode;
listNode* init_list(int n);
listNode* addTail_list(listNode* node, int n);
listNode* addHead_list(listNode* head, int n);
int length_list(listNode* node);
void print_list(listNode* head);
void rec_print_list(listNode* node);
void printNode_list(listNode* node);
void findPrintNode_list(listNode* head, int val);
listNode* findNode_list(listNode* head, int val);
listNode* getNode_list(listNode* head, int pos);
listNode* remNode_list(listNode* head, int n);
listNode* free_list(listNode* head);



/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - INTEGER LINKED LIST - - - - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
//required use of pointer
typedef struct listNODE listNode;

//this single-way linked list accept only intgers (or chars) as value
struct listNODE {
    int value;
    listNode* prev;
    listNode* next;
};

/*
 * function that alloc and initialize the node of the list
 */
listNode* init_list(int n) {
    listNode* node = NULL; /* the new node of the list */

    //alloc the new node
    node = (listNode*) malloc(sizeof(listNode));
    if(node == NULL) {
            printf(ANSI_RED "Error on allocating new list node!\n"
                   ANSI_RESET);
            return NULL;
    }
    //and assign the arg value to the content of the node
    node->value = n;
    node->prev = NULL;
    node->next = NULL;

    //return the new allocated node
    return node;
}

/*
 * function that add an element at the tail of the linked list
 */
listNode* addTail_list(listNode* node, int n) {
    listNode* new = NULL; /* the new node will be stored here */
    listNode* start = NULL; /* start node that is useful for void lists */
    listNode* prev = NULL; /* previous node for the last visited node */

    start = node;
    //allocate the new node
    new = init_list(n);
    //check if there is an old node to attach else "new" is the new node
    if(node == NULL)
        return new;
    //the new node goes to the tail of the list
    while(node->next != NULL) {
        prev = node;
        node = node->next;
    }
    printf("\n");
    //and link prev node with this new node
    node->prev = prev;
    //assign the pointer of the new node to the link of the old tail
    node->next = new;

    //return the head of the list
    return start;
}

/*
 * function that create a new head for the list
 */
listNode* addHead_list(listNode* head, int n) {
    listNode* new = NULL;

    //return to the real head of the list
    while(head->prev != NULL) {
        head = head->prev;
    }
    //allocate the new node
    new = init_list(n);
    //if the head wasn't initialized before, new is the new list
    if(head == NULL)
        return new;
    //link the new node to the next node of the old head
    new->next = head;

    //the new node is the new head
    return new;
}

/*
 * recursive function that return the length of the list
 */
int length_list(listNode* node) {
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
void print_list(listNode* head) {

	//check if it's empty
	if(head == NULL) {
		printf(ANSI_RED "Empty list!" ANSI_RESET"\n");
		return;
	}
    //return to the real head of the list
    while(head->prev != NULL) {
        head = head->prev;
    }
	//otherwise print in a formatted manner
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
 * function that print in a recursive way
 */
void rec_print_list(listNode* node) {

    //if the list is void print "end", same if contains something
    if(node == NULL)
        printf(ANSI_RED "End" ANSI_RESET "\n");
    else {
        printf(ANSI_GREEN "%d ", node->value);
        //pass to the next node with recursion
        print_list(node->next);
    }

}

/*
 * function that print only the passed node
 */
void printNode_list(listNode* node) {

	//check if it's empty
	if(node == NULL) {
		printf(ANSI_RED " End!" ANSI_RESET "\n");
		return;
	}
	//otherwise print in a formatted manner
	printf(ANSI_GREEN "Value of this node: %d" ANSI_RESET "\n", node->value);

}

/*
 * function that print all found elements in the list
 */
void findPrintNode_list(listNode* head, int val) {
    unsigned int pos = 0; /* counter that is used for printing the position */
    short int flag = 0; /* set to 1 if there is almost 1 entry in the list */

    //return to the real head of the list
    while(head->prev != NULL) {
        head = head->prev;
    }
	//print the position if it find the val
	while(head != NULL) {
        if(head->value == val) {
    	    printf(ANSI_GREEN "Found value %d on position %d"
                   ANSI_RESET "\n", head->value, pos+1);
            flag = 1;
        }
		head = head->next;
        pos++;
	}

    if(flag == 0)
        printf(ANSI_YELLOW "Nothing found!" ANSI_RESET "\n");
}

/*
 * function that print the first occourence in the list
 */
listNode* findNode_list(listNode* head, int val) {
    unsigned int pos = 0; /* counter that is used for printing the position */

    //return to the real head of the list
    while(head->prev != NULL) {
        head = head->prev;
    }
	//return the node if it find the val
	while(head != NULL) {
        if(head->value == val)
            return head;
		head = head->next;
        pos++;
	}

    //if nothing found, return NULL
    return NULL;
}

/*
 * function that return the node in the position passed as argument
 */
listNode* getNode_list(listNode* head, int pos) {
    unsigned int i = 0; /* counter that is used for finding the position */

    //return to the real head of the list
    while(head->prev != NULL) {
        head = head->prev;
    }
    //if the length is wrong exit
    if(pos > length_list(head) || pos < 0) {
        printf(ANSI_RED "Wrong length required!");
        return head;
    }
    //goes to the "pos" position of the list
	while(head != NULL && i < pos) {
        head = head->next;
        i++;
    }

    return head;
}

/*
 * function that remove one node that has the position of "n" in the list
 */
listNode* remNode_list(listNode* head, int n) {
    listNode* tmp = NULL; /* save the current node before the one to delete */
    listNode* start = NULL; /* save the start of the list in case of n = 0 */
    unsigned int pos = 0; /* counter that is used for counting the position */

    //return to the real head of the list
    while(head->prev != NULL) {
        head = head->prev;
    }
    start = head;
    //if the length is wrong exit
    if(head == NULL || n < 0 || n > length_list(head)) {
        printf(ANSI_RED "Wrong length!" ANSI_RESET "\n");
        return head;
    }
    //if it has only 1 node delete it and return an empty list
    if(head->next == NULL) {
        free(head);
        return NULL;
    }
    //goes to the node before the "n" node
    while(head != NULL && pos < n-1) {
        printf("pos = %d n = %d - 1\n", pos, n);
        head = head->next;
        pos++;
    }
    //save the n-1 position
    tmp = head;
    //goes to the n position that has to be free
    head = head->next;
    //link the n-1 node with n+1 node
    tmp->next = tmp->next->next;
    //free the n node
    free(head);

    return start;
}

/*
 * function that free the list from the head
 */
listNode* free_list(listNode* head) {
    listNode* tmp = NULL; /* temp node for saving the next node on freeing */

    //return to the real head of the list
    while(head->prev != NULL) {
        head = head->prev;
    }
    //scoll the list
    while(head != NULL) {
        tmp = head;
        //free the current node
        free(head);
        //and continue to the next
        head = head->next;
        tmp->next = NULL;
    }

    return head;
}
