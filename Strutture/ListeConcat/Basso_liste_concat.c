/*
 * Basso Nicola
 * 4^AI
 */
/*
 * Liste concatenate NATALE 2018
 * Nel gioco del lotto ci sono 11 ruote,
 * a ciascuna sono legati 5 numeri estratti casualmente e compresi tra 1 e 90.
 * Realizzare un programma per rappresentare le estrazioni di una serata
 * (si generi casualmente ogni numero estratto) mediante una lista di 11 nodi
 * dove ciascuno sarà contraddistinto dal numero di ruota
 * e punterà contemporaneamente sia al nodo della ruota successiva
 * e sia al primo elemento della lista
 * dei cinque estratti legati alla ruota stessa.
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
                value = length_list(list);
                if(value)
                    printf(ANSI_GREEN "La lista ha una lunghezza di %d elementi"
                           ANSI_RESET "\n", value);
                else
                    printf(ANSI_YELLOW "La lista ha lunghezza 0!"
                           ANSI_RESET "\n");
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
                findPrintNode_list(list, value);
                break;
            //elimina ultimo elemento inserito
            case 7:
                //se la lista e' vuota non esegue nulla
                if(list == NULL) {
                    printf(ANSI_RED "Lista vuota!\n"
                           "Impossibile eliminare elementi!" ANSI_RESET "\n");
                    break;
                }
                //stampa dati ultimo elemento se presente
                printNode_list(getNode_list(list, length_list(list)-1) );
                //richiesta conferma
                printf(ANSI_BLUE
                       "Siete sicuri di voler eleminare questo elemento?\n"
                       ANSI_CYAN "[0 = no, 1 = si]" ANSI_RESET "\n");
                getLimitInt(&confirm, 0, 1);
                //eliminazione elemento se confermato
                if(confirm)
                    list = remNode_list(list, length_list(list)-1);
                break;
            //elimina alcuni degli ultimi elementi inseriti
            case 8: //TODO
                //richiesta quanti elementi
                printf(ANSI_BLUE
                       "Quanti degli ultimi elementi volete eliminare?\n"
                       ANSI_CYAN "[da 0 a %d]"
                       ANSI_RESET "\n", length_list(list));
                //controllo sul valore inserito
                getLimitInt(&value, 0, length_list(list));
                //stampa di n ultimi elementi
                print_list((found = getNode_list(list, length_list(list)-value)));
                //richiesta conferma
                printf(ANSI_BLUE
                       "Siete sicuri di voler eleminare questi elementi?\n"
                       ANSI_CYAN "[0 = no, 1 = si]" ANSI_RESET "\n");
                getLimitInt(&confirm, 0, 1);
                //eliminazione elementi se confermato
                if(confirm) {
                    //se ha deciso di eliminare tutto allora porta a NULL
                    if(value == length_list(list))
                        list = NULL;
                    //libera da lunghezza - punto di partenza di eliminazione
                    free_list(found);
                }
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
