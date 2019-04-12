/*
 * Basso Nicola
 * 4^AI
 * 26/10/2018
 */
/*
 * Libreria utile a gestire i file
 */

#include <stdio.h>

/* funzione che scrive sul file l'array passata
 * params: puntatore all'array
 *         dimensione dell'array
 * return: void
 */
void saveToFile(int* arr, int dim) {
    FILE *fp = NULL; /* puntatore al file */
    int i = 0;

    //crea il file
    if ((fp = fopen(NOME_FILE, "w+")) == NULL) {
            printf(ANSI_RED "Impossibile creare o scrivere il file!\n"
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
void stampaFile() {
        FILE *fp;

        //apre il file
        if ((fp = fopen(NOME_FILE, "r")) == NULL)
        {
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
