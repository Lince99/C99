/*
 * Basso Nicola
 * 4^AI
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * funzione che stampa tutte le informazioni dei parametri disponibili
 * params: intero che descrive la dimensione dell'array di parametri
 *         array di stringhe con tutti i parametri
 * return: void
 */
void printHelp(int argc, char** argv) {
    int i = 0;
    int flag = 0; /* controlla se alcuni comandi sono gia' stati inseriti */

    for(i = 1; i < argc; i++) {
        //se e' la prima volta che trova -h o --help
        if(!flag &&
          (strcmp(argv[i], "-h") ||
           strcmp(argv[i], "-?") ||
           strcmp(argv[i], "--help") )) {
            //stampa le informazioni base sull'utilizzo del programma
            printf( "Use: %s [OPTION...] [VALUES...]\n"
                    "Options:\n"
                    "  -h, --help\t\tDisplay this information\n",
                    *argv );
                    //TODO aggiungere le informazioni sui campi qui
            flag = 1;
        }
    }
}



/*
 * funzione che cerca i parametri passati nella matrice
 * ed estrae il valore scelto
 * params: intero che descrive la dimensione dell'array di parametri
 *         array di stringhe con tutti i parametri
 *         stringa che descrive l'opzione
 *         stringa che descrive l'opzione con il parametro esteso
 * return: void
 */
int* getInt(int argc, char** argv, char* option, char* fullOption) {
    int i = 0;
    int* val = NULL;

    val = (int*) malloc(sizeof(int));
    for(i = 1; i < argc-1; i++) {
        if(strchr(argv[i+1], '-') == NULL &&
          (strcmp(argv[i], option) ||
           strcmp(argv[i], fullOption) )) {
            *val = atoi(argv[i+1]);
            return val;
        }
    }

    return NULL;
}

/*
 * funzione che cerca i parametri passati nella matrice
 * ed estrae la stringa inserita
 * params: intero che descrive la dimensione dell'array di parametri
 *         array di stringhe con tutti i parametri
 *         stringa che descrive l'opzione
 *         stringa che descrive l'opzione con il parametro esteso
 * return: void
 */
char* getChars(int argc, char** argv, char* option, char* fullOption) {
    int i = 0;
    char* str = NULL;
    int max_len = 50;

    str = (char*) malloc(sizeof(char)*max_len);
    for(i = 1; i < argc-1; i++) {
        if(strchr(argv[i+1], '-') == NULL &&
          (strcmp(argv[i], option) ||
           strcmp(argv[i], fullOption) )) {
            str = argv[i+1];
            //TODO aggiungere realloc per risparmiare memoria
            return str;
        }
    }

    return NULL;
}
