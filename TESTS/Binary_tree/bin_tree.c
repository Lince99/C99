/*
 * Basso Nicola
 * aka Lince99
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/colors.h"
#include "lib/input_check.h"
#include "lib/binary_tree.h"

//firme
void clear_operations();
int menu(leaf* node);



int main(int argc, char** argv) {
    leaf* root = NULL;
    leaf* node = NULL;
    int scelta = 0;
    int mod = 0;
    int vol = 0;
    int n = 0;

    do {
        scelta = menu(node);
        switch(scelta) {
            case 1:
                printf(ANSI_GREEN "Vuoi inserirli in serie?"
                       " [0 = no, 1..n = si]" ANSI_RESET "\n");
                getInt(&mod);
                if(mod) {
                    printf(ANSI_GREEN "Per quante volte?" ANSI_RESET "\n");
                    getLimitInt(&vol, 0, INT_MAX);
                    for(; vol > 0; vol--) {
                        printf(ANSI_GREEN "%d ", vol);
                        getInt(&n);
                        //crea l'albero al primo inserimento
                        if(root == NULL) {
                            root = add_leaf(root, n);
                            node = root;
                        }
                        else
                            add_leaf(root, n);
                    }
                }
                else {
                    printf(ANSI_GREEN "Inserisci il valore:"
                           ANSI_RESET "\n");
                    getInt(&n);
                    //crea l'albero al primo inserimento
                    if(root == NULL) {
                        root = add_leaf(root, n);
                        node = root;
                    }
                    else
                        add_leaf(root, n);
                }
                break;
            case 2:
                printf(ANSI_GREEN "Inserisci il valore:" ANSI_RESET "\n");
                getInt(&n);
                //crea l'albero al primo inserimento
                if(root == NULL) {
                    root = add_left(root, n);
                    node = root;
                }
                else
                    add_left(root, n);
                break;
            case 3:
                printf(ANSI_GREEN "Inserisci il valore:" ANSI_RESET "\n");
                getInt(&n);
                //crea l'albero al primo inserimento
                if(root == NULL) {
                    root = add_right(root, n);
                    node = root;
                }
                else
                    add_right(root, n);
                break;
            case 4:
                rem_left(root);
                printf(ANSI_BLUE "Sottoalbero sinistro rimosso!"
                       ANSI_RESET "\n");
                break;
            case 5:
                rem_right(root);
                printf(ANSI_BLUE "Sottoalbero destro rimosso!"
                       ANSI_RESET "\n");
                break;
            case 6:
                printf(ANSI_BLUE "Nodo corrente:" ANSI_RESET "\n");
                print_node(node);
                if(node == NULL) {
                    printf(ANSI_RED "E' richiesto almeno un nodo"
                           " per poter procedere!" ANSI_RESET "\n");
                    break;
                }
                printf(ANSI_GREEN "Vuoi passare:\n"
                       " 1 - al ramo sinistro\n"
                       " 2 - al ramo destro\n"
                       " 3 - o tornare alla radice\n"
                       " 0 - oppure rimanere in quello corrente"
                       ANSI_RESET "\n");
                getLimitInt(&mod, 0, 3);
                switch(mod) {
                    case 1:
                        if(node->left != NULL)
                            node = node->left;
                        else
                            printf(ANSI_YELLOW "Non esiste il ramo"
                                   " sinistro del nodo corrente!"
                                   ANSI_RESET "\n");
                        break;
                    case 2:
                        if(node->right != NULL)
                            node = node->right;
                        else
                            printf(ANSI_YELLOW "Non esiste il ramo"
                                   " destro del nodo corrente!"
                                   ANSI_RESET "\n");
                        break;
                    case 3:
                        node = root;
                        break;
                    default:
                        break;
                }
                break;
            case 7:
                printf(ANSI_BLUE "Albero:" ANSI_RESET "\n");
                print_tree(root);
                break;
            case 8:
                if(node == NULL)
                    break;
                printf(ANSI_BLUE "Sottoalbero %d:"
                       ANSI_RESET "\n", node->val);
                print_tree(node);
                break;
            default:
                printf(ANSI_BLUE "Uscita dal programma..."
                       ANSI_RESET "\n");
                break;
        }
        printf("\n- - - - - - - - - - - - - - - -\n");
    }while(scelta != 0);
    //alla fine libera la memoria se e' stata usata
    if(root != NULL)
        free_tree(root);

    return 0;
}



int menu(leaf* node) {
    int ask = 0;
    int val = 0;

    printf(ANSI_GREEN "Cosa vuoi fare?" ANSI_RESET "\n");
    if(node != NULL)
        val = node->val;
    else
        printf(ANSI_CYAN "Nessun nodo selezionato!"
               " (adottato 0 come default)" ANSI_RESET "\n");
    printf(ANSI_GREEN "1 - Aggiungere una o piu' foglie\n");
    printf(ANSI_GREEN "2 - Aggiungere una foglia a sinistra del nodo corrente"
           ANSI_RESET "\n");
    printf(ANSI_GREEN "3 - Aggiungere una foglia a destra del nodo corrente"
           ANSI_RESET "\n");
    printf(ANSI_GREEN "4 - Rimuovere il sottoalbero sinistro del nodo corrente"
           ANSI_RESET "\n");
    printf(ANSI_GREEN "5 - Rimuovere il sottoalbero destro del nodo corrente"
           ANSI_RESET "\n");
    printf(ANSI_GREEN "6 - Cambiare il nodo di riferimento (corrente =  "
           ANSI_CYAN "%d" ANSI_GREEN ")" ANSI_RESET "\n", val);
    printf(ANSI_GREEN "7 - Stampare l'albero binario"
           ANSI_RESET "\n");
    printf(ANSI_GREEN "8 - Stampare il sottoalbero selezionato"
           ANSI_RESET "\n");
    printf(ANSI_GREEN " 0 - Uscire" ANSI_RESET "\n");
    getLimitInt(&ask, 0, 8);

    return ask;
}
