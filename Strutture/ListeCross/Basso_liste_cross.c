/*
 * Basso Nicola
 * 4^AI
 */
/*
 * CROSS selection eserc. Natale 2018
 * Si scriva una funzione crossSelection() che,
 * ricevute in ingresso due liste di interi positivi L1 e L2,
 * restituisca una terza lista (eventualmente non ordinata)
 * contenente gli interi di L2 che sono nelle posizioni
 * indicate dai valori di L1
 * (si assuma per convenzione che il primo elemento di una lista
 * sia in posizione 1). Ad esempio, date due liste:
 * L1=[1,3,4] e L2=[2,4,6,8,10,12],
 * la lista risultante deve contenere gli elementi di L2 che sono in prima,
 * terza e quarta posizione, cioè: [2,6,8]
 */

#include <stdio.h>
#include <time.h>
#include "./lib/colors.h"
#include "./lib/input_check.h"
#include "./lib/list.h"

//firme
listNode* crossSelection(listNode* L1, listNode* L2);
listNode* fillList();


int main(int argc, char** argv) {
    listNode* L1 = NULL; /* lista che indicherà le posizioni da cui estrarre */
    listNode* L2 = NULL; /* lista da cui estrarre i valori */
    listNode* cross = NULL; /* lista risultante */

    //richiede i dati all'utente
    printf(ANSI_BLUE "Inserisci i valori della lista L1:" ANSI_RESET "\n");
    L1 = fillList();
    printf(ANSI_BLUE "Inserisci i valori della lista L2:" ANSI_RESET "\n");
    L2 = fillList();
    //ed esegue la selezione incrociata degli elementi
    cross = crossSelection(L1, L2);
    //poi stampa tutte le informazioni e le liste
    printf(ANSI_GREEN "Lista L1:" ANSI_RESET "\n");
    print_list(L1);
    printf(ANSI_GREEN "Lista L2:" ANSI_RESET "\n");
    print_list(L2);
    printf(ANSI_GREEN "Lista con gli elementi estratti da L2 "
           "secondo le posizioni indicate da L1:" ANSI_RESET "\n");
    print_list(cross);

    //infine libera tutto
    free_list(L1);
    free_list(L2);
    free_list(cross);
    return 0;
}



/*
 * funzione che esegue l'operazione descritta dalla consegna
 */
listNode* crossSelection(listNode* L1, listNode* L2) {
    listNode* cross = NULL; /* lista risultante */
    listNode* extractNode = NULL; /* nodo estratto da L2 */
    int pos = 0; /* posizione estratta da L1 */

    //scorre gli indici da leggere
    while(L1 != NULL) {
        //prende da L1 la posizione
        pos = L1->value;
        //ed estrae a tale posizione da L2
        extractNode = getNode_list(L2, pos);
        cross = addTail_list(cross, extractNode->value);
        //e prosegue
        L1 = L1->next;
    }

    return cross;
}

/*
 * funzione che chiede all'utente di riempire una lista con interi
 */
listNode* fillList() {
    listNode* new = NULL;
    int n = 0;
    int quit = -1; /* valore che permette di uscire dall'inserimento */

    printf(ANSI_CYAN "Inserisci -1 per uscire" ANSI_RESET "\n");
    while(n != quit) {
        //accetta -1 solo per uscire
        getInt(&n);
        if(n != quit)
            new = addTail_list(new, n);
    }

    return new;
}
