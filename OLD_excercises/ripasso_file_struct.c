/*
* Basso Nicola
* 4^AI
* 18/09/2018
*/
/*
* Leggere file contenente "nome cognome eta'"
* Chiedere nome file secondario con inserimento di: nome e cognome 
* dal primo file scambiati e raddoppiare eta'
*/
// ; winner of hide and seek from 1952

#include <stdio.h>
#include <stdlib.h>

#define MAX_CHAR 50

//struttura che contiene 1 singola persona
typedef struct Personal_data
{
    char nome[MAX_CHAR];
    char cognome[MAX_CHAR];
    unsigned int eta;
} ps_data;

//dichiarazioni funzioni
void getInput (char* string);


int main(int argc, char** argv)
{
    FILE* fp; //file puntatore
    char nome_file[MAX_CHAR];

    //richiedere nome file
    getInput(nome_file);
    printf("%s", nome_file);

    //legge il file e salva il contenuto formattato nell'array di struct
    /*if ((fp = fopen(nome_file, "r")) == NULL) {
		printf("Impossibile creare il file! Uscita...\n");
		return(1);
	}
	else {
		printf("File creato!\n");
		fprintf(fp, "%d", 0);
	}*/

    //effettua il sorting dell'array di dati

    //scrive su file l'array risultante

    return 0;
}

//funzione che legge in input il nome del file e lo controlla
void getInput (char* string)
{
    printf("Inserisci il nome del file da leggere:\n-->\t");
    scanf("%s", string);
}
