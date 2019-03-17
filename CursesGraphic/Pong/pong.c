#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

int DELAY = 30000;
int SPEED_MAX_LIMIT = 100000;
int SPEED_MIN_LIMIT = 1000;

//signatures
WINDOW* newWindow(int* nlines, int* ncols, int y, int x);



int main(int argc, char *argv[]) {
    //window params
    WINDOW* main_w;
    int nlines = 0;
    int ncols = 0;
    int y = 0;
    int x = 0;
    //ball params
    int direction_y = 1;
    int direction_x = 1;
    char ball = 'x';
    //user params
    int ch = 0;
    /*
        # <-- player_y, player_x
        #
        #
    */
    int player_y = 0;
    int player_x = 2;
    int player_dim = 3;
    int collision = 0;

    //initialize Ncurses
    initscr();

    //create a new window
    main_w = newWindow(&nlines, &ncols, 0, 0);
    //continue the game until q is reached
    while(ch != 'q') {
        getmaxyx(stdscr, nlines, ncols);

        //CHANGE BALL POSITION
        //if on top
        if(y == 0)
            direction_y = 1;
        //if on bottom
        else if(y == nlines-1)
            direction_y = 0;
        //if on left
        if(x == 0)
            direction_x = 1;
        //if on right
        else if(x == ncols-1)
            direction_x = 0;

        //CHANGE PLAYER POSITION
        wrefresh(main_w);
        ch = wgetch(main_w);
        switch(ch) {
            case 'w':
                if(player_y > 0)
                    player_y--;
                break;
            case 's':
                if(player_y < nlines-1-player_dim)
                    player_y++;
                break;
            case 'l':
                if(DELAY < SPEED_MAX_LIMIT)
                    DELAY += 1000;
                break;
            case 'p':
                if(DELAY > SPEED_MIN_LIMIT)
                    DELAY -= 1000;
                break;
            case 'q':
                mvwprintw(main_w, 0, 0, "Quitting...");
                wgetch(main_w);
                break;
            default:
                break;
        }
        wattron(main_w, A_BOLD);
        mvwprintw(main_w, player_y, player_x, "#");
        mvwprintw(main_w, player_y+1, player_x, "#");
        mvwprintw(main_w, player_y+2, player_x, "#");
        wattroff(main_w, A_BOLD);
        //check collision
        if(x == player_x) {
            if(y == player_y || y == player_y-1 || y == player_y-2) {
                collision = 1;
                direction_x = !direction_x;
            }
            else
                collision = 0;
        }
        else
            collision = 0;

        //move cursor
        if(direction_y)
            y++;
        else
            y--;
        if(direction_x)
            x++;
        else
            x--;
        mvwprintw(main_w, y, x, "%c", ball);

        mvwprintw(main_w, nlines-2, ncols-20, "y=%d x=%d delay=%d", y, x, (int)DELAY/1000);
        if(collision)
            mvwprintw(main_w, nlines-1, ncols-10, "COLLISION");
        //update window content
        wrefresh(main_w);
        wclear(main_w);
        if(ch != 'q')
            usleep(DELAY);
    }

    //free Ncurses window
    delwin(main_w);
    //stop Ncurses
    endwin();

    return 0;
}

/*
 * initscr() MUST be already called
 */
WINDOW* newWindow(int* lines, int* cols, int y, int x) {
    WINDOW* w = NULL;
    int nlines = *lines;
    int ncols = *cols;

    //get current terminal window max coordinates
    getmaxyx(stdscr, nlines, ncols);
    w = newwin(nlines, ncols, y, x);

    //cbreak();
    raw();
    nodelay(w, 1);
    keypad(w, 1);
    curs_set(0);
    noecho();

    return w;
}
