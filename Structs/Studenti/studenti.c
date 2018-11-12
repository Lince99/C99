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
#include <limits.h>
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
int compileStud(studenti* studs, int dim, int pos);
int compileAllStud(studenti* studs, int dim);
void printPosStud(studenti* studs, int dim, int pos);
int isEmptyStud(studenti* studs, int dim, int pos);
void getInt(int* x);
void getLimitInt(int* x, int min, int max);
void getString(char* str);
studenti* newArr(int dim);



int main(int argc, char** argv) {
    int n = 0;
    int sogliaVoto = 0;
    int anniRichiesti = 0;
    int scelta = 0;
    int pos = 0;
    studenti* studs = NULL;

    //presentazione
    printf(ANSI_BLUE
           "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"
           "Programma dedicato alla gestione dei dati degli studenti.\n"
           "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"
           ANSI_RESET);
	//richiesta di quanti studenti si vogliono creare
    printf(ANSI_GREEN "Quanti studenti vuoi inserire?\n" ANSI_RESET);
    getLimitInt(&n, 0, INT_MAX);
    studs = newArr(n);
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
                       "[1 - qualsiasi numero]\n"
                       ANSI_RESET);
                getInt(&pos);
                //inserimento dei dati dei singoli studenti
                if(pos == 1) {
                    printf("Inserisci la posizione in cui si vuole "
                           "inserire i dati:\n");
                    getLimitInt(&pos, 0, n-1);
                    if(compileStud(studs, n, pos))
                        printf(ANSI_RED "Nessuna modifica apportata..."
                               ANSI_RESET);
                }
                //inserimento in blocco
                else {
                    compileAllStud(studs, n);
                }
                break;
            //stampa dell'array di studenti
            case 2:
                printf(ANSI_MAGENTA "\n\nSTUDENTI:\n");
                for(pos = 0; pos < n; pos++)
                    printPosStud(studs, n, pos);
                break;
            //salva i dati su file //TODO
            case 3:
                break;
            //ricerca studenti migliori
            //e stampa totale degli studenti meritevoli
            case 4:
                break;
            //nel caso l'utente inserisce 0 o altro esce
            default:
                printf(ANSI_RED "Uscita dal programma...\n" ANSI_RESET);
                return 0;
        }
    }while(scelta);

	return 0;
}



/*
 * funzione di inserimento dei dati in uno studente
 * params: puntatore all'array di studenti
 *         dimensione dell'array
 *         posizione in cui modificare i dati
 * return: un intero che vale 1 in caso di inserimento valido
 *         e 0 in caso di non inserimento
 */
int compileStud(studenti* studs, int dim, int pos) {
    int flag = 0;

    //se ci sono dei dati li stampa
    if(!isEmptyStud(studs, dim, pos)) {
        printf(ANSI_RED "Elementi presenti in posizione %d\n" ANSI_RESET, pos);
        printPosStud(studs, dim, pos);
        //e chiede all'utente se e' sicuro di sovrascriverli
        printf(ANSI_BLUE "Vuoi modificarli? [1 = si, 0 = no]\n" ANSI_RESET);
        getLimitInt(&flag, 0, 1);
        if(!flag)
            return 0;
    }

    //chiede all'utente tutti i dati dello studente
    //cognome
    printf(ANSI_GREEN "Cognome: " ANSI_RESET);
    getString(((studs+pos)->cognome));
    //nome
    printf(ANSI_GREEN "Nome: " ANSI_RESET);
    getString(((studs+pos)->nome));
    //corso
    printf(ANSI_GREEN "Corso attuale: " ANSI_RESET);
    getLimitInt(&((studs+pos)->corso), 1900, 2100);
    //voto
    printf(ANSI_GREEN "Voto: " ANSI_RESET);
    getLimitInt(&((studs+pos)->voto), 0, 10);
    //anni_iscrizione
    printf(ANSI_GREEN "Anni di iscrizione: " ANSI_RESET);
    getLimitInt(&((studs+pos)->corso), 0, 30);

    return 1;
}

/*
 * funzione di inserimento dei dati di tutti gli studenti
 * params: puntatore all'array di studenti
 *         dimensione dell'array
 * return: un contatore di quanti dati sono stati inseriti
 */
int compileAllStud(studenti* studs, int dim) {
    int count = 0;
    int pos = 0;

    for(pos = 0; pos < dim; pos++) {
        if(compileStud(studs, dim, pos))
            count++;
    }

    return count;
}

/*
 * funzione di inserimento dei dati in uno studente
 * params: puntatore all'array di studenti
 *         dimensione dell'array
 *         posizione in cui andare a leggere
 * return: void
 */
void printPosStud(studenti* studs, int dim, int pos) {

    printf(ANSI_MAGENTA "Studente numero %d\n", pos);
    //se non ci sono dati avvisa l'utente
    if(isEmptyStud(studs, dim, pos))
        printf(ANSI_RED "Nessun dato...\n" ANSI_RESET);
    else
        printf("%s %s, frequenta il corso %d, iscritto/a da %d anni, \n"
               "Ha una media di voti pari a %d.\n" ANSI_RESET,
               *(studs[pos].cognome), *(studs[pos].nome),
               studs[pos].corso, studs[pos].anni_iscrizione,
               studs[pos].voto);

}

/*
 * funzione di controllo se un elemento nell'array contiene dei dati
 * params: puntatore all'array di studenti
 *         dimensione dell'array
 *         posizione in cui andare a leggere
 * return: un intero che vale 1 in caso di elemento vuoto
 *         e 0 in caso di presenza di almeno 1 dato
 */
int isEmptyStud(studenti* studs, int dim, int pos) {

    if(!studs[pos].cognome)
        return 0;
    else if(!studs[pos].nome)
        return 0;
    else if(!studs[pos].corso)
        return 0;
    else if(!studs[pos].voto)
        return 0;
    else if(!studs[pos].anni_iscrizione)
        return 0;

    return 1;
}

/*
 * funzione di controllo dell'input di un intero solo positivo
 * params: puntatore alla variabile dove salvare l'input
 * return: void
 */
void getInt(int* x) {

    do {
        printf(ANSI_RESET "-->\t");
        scanf(" %d", &*x);
        getchar();
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

    do {
        printf(ANSI_RESET "-->\t");
        scanf(" %d", &*x);
        getchar();
        if(*x < min || *x > max)
            printf(ANSI_RED
                   "Valore non valido! (deve essere compreso tra %d e %d)\n"
                   ANSI_RESET, min, max);
    } while(*x < min || *x > max);

}

/*
 * funzione che riceve una stringa dall'utente e la controlla
 * params: puntatore alla variabile dove salvare l'input
 * return: void
 */
void getString(char* str) {

    //controlla che riceva un input valido (accetta spazi)
    do {
        printf(ANSI_RESET "-->\t");
        str = fgets(str, MAX_CHAR, stdin);

        if(str == NULL)
            printf(ANSI_RED
                   "Stringa non valida! Re-inseriscila\n"
                   ANSI_RESET);
    } while(str == NULL);

}

/*
 * funzione che ritorna il puntatore della nuova array di studenti allocata
 * con tutti i valori a 0 e con i controlli se c'e' spazio per allocarla
 * params: dimensione dell'array
 * return puntatore alla prima struttura dell'array
 */

studenti* newArr(int dim) {
    studenti* st = NULL;

    if(!(st = (studenti*)calloc(dim, sizeof(studenti)))) {
        printf(ANSI_RED
               "Impossibile allocare l'array di studenti!\n"
               ANSI_RESET);
        return NULL;
    }

    return st;
}
