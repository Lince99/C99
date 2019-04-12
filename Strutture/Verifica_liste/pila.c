/*
 * Basso Nicola
 * 4^AI
 * 21/01/2019
 */

/*
 * Sviluppare un programma per inserire in una pila una serie di N
 * numeri interi, chiedere all'utente quanti ne vuole rimuovere e ricopiare,
 * dopo ogni estrazione, l'elemento in una seconda pila.
 * Stampare la prima pila dopo l'inserimento e dopo l'estrazione,
 * stampare anche la seconda pila con in nuovi elementi provenienti dalla prima.
 * Definire gli opportuni sottoprogrammi per:
 *
 * creare la pila
 * inserire in testa
 * pop
 * push
 * stampa
 */

#include <stdio.h>
#include <stdlib.h>
#include "lib/tail.h"



int main(int argc, char** argv) {
    pila* first = NULL;
    pila* second = NULL;
    int N = 0;
    int move = 0;
    int i = 0;

    //richiesta della quantita' di elementi da usare
    printf("Quanti interi vuoi usare?\n");
    scanf("%d", &N);
    if(N == 0) {
        printf("Impossibile procedere con 0 elementi!");
        return 1;
    }
    printf("Quanti elementi vuoi rimuovere dalla prima pila per metterli nella seconda?\n");
    do {
        scanf("%d", &move);
        if(move >= N)
            printf("Non puoi spostare piu' elementi di quelli esistenti!\n");
    } while(move >= N);
    //aggiunge gli elementi
    for(; i <= N; i++) {
        if(i == 0)
            first = push(first, i);
        else
            push(first, i);
    }
    printf("Prima Pila:\n");
    print_list(first);

    //sposta gli elementi dalla prima alla seconda
    for(i = 0; i < move; i++) {
        second = push_node(second, pop(first));
    }
    printf("\nSposta gli elementi dalla prima alla seconda:\n");
    printf("Prima Pila:\n");
    print_list(first);
    printf("Seconda Pila:\n");
    print_list(second);

    return 0;
}
