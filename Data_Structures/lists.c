/* Copyright (C) 2019  Lince99
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see http://www.gnu.org/licenses .
 */
/*
 * Basso Nicola
 * 4^AI
 */
/*
 * Programma di test delle funzioni dedicate alla gestione delle liste
 */

#include <stdio.h>
#include "lib/lists/intList.h"
#include "lib/lists/circList.h"
#include "lib/lists/bidirList.h"
#include "lib/lists/voidList.h"

//firme delle prove
void testLinkedList();
void testVoidList();

int main() {

    printf(ANSI_BLUE "- - - - - - TEST LINK LIST - - - - - - " ANSI_RESET "\n");
    testLinkedList();
    printf(ANSI_BLUE "- - - - - - TEST VOID* LIST - - - - - -" ANSI_RESET "\n");
    testVoidList();

    return 0;
}



//simple tests with integers saved on a linked list
void testLinkedList() {
    int a = 0;
    int i = 0;
    listNode* list = NULL;

    printf(ANSI_BLUE "Inserisci un valore:" ANSI_RESET"\n");
    getInt(&a);

    print_list(list);
    //list = init_list(a);
    list = addTail_list(list, a);
    print_list(list);
    addTail_list(list, ++a);
    print_list(list);
    addTail_list(list, a++);
    print_list(list);
    for(i = 0; i < a; i++) {
        addTail_list(list, i);
        print_list(list);
    }
    list = addHead_list(list, a*2);
    print_list(list);
    list = free_list(list);
    print_list(list);

}



//test void* linked list
void testVoidList() {
    //HHEEEEEEELLLLLLLLLLL
    /*
    void* test = NULL;
    int* n = NULL;
    test = malloc(sizeof(int));


    *(int*)test = *n;
    printf("test = %d\n", *(int*)test);
    free(test);
    */
    //END HHEEEEEEELLLLLLLLLLL

    voidNode* head = NULL;
    int* n = NULL;

    n = (int*)malloc(sizeof(int));
    *n = 2;

    head = init_voidNode(n);
    *n += 10;
    addTail_voidNode(head, n);
    *n += 12;
    addTail_voidNode(head, n);
    print_voidNode_int(head);

    //test 2
    free_voidNode(head);
    voidNode* bob = NULL;
    *n += 12;
    bob = init_voidNode(n);
    *n += 2;
    addTail_voidNode(bob, n);
    addTail_voidNode(bob, n);
    addTail_voidNode(bob, n);
    head = init_voidNode(bob);

    printf(ANSI_YELLOW "Bob\t");
    print_voidNode_int(bob);
    printf(ANSI_BLUE "head->value\t");
    print_voidNode_int(head->value); //<-- OMG
    printf(ANSI_RED "head\t");
    print_voidNode_int(head);
}
