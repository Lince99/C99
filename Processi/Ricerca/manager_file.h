/*
 * Basso Nicola
 * 4^AI
 */
/*
 * Libreria utile a gestire i file
 */

#include <stdio.h>
#include <time.h>



/* funzione che scrive sul file l'array passata
 * params: puntatore all'array
 *         dimensione dell'array
 * return: void
 */
void saveToFile(char* fileName, int* arr, int dim) {
    FILE *fp = NULL; /* puntatore al file */
    int i = 0;

    //crea il file
    if((fp = fopen(fileName, "w+")) == NULL) {
        printf(ANSI_RED "Impossibile creare o scrivere sul file!\n"
               ANSI_RESET);
        exit(1);
    }
    //salva l'array nel file
    for(i = 0; i < dim; i++)
            fprintf(fp, "%d ", *(arr+i));
    fclose(fp);

}

/* funzione che stampa a video il contenuto del file
 * params: void
 * return: void
 */
void printFile(char* fileName) {
    FILE *fp;

    //apre il file
    if((fp = fopen(fileName, "r")) == NULL) {
            printf(ANSI_RED "Impossibile leggere il file!\n" ANSI_RESET);
            exit(1);
    }
    //e stampa carattere per carattere
    char c;
    while(1) {
            c = fgetc(fp);
            if(feof(fp))
                    break;
            printf("%c", c);
    }
    printf("\n");
    fclose(fp);

}

/*
 * funzione che ritorna il timestamp o con la data o in UNIX time
 * params: flag = 0 = data normale concatenata secondo lo stile hhmmssggMMyyyy
 *         flag = 1 = data in tempo Unix
 * return: stringa contenente il timestamp
 */
char* getTimestamp(int flag) {
    time_t t;
    struct tm tm;
    char* res = NULL; /* stringa risultante */

    t = time(NULL);
    tm = *localtime(&t);
    //tempo unix
    if(flag)
        sprintf(res, "%u", (unsigned)time(NULL));
    //data attuale
    else {
        //alloca la dimensione fissa in caso di data normale
        res = (char*) malloc(sizeof(char)*14);
        //modificare l'ordine dei parametri per cambiare formato della data
        if( sprintf(res, "%d%d%d%d%d%d",
                    tm.tm_hour, tm.tm_min, tm.tm_sec,
                    tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900) < 0) {
            printf(ANSI_RED "Impossibile creare il timestamp!\n" ANSI_RESET);
            return "";
        }
    }

    return res;
}

/*
 * funzione che salva in un file csv la matrice di stringhe passate
 * params: stringa del nome del file su cui salvare
 *         flag addTime se = 0 allora non aggiunge il tempo al nome, se > 0 si
 *         matrice di stringhe da cui leggere
 *         dimensione x della matrice (larghezza)
 *         dimensione y della matrice (altezza)
 * return: void
 */
void saveToCsv(char* fileName, int addTime, char** matrix, int x, int y) {
    FILE* fp = NULL;
    char* timeStr = NULL;
    int i = 0;
    int j = 0;

    //se viene aggiunto il timestamp
    if(flag) {
        //concatena il fileName con il timestamp timeStr
        timeStr = getTimestamp(0);
        fileName = realloc(fileName, strlen(fileName)+strlen(timeStr));
        strcat(fileName, timeStr);
    }

    //crea il file
    if((fp = fopen(fileName, "w+")) == NULL) {
        printf(ANSI_RED "Impossibile creare o scrivere sul file!\n"
               ANSI_RESET);
        exit(1);
    }
    //scrive la riga di intestazione delle colonne
    fprintf(fp, "'ARRAY';'TIME_SINGLE';'TIME_MULTI';'MAXELEM';'UNIQUE';'MIN';'MAX';'ELEM'");
    //salva la matrice nel file
    for(i = 1; i < y; i++) {
        for(j = 0; j < x; j++) {
            //TODO
        }
    }

    fclose(fp);

}
