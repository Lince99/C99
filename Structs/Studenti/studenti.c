/*
 * Basso Nicola
 * 4^AI
 */
/*
 * Definire ed implementare una struttura studenti che consenta di memorizzare
 * Cognome, nome, corso(int) , voto(int), e  anni di iscrizione.
 * Implementare le funzioni che consentano di inserire "n" studenti
 * dove n viene chiesto all'utente, fare la stampa di tutti gli studenti.
 * Aggiungere una funzione che trovi gli studenti migliori
 * secondo i seguenti criteri:
 * dopo aver chiesto all'utente la soglia voto e numeri di anni di iscrizione,
 * stampare gli studenti che rientrano nel range,
 * la funzione deve anche restituire il numero totale
 * di studenti meritevoli trovati.
 */

#include <stdio.h>
#include <stdlib.h>
#include "colors.h"

//massimo numero di caratteri per i nomi e cognomi
#define MAX_CHAR 50

//tipo di dato "studenti" con i dati base richiesti dal programma
typedef struct STUDENTI {
	char* cognome;
	char* nome;
	int corso;
	int voto;
	int anni_iscrizione;
} studenti;

//firme
void getInt(int* x);
studenti* newArr(int dim);



int main(int argc, char** argv) {
    int n = 0;
    int sogliaVoto = 0;
    int anniRichiesti = 0;
    studenti* studs = NULL;

    printf(ANSI_COLOR_BLUE
           "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"
           "Programma dedicato alla gestione dei dati degli studenti.\n"
           "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"
           ANSI_COLOR_RESET);
	//richiesta di quanti studenti si vogliono creare
    printf("Quanti studenti vuoi inserire?\n");
    getInt(&n);
	//inserimento dei dati dei singoli studenti
    studs = newArr(n);
	//stampa dell'array di studenti

	//ricerca studenti migliori
	//stampa totale degli studenti meritevoli

	return 0;
}

/*
 * funzione di controllo dell'input di un intero solo positivo
 * params: puntatore alla variabile dove salvare l'input
 * return: void
 */
void getInt(int* x) {

    do {
        printf("-->\t");
        scanf("%d", &*x);
        if(*x < 0)
            printf(ANSI_COLOR_RED
                   "Valore non valido! (solo positivi)\n"
                   ANSI_COLOR_RESET);
    } while(*x < 0);

}

/*
 * funzione che ritorna il puntatore della nuova array di studenti allocata
 * con tutti i parametri a 0 e con i controlli se c'e' spazio per allocarla
 * params: dimensione dell'array
 * return puntatore alla prima struttura dell'array
 */

studenti* newArr(int dim) {
    studenti* st = NULL;

    if(!(st = (studenti*)calloc(dim, sizeof(studenti)))) {
        printf(ANSI_COLOR_RED
               "Impossibile allocare l'array di studenti!\n"
               ANSI_COLOR_RESET);
        return NULL;
    }

    return st;
}
