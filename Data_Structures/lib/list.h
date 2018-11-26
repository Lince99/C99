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




/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - INTEGER LINKED LIST - - - - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
//required use of pointer
typedef struct listNODE listNode;

//this single-way linked list accept only intgers (or chars) as value
struct listNODE {
    int value;
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
    node->next = NULL;

    //return the new allocated node
    return node;
}

/*
 * function that add an element at the tail of the linked list
 */
listNode* addTail_list(listNode* node, int n) {
    listNode* new = NULL;

    //allocate the new node
    new = init_list(n);
    //check if there is an old node to attach else "new" is the new node
    if(node == NULL)
        return new;
    //the new node goes to the tail of the list
    while(node->next != NULL)
        node = node->next;
    //assign the pointer of the new node to the link of the old tail
    node->next = new;
}

/*
 * function that create a new head for the list
 */
listNode* addHead_list(listNode* head, int n) {
    listNode* new = NULL;

    //allocate the new node
    new = init_list(n);
    //if the head wasn't initialized before, new is the new list
    if(head == NULL)
        return new;

    if(head != NULL) {
        //link the new node to the next node of the old head
        new->next = head->next;
        //free the old head, not returning or other things
        free(head);
    }

    //the new node is the new head
    return new;
}

/*
 * recursive function that return the length of the list
 */
int length_list(listNode* node) {
    //WIP (node == NULL) ? return 0 : return length_list(node->next)+1;
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
 * function that remove one node that has the same value of "n" in the list
 */
listNode* remNode_list(listNode* head, int n) {

    //TODO

}

/*
 * function that remove a piece of the list from start to end
 */
//TODO
listNode* remSector_list(listNode* node, int start, int end) {
    listNode* tmp = NULL; /* save the current node before the one to delete */
    int i = 0; /* position that has to reach "start" */

    //if there is no elements return immediately
    if(node == NULL)
        return node;
    //check if parameters aren't valid
    if(start > end)
        return node;

    //scoll the list until "i" reaches the node before that one has to be free
    while(head != NULL && i < start) {
        head = head->next;
        tmp = head;
        i++;
    }
    head->next = head->/*delete this*/next->next;
    free(tmp->next);

    return head;
}

/*
 * function that free the list from the head
 */
listNode* free_list(listNode* head) {
    listNode* tmp = NULL; /* temp node for saving the next node on freeing */

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



/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - VOID* LINKED LIST - - - - - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
typedef struct voidNODE voidNode;

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
