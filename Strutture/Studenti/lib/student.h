/*
 * Basso Nicola
 * 4^AI
 */
/*
 * libreria contenente definizione e funzioni del tipo studente
 */

#include <stdio.h> //fprintf, fscanf
#include <stdlib.h> //malloc
#include "colors.h" //ANSI_BLUE, ANSI_RESET

//tipo di dato "studente" con i dati base richiesti dal programma
typedef struct STUDENTE {
	char* cognome;
	char* nome;
	int corso;
	int voto;
	int anniIscrizione;
} studente;

//firme
studente* newStudArr(int dim);
int compileStud(studente* studs, int dim, int pos);
int compileAllStud(studente* studs, int dim);
void printPosStud(studente* studs, int pos);
int isEmptyStud(studente* studs, int pos);
void saveStud(studente* studs, int dim, char* fname);
void readStud(studente* studs, int dim, char* fname);
int findBestStud(studente* studs, int dim, int flag);



/*
 * funzione che ritorna il puntatore della nuova array di studenti allocata
 * con tutti i valori a 0 e con i controlli se c'e' spazio per allocarla
 * params: dimensione dell'array
 * return puntatore alla prima struttura dell'array
 */

studente* newStudArr(int dim) {
    studente* st = NULL;

    if(!(st = (studente*)calloc(dim, sizeof(studente)))) {
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
int compileStud(studente* studs, int dim, int pos) {
    int flag = 0;

    //se ci sono dei dati li stampa
    if(!isEmptyStud(studs, pos)) {
        printf(ANSI_RED "Elemento presente in posizione %d\n" ANSI_RESET, pos);
        printPosStud(studs, pos);
        //e chiede all'utente se e' sicuro di sovrascriverli
        printf(ANSI_GREEN "Vuoi modificarlo?\n[1 = si, 0 = no]\n" ANSI_RESET);
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
int compileAllStud(studente* studs, int dim) {
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
void printPosStud(studente* studs, int pos) {

    printf(ANSI_MAGENTA "Studente n* %d\n", pos);
    //se non ci sono dati avvisa l'utente
    if(isEmptyStud(studs, pos))
        printf(ANSI_RED "\tNessun dato...\n" ANSI_RESET);
    else
        printf(ANSI_BLUE "\t%s %s\n\tFrequenta il corso %d, "
               "iscritto/a da %d anni.\n"
               "\tHa una media di voti pari a %d.\n" ANSI_RESET,
               (studs+pos)->cognome, (studs+pos)->nome,
               (studs+pos)->corso, (studs+pos)->anniIscrizione,
               (studs+pos)->voto);

}

/*
 * funzione di controllo se un elemento nell'array contiene dei dati
 * params: puntatore all'array di studenti
 *         posizione in cui andare a leggere
 * return: un intero che vale 1 in caso di elemento vuoto
 *         e 0 in caso di presenza di almeno 1 dato
 */
int isEmptyStud(studente* studs, int pos) {

    if((studs+pos)->cognome != NULL)
        return 0;
    else if((studs+pos)->nome != NULL)
        return 0;
    else if((studs+pos)->corso != 0)
        return 0;
    else if((studs+pos)->voto != 0)
        return 0;
    else if((studs+pos)->anniIscrizione != 0)
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
void saveStud(studente* studs, int dim, char* fname) {
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
              (studs+i)->cognome,
              (studs+i)->nome,
              (studs+i)->corso,
              (studs+i)->voto,
              (studs+i)->anniIscrizione);
    }
    printf(ANSI_BLUE "File salvato!\n" ANSI_RESET);

    fclose(fp);
}

/*
 * funzione che legge i dati dal file e li salva nelle strutture
 * params: puntatore all'array di studenti
 *         dimensione dell'array
 *         nome del file
 * return: void
 */
 //TODO
void readStud(studente* studs, int dim, char* fname) {
    FILE* fp = NULL;
    int i = 0;

    if( (fp = fopen(fname, "r")) == NULL) {
        printf(ANSI_RED "Impossibile aprire il file!\n" ANSI_RESET);
        return;
    }
	//legge riga per riga il file estraendo i dati separati da una tabulazione
	for(i = 0; i < dim; i++) {
		fscanf(fp, "%s\t%s\t%d\t%d\t%d\n",
			  (studs+i)->cognome,
			  (studs+i)->nome,
			  &((studs+i)->corso),
			  &((studs+i)->voto),
			  &((studs+i)->anniIscrizione) );
		printPosStud(studs, i);
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
int findBestStud(studente* studs, int dim, int flag) {
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
        if((studs+i)->voto >= maxVoto && (studs+i)->anniIscrizione <= anniReq) {
            tot++;
            if(flag)
                printPosStud(studs, i);
        }
    }

    return tot;
}
