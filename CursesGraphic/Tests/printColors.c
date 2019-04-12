#include <stdio.h>
#include <ncurses.h>

int main()
{
    initscr();

    if(!has_colors()) {
        endwin();
        printf("No color support!\n");
        return -1;
    }

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    attron(COLOR_PAIR(1));
    printw("This is a test!");
    attroff(COLOR_PAIR(1));

    endwin();

    return 0;
}
