/*
 * Basso Nicola
 * 4^AI
 */
/*
 * lista nov 2018
 * eseguire un programma in linguaggio C con la creazione di lista,
 * l'utente sceglierà le operazioni da eseguire attraverso un menu:
 * creare lista vuota,
 * inserire i valori
 * determinare lunghezza lista
 * sapere se la lista è vuota
 * stampare gli elementi della lista
 * cercare un elemento in base al valore,
 * se c'è allora restituire il puntatore all'elemento
 * eliminare l'ultimo elemento inserito
 * eliminare alcuni valori (gli ultimi n valori inseriti)
 */

#include <stdio.h>
#include "lib/colors.h"
#include "lib/input_check.h"

//firme
int print_menu();



int main(int argc, char** argv) {
	unsigned int scelta = 0; /* valore della scelta fatta dall'utente */

	//introduzione
	printf(ANSI_BG_RED "- - - - - - - - - - - - - - - - - - - - - -"
		   ANSI_RESET "\n"
		   ANSI_BG_RED "- - - - PROGRAMMA DI TEST PER LISTE - - - -"
		   ANSI_RESET "\n"
		   ANSI_BG_RED "- - - - - - - - - - - - - - - - - - - - - -"
		   ANSI_RESET "\n\n");

    //continua a chiedere finche' non inserisce 0
    do {
        //stampa del menu e richiesta input
	    scelta = print_menu();
        //TODO
        switch(scelta) {
            //crea una lista vuota
            case 1:
                break;
            //inserimento valore nella lista
            case 2:
                //richiesta di inserimento in testa o in coda
                //richiesta elemento
                //aggiunta elemento
                break;
            //lunghezza della lista
            case 3:
                //stampa della lunghezza
                break;
            //controllo se e' vuota
            case 4:
                //stampa vero / falso
                break;
            //stampa della lista
            case 5:
                //stampa formattata
                break;
            //ricerca elemento
            case 6:
                //richiesto elemento
                //stampa dei vari risultati
                break;
            //elimina ultimo elemento inserito
            case 7:
                //stampa dati ultimo elemento
                //richiesta conferma
                //eliminazione elemento
                break;
            //elimina alcuni degli ultimi elementi inseriti
            case 8:
                //richiesta quanti elementi
                //stampa di n ultimi elementi
                //richiesta conferma
                //eliminazione elementi
                break;
            //in caso sia 0 uscita dal programma
            default:
                printf(ANSI_RED "Uscita dal programma..." ANSI_RESET "\n\n");
                break;
        }
    } while(scelta != 0);

	return 0;
}

/*
 * funzione di stampa e richiesta delle possibili operazioni con le liste
 */
int print_menu() {
    unsigned int scelta = 0;

    //stampa delle scelte
	printf(ANSI_CYAN "1 - " ANSI_BLUE
           "Crea una lista vuota"
           ANSI_RESET "\n");
    printf(ANSI_CYAN "2 - " ANSI_BLUE
           "Inserisci un valore nella lista"
           ANSI_RESET "\n");
    printf(ANSI_CYAN "3 - " ANSI_BLUE
           "Determina la lunghezza della lista"
           ANSI_RESET "\n");
    printf(ANSI_CYAN "4 - " ANSI_BLUE
           "La lista e' vuota?"
           ANSI_RESET "\n");
    printf(ANSI_CYAN "5 - " ANSI_BLUE
           "Stampa gli elementi della lista"
           ANSI_RESET "\n");
    printf(ANSI_CYAN "6 - " ANSI_BLUE
           "Cerca un elemento nella lista"
           ANSI_RESET "\n");
    printf(ANSI_CYAN "7 - " ANSI_BLUE
           "Elimina l'ultimo elemento inserito"
           ANSI_RESET "\n");
    printf(ANSI_CYAN "8 - " ANSI_BLUE
           "Elimina una parte degli ultimi valori inseriti"
           ANSI_RESET "\n");

    printf(ANSI_RED "0 - " ANSI_BLUE
           "Inserisci 0 per uscire..."
           ANSI_RESET "\n");

    //richiede l'opzione tra quelle presenti nel menu da eseguire
    getLimitInt(&scelta, 0, 8);

    return scelta;
}
