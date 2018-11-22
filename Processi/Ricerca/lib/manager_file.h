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
        if(sprintf(res, "%d%d%d%d%d%d",
                   tm.tm_hour, tm.tm_min, tm.tm_sec,
                   tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900) < 0) {
            printf(ANSI_RED "Impossibile creare il timestamp!\n" ANSI_RESET);
            return "";
        }
    }

    return res;
}

/*
 * struttura dati dedicata al settaggio del file csv per salvare un confronto
 * tra due misurazioni temporali
 */
typedef struct CSV_FILE_TIME {
    char* intestation; /* intestazione della tabella */
    char sep; /* carattere utilizzato come separatore di campi */
    char strler; /* carattere utilizzabile come identificatore di stringhe */
    double times[2]; /* tempo di ricerca a processo singolo
                        e tempo di ricerca a processo multiplo */
    int dim; /* dimensione dell'array usata come test */
} csv_time;

/*
 * funzione che concatena il prefisso del file,
 * la versione o data e l'estensione passati come parametri
 */
char* fileStrcat(char* prefix, char* second, char* extension) {
    int dim = 0;
    char* result = NULL;

    //somma le varie dimensioni dei parametri per allocare la stringa
    dim = strlen(prefix)+strlen(second)+strlen(extension);
    result = (char*) calloc(dim, sizeof(char));
    //concatena le stringhe
    strcat(result, prefix);
    strcat(result, second);
    strcat(result, extension);

    return result;
}

/*
 * funzione che salva in un file csv la matrice di stringhe passate
 * params: stringa del nome del file su cui salvare
 *         addTime contiene il timestamp da aggiungere
 *         dati da salvare nella tabella
 * return: void
 */
void saveToCsv(char* fileName, csv_time report) {
    FILE* fp = NULL; /* puntatore al file dove salvare i dati */
    int tmp = 0; /* variabile temporanea usata per allocazioni e ritorni */


    //crea il file
    if((fp = fopen(fileName, "a+")) == NULL) {
        printf(ANSI_RED "Impossibile creare o scrivere sul file!\n"
               ANSI_RESET);
        exit(1);
    }

    //se il file e' nuovo stampa l'intestazione della tabella
    if(fscanf(fp, "%d", &tmp) == EOF)
        fprintf(fp, "%s\n", report.intestation);

    /*stampa prima la dimensione,
     * poi il tempo impiegato dal singolo processo
     * e infine dal multiprocesso
     */
    fprintf(fp, "%d%c%c%f%c%c%c%f%c\n",
            report.dim, report.sep,
            report.strler, report.times[0], report.strler, report.sep,
            report.strler, report.times[1], report.strler);

    fclose(fp);
}
