/*
 * Basso Nicola
 * 4^AI
 */
/*
 * libreria dedicata alla gestione della comunicazione tra processi
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "colors.h"
#include "manager_array.h"

/*
 * Create pipe
 * Fork
 * In parent:
 *     Close read end of pipe
 *     Write data to be sorted down write end of pipe
 *     Close write end of pipe
 *     Wait for child to die
 * In child
 *     Close write end of pipe
 *     Duplicate read end of pipe to stdin
 *     Close read end of pipe
 *     Exec the sort program
 *     Exit with an error if the exec returns
 */



void writePipe
