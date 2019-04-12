/*
 * Basso Nicola
 * 4^AI
 */
/*
 * libreria contenente funzioni di input formattati e controllati
 */

#include <stdio.h> //printf
#include <stdlib.h> //atoi, malloc
#include <string.h> //strlen
#include "colors.h" //printf colors

//massimo numero di caratteri per i nomi e cognomi
#ifndef MAX_CHAR
    #define MAX_CHAR 50
#endif

//firme
void getInt(int* x);
void getLimitInt(int* x, int min, int max);
void getString(char** str);



/*
 * funzione di controllo dell'input di un intero solo positivo
 * params: puntatore alla variabile dove salvare l'input
 * return: void
 */
void getInt(int* x) {
    char* str = NULL;

    do {
        //printf(ANSI_GREEN "-->\t" ANSI_RESET);
        //scanf(" %d", &*x);
        //getchar();
        getString(&str);
        *x = atoi(str);
        if(x == NULL)
            printf(ANSI_RED
                   "Valore non valido!\n"
                   ANSI_RESET);
    } while(x == NULL);

}

/*
 * funzione di controllo dell'input di un intero
 * con un valore minimo e un massimo
 * params: puntatore alla variabile dove salvare l'input
 *         valore minimo accettato
 *         valore massimo accettato
 * return: void
 */
void getLimitInt(int* x, int min, int max) {
    char* str = NULL;

    do {
        //printf(ANSI_GREEN "-->\t" ANSI_RESET);
        //scanf(" %d", &*x);
        //getchar();
        getString(&str);
        *x = atoi(str);
        if(*x < min || *x > max)
            printf(ANSI_RED
                   "Valore non valido! (deve essere compreso tra %d e %d)\n"
                   ANSI_RESET, min, max);
    } while(*x < min || *x > max);

}

/*
 * funzione che riceve una stringa dall'utente e la controlla
 * params: puntatore al puntatore della stringa dove salvare l'input
 * return: void
 */
void getString(char** str) {
    int lung = 0;

    if( !(*str = (char*) malloc(sizeof(char)*MAX_CHAR)) ) {
        printf(ANSI_RED
               "Impossibile allocare l'array di studenti!\n"
               ANSI_RESET);
        *str = NULL;
        return;
    }
    //controlla che riceva un input valido (accetta spazi)
    do {
        printf(ANSI_GREEN "-->\t" ANSI_RESET);
        *str = fgets(*str, MAX_CHAR, stdin);
        lung = strlen(*str);
        //pulisce l'invio finale
        if (lung && (*(*str+lung-1) == '\n'))
            *(*str+lung-1) = '\0';
        //e richiede l'input nel caso la stringa non sia valida
        if(*str == NULL || !lung)
            printf(ANSI_RED
                   "Stringa non valida! Re-inseriscila\n"
                   ANSI_RESET);
    } while(*str == NULL || !lung);

}
