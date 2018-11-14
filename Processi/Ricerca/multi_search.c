/*
 * Basso Nicola
 * 4^AI
 */

/*
 * Il processo padre genera un vettore, di dimensione maxElem,
 * di valori casuali compresi tra ValMin e ValMax.
 * Il processo padre domanda l'elemento, che può essere ripetuto, da cercare.
 * Poi, il processo padre, domanda quanti figli generare
 * per effettuare una ricerca di elemento ripetuto su vettore.
 * Dopo fork opportuni ciascun figlio cerca, su elementi non ordinati, nella
 * sua porzione di vettore un elemento che potrebbe presentarsi piu' volte.
 * Inciso: il figlio, trovata la corrispondenza,
 * la stampa a video non ordinata insieme alla relativa posizione.
 * L'ultimo figlio cerca fino in fondo, perche' non sempre la dimensione maxElem
 * é divisibile senza resto con il numero di figli.
 * Creare poi una funzione per generare array
 * con elementi casuali senza ripetizioni.
 * Ritestare l'algoritmo di ricerca su array molto grandi,
 * confrontandolo anche con l'algoritmo di riicerca sequenziale
 * con unico processo.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <types.h>
#include <unistd.h>
#include <limits.h>
#include "colors.h"
#include "input_check.h"

//firme




int main(int argc, char** argv) {
    int maxElem = 0; /* dimensione del vettore */
    int flagRep = 0; /* flag che e' = a 1 se l'utente vuole numeri univochi */
    int valMin = 0; /* valore minimo per il random */
    int valMax = 0; /* valore massimo per il random */
    int elem = 0; /* valore da trovare */
    int nFigli = 0; /* numero di figli da realizzare */
    pid_t pid = NULL; /* pid gestito dai fork */
    int* arr = NULL; /* array su cui ricercare */

    //crea un vettore di dimensioni scelte dall'utente
    printf(ANSI_BLUE "Inserisci la dimensione dell'array:\n" ANSI_RESET);
    getInt(&maxElem);
    arr = newArr(arr, maxElem);
    //chiede se vuole numeri random ripetuti o univochi
    printf(ANSI_BLUE
           "Desideri usare numeri generati che potrebbero ripetersi?\n"
           "[0 = no, 1 = si]\n"
           ANSI_RESET);
    getLimitInt(&flag, 0, 1);
    //inizializza il vettore con numeri random tra valMin e valMax
    printf(ANSI_BLUE "Inserisci il valore " ANSI_CYAN "minimo"
           ANSI_BLUE" generabile:\n" ANSI_RESET);
    getInt(&valMin);
    printf(ANSI_BLUE "Inserisci il valore " ANSI_CYAN "massimo"
           ANSI_BLUE " generabile:\n" ANSI_RESET);
    getLimitInt(&valMin, valMin, INT_MAX);
    randIntArr(arr, maxElem, valMin, valMax, flag);
    //stampa l'array
    //l'utente sceglie che valore cercare e quanti processi
    //ogni processo stampa i suoi risultati
    //padre aspetta che i figli terminino per stampare tempo totale impiegato

    return 0;
}

/*
 * funzione che alloca un'array data la sua dimensione
 * con tutti i valori a 0 e ritorna il suo nuovo puntatore
 */
int* newArr(int* arr, int dim) {

    if((*arr = (int*)calloc(dim, sizeof(int))) ) {
        printf(ANSI_RED "Impossibile allocare l'array!\n" ANSI_RESET);
        return NULL;
    }

    return arr;
}

/*
 * funzione che imposta i valori dell'array in valori random dati i due estremi,
 * se flag = 1 allora evita di ripetere i numeri
 */
void randIntArr(int* arr, int dim, int min, int max, int flag) {
    int i = 0;
    int gen = 0;

    for(i = 0; i < dim, i++) {
        do
        {
            gen = (int)rand()%max;
            isOnce(arr, dim, gen);
        } while();
    }
}
