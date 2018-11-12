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
#include "input_check.h"

//tipo di dato "studenti" con i dati base richiesti dal programma
typedef struct STUDENTI {
	char* cognome;
	char* nome;
	int corso;
	int voto;
	int anniIscrizione;
} studenti;

//firme
studenti* newStudArr(int dim);
int compileStud(studenti* studs, int dim, int pos);
int compileAllStud(studenti* studs, int dim);
void printPosStud(studenti* studs, int pos);
int isEmptyStud(studenti* studs, int pos);
void saveStud(studenti* studs, int dim, char* fname);
int findBestStud(studenti* studs, int dim, int flag);



int main(int argc, char** argv) {
    int n = 0;
    int scelta = 0;
    int pos = 0;
    int meritevoli = 0;
    char* fileName = NULL;
    studenti* studs = NULL;

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
                           "inserire i dati:\n [da 0 a %d]\n" ANSI_RESET, n);
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
                    //TODO leggi da file
                    printf(ANSI_RED "Funzione non ancora supportata...\n"
                           ANSI_RESET);
                }
                break;
            //stampa dell'array di studenti
            case 2:
                printf(ANSI_MAGENTA "\n\nSTUDENTI:\n");
                for(pos = 0; pos < n; pos++)
                    printPosStud(studs, pos);
                break;
            //salva i dati su file //TODO
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
    }while(scelta);

    free(fileName);
    free(studs);
	return 0;
}



/*
 * funzione che ritorna il puntatore della nuova array di studenti allocata
 * con tutti i valori a 0 e con i controlli se c'e' spazio per allocarla
 * params: dimensione dell'array
 * return puntatore alla prima struttura dell'array
 */

studenti* newStudArr(int dim) {
    studenti* st = NULL;

    if(!(st = (studenti*)calloc(dim, sizeof(studenti)))) {
        printf(ANSI_RED
               "Impossibile allocare l'array di studenti!\n"
               ANSI_RESET);
        return NULL;
    }

    return st;
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
    if(!isEmptyStud(studs, pos)) {
        printf(ANSI_RED "Elemento presente in posizione %d\n" ANSI_RESET, pos);
        printPosStud(studs, pos);
        //e chiede all'utente se e' sicuro di sovrascriverli
        printf(ANSI_GREEN "Vuoi modificarlo? [1 = si, 0 = no]\n" ANSI_RESET);
        getLimitInt(&flag, 0, 1);
        if(!flag)
            return 0;
    }

    //chiede all'utente tutti i dati dello studente
    //cognome
    printf(ANSI_GREEN "Cognome: " ANSI_RESET);
    getString(&((studs+pos)->cognome));
    //nome
    printf(ANSI_GREEN "Nome: " ANSI_RESET);
    getString(&((studs+pos)->nome));
    //corso
    printf(ANSI_GREEN "Corso attuale: " ANSI_RESET);
    getLimitInt(&((studs+pos)->corso), 1, 5);
    //voto
    printf(ANSI_GREEN "Voto: " ANSI_RESET);
    getLimitInt(&((studs+pos)->voto), 0, 10);
    //anniIscrizione
    printf(ANSI_GREEN "Anni di iscrizione: " ANSI_RESET);
    getLimitInt(&((studs+pos)->anniIscrizione), 0, 30);

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
        printf(ANSI_MAGENTA "n* %d\n" ANSI_RESET, pos);
        if(compileStud(studs, dim, pos))
            count++;
    }

    return count;
}

/*
 * funzione di inserimento dei dati in uno studente
 * params: puntatore all'array di studenti
 *         posizione in cui andare a leggere
 * return: void
 */
void printPosStud(studenti* studs, int pos) {

    printf(ANSI_MAGENTA "Studente n* %d\n", pos);
    //se non ci sono dati avvisa l'utente
    if(isEmptyStud(studs, pos))
        printf(ANSI_RED "\tNessun dato...\n" ANSI_RESET);
    else
        printf(ANSI_BLUE "\t%s %s\n\tFrequenta il corso %d, "
               "iscritto/a da %d anni.\n"
               "\tHa una media di voti pari a %d.\n" ANSI_RESET,
               studs[pos].cognome, studs[pos].nome,
               studs[pos].corso, studs[pos].anniIscrizione,
               studs[pos].voto);

}

/*
 * funzione di controllo se un elemento nell'array contiene dei dati
 * params: puntatore all'array di studenti
 *         posizione in cui andare a leggere
 * return: un intero che vale 1 in caso di elemento vuoto
 *         e 0 in caso di presenza di almeno 1 dato
 */
int isEmptyStud(studenti* studs, int pos) {

    if(studs[pos].cognome != NULL)
        return 0;
    else if(studs[pos].nome != NULL)
        return 0;
    else if(studs[pos].corso != 0)
        return 0;
    else if(studs[pos].voto != 0)
        return 0;
    else if(studs[pos].anniIscrizione != 0)
        return 0;

    return 1;
}

/*
 * funzione che salva l'array di strutture in un file qualsiasi
 * params: puntatore all'array di studenti
 *         dimensione dell'array
 *         nome del file
 * return: void
 */
void saveStud(studenti* studs, int dim, char* fname) {
    FILE* fp = NULL;
    int i = 0;

    if( (fp = fopen(fname, "w+")) == NULL) {
        printf(ANSI_RED "Impossibile creare il file!\n" ANSI_RESET);
        return;
    }
    //stampa riga per riga dove ogni dato di un singolo studente e' separato da
    //una tabulazione
    for(i = 0; i < dim; i++) {
        fprintf(fp, "%s\t%s\t%d\t%d\t%d\n",
              studs[i].cognome,
              studs[i].nome,
              studs[i].corso,
              studs[i].voto,
              studs[i].anniIscrizione);
    }
    printf(ANSI_BLUE "File salvato!\n" ANSI_RESET);

    fclose(fp);
}

/*
 * funzione che cerca gli studenti migliori in base ai criteri scelti
 * params: puntatore all'array di studenti
 *         dimensione dell'array
 *         flag = 1 significa che stampa tutte le corrispondenze trovate,
 *         flag = 0 significa che non stampa nulla
 * return: int di quante corrispondenze ha trovato
 */
int findBestStud(studenti* studs, int dim, int flag) {
    int maxVoto = 0;
    int anniReq = 0;
    int tot = 0;
    int i = 0;

    //chiede i limiti da usare per i confronti
    printf(ANSI_GREEN "Inserisci la soglia del voto minimo richiesto:\n"
           ANSI_RESET);
    getLimitInt(&maxVoto, 0, 10);
    printf(ANSI_GREEN "Inserisci il massimo di anni di iscrizione:\n"
           ANSI_RESET);
    getLimitInt(&anniReq, 0, 10);

    //effettua i confronti e le stampe in caso di risultati positivi e flag = 1
    for(i = 0; i < dim; i++) {
        if(studs[i].voto >= maxVoto && studs[i].anniIscrizione <= anniReq) {
            tot++;
            if(flag)
                printPosStud(studs, i);
        }
    }

    return tot;
}
