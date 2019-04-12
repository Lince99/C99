/*
 * Basso Nicola
 * 4^AI
 */
/*
 * Lista Bidirezionale
 * Definire una lista di interi, bidirezionale.
 * In questa lista ogni nodo dovra’ avere un puntatore al nodo precedente
 * (prev) e un puntatore al nodo successivo della lista (next),
 * oltre al valore contenuto (val, un intero).
 * Naturalmente se il nodo precedente o il nodo successivo non esistesse,
 * il corrispondente puntatore sarebbe NULL.
 * Si noti che a differenza delle liste semplici, per manipolare una lista
 * bidirezionale basta avere un puntatore a uno qualunque dei suoi nodi,
 * non necessariamente alla testa.
 * Scrivere una programma nel cui main viene inizializzata una lista
 * bidirezionale con 6 valori casuali.
 * Scrivere una funzione stampa_lista che, ricevuto un puntatore a un
 * nodo qualsiasi di una lista bidirezionale, stampi la lista
 */

#include <stdio.h>
#include <time.h>
#include "./lib/colors.h"
#include "./lib/input_check.h"
#include "./lib/bidir_list.h"

//firme
void getRandInt(int* x, int min, int max);
listNode* init_rand_list(int min, int max, int dim);



int main(int argc, char** argv) {
    unsigned int dim = 0; /* vdimensione della lista bidirezionale */
    int min = 0; /* valore massimo per il random */
    int max = 0; /* valore minimo per il random */
    int value = 0; /* valori random da inserire nell'array */
    listNode* list = NULL; /* lista utilizzata dal programma */
    srand((unsigned) time(NULL)); /* inizializza il seed per il random */

    //chiede la dimensione della lista
    printf(ANSI_GREEN "Inserisci la dimensione della lista:" ANSI_RESET "\n");
    getLimitInt(&dim, 0, INT_MAX);
    //inizializza la lista con numeri casuali scelti dall'utente
    printf(ANSI_GREEN "Qual'e' il numero minore generabile?" ANSI_RESET "\n");
    getInt(&min);
    printf(ANSI_GREEN "Qual'e' il numero maggiore generabile?" ANSI_RESET "\n");
    do {
        getInt(&max);
        if(max < min)
            printf(ANSI_YELLOW "Il numero inserito non e' valido!\n"
                   "Deve essere maggiore o uguale di %d!" ANSI_RESET "\n", min);
    } while(max < min);
    //crea la lista
    list = init_rand_list(min, max, dim);
    //stampa la lista creata
    print_list(list);

    return 0;
}

/*
 * Funzione che inizializza a random dim valori della lista bidirezionale
 */
listNode* init_rand_list(int min, int max, int dim) {
    listNode* head = NULL;
    unsigned int i = 0;
    int rand = 0;

    for(; i < dim; i++) {
        getRandInt(&rand, min, max);
        head = addTail_list(head, rand);
    }

    return head;
}

/*
 * Funzione che inizializza a random il valore di x dati i limiti
 */
void getRandInt(int* x, int min, int max) {

    if(x == NULL)
        x = (int*) malloc(sizeof(int));
    //assegna il valore random delimitato tra min e max
    *x = min + (int)(rand()%max);

}
