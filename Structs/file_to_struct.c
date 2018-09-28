/*
* Basso Nicola
* 4^AI
* 18/09/2018
*/
/*
* Implementare un programma che apra un file di testo in lettura;
* il file sarà composta da n righe formate da un cognome,
* un nome ed un valore numero intero non nullo.

* Il programma creerà un nuovo file, mettendo le righe in ordine alfabetico
* per cognome e moltiplicando per 2 tutti i valori numerici.

* Il nome del file di ingresso e del file in uscita
* sono parametri che inserirà l'utente.

* Commentare opportunamente e prevedere casi particolare e problemi vari.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"

#define MAX_CHAR 50
#define MAX_DATA 100

//struttura che contiene i dati di una persona
typedef struct Personal_data
{
    char cognome [MAX_CHAR];
    char nome [MAX_CHAR];
    unsigned int eta;
} ps_data;

//dichiarazioni funzioni
void initialize (ps_data* people);
void getFileName (char* fname, int init);
void readContent (char* fname, ps_data* people, char* format);
void printContent (ps_data* people);
void writeContent (char* fname, ps_data* people, char* format);
void orderContent (ps_data* people);

//dichiarazioni variabili globali
int newDim; //variabile che conterra' la dimensione del totale dei dati letti

int main (int argc, char** argv)
{
    FILE* fp; //file puntatore
    ps_data people[MAX_DATA];
    char nome_file[MAX_CHAR];
    char nome_file_out[MAX_CHAR];
    char* format;
    int newDim;


    //inizializza l'array di persone
    initialize(people);
    newDim = 0;
    //--MODIFICARE QUESTO NEL CASO IL FILE ABBIA UN FORMATO DIVERSO--
    format = "%s\t%s\t%d\n"; //formato di lettura dei dati dal file

    //legge i dati dal file richiesto e li salva nelle struct
    getFileName(nome_file, 1);
    readContent(nome_file, people, "%s\t%s\t%d\n");
    //stampa i risultati
    printContent(people);

	//esegue l'ordinamento alfabetico
    orderContent(people);
    //e lo stampa
    printf(ANSI_COLOR_GREEN "Array ordinata alfabeticamente:\n" ANSI_COLOR_RESET);
    printContent(people);

    //infine lo scrive su file la struttura aggiornata
    getFileName(nome_file_out, 0);
    writeContent(nome_file_out, people, "%s\t%s\t%d\n");

    return 0;
}



//funzione che inizializza tutto a 0 l'array di persone
void initialize (ps_data* people)
{
    int i;

    for(i = 0; i < MAX_DATA; i++)
    {
        strcpy(people[i].cognome, "");
        strcpy(people[i].nome, "");
        people[i].eta = 0;
    }
}

//funzione che legge in input il nome del file e lo controlla
//init e' un flag di controllo per stampare le condizioni di lettura
void getFileName (char* fname, int init)
{
    int check;
    printf("Inserisci il nome del file:\n");
    if(init)
    {
        printf(ANSI_COLOR_YELLOW "- gli spazi verranno ignorati\n");
        printf("- max %d caratteri\n", MAX_CHAR);
        printf("- ordine: NOME tabulazione COGNOME tabulazione ETA' invio\n" ANSI_COLOR_RESET);
    }
    do
    {
        printf(ANSI_COLOR_GREEN "--> " ANSI_COLOR_RESET);
        check = scanf("%s", fname);
        if(check == 0 || check == EOF)
            printf(ANSI_COLOR_RED "Input non valido!\nRe-Inserisci il nome del file:\n" ANSI_COLOR_RESET);
    } while(check == 0 || check == EOF);
}

//funzione che dato il nome del file ne estrapola i dati
//formattati secondo istruzioni date da consegna
void readContent (char* fname, ps_data* people, char* format)
{
    FILE* fp;
    char c;
    int i, check;

	//apre il file in sola lettura
	if((fp = fopen(fname, "r")) == NULL)
	{
		printf(ANSI_COLOR_RED "Impossibile leggere il file!\nChiusura programma...\n" ANSI_COLOR_RESET);
		exit(1);
	}
	//e aggiunge i dati alla struct con la formattazione data
    //fino al massimo definito in MAX_DATA se necessario
    i, check = 0;
    do
    {
        check = fscanf(fp, format,
                       people[i].cognome, people[i].nome, &people[i].eta);
        i++;
    } while(check != EOF);
    newDim = i;
    //printf("dimensione = %d\n", i);
    fclose(fp);
}

//funzione che stampa il contenuto della struct
void printContent (ps_data* people)
{
    int i;
    for(i = 0; i < newDim; i++)
    {
        if(people[i].eta != 0)
            printf("%s %s %d\n", people[i].cognome,
                   people[i].nome, people[i].eta);
    }
}

//funzione che scrive su file l'array di strutture seguendo il format dato
void writeContent (char* fname, ps_data* people, char* format)
{
	FILE* fp;
	int i;

	if((fp = fopen(fname, "w+")) == NULL)
	{
		printf(ANSI_COLOR_RED "Imposssibile scrivere sul file!\nChiusura programma...\n" ANSI_COLOR_RESET);
		exit(1);
	}
    //scrive sul file fino alla costante che fa da limite
    for(i = 0; i < newDim; i++)
    {
        if(people[i].eta != 0)
            fprintf(fp, format, people[i].cognome,
                    people[i].nome, people[i].eta);
    }
	fclose(fp);
}

//funzione principale del programma:
//ordina alfabeticamente l'array di persone, e moltiplica x 2 l'eta'
void orderContent (ps_data* people)
{
    int i, j;
    char conc0[MAX_CHAR*2];
    char conc1[MAX_CHAR*2];
    ps_data tmpPers;

    //bubblesort
    for(i = 0; i < newDim; i++)
    {
        //moltiplica per 2 l'eta'
        people[i].eta *= 2;
        for(j = 0; j < (newDim-i-1); j++)
        {
            //unisce cognome e nome in una sola stringa per facilitare
            //il confronto tra le due stringhe
            strcpy(conc0, people[j].cognome);
            strcat(conc0, people[j].nome);
            strcpy(conc1, people[j+1].cognome);
            strcat(conc1, people[j+1].nome);
            //se il successivo e' maggiore del secondo li scambia
            if(strcmp(conc0, conc1) > 0)
            {
                tmpPers = people[j];
                people[j] = people[j+1];
                people[j+1] = tmpPers;
            }
        }
    }
}
