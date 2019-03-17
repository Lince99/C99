#include <ncurses.h>



int main(int argc, char *argv[]) {
    WINDOW *main_w;
    int ncols = 0;
    int nlines = 0;
    int x = 0;
    int y = 0;

    int ch = 0;

    //initialize Ncurses
    initscr();
    //get current terminal window max coordinates
    getmaxyx(stdscr, nlines, ncols);
    wprintw(stdscr, "Dimensions: y = %d\tx = %d\n", nlines, ncols);
    wprintw(stdscr, "Press any button to continue\n");
    getch();
    wclear(stdscr);
    //create the main window
    main_w = newwin(nlines, ncols, y, x);


    raw();
    keypad(main_w, 1);
    //curs_set(0);
    noecho();

    while(1) {
        ch = wgetch(main_w);
        if(ch == 'q') {
            wclear(main_w);
            wmove(main_w, 0, 0);
            wprintw(main_w, "Quitting...");
            //free Ncurses window
            delwin(main_w);
            //wait for user to stop
            getch();
            break;
        }
        getmaxyx(stdscr, nlines, ncols);
        wmove(main_w, y, x);
        switch(ch) {
            case KEY_UP:
                wprintw(main_w, "\nUp Arrow");
                break;
            case KEY_DOWN:
                wprintw(main_w, "\nDown Arrow");
                break;
            case KEY_LEFT:
                wprintw(main_w, "\nLeft Arrow");
                break;
            case KEY_RIGHT:
                wprintw(main_w, "\nRight Arrow");
                break;
            default:
                wprintw(main_w, "\nThe pressed key is ");
                attron(A_BOLD);
                wprintw(main_w, "%c", ch);
                attroff(A_BOLD);
                break;
        }
        y == nlines-1 ? y = 0 : y++;
        //update window content
        //wrefresh(main_w);
    }

    //stop Ncurses
    endwin();

    return 0;
}
