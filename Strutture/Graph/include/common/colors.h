/*
 * Copyright 2019 Lince99
 * for the license refer to the prject's license
 */
/*
 * library dedicated only to define constant string that change text color or background
 * on terminals that support ANSI escape characters
 */

#ifndef COLORS_H
#define COLORS_H



//move cursor
#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))
/*void gotoxy(int x, int y) {
    printf("\033[%d;%dH", x, y);
}*/

//clear the screen
#ifndef ANSI_CLEAN
    #define ANSI_CLEAN "\x1b[H\x1b[J"
#endif

//font colors (foreground)
#ifndef ANSI_BLACK
    #define ANSI_BLACK "\x1b[30m"
#endif

#ifndef ANSI_RED
    #define ANSI_RED "\x1b[31m"
#endif

#ifndef ANSI_GREEN
    #define ANSI_GREEN  "\x1b[32m"
#endif

#ifndef ANSI_YELLOW
    #define ANSI_YELLOW  "\x1b[33m"
#endif

#ifndef ANSI_BLUE
    #define ANSI_BLUE    "\x1b[34m"
#endif

#ifndef ANSI_MAGENTA
    #define ANSI_MAGENTA "\x1b[35m"
#endif

#ifndef ANSI_CYAN
    #define ANSI_CYAN    "\x1b[36m"
#endif

#ifndef ANSI_WHITE
    #define ANSI_WHITE     "\x1b[37m"
#endif



//background colors
#ifndef ANSI_BG_BLACK
    #define ANSI_BG_BLACK     "\x1b[40m"
#endif

#ifndef ANSI_BG_RED
    #define ANSI_BG_RED     "\x1b[41m"
#endif

#ifndef ANSI_BG_GREEN
    #define ANSI_BG_GREEN   "\x1b[42m"
#endif

#ifndef ANSI_BG_YELLOW
    #define ANSI_BG_YELLOW  "\x1b[43m"
#endif

#ifndef ANSI_BG_BLUE
    #define ANSI_BG_BLUE    "\x1b[44m"
#endif

#ifndef ANSI_BG_MAGENTA
    #define ANSI_BG_MAGENTA "\x1b[45m"
#endif

#ifndef ANSI_BG_CYAN
    #define ANSI_BG_CYAN    "\x1b[46m"
#endif

#ifndef ANSI_BG_WHITE
    #define ANSI_BG_WHITE     "\x1b[47m"
#endif

#ifndef ANSI_REVERSE
    #define ANSI_REVESE     "\x1b[7m"
#endif


//font styles
#ifndef ANSI_BOLD
    #define ANSI_BOLD    "\x1b[1m"
#endif

#ifndef ANSI_ITALIC
    #define ANSI_ITALIC    "\x1b[3m"
#endif

#ifndef ANSI_UNDERLINE
    #define ANSI_UNDERLINE    "\x1b[4m"
#endif

#ifndef ANSI_NOT_OVERLINE
    #define ANSI_NOT_OVERLINE    "\x1b[24m"
#endif

#ifndef ANSI_OVERLINE
    #define ANSI_OVERLINE    "\x1b[53m"
#endif



//restore the original foreground and background colors
#ifndef ANSI_RESET
    #define ANSI_RESET   "\x1b[0m"
#endif

#endif //COLORS_H
