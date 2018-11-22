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

#include <stdio.h> //printf, scanf
#include <unistd.h> //fork
#include <sys/wait.h> //wait
#include <sys/types.h> //pid_t
#include <sys/time.h> //gettimeofday
#include "lib/input_check.h" //valid input
#include "lib/manager_array.h" //newArr, initRandom
#include "lib/manager_file.h" //saveToFile, printFile

//globals
int* arr = NULL; /* array su cui ricercare */
//TODO aggiungere report


int main(int argc, char** argv) {
    int maxElem = 0; /* dimensione del vettore */
    int unique = 0; /* flag che e' = a 1 se l'utente vuole numeri univochi */
    int valMin = 0; /* valore minimo per il random */
    int valMax = 0; /* valore massimo per il random */
    int elem = 0; /* valore da trovare */
    int nProc = 0; /* numero di figli da realizzare */
    pid_t pid = 0; /* pid gestito dai fork */
    int i = 0; /* contatore generale */
    int prev = 0; /* posizione inziale da dove cercare per 1 processo */
    int next = 0; /* posizione finale per la ricerca per 1 processo */
    struct timeval stop, start; /* variabili per salvare il tempo */
    double timeTot = 0; /* tempo totale impiegato dalla ricerca */
    /* possibile soluzione POSIX-compliant
        http://man7.org/linux/man-pages/man2/clock_gettime.2.html
        static double TimeSpecToSeconds(struct timespec* ts)
        {
            return (double)ts->tv_sec + (double)ts->tv_nsec / 1000000000.0;
        }
        //. . . .
        struct timespec start;
        struct timespec end;
        double elapsedSeconds;
        if(clock_gettime(CLOCK_MONOTONIC, &start)) { //handle error }
        //Do stuff
        if(clock_gettime(CLOCK_MONOTONIC, &end)) { //handle error }
        elapsedSeconds = TimeSpecToSeconds(&end) - TimeSpecToSeconds(&start);
    */

	//- - - - - - - - - - - - RICHIEDE DATI ALL'UTENTE - - - - - - - - - - - -//
    //chiede se si vuole automatizzare e la quantita' in caso affermativo
    //crea un vettore di dimensioni scelte dall'utente
    printf(ANSI_BLUE "Inserisci la dimensione dell'array:\n" ANSI_RESET);
    getLimitInt(&maxElem, 1, INT_MAX);
    //alloca l'array controllando che non ecceda il limite
    if((arr = newArr(arr, maxElem)) == NULL) {
        printf(ANSI_RED "Impossibile proseguire senza un'array valida!\n"
               ANSI_RESET);
        return 1;
    }
    //chiede se vuole numeri random ripetuti o univochi
    printf(ANSI_BLUE
           "Desideri usare numeri generati unici?\n"
           "[0 = no, 1 = si]\n"
           ANSI_RESET);
    getLimitInt(&unique, 0, 1);
    //nel caso di numeri random chiede il minimo e il massimo
    if(!unique) {
		//chiede il valore minimo
		printf(ANSI_BLUE "Inserisci il valore " ANSI_CYAN "minimo"
			   ANSI_BLUE" generabile:\n" ANSI_RESET);
		getInt(&valMin);
		//chiede il valore massimo
		printf(ANSI_BLUE "Inserisci il valore " ANSI_CYAN "massimo"
               ANSI_BLUE " generabile:\n");
        printf("[da %d]\n" ANSI_RESET, valMin);
        getLimitInt(&valMax, valMin, INT_MAX);
    }
    //nel caso di numeri univoci inserisce numeri consecutivi mixati
    else {
		valMin = 0;
		valMax = maxElem;
	}

	//- - - - - - - - - - - - INIZIALIZZA ARRAY - - - - - - - - - - - - - - - //
	//inizializza il vettore con numeri random tra valMin e valMax
    arr = initLimitRand(arr, maxElem, valMin, valMax, unique);
    //stampa l'array
    printArr(arr, maxElem);

	//- - - - - - - - - - - - RICERCA MULTIPROCESSO - - - - - - - - - - - - - //
    //l'utente sceglie che valore cercare
    printf(ANSI_BLUE "Quale valore vuoi cercare nell'array?\n" ANSI_RESET);
    getInt(&elem);
    //richiede quanti processi si vogliono creare
    printf(ANSI_BLUE "Quanti processi vuoi creare?\n[da 1 a %d]\n"
           ANSI_RESET, maxElem);
    getLimitInt(&nProc, 1, maxElem);

    printf(ANSI_BLUE "\nRicerca dell'elemento %d con %d processi...\n"
           ANSI_RESET, elem, nProc);
    //salva il tempo del punto di partenza
    //funzione non compatibile con POSIX.1-2008
    //TODO sostituire con clock_gettime()
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
            //ogni processo stampa i suoi risultati
            if(searchPrintElem(arr, prev, next, elem))
                printf(ANSI_GREEN "\tdal processo %d\n", getpid());
            else
                printf(ANSI_YELLOW "Nessuna corrsispondenza trovata\n"
                       ANSI_YELLOW "\tdal processo %d\n" ANSI_RESET, getpid());
            //return 0;
            exit(0);
        }
        //il padre aspetta che i figli terminino la ricerca
        else if(pid > 0 && i == nProc-1) {
            waitpid(pid, NULL, 0);
            //wait(NULL);
        }
        else if(pid < 0){
            printf(ANSI_RED "Errore nel fork %d!\n" ANSI_RESET, pid);
            exit(1);
        }
    }
    //il padre aspetta che l'ultimo processo termini
    waitpid(pid, NULL, 0);
    //salva il tempo del punto di arrivo
	gettimeofday(&stop, NULL);
	timeTot = (double)(stop.tv_usec - start.tv_usec) / 1000000 +
			  (double)(stop.tv_sec - start.tv_sec);
	//stampa il tempo totale impiegato
	printf(ANSI_GREEN "Tempo totale impiegato da %d processi = %.3f [ms]\n\n"
		   ANSI_RESET, nProc, timeTot);

    //- - - - - - - - - - - RICERCA SINGOLO PROCESSO - - - - - - - - - - - - -//
    printf(ANSI_BLUE "\nRicerca dell'elemento %d con processo singolo...\n"
           ANSI_RESET, elem);
    //salva il tempo del punto di partenza
    gettimeofday(&start, NULL);
    if(!searchPrintElem(arr, 0, maxElem, elem))
		printf(ANSI_YELLOW "Nessuna corrsispondenza trovata "
			  "con il processo singolo\n" ANSI_RESET);
    //salva il tempo del punto di arrivo
	gettimeofday(&stop, NULL);
	timeTot = (double)(stop.tv_usec - start.tv_usec) / 1000000 +
			  (double)(stop.tv_sec - start.tv_sec);
	//stampa il tempo totale impiegato
	printf(ANSI_GREEN
           "Tempo totale impiegato dal singolo processo = %.3f [ms]\n\n"
		   ANSI_RESET, timeTot);

    //TODO export17445516112018.csv --> export 17:44:55 16/11/2018
    printf("timestamp = %s\n", getTimestamp(0));

    return 0;
}
