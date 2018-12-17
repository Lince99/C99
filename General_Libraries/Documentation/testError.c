#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

extern int errno;

int main(int argc, char** argv) {
	unsigned int i = 0;

	if(argc > 1) {
		for(i = 0; i < atoi(argv[1]); i++) {
			errno = i;
			fprintf(stderr, "%d - %s\n", i, strerror(errno));
		}
	}

	return 0;
}
