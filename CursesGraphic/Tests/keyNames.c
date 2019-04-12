#include <stdio.h>
#include <ncurses.h>
#define ctrl(x)           ((x) & 0x1f)

int main(void) {
    int c;
    initscr();
    keypad(stdscr, TRUE);
    //cbreak();
    noecho();
    raw();

    while(1) {
        c = wgetch(stdscr);
        mvprintw(0, 0, "KEY NAME: %s - %d\n", keyname(c), c);
    }
    printw("now press a key to end ");
    getch();
    endwin();

    return 0;
}
