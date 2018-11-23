/*
 * Basso Nicola
 * 4^AI
 */

/*
 * Automazione del programma multi_search per stampare su file varie misurazioni
 * Richiede tutte le informazioni richieste all'inizio per poi generare
 * un file csv contenente 3 colonne:
 *     la dimensione dell'array,
 *     il tempo impiegato dalla ricerca a singolo processo
 *     il tempo impiegato dalla ricerca a multiprocesso
 */

#include <stdio.h> //printf, scanf
#include <unistd.h> //fork
#include <sys/wait.h> //wait
#include <sys/types.h> //pid_t
#include <sys/time.h> //gettimeofday
#include "./lib/input_check.h" //valid input
#include "./lib/manager_array.h" //newArr, initRandom
#include "./lib/manager_file.h" //saveToFile, printFile

//numero massimo utilizzabile come input durante l'esecuzione
#define MAXTEST 1000

//firme
double multi_proc_search(int* arr, int maxElem, int elem, int nProc);
double single_proc_search(int* arr, int maxElem, int elem);

//globals
int* arr = NULL; /* array su cui ricercare */
int errors_fork = 0; /* contatore di errori nella creazione di processi */



int main(int argc, char** argv) {
    int maxElem = 0; /* dimensione del vettore */
    int unique = 0; /* flag che e' = a 1 se l'utente vuole numeri univochi */
    int valMin = 0; /* valore minimo per il random */
    int valMax = 0; /* valore massimo per il random */
    int elem = 0; /* valore da trovare */
    int nProc = 0; /* numero di figli da realizzare */
    int i = 0; /* contatore generale */
    int j = 0; /* contatore del numero di volte di test con gli stessi dati */
    int polls = 0; /* numero di misurazioni da effettuare */
    int tests = 0; /* numero di misurazioni con gli stessi dati da effettuare */
    int factor = 0; /* fattore di moltiplicazione della dimensione dell'array */
    char* timeStp; /* timestamp dell'esecuzione corrente del programma */
    csv_time report; /* struct contenente le informazioni da salvare su file*/
    char* fileName = NULL; /* nome del file completo */
    char* filePrefix = NULL; /* prefisso del nome del file da salvare */

	//- - - - - - - - - - - - RICHIEDE DATI ALL'UTENTE - - - - - - - - - - - -//
    //chiede il numero di misurazioni
    printf(ANSI_BLUE "Quante misurazioni vuoi effettuare?\n" ANSI_RESET);
    getLimitInt(&polls, 1, INT_MAX);
    //chiede il numero di misurazioni con gli stessi dati
    printf(ANSI_BLUE
           "Quanti confronti con gli stessi dati vuoi effettuare?\n"
           ANSI_CYAN "[da 1 a %d]\n" ANSI_RESET, MAXTEST);
    getLimitInt(&tests, 1, MAXTEST);

    //chiede le dimensioni dell'array
    printf(ANSI_BLUE "Inserisci la dimensione dell'array iniziale:\n"
           ANSI_RESET);
    getLimitInt(&maxElem, 0, INT_MAX);
    //nel caso la dimensione sia 0 allora esce subito dal programma
    if(!maxElem) {
        printf(ANSI_RED "Dimensione dell'array pari a 0!\n"
               "Impossibile procedere con le operazioni...\n" ANSI_RESET);
        return 1;
    }
    //chiede il valore da aggiungere ogni volta per incrementare la dimensione
    if(polls > 1) {
        printf(ANSI_BLUE
               "Quale valore vuoi aggiungere alla dimensione dell'array\n"
               "dopo %d test effettuati con la stessa dimensione?\n"
               ANSI_CYAN "[da 0 a %d]\n" ANSI_RESET, tests, MAXTEST);
        getLimitInt(&factor, 0, MAXTEST);
    }

    //chiede se vuole numeri random ripetuti o univoci
    printf(ANSI_BLUE "Desideri usare numeri generati unici?\n"
           ANSI_CYAN "[0 = no, 1 = si]\n" ANSI_RESET);
    getLimitInt(&unique, 0, 1);
    //nel caso di numeri random chiede il minimo e il massimo
    if(!unique) {
        //chiede il valore minimo
        printf(ANSI_BLUE "Inserisci il valore " ANSI_CYAN "minimo"
               ANSI_BLUE" generabile:\n" ANSI_RESET);
        getInt(&valMin);
        //chiede il valore massimo
        printf(ANSI_BLUE "Inserisci il valore " ANSI_CYAN "massimo"
               ANSI_BLUE " generabile:\n" ANSI_CYAN "[da %d]\n"
               ANSI_RESET, valMin);
        getLimitInt(&valMax, valMin, INT_MAX);
    }

    //l'utente sceglie che valore cercare
    printf(ANSI_BLUE "Quale valore vuoi cercare nell'array?\n" ANSI_RESET);
    getInt(&elem);
    //richiede quanti processi si vogliono creare
    printf(ANSI_BLUE "Quanti processi vuoi creare?\n" ANSI_RESET);
    getLimitInt(&nProc, 1, INT_MAX);

    //richiede dove e che prefisso dare al file di esportazione
    printf(ANSI_BLUE "Dove e con quale prefisso vuoi salvare l'esportazione?\n"
           ANSI_CYAN "[Esempio: \"export_\" produce export_123456789.csv]\n"
           ANSI_RESET);
    getString(&filePrefix);

    //- - - - - - - - - - - - - ESEGUE LE MISURE - - - - - -  - - - - - - - - //
    //inizializza i dati da salvare nel file
    report.intestation = "'DIMENSIONE';'TIME_SINGLE';'TIME_MULTI'";
    report.sep = ';';
    report.strler = '\'';
    //concatena il prefisso del nome del file con il timestamp e l'estensione
    fileName = fileStrcat(filePrefix, getTimestamp(0), ".csv");

    for(i = 0; i < polls; i++) {
        //incrementa la dimensione per passare alla prossima misurazione
        if(polls > 1 && i > 0)
            maxElem += factor;
        //aggiunge la dimensione attuale da stampare
        report.dim = maxElem;
        //- - - - - - - - - - - - INIZIALIZZA ARRAY - - - - - - - - - - - - - //
        valMax = maxElem;
        //alloca l'array controllando che non ecceda il limite
        if((arr = newArr(arr, maxElem)) == NULL) {
            printf(ANSI_RED "Impossibile proseguire senza un'array valida!\n"
                   ANSI_RESET);
            return 1;
        }
    	//inizializza il vettore con numeri random tra valMin e valMax
        arr = initLimitRand(arr, maxElem, valMin, valMax, unique);
        //stampa l'array nel caso di 1 sola misurazione
        if(polls == 1)
            printArr(arr, maxElem);
        //- - - - - - - - - - ESEGUE PIU' VOLTE LE MISURE - - - - - - - - - - //
        for(j = 0; j < tests; j++) {
            printf(ANSI_CYAN "\n%d_%d - Dimensione = %d\n"
                   ANSI_RESET, i+1, j+1, maxElem);
            //- - - - - - - - - RICERCA SINGOLO PROCESSO - - - - - - - - - - -//
            printf(ANSI_GREEN "Time single = %f\n" ANSI_RESET,
                     single_proc_search(arr, maxElem, elem));
            report.times[0] = single_proc_search(arr, maxElem, elem);

            //- - - - - - - - - - RICERCA MULTIPROCESSO - - - - - - - - - - - //
            printf(ANSI_GREEN "Time multi = %f\n" ANSI_RESET,
                     multi_proc_search(arr, maxElem, elem, nProc));
            report.times[1] = multi_proc_search(arr, maxElem, elem, nProc);

            saveToCsv(fileName, report);
        }
        free(arr);
    }

    //stampa del nome del file csv univoco per ogni esecuzione (timestamp)
    printf(ANSI_BLUE "\nDati salvati in: "
           ANSI_CYAN "%s" ANSI_RESET"\n\n", fileName);
    //stampa il numero di errori nella creazione di processi,
    //sta all'utente decidere se trascurarli o no
    if(errors_fork)
        printf(ANSI_BG_RED "Errori totali nel fork: %d su %d test"
               ANSI_RESET"\n", errors_fork, polls*tests);

    //free(arr);
    return 0;
}



/*
 * funzione che data l'array e la sua dimensione, cerca con nProc processi
 * l'elemento elem, restituendo il tempo totale impiegato
 */
double multi_proc_search(int* arr, int maxElem, int elem, int nProc) {
    struct timeval stop, start; /* variabili per salvare il tempo */
    double timeTot = 0; /* tempo totale impiegato dalla ricerca */
    pid_t pid = 0; /* pid gestito dai fork */
    int prev = 0; /* posizione inziale da dove cercare per 1 processo */
    int next = 0; /* posizione finale per la ricerca per 1 processo */
    int i = 0; /* contatore generale */

    //salva il tempo del punto di partenza
	gettimeofday(&start, NULL);
    //crea nProc processi per la ricerca nell'array suddivisa
    for(i = 0; i < nProc; i++) {
        //suddivide l'array tra i vari processi
        prev = next;
        if(i == nProc-1)
            next = maxElem;
        else
            next = prev + (int)(maxElem/nProc);
        //crea il processo figlio per nProc volte
        pid = fork();
        if(pid == 0) {
            searchElem(arr, prev, next, elem);
            exit(0);
        }
        //il padre aspetta che i figli terminino la ricerca
        else if(pid > 0 && i == nProc-1) {
            //waitpid(pid, NULL, 0);
            wait(NULL);
        }
        else if(pid < 0){
            printf(ANSI_RED "Errore nel fork %d!" ANSI_RESET"\n", i);
            errors_fork++;
            break;
            //exit(1);
        }
    }
    //il padre aspetta che l'ultimo processo termini
    waitpid(pid, NULL, 0);
    //salva il tempo del punto di arrivo
	gettimeofday(&stop, NULL);
	timeTot = (double)(stop.tv_usec - start.tv_usec) / 1000000 +
			  (double)(stop.tv_sec - start.tv_sec);

    //ritorna il tempo totale impiegato
    return timeTot;
}

/*
 * funzione che data l'array e la sua dimensione, cerca l'elemento elem,
 * restituendo il tempo totale impiegato
 */
double single_proc_search(int* arr, int maxElem, int elem) {
    struct timeval stop, start; /* variabili per salvare il tempo */
    double timeTot = 0; /* tempo totale impiegato dalla ricerca */

    //salva il tempo del punto di partenza
    gettimeofday(&start, NULL);
    searchElem(arr, 0, maxElem, elem);
    //salva il tempo del punto di arrivo
	gettimeofday(&stop, NULL);
	timeTot = (double)(stop.tv_usec - start.tv_usec) / 1000000 +
			  (double)(stop.tv_sec - start.tv_sec);

	//ritorna il tempo totale impiegato
	return timeTot;
}
