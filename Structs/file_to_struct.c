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

#define MAX_CHAR 50
#define MAX_DATA 100

//struttura che contiene i dati di una persona
typedef struct Personal_data
{
    char nome [MAX_CHAR];
    char cognome [MAX_CHAR];
    unsigned int eta;
} ps_data;

//dichiarazioni funzioni
void getFileName (char* fname);
void readContent (char* fname, ps_data* people, char* format);
void printContent (ps_data* people);
void writeContent (char* fname, ps_data* people, char* format);
void orderContent (ps_data* people);



int main (int argc, char** argv)
{
    FILE* fp; //file puntatore
    ps_data people[MAX_DATA];
    char nome_file[MAX_CHAR];

    //richiedere nome file
    getFileName(nome_file);
    //legge i dati dal file e li salva nelle struct
    readContent(nome_file, people, "%s\t%s\t%d");
    //stampa i risultati
    printContent(people);
	//esegue l'ordinamento alfabetico
    orderContent(people);
    //e lo stampa
    printf("Array ordinata alfabeticamente:\n");
    printContent(people);
    //infine lo scrive su file la struttura aggiornata
    writeContent("ordered.txt", people, "%s\t%s\t%d");

    return 0;
}

//funzione che legge in input il nome del file e lo controlla
void getFileName (char* fname)
{
    int check;
    printf("Inserisci il nome del file da leggere ");
    printf("- senza spazi\n");
    printf("- max %d caratteri\n", MAX_CHAR);
    printf("- ordine: NOME tabulazione COGNOME tabulazione ETA' invio\n");
    do
    {
        printf("--> ");
        check = scanf("%s", fname);
        if(check == 0 || check == EOF)
            printf("Input non valido!\nRe-Inserisci il nome del file:\n");
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
		printf("Impossibile leggere il file!\nChiusura programma...\n");
		exit(1);
	}
	//e aggiunge i dati alla struct con la formattazione data
  //fino al massimo definito in MAX_DATA se necessario
  i, check = 0;
  do
  {
      check = fscanf(fp, format,
                     people[i].cognome, people[i].nome, &people[i].eta);
  } while(check != EOF && i < MAX_DATA);
  fclose(fp);
}

//funzione che stampa il contenuto della struct
void printContent (ps_data* people)
{
    int i;
    for(i = 0; i < MAX_DATA; i++)
    {
        printf("%s %s %d\n",
               people[i].nome, people[i].cognome, people[i].eta);
    }
}

//funzione che scrive su file l'array di strutture seguendo format
void writeContent (char* fname, ps_data* people, char* format)
{
	FILE* fp;
	int i;

	if((fp = fopen(fname, "w+")) == NULL)
	{
		printf("Imposssibile scrivere sul file!\nChiusura programma...\n");
		exit(1);
	}
    //scrive sul file fino alla costante che fa da limite
    for(i = 0; i < MAX_DATA; i++)
	   fprintf(fp, format, people[i].cognome, people[i].nome, people[i].eta);
	fclose(fp);
}

//funzione principale del programma:
//ordina alfabeticamente l'array di persone, e moltiplica x 2 l'eta'
void orderContent (ps_data* people)
{
    int i, j;
    char* conc0, conc1;
    ps_data tmpPers;

    //selection sort
    for(i = 0; i < MAX_DATA; i++)
    {
        for(j = 1; j < MAX_DATA; j++)
        {
            //TODO HERE
            strcat(conc0, people[i].cognome people[i].nome);
            strcat(conc1, people[j].cognome people[j].nome);
            //scambia la prima se e' maggiore della seconda
            if(strcmp(conc0, conc1) > 0)
            {
                tmpPers = people[i];
                people[i] = people[j];
                people[j] = tmpPers;
            }
        }
    }
}
