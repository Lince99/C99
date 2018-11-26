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
#include "colors.h"
#include "input_check.h"

int main(int argc, char** argv) {
	int scelta = 0; /*valore corrispondente alla scelta fatta dall'utente */

	//introduzione
	printf(ANSI_BG_RED "- - - - - - - - - - - - - - - - - - - - - -"
		   ANSI_RESET "\n"
		   ANSI_BG_RED "- - - - PROGRAMMA DI TEST PER LISTE - - - -"
		   ANSI_RESET "\n"
		   ANSI_BG_RED "- - - - - - - - - - - - - - - - - - - - - -"
		   ANSI_RESET "\n\n");

	//stampa del menu e richiesta input


	return 0;
}
