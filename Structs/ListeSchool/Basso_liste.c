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
#include "./lib/colors.h"
#include "./lib/input_check.h"
#include "./lib/list.h"

//firme
int print_menu();



int main(int argc, char** argv) {
    unsigned int scelta = 0; /* valore della scelta fatta dall'utente */
    unsigned int confirm = 0; /* flag usato per confermare operazioni */
    int value = 0; /* valore inserito dall'utente utilizzato dalla lista */
    listNode* list = NULL; /* lista utilizzata dal programma */
    listNode* found = NULL; /* nodo trovato dalla funzione di ricerca */

	//introduzione
	printf(ANSI_BG_RED "- - - - - - - - - - - - - - - - - - - - - -"
		   ANSI_RESET "\n"
		   ANSI_BG_RED "- - - - PROGRAMMA DI TEST PER LISTE - - - -"
		   ANSI_RESET "\n"
		   ANSI_BG_RED "- - - - - - - - - - - - - - - - - - - - - -"
		   ANSI_RESET "\n");

    //continua a chiedere finche' non inserisce 0
    do {
        //stampa del menu e richiesta input
	    scelta = print_menu();
        //esegue l'operazione scelta
        switch(scelta) {
            //crea una lista vuota
            case 1:
                //controlla se la lista e' piena
                if(list != NULL)
                    list = free_list(list);
                printf(ANSI_GREEN "Lista vuota creata!" ANSI_RESET "\n");
                break;
            //inserimento valore nella lista
            case 2:
                //richiesta di inserimento in testa o in coda
                printf(ANSI_BLUE "Vuoi inserire l'elemento in testa o in coda?"
                       "\n" ANSI_CYAN "[0 = testa, 1 = coda]" ANSI_RESET "\n");
                getLimitInt(&confirm, 0, 1);
                //richiesta elemento
                printf(ANSI_BLUE "Inserisci il valore da inserire nella lista:"
                       ANSI_RESET "\n");
                getInt(&value);
                //aggiunta elemento
                if(confirm == 0)
                    //in testa
                    list = addHead_list(list, value);
                else
                    //o in coda
                    list = addTail_list(list, value);
                break;
            //lunghezza della lista
            case 3:
                //stampa della lunghezza
                printf(ANSI_GREEN "La lista ha una lunghezza di %d elementi"
                       ANSI_RESET "\n", length_list(list));
                break;
            //controllo se e' vuota
            case 4:
                //stampa vero / falso
                if(length_list(list) == 0)
                    printf(ANSI_YELLOW "La lista e' vuota!" ANSI_RESET "\n");
                else
                    printf(ANSI_GREEN "La lista non e' vuota." ANSI_RESET "\n");
                break;
            //stampa della lista
            case 5:
                //stampa formattata
                printf(ANSI_GREEN "Lista salvata:" ANSI_RESET "\n");
                print_list(list);
                break;
            //ricerca elemento
            case 6:
                //richiesto elemento
                printf(ANSI_BLUE "Inserisci il valore da cercare nella lista:"
                       ANSI_RESET "\n");
                getInt(&value);
                //stampa della prima occorrenza
                found = findNode_list(list, value);
                printNode_list(found);
                break;
            //elimina ultimo elemento inserito
            case 7: //TODO
                //stampa dati ultimo elemento
                //richiesta conferma
                //eliminazione elemento
                break;
            //elimina alcuni degli ultimi elementi inseriti
            case 8: //TODO
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

    free_list(list);
    return 0;
}

/*
 * funzione di stampa e richiesta delle possibili operazioni con le liste
 */
int print_menu() {
    unsigned int scelta = 0;

    //stampa delle scelte
    printf("\n\n\n");
	printf(ANSI_CYAN "1 - " ANSI_WHITE
           ANSI_UNDERLINE "Crea" ANSI_NOT_OVERLINE " una "
           ANSI_UNDERLINE "lista vuota"
           ANSI_RESET "\n");
    printf(ANSI_CYAN "2 - " ANSI_WHITE
           ANSI_UNDERLINE "Inserisci" ANSI_NOT_OVERLINE " un "
           ANSI_UNDERLINE "valore" ANSI_NOT_OVERLINE " nella lista"
           ANSI_RESET "\n");
    printf(ANSI_CYAN "3 - " ANSI_WHITE
           "Determina la " ANSI_UNDERLINE "lunghezza"
           ANSI_NOT_OVERLINE " della lista"
           ANSI_RESET "\n");
    printf(ANSI_CYAN "4 - " ANSI_WHITE
           "La lista " ANSI_UNDERLINE "e' vuota?"
           ANSI_RESET "\n");
    printf(ANSI_CYAN "5 - " ANSI_WHITE
           ANSI_UNDERLINE "Stampa" ANSI_NOT_OVERLINE " gli elementi della lista"
           ANSI_RESET "\n");
    printf(ANSI_CYAN "6 - " ANSI_WHITE
           ANSI_UNDERLINE "Cerca" ANSI_NOT_OVERLINE " un elemento nella lista"
           ANSI_RESET "\n");
    printf(ANSI_CYAN "7 - " ANSI_WHITE
           ANSI_UNDERLINE "Elimina" ANSI_NOT_OVERLINE " l'ultimo "
           ANSI_UNDERLINE "elemento" ANSI_NOT_OVERLINE " inserito"
           ANSI_RESET "\n");
    printf(ANSI_CYAN "8 - " ANSI_WHITE
           ANSI_UNDERLINE "Elimina" ANSI_NOT_OVERLINE " una parte degli "
           ANSI_UNDERLINE "ultimi valori" ANSI_NOT_OVERLINE " inseriti"
           ANSI_RESET "\n");

    printf(ANSI_RED "0 - " ANSI_WHITE
           ANSI_UNDERLINE "Esci" ANSI_NOT_OVERLINE " dal programma..."
           ANSI_RESET "\n");

    //richiede l'opzione tra quelle presenti nel menu da eseguire
    getLimitInt(&scelta, 0, 8);

    return scelta;
}
