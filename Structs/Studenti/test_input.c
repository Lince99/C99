#include <stdio.h>
#include <stdlib.h>

typedef struct st {
	char* str;
} ST;

int main() {
	ST* test = NULL;

	test = (ST*) malloc(sizeof(ST)*5);
	(test+1)->str = (char*) malloc(sizeof(char)*50);

	printf("Inserisci Stringa:\n");
	scanf("%s", (test+1)->str);

	int n = 0;
	fscanf(stdin, "%d", &n);
	printf("%s\n", test[1].str);

	fprintf(stdout, "n = %d\n", n);
	return 0;
}
