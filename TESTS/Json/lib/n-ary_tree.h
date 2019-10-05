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

//numero massimo di foglie per radice
#ifndef MAX_LEAFS
    #define MAX_LEAFS 3
#endif



typedef struct NARYNODE naryNode;

struct NARYNODE {
    int value; /* valore contenuto nel nodo */
    int n_leaves; /* numero di foglie del nodo corrente (per alloc) */
    naryNode** leaves; /* array di foglie dinamico */
};



/*
 * alloca e inizializza una nuova foglia cn un valore passato per parametro
 */
naryNode* init_node(int val) {
    naryNode* node = NULL;

    node = (naryNode*) malloc(sizeof(naryNode));
    if(node == NULL) {
        printf(ANSI_RED "Error on alloc new tree node!" ANSI_RESET "\n");
        return NULL;
    }
    node->value = val;
    node->n_leaves = 0;
    node->leaves = NULL;

    return node;
}

/*
 * stampa formattata del nodo passato per parametro
 * e i valori delle foglie
 */
void print_node(naryNode* node) {
    int i = 0;

    if(node == NULL) {
        printf(ANSI_YELLOW "Void node!" ANSI_RESET "\n");
        return;
    }
    //stampa il valore al centro e i figli sotto
    for(; i < node->n_leaves-1; i++)
        printf("  ");
    printf(ANSI_BLUE "%d" ANSI_RESET "\n", node->value);
    //se non ci sono foglie allora lo comunica
    if(node->n_leaves == 0) {
        printf(ANSI_CYAN "nil " ANSI_RESET "\n");
        return;
    }
    //se ci sono allora le stampa tutte
    for(i = 0; i < node->n_leaves; i++) {
        if(node->leaves[i] != NULL)
            printf(ANSI_CYAN "%d   ", node->leaves[i]->value);
        else
            printf(ANSI_CYAN "nil ");
    }
    printf(ANSI_RESET "\n");

}

/*
 * stampa formattata dell'albero n-ario,
 * se una foglia della radice iniziale ha a sua volta delle foglie
 * il formato di stampa e' il seguente:
 * [valore radice] foglie
 */
void print_tree(naryNode* root, int level) {
    int i = 0;

    if(root == NULL) {
        if(level == 0)
            printf(ANSI_YELLOW "Void tree!" ANSI_RESET "\n");
        return;
    }
    //se sono al livello 0 stampo il valore di root
    if(level == 0)
        print_node(root);
    //se la radice attuale ha piu' foglie allora ne stampa i valori
    else if(root->n_leaves != 0){
        printf(ANSI_BLUE "[%d] " ANSI_RESET, root->value);
        for(i = 0; i < root->n_leaves; i++) {
            if(root->leaves[i] != NULL)
                printf(ANSI_CYAN "%d   ", root->leaves[i]->value);
            else
                printf(ANSI_CYAN "nil ");
        }
        printf(ANSI_RESET "\n");
    }
    ++level;
    //stampa ricorsiva delle foglie che diventano a loro volta radici
    for(i = 0; i < root->n_leaves; i++) {
        if(root->leaves != NULL)
            print_tree(root->leaves[i], level);
    }
}

/*
 * aggiunge un nodo come foglia alla radice passata come parametro,
 * poi gli assegna il valore
 */
naryNode* add_node(naryNode* root, int val) {
    naryNode* new = NULL;

    new = init_node(val);
    if(root == NULL || new == NULL)
        return new;
    //aggiunge 1 al contatore (dimensione dell'array) delle foglie
    root->n_leaves++;
    //se questa nuova foglia e' la prima della radice allora esegue malloc
    if(root->n_leaves == 0) {
        root->leaves = (naryNode**) malloc(sizeof(naryNode*));
        //se fallisce ritorna semplicemente la testa
        if(root->leaves == NULL) {
            printf(ANSI_RED "Error on alloc new leaf to %d!"
                   ANSI_RESET "\n", root->value);
            return root;
        }
        //altrimenti assegna la foglia alla radice
        root->leaves[0] = new;
    }
    //altrimenti fa una realloc aggiungendo un elemento
    else {
        root->leaves = realloc(root->leaves,
                              sizeof(naryNode*)*(root->n_leaves));
        root->leaves[root->n_leaves-1] = new;
    }

    return root;
}

/*
 * aggiunge una foglia passata per parametro alla radice sempre passata
 */
naryNode* add_leaf(naryNode* root, naryNode* leaf) {

    if(root == NULL)
        return NULL;
    if(leaf == NULL)
        return root;
    //aggiunge 1 al contatore (dimensione dell'array) delle foglie
    root->n_leaves++;
    //se questa nuova foglia e' la prima della radice allora esegue malloc
    if(root->n_leaves == 0) {
        root->leaves = (naryNode**) malloc(sizeof(naryNode*));
        //se fallisce ritorna semplicemente la testa
        if(root->leaves == NULL) {
            printf(ANSI_RED "Error on alloc new leaf to %d!"
                   ANSI_RESET "\n", root->value);
            return root;
        }
        //altrimenti assegna la foglia alla radice
        root->leaves[0] = leaf;
    }
    //altrimenti fa una realloc aggiungendo un elemento
    else {
        root->leaves = realloc(root->leaves,
                              sizeof(naryNode*)*(root->n_leaves));
        if(root->leaves == NULL) {
            printf(ANSI_RED "Error on realloc new leaf to %d!"
                   ANSI_RESET "\n", root->value);
            return root;
        }
        root->leaves[root->n_leaves-1] = leaf;
    }

    return root;
}

/*
 * chiede man mano di inserire i valori per le foglie di ogni radice
 */
naryNode* fill_tree_user(naryNode* root, int max_leaf) {
    naryNode* tmp = NULL;
    int val = 0;
    char scelta = 0;
    int n_leaf = 0;
    int i = 0;
    int max = 0;

    if(root == NULL) {
        printf(ANSI_GREEN "Inserisci i valori di ogni foglia dell'albero"
               ANSI_RESET "\n");
    }
    else {
        printf(ANSI_GREEN "Inserisci i valori delle foglie di %d"
               ANSI_RESET "\n", root->value);
    }
    printf(ANSI_GREEN "['q' per terminare]\n");
    printf("['n' per saltare il prossimo nodo]:" ANSI_RESET "\n");
    //per il primo sottoalbero che include anche la radice di tutto
    //ne richiede un valore in piu'
    if(root == NULL)
        max = max_leaf+1;
    else
        max = max_leaf;
    while(1) {
        if(root != NULL)
            printf(ANSI_GREEN "[%d]" ANSI_RESET, root->value);
        else
            printf(ANSI_GREEN "ROOT" ANSI_RESET);
        //controllo sull'input
        val = getChar(&scelta);
        if(scelta == 'q')
            break;
        if(scelta != 'n') {
            //se il nodo e' nuovo allora lo crea
            if(root == NULL)
                root = add_node(root, val);
            //altrimenti aggiunge delle foglie alla radice
            else
                add_node(root, val);
            //se e' la radice dell'albero allora lo salva
            if(i == 0 && n_leaf == 0)
                tmp = root;
            n_leaf++;
        }
        if(n_leaf == max || scelta == 'n') {
            if(scelta != 'n')
                printf(ANSI_YELLOW "Raggiunto numero massimo di foglie!"
                       ANSI_RESET "\n");
            //print_tree(root, 0);
            for(i = 0; i < root->n_leaves; i++)
                fill_tree_user(root->leaves[i], max_leaf);
            break;
        }
    }

    return tmp;
}

/*
 * data la radice ritorna il puntatore della foglia in posizione "pos"
 */
naryNode* get_leaf_node(naryNode* root, int pos) {

    //effettua vari controlli sui parametri
    if(root == NULL || root->leaves == NULL || root->n_leaves == 0)
        return NULL;
    if(pos > root->n_leaves-1)
        return NULL;
    if(pos < 0)
        return NULL;

    //se tutto va bene allora ritorna il puntatore
    return root->leaves[pos];
}

/*
 * dealloca la radice e tutte le sue foglie
 */
int free_node(naryNode* root) {
    int i = 0;

    if(root == NULL)
        return 1;
    if(root->n_leaves == 0)
        free(root);
    else {
        for(; i < root->n_leaves; i++)
            free_node(root->leaves[i]);
        free(root);
    }

    return 0;
}

/*
 * dealloca la foglia in posizione scelta e le sue sottofoglie
 */
int free_subtree(naryNode* root, int pos) {

    //controlla che i parametri siano validi
    if(root == NULL)
        return 1;
    if(pos < 0)
        return 1;
    else if(pos > root->n_leaves-1)
        return 1;
    if(root->leaves[pos] == NULL)
        return 1;
    //per poi liberare il sottoalbero
    free_node(root->leaves[pos]);
    root->leaves[pos] = NULL;

    return 0;
}
