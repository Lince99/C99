/*
 * Basso Nicola
 * 4^AI
 */

#include <stdio.h>
#include <stdlib.h>
#include "lib/manager_params.h"

int main(int argc, char** argv) {
    int i = 0;
    int* ret = NULL;
    char* str = NULL;

    printf("argc = %d\n", argc);
    for(i = 1; i < argc; i++)
        printf("argv = %s\n", *(argv+i));
    printHelp(argc, argv);
    ret = getInt(argc, argv, "-n", "--number");
    if(ret != NULL)
        printf("ret = %d\n", *ret);

    str = getChars(argc, argv, "-s", "--string");
    if(str != NULL)
        printf("str = %s\n", str);

	return 0;
}
