/*
 * Basso Nicola
 * 4^AI
 * 21/01/2019
 */

/*
 * Sviluppare un programma per la gestione della classifica di una graduatoria
 * di salto in lungo mediate una lista di puntatori.
 * La graduatoria (lista) dovrà essere sempre ordinata dopo ogni inserimento,
 * pertanto prevedere gli opportuni sottoprogrammi per:
 *
 * visualizzazione
 * inserimento nodo
 * inserimento nodo in testa
 * inserimento nodo in coda
 * cancellazione nodo
 * cancellazione nodo in testa
 * cancellazione nodo in coda
 */

#include <stdio.h>
#include <stdlib.h>
#include "lib/list.h"

//firme
int menu();



int main(int argc, char** argv) {
    list* grade = NULL;
    int scelta = 0;
    char name = 0;
    float lung = 0;

    //stampa il menu
    do {
        scelta = menu();
        switch(scelta) {
            case 1:
                printf("Graduatoria:\n[Iniziale Nome] [metri]\n");
                print_list(grade);
                break;
            case 2:
                printf("\t1 - inserirlo/a in ordine crescente;\n");
                printf("\t2 - inserirlo/a in testa;\n");
                printf("\t3 - inserirlo/a in coda;\n");
                printf("\t0 - tornare al menu precedente.\n");
                do {
                    if(scanf("%d", &scelta) == EOF)
                        scelta = -1;
                }while(scelta < 0 || scelta > 3);
                //richiede i dati dell'alteta con controlli
                printf("Inserisci i dati dell'atleta:\n");
                printf("Iniziale del Nome:");
                scanf("%c", &name);
                printf("Lunghezza del salto:");
                scanf("%f", &lung);
                //e applica la tipologia di inserimento scelta
                switch(scelta) {
                    case 1:
                        grade = add_node(grade, name, lung);
                        break;
                    case 2:
                        grade = add_node_head(grade, name, lung);
                        break;
                    case 3:
                        grade = add_node_tail(grade, name, lung);
                        break;
                    default:
                        break;
                }
            case 3:
                printf("\t1 - rimuoverlo/a data la lunghezza;\n");
                printf("\t2 - rimuoverlo/a in testa;\n");
                printf("\t3 - rimuoverlo/a in coda;\n");
                printf("\t0 - tornare al menu precedente.\n");
                do {
                    if(scanf("%d", &scelta) == EOF)
                        scelta = -1;
                }while(scelta < 0 || scelta > 3);
                if(scelta == 1) {
                    printf("Lunghezza del salto da eliminare:");
                    scanf("%f", &lung);
                }
                //e applica la tipologia di inserimento scelta
                switch(scelta) {
                    case 1:
                        grade = rem_node(grade, lung);
                        break;
                    case 2:
                        grade = rem_node_head(grade);
                        break;
                    case 3:
                        grade = rem_node_tail(grade);
                        break;
                    default:
                        break;
                }
            default:
                printf("Uscita dal programma...\n");
                break;
        }
    } while(scelta != 0);

    return 0;
}



int menu() {
    int scelta = 0;

    printf("\nCosa desideri fare?\n");
    printf("1 - visualizzare la graduatoria;\n");
    printf("2 - inserire un/a nuovo/a atleta;\n");
    printf("3 - cancellare un/a atleta dalla lista;\n");
    printf("0 - uscire dal programma.\n");
    //controlla che l'utente insersca un input valido
    do {
        if(scanf("%d", &scelta) == EOF)
            scelta = -1;
    }while(scelta < 0 || scelta > 3);

    return scelta;
}
