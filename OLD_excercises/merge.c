/**
 * Merge multiprocessing in c
 * Tomas  Fornasa
 * 22/10/2017
 */

/**
 * WORKING
 * - count cores
 */

/**
 * TODO
 * - manage fork()
 * - merge
 * - join the outputs
 * - files
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

/* INFO ABOUT PROGRAM VERSION */
#define WIP 1
#define VERSION "0.0.3 lambda λ"
/**
 * I File sul quale il programma lavorerá,
 * saranno principalmetnte i nomi dei processi
 * p1, p2, p3, p4, ecc...
 */
#define NOME_FILE "array.data" // Nome file output
/**
 * numero massimo di caratteri da leggere
 * Min 1500 char in /proc/cpuinfo per un Dual-core
 */
#define MAX_FILE 100000
/**
 * EXIT ERRORS
 */
#define EXIT 0
#define EXIT_FILE_READ 1
#define EXIT_FILE_WRITE 2
#define EXIT_FILE_APPEND 3

int str_len(char* string);
void fill_rand(int a[], int size);
void copy_array(int len, char* a, char* b);
int startswith( int start, char string[], char prefix[]);
int write_file(int a[], int size);
int check_cores();

/* GLOABAL VARS */
int DEBUG = 0;

/* MAIN */
int main(int argc, char** argv)
{
	/* ARGV */
	if(argc == 2) {
		if((char)argv[1][0] == '-') {
			// Help
			if((char)argv[1][1] == 'h') {
				printf("Usage: ./merge args\n");
				printf("\n	-h: Help\n		Show this help\n");
				printf("\n	-V: Verbose\n		Outputs debug infos in prints\n");
				printf("\n	-v: Version\n		Display current version of the program\n\n");
				return 0;
			}
			// Version
			else if((char)argv[1][1] == 'v') {
				if(WIP) {
					printf("Work In Progress version\n");
					printf("please if you find any bug contact oples@hoplestreasure.tk\n\n");
				}
				printf("Version: %s\n", VERSION);
				return 0;
			}
			// Verbose
			else if((char)argv[1][1] == 'V') {
				DEBUG = 1; // Output debug
			}
		}
	}

	int a[10];
	int size = sizeof(a)/sizeof(int);

	int proc = check_cores();

	// linux more likely
	if(proc > 0) {
		printf("Found %d cores!\n", proc);
	}
	// other os
	else {
		printf("Error on getting cores information\n");
		printf("seek to use this program on linux in the future\n");
	}
	printf("If the cores aren't right please specify\n");

	fill_rand(a, size);

	return write_file(a, size);
}

/* Get length of a string/char[] */
int str_len(char* string)
{
	int i;

	i = 0;
	while(string[i++]);

	return i;
}

/* Fill an array in random numbers */
void fill_rand(int a[], int size)
{
	int i;

	// Randomize the seed
	srand(time(NULL));

	for(i = 0; i < size; i++) {
		a[i] = rand()%42+1;
	}
}

/* Scrivi nel file un array */
int write_file(int a[], int size)
{
	// Vars
	FILE *fp;
	int i;

	// Exec
	if((fp = fopen( NOME_FILE, "a")) == NULL) {
		if((fp = fopen( NOME_FILE, "w")) == NULL) {
			return EXIT_FILE_WRITE;
		}
	}

	for(i = 0; i < size; i++) {
		fprintf(fp, "%d ", a[i]);
	}

	fprintf(fp, "\n");
	fclose(fp);

	return EXIT;
}

/* Cores count */
int check_cores()
{
	FILE *fp; // Puntatore file
	int i; // contatore
	int size; // dimenasione file
	char c[1]; // carattere singolo

	if(DEBUG){ printf("::\n:: check_cores()\n"); }

	fp = fopen("/proc/cpuinfo","r");

	if(DEBUG && (fp != NULL)){ printf("::   File /proc/cpuinfo is open!\n"); }
	else if(DEBUG && (fp == NULL)){ printf("::   File /proc/cpuinfo failed to read\n"); }

	if(fp == NULL) {
		/* return an error more likely
		 * it's not running on windows
		 */
		return -1;
	}

	// vai alla fine del file e leggi
	// l'indirizzo ritornano cosi' la dimensione del file
	char buffer[MAX_FILE]; // salva il file in RAM

	i = 0;
	while((!feof(fp)) && (MAX_FILE > i)) {
		fscanf(fp, "%c", c);
		buffer[i] = c[0];
		i++;
	}
	buffer[i] = 0;

	// DEBUG
	if(DEBUG){ printf("::   Chars in buffer[%d]: %d\n", MAX_FILE, str_len(buffer)); }

	char new_buffer[str_len(buffer)]; // salva il file in RAM

	copy_array( str_len(buffer), buffer, new_buffer);

	//printf("%s", buffer);

	int k = 0; // Counter
	int max = str_len(new_buffer); // length of new_buffer
	int pos;   // Position for the lecture of new_buffer
	int cores = 0; // Cores count
	while(k < max) {
		// Search for the word processor : in the cpuinfo file
		pos = startswith( k++, new_buffer, "processor\t:");

		if(pos > 0) {
			cores++;

			if(DEBUG) {
				printf("::   Contatore K: %d\n", k);
				printf("::   Core: %c\n", new_buffer[pos+1]);
			}
		}

	}
	// close file
	fclose(fp);

	if(DEBUG) { printf("::\n"); }

	// return the cores found in the file
	return cores;
}

void merge(int a[], int b[]);

int startswith(int start, char string[], char prefix[])
{
	// Vars
	int i, j;

	j = start < str_len(string) ? start : 0;
	i = 0;

	while(prefix[i]) {
		if(prefix[i++] != string[j++]) {
			return 0;
		}
	}

	return j;
}

/* Reach end oh line and return */
int end(int start, char string[])
{
	int i; // counter

	i = start;
	while(string[i]) {
		if(string[i] == '\n') {
			return i;
		}
		i++;
	}
	return -1;
}

/* Copy A in B */
void copy_array(int len, char* a, char* b)
{
	int i;

	for(i = 0; i < len; i++) {
		b[i] = a[i];
	}
}
