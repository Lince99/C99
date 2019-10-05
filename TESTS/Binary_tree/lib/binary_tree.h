/*
 * Basso Nicola
 * aka Lince99
 */
/*
 * library that is the core for the n-ary tree
 */

#include <stdio.h>
#include <string.h>
#include "colors.h"

typedef struct LEAF leaf;

struct LEAF {
    int val;
    leaf* left;
    leaf* right;
};

/*
 * alloca e inizializza una nuova foglia
 */
leaf* init_node() {
    leaf* node = NULL;

    node = (leaf*) malloc(sizeof(leaf));
    if(node == NULL) {
        printf(ANSI_RED "Error on alloc new tree node!" ANSI_RESET "\n");
        return NULL;
    }
    node->val = 0;
    node->left = NULL;
    node->right = NULL;

    return node;
}

/*
 * stampa formattata di un nodo dell'albero binario
 */
void print_node(leaf* node) {

    //altrimenti esegue la stampa indentata e colorata
    printf("    ");
    printf(ANSI_BLUE " %d " ANSI_RESET, node->val);
    printf("\n ");
    //stampa i valori delle foglie
    if(node->left != NULL)
        printf(ANSI_BLUE " %d " ANSI_RESET, node->left->val);
    else
        printf(ANSI_CYAN "nil" ANSI_RESET);
    printf("   ");
    if(node->right != NULL)
        printf(ANSI_BLUE " %d " ANSI_RESET, node->right->val);
    else
        printf(ANSI_CYAN "nil" ANSI_RESET);
    printf("\n");

}

/*
 * stampa formattata suddivisa per sottoalberi con altezza pari a 1
 */
void print_tree(leaf* root) {

    if(root == NULL) {
        printf(ANSI_YELLOW "Void tree!" ANSI_RESET "\n");
        return;
    }
    //stampa la foglia corrente
    print_node(root);
    //passa alla stampa della foglia sinistra del nodo appena stampato
    if(root->left != NULL) {
        //se la foglia successiva non ne ha a sua volta non viene stampata
        if( !((root->left->left == NULL) &&
              (root->left->right == NULL)) ) {
            printf(ANSI_MAGENTA "leaves of %d (leaf left of %d)"
                   ANSI_RESET "\n", root->left->val, root->val);
            print_tree(root->left);
        }
    }
    //stampa ricorsivamente anche la foglia destra
    if(root->right != NULL) {
        if( !((root->right->left == NULL) &&
              (root->right->right == NULL)) ) {
            printf(ANSI_MAGENTA "leaves of %d (leaf right of %d)"
                   ANSI_RESET "\n", root->right->val, root->val);
            print_tree(root->right);
        }
    }

}

/*
 * funzione che restituisce il nodo che possiede il valore cercato
 */
leaf* find_node(leaf* root, int val) {

    //nel caso il nodo sia vuoto non fa nulla
    if(root == NULL)
        return NULL;
    //se ha trovato il nodo con il valore allora lo ritorna
    if(root->val == val)
        return root;
    //altrimenti passa alle foglie la ricerca
    if(root->left != NULL)
        return find_node(root->left, val);
    if(root->right != NULL)
        return find_node(root->right, val);

    return NULL;
}

/*
 * aggiunge una foglia sinistra alla radice, se non c'e' spazio allora
 * esplora l'albero per trovargli il primo spazio sinistro disponibile
 */
leaf* add_left(leaf* root, int val) {
    leaf* new = NULL;

    //alloca il nuovo nodo
    new = init_node();
    if(new != NULL)
        new->val = val;
    //se non esiste una radice new lo diventa
    if(root == NULL)
        return new;
    //se esiste gia' una foglia sinistra
    //allora prosegue finche' non trova un posto a sinistra
    if(root->left != NULL)
        return add_left(root->left, val);
    else
        root->left = new;

    return root;
}

/*
 * aggiunge una foglia destra alla radice, se non c'e' spazio allora
 * esplora l'albero per trovargli il primo spazio destro disponibile
 */
leaf* add_right(leaf* root, int val) {
    leaf* new = NULL;

    //alloca il nuovo nodo
    new = init_node();
    if(new != NULL)
        new->val = val;
    //se non esiste una radice new lo diventa
    if(root == NULL)
        return new;
    //se esiste gia' una foglia destra
    //allora prosegue finche' non trova un posto a destra
    if(root->right != NULL)
        return add_right(root->right, val);
    else
        root->right = new;

    return root;
}

/*
 * aggiunge una foglia nella prima posizione disponibile,
 * che sia destra o sinistra (preferisce la sinistra quando possibile)
 */
leaf* add_leaf(leaf* root, int val) {
    leaf* new = NULL;

    //alloca il nuovo nodo
    new = init_node();
    if(new != NULL)
        new->val = val;
    //se non esiste una radice new lo diventa
    if(root == NULL)
        return new;
    //aggiunge la nuova foglia alla radice
    if(root->left != NULL) {
        if(root->right != NULL)
            return add_leaf(root->left, val);
        else
            root->right = new;
    }
    else
        root->left = new;

    return root;
}

/*
 * libera ricorsivamente la memoria partendo dalla radice passata
 */
void free_tree(leaf* root) {
    leaf* tmp = root;
    //se non ha nulla da eliminare si ferma
    if(root == NULL)
        return;
    //elimina il nodo corrente
    free(root);
    //poi passa alle foglie
    if(tmp->left != NULL)
        free_tree(tmp->left);
    if(tmp->right != NULL)
        free_tree(tmp->right);

}

/*
 * rimuove soltanto la foglia sinistra
 * (e il conseguente sottoalbero) della radice passata
 */
leaf* rem_left(leaf* root) {

    //se non esiste una radice new lo diventa
    if(root == NULL)
        return NULL;
    //se non ha nodi a sinistra non fa nulla
    if(root->left == NULL)
        return root;
    //se ce l'ha lo elimina insieme a tutti le sue foglie
    free_tree(root->left);
    root->left = NULL;

    return root;
}

/*
 * rimuove soltanto la foglia destra
 * (e il conseguente sottoalbero) della radice passata
 */
leaf* rem_right(leaf* root) {

    //se non esiste una radice new lo diventa
    if(root == NULL)
        return NULL;
    //se non ha nodi a sinistra non fa nulla
    if(root->right == NULL)
        return root;
    //se ce l'ha lo elimina insieme a tutti le sue foglie
    free_tree(root->right);
    root->right = NULL;

    return root;
}
