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
            //getch();
            break;
        }
        getmaxyx(stdscr, nlines, ncols);
        //wmove(main_w, y, x);
        switch(ch) {
            case KEY_UP:
                if(y-1 >= 0)
                    y--;
                //wprintw(main_w, "\nUp Arrow");
                break;
            case KEY_DOWN:
                if(y+1 < nlines)
                    y++;
                //wprintw(main_w, "\nDown Arrow");
                break;
            case KEY_LEFT:
                if(x-1 >= 0)
                    x--;
                //wprintw(main_w, "\nLeft Arrow");
                break;
            case KEY_RIGHT:
                if(x+1 < ncols)
                    x++;
                //wprintw(main_w, "\nRight Arrow");
                break;
            default:
                //mvwprintw(main_w, y, x, "\nThe pressed key is ");
                attron(A_BOLD);
                mvwprintw(main_w, y, x, "%c", ch);
                attroff(A_BOLD);
                break;
        }
        wmove(main_w, y, x);
        //y == nlines-1 ? y = 0 : y++;
        //update window content
        wrefresh(main_w);
    }

    //stop Ncurses
    endwin();

    return 0;
}
