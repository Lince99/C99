#include <ncurses.h>
#include <signal.h>

//signatures



int main(int argc, char *argv[]) {
    int nlines = 0; //y
    int ncols = 0; //x
    int y = 0;
    int x = 0;
    int ch_in = 0;
    WINDOW *main_w;

    //initialize Ncurses
    initscr();
    //ncurses doesn't print what you write
    noecho();
    //one char at time (aka no buffering)
    cbreak();
    //hide terminal cursor
    curs_set(FALSE);
    //accept special character
    keypad(main_w, TRUE);
    //getch return ERR if the key input is not ready
    nodelay(stdscr, TRUE);

    //get current terminal window max coordinates
    getmaxyx(stdscr, nlines, ncols);
    //create the main window
    main_w = newwin(nlines, ncols, y, x);

    //create a static box
    //box(main_w, 0, 0);
    //draw a box surrounding all borders
    //wborder(main_w, 0, 0, 0, 0, 0, 0, 0, 0);
    //draw a straight line
    //whline(main_w, ACS_HLINE, ncols);

    //getyx(main_w, y, x);
    //mvwprintw(main_w, y, x, "%d, ", ch_in);
    //move cursor to y x
    //wmove(main_w, y, x);
    //print 1 char at the current position
    //waddch(main_w, 'x');

    //DO STUFF
    while(1) {
        //get current terminal window max coordinates
        getmaxyx(stdscr, nlines, ncols);

        //print on window some data
        wprintw(main_w, "Dimension: y=%d\tx=%d", nlines, ncols);
        y = (y == nlines-1) ? 0 : y++;
        wmove(main_w, y++, x) ? y = 0 : y;

        whline(main_w, ACS_HLINE, ncols);
        y = (y == nlines-1) ? 0 : y++;
        wmove(main_w, y++, x) ? y = 0 : y;

        wrefresh(main_w);

        //get user input and print it
        ch_in = wgetch(main_w);

        wattron(main_w, A_STANDOUT);

        wprintw(main_w, "ch_in = %d\n", ch_in);
        wmove(main_w, y++, x) ? y = 0 : y;

        wattroff(main_w, A_STANDOUT);

        //update window content
        wrefresh(main_w);
    }

    //free Ncurses window
    delwin(main_w);

    //stop Ncurses
    endwin();
    return 0;
}
