/*
 * Basso Nicola
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    int dim = 0;
    int* p = NULL;
    int val = 0;
    int i = 0;

    do {
        printf("Inserisci il %d valore (0 per uscire):\t", dim);

        scanf("%d", &val);
        if(val != 0) {
            dim += 1;
            p = (int*) realloc(p, dim*sizeof(int));
            *(p+dim-1) = val;
        }
        else
            printf("Uscita...\n");
    } while(val != 0);

    printf("Array:\n");
    for(i = 0; i < dim; i++)
        printf("%d ", *(p+i));
    printf("\n");
    return 0;
}
