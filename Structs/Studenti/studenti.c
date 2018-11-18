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

#include <stdio.h> //printf, scanf
#include <stdlib.h> //malloc, free
#include <limits.h> //INT_MAX
#include "lib/colors.h" //ANSI_RED, ANSI_RESET
#include "lib/input_check.h" //getInt, getString
#include "lib/student.h" //newStudArr, readStud



int main(int argc, char** argv) {
    int n = 0;
    int scelta = 0;
    int pos = 0;
    int meritevoli = 0;
    char* fileName = NULL;
    studente* studs = NULL;

    //presentazione
    printf(ANSI_BLUE
           "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"
           "Programma dedicato alla gestione dei dati degli studenti.\n"
           "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"
           ANSI_RESET);
	//richiesta di quanti studenti si vogliono creare
    printf(ANSI_GREEN "Quanti studenti vuoi inserire?\n" ANSI_RESET);
    getLimitInt(&n, 1, INT_MAX);
    studs = newStudArr(n);
    //stampa del menu di gestione degli studenti
    do {
        printf(ANSI_GREEN "\nCosa vuoi fare?\n"
               ANSI_CYAN "1 - "
               ANSI_RESET "Inserire / modificare i dati \n"
               ANSI_CYAN "2 - "
               ANSI_RESET "Visualizzare i dati\n"
               ANSI_CYAN "3 - "
               ANSI_RESET "Salvare i dati su file\n"
               ANSI_CYAN "4 - "
               ANSI_RESET "Ricercare degli studenti migliori\n"
               ANSI_RED "0 - "
               ANSI_RESET "Uscire dal programma\n\n");
        getLimitInt(&scelta, 0, 4);

        switch(scelta) {
            //modifica dei dati degli studenti
            case 1:
                printf(ANSI_GREEN "Vuoi modificarne 1 o tutti?\n"
                       "[1 - 2 (tutti) - 3 (leggi da file tutti)]\n"
                       ANSI_RESET);
                getLimitInt(&pos, 1, 3);
                //inserimento dei dati dei singoli studenti
                if(pos == 1) {
                    printf(ANSI_GREEN "Inserisci la posizione in cui si vuole "
                           "inserire i dati:\n[da 0 a %d]\n" ANSI_RESET, n);
                    getLimitInt(&pos, 0, n-1);
                    if(!compileStud(studs, n, pos))
                        printf(ANSI_RED "Nessuna modifica apportata...\n"
                               ANSI_RESET);
                }
                //inserimento in blocco
                else if(pos == 2){
                    compileAllStud(studs, n);
                }
                else {
                    //legge da un file formattato
					printf(ANSI_GREEN "Da dove lo vuoi leggere?\n" ANSI_RESET);
	                getString(&fileName);
	                readStud(studs, n, fileName);
                }
                break;
            //stampa dell'array di studenti
            case 2:
                printf(ANSI_BLUE "\n\nSTUDENTI:\n");
                for(pos = 0; pos < n; pos++)
                    printPosStud(studs, pos);
                break;
            //salva i dati su file
            case 3:
                printf(ANSI_GREEN "Dove lo vuoi salvare?\n" ANSI_RESET);
                getString(&fileName);
                saveStud(studs, n, fileName);
                break;
            //ricerca studenti migliori e li stampa
            //e stampa totale degli studenti meritevoli
            case 4:
                printf(ANSI_BLUE "Numero degli studenti meritevoli = %d\n"
                       ANSI_RESET, findBestStud(studs, n, 1));
                break;
            //nel caso l'utente inserisce 0 o altro esce
            default:
                printf(ANSI_RED "Uscita dal programma...\n" ANSI_RESET);
                return 0;
        }
    } while(scelta);

    free(fileName);
    free(studs);
	return 0;
}
