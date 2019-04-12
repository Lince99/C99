/*
Il processo padre genera un vettore, di dimensione 99 elementi, di valori casuali compresi tra ValMin e ValMax.

Genererà poi dei processi figli in modo che ognuno ordini una porzione di 33 elementi dell'array.

Dopo questo ordinamento parziale, il padre completerà il lavoro.

Sarà possibile poi generalizzare in modo da ordinare array di qualsiasi dimensione e con uin numero qualsiasi di sottoprocessi.

Riflettere sulla consegna stessa..
*/

/*
 * Basso Nicola
 * 4^AI
 */

#include <stdio.h>
#include "manager_array.h"
#include "manager_process.h"
#include "colors.h"

void testArray();

int main(int argc, char** argv) {

    testArray();

    return 0;
}

//funzione che testa l'ordinamento di un'array
void testArray() {
    int* arr = NULL;
    int dim = 0;

    printf("Inserisci la dimensione dell'array:\t");
    scanf("%d", &dim);
    printf("dim = %d\n", dim);

    arr = initRandom(arr, 0, 100, dim);
    printArr(arr, dim);

    printf("Ordinata:\n");
    arr = bubbleSort(arr, dim);
    printArr(arr, dim);
}
