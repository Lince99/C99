#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/colors.h"

//signatures
void print_rainbow(int count, int mult);

//globals
unsigned int slep = 8000;

int main(int argc, char** argv) {
    int m = 1;
    int c = 1;

    for(int i = 0; i < argc; i++)
        printf("[%d] %s\n", i, argv[i]);
    if(argc > 1)
        c = atoi(argv[1]);
    if(argc > 2)
        m = atoi(argv[2]);
    if(argc > 3)
        slep = (unsigned int)atoi(argv[3])*1000;
    printf("\n");
    scanf("Press Enter to continue...");
    print_rainbow(c, m);
    printf(ANSI_CLEAN);

    return 0;
}

void print_rainbow(int count, int mult) {
    char ch = ' ';
    int x = 0;
    int n = 0;
    int y = 0;
    int tmp = 0;

    //for(y = 0; y < count; y++) {
    while(true) {
        //slep = (int)(rand()%10)*5000;
        for(n = 0; n < count; n++) {
            for(x = 0; x < n; x++)
                printf(ANSI_RESET "%c", ch);
            for(tmp = 0; tmp < mult; tmp++)
                printf(ANSI_BOLD ANSI_BG_MAGENTA ANSI_MAGENTA "%c", ch);
            for(tmp = 0; tmp < mult; tmp++)
                printf(ANSI_BG_MAGENTA ANSI_MAGENTA "%c", ch);
            for(tmp = 0; tmp < mult; tmp++)
                printf(ANSI_BOLD ANSI_BG_BLUE ANSI_BLUE "%c", ch);
            for(tmp = 0; tmp < mult; tmp++)
                printf(ANSI_BG_BLUE ANSI_BLUE "%c", ch);
            for(tmp = 0; tmp < mult; tmp++)
                printf(ANSI_BOLD ANSI_BG_GREEN ANSI_GREEN "%c", ch);
            for(tmp = 0; tmp < mult; tmp++)
                printf(ANSI_BG_GREEN ANSI_GREEN "%c", ch);
            for(tmp = 0; tmp < mult; tmp++)
                printf(ANSI_BOLD ANSI_BG_YELLOW ANSI_YELLOW "%c", ch);
            for(tmp = 0; tmp < mult; tmp++)
                printf(ANSI_BG_YELLOW ANSI_YELLOW "%c", ch);
            for(tmp = 0; tmp < mult; tmp++)
                printf(ANSI_BOLD ANSI_BG_RED ANSI_RED "%c", ch);
            for(tmp = 0; tmp < mult; tmp++)
                printf(ANSI_BG_RED ANSI_RED "%c", ch);
            for(; x < n; x++) {
                printf(ANSI_BG_BLACK ANSI_BLACK "%c", ch);
            }
            printf(ANSI_RESET "\n");
            usleep(slep);
        }
        for(n = count-1; n >= 0; n--) {
            for(x = 0; x < n; x++)
                printf(ANSI_RESET "%c", ch);
            for(tmp = 0; tmp < mult; tmp++)
                printf(ANSI_BOLD ANSI_BG_MAGENTA ANSI_MAGENTA "%c", ch);
            for(tmp = 0; tmp < mult; tmp++)
                printf(ANSI_BG_MAGENTA ANSI_MAGENTA "%c", ch);
            for(tmp = 0; tmp < mult; tmp++)
                printf(ANSI_BOLD ANSI_BG_BLUE ANSI_BLUE "%c", ch);
            for(tmp = 0; tmp < mult; tmp++)
                printf(ANSI_BG_BLUE ANSI_BLUE "%c", ch);
            for(tmp = 0; tmp < mult; tmp++)
                printf(ANSI_BOLD ANSI_BG_GREEN ANSI_GREEN "%c", ch);
            for(tmp = 0; tmp < mult; tmp++)
                printf(ANSI_BG_GREEN ANSI_GREEN "%c", ch);
            for(tmp = 0; tmp < mult; tmp++)
                printf(ANSI_BOLD ANSI_BG_YELLOW ANSI_YELLOW "%c", ch);
            for(tmp = 0; tmp < mult; tmp++)
                printf(ANSI_BG_YELLOW ANSI_YELLOW "%c", ch);
            for(tmp = 0; tmp < mult; tmp++)
                printf(ANSI_BOLD ANSI_BG_RED ANSI_RED "%c", ch);
            for(tmp = 0; tmp < mult; tmp++)
                printf(ANSI_BG_RED ANSI_RED "%c", ch);
            printf(ANSI_RESET "\n");
            usleep(slep);
        }
    }

}
