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
#include <limits.h> //INT_MAX
#include "colors.h" //printf colors

//massimo numero di caratteri per i nomi e cognomi
#ifndef MAX_CHAR
    #define MAX_CHAR 64
#endif

//firme
void getInt(int* x);
void getLimitInt(int* x, int min, int max);
void getFloat(float *x);
int checkNumber(char* str, size_t dim);
int getString(char** str);



/*
 * funzione di controllo dell'input di un intero solo positivo
 * params: puntatore alla variabile dove salvare l'input
 * return: void
 */
void getInt(int* x) {
    char* str = NULL; /* stringa dove verra' salvato l'input */
    int strDim = 0; /* lunghezza della stringa ritornata da getString */
    int valid = 0; /* flag di controllo se ci sono caratteri accettabili */

    //richiede di reinserire il valore finche' non e' un numero
    do {
        strDim = getString(&str);
        //controlla la stringa se e' davvero un numero
        valid = checkNumber(str, strDim);
        if(!valid)
            printf(ANSI_RED "Valore non valido!" ANSI_RESET "\n");
        //se e' un numero allora converte i caratteri in interi
        else
            *x = atoi(str);
    } while(!valid);

}

/*
 * funzione di controllo dell'input di un intero
 * con un valore minimo e un massimo (inclusi)
 * params: puntatore alla variabile dove salvare l'input
 *         valore minimo accettato
 *         valore massimo accettato
 * return: void
 */
void getLimitInt(int* x, int min, int max) {

    //richiede il valore finche' non e' tra il minimo e il massimo
    do {
        getInt(x);
        if(*x <= min || *x >= max)
            printf(ANSI_RED "Valore non valido!"
                   ANSI_YELLOW "(deve essere compreso tra %d e %d)"
                   ANSI_RESET "\n", min, max);
    } while(*x <= min || *x >= max);

}

/*
 * funzione che controlla se nella stringa passata ci sono solo numeri
 * e i caratteri accettabili
 * params: puntatore alla stringa da controllare
 *         dimensione della stringa
 * return: 1 in caso sia corretta, 0 nel caso ci sia almeno 1 carattere errato
 */
int checkNumber(char* str, size_t dim) {
    int i = 0; /* contatore generale */
    int nPunti = 0; /* accetta solamente 1 virgola per i decimali */

    for(i = 0; i < dim; i++) {
        //converte le virgole in punti e segna che ha trovato 1 punto
        if(str[i] == ',')
            str[i] = '.';
        //se non sono cifre controlla se e' il punto, altrimenti ritorna 0
        if(str[i] < 47 || str[i] > 57) {
            //se trova 1 punto aggiunge 1 al contatore
            if(str[i] == '.')
                nPunti++;
            else
                return 0;
            //ritorna 0 se ci sono piu' di 1 punto
            if(nPunti > 1)
                return 0;
        }
    }

    //se e' tutto valido ritorna True
    return 1;
}

/*
 * funzione che riceve una stringa dall'utente e la controlla
 * params: puntatore al puntatore della stringa dove salvare l'input
 * return: lunghezza della stringa
 */
int getString(char** str) {
    int lung = 0; /* */

    if( !(*str = (char*) malloc(sizeof(char)*MAX_CHAR)) ) {
        printf(ANSI_RED "Impossibile allocare l'array di studenti!"
               ANSI_RESET "\n");
        *str = NULL;
        return -1;
    }
    //controlla che riceva un input valido (accetta spazi)
    do {
        printf(ANSI_GREEN "-->\t" ANSI_RESET);
        *str = fgets(*str, MAX_CHAR, stdin);
	//se str contiene solo l'invio (lung = 1) allora l'input non e' valido
        lung = strlen(*str);
        //pulisce l'invio finale
        if (lung > 1 && (*(*str+lung-1) == '\n'))
            *(*str+lung-1) = '\0';
        //e richiede l'input nel caso la stringa non sia valida
        if(*str == NULL || lung == 1)
            printf(ANSI_RED "Stringa non valida! Re-inseriscila"
                   ANSI_RESET "\n");
    } while(*str == NULL || lung == 1);

    return strlen(*str);
}
