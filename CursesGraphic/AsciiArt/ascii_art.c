#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/queue_char.h"

//manage Ctrl+other buttons
#ifndef CTRL
    #define CTRL(c) ((c) & 037)
#endif

#ifndef QUEUE_LIMIT
    #define QUEUE_LIMIT 10000
#endif



int main(int argc, char *argv[]) {
    WINDOW *main_w;
    q_char* queue = NULL;
    q_char* move_queue = NULL;
    int queue_dim = 0;
    int ncols = 0;
    int nlines = 0;
    int x = 0;
    int y = 0;

    int ch = 0;

    //initialize Ncurses
    initscr();
    //get current terminal window max coordinates
    getmaxyx(stdscr, nlines, ncols);
    //print general info
    curs_set(0);
    noecho();
    raw();
    keypad(stdscr, 1);
    nodelay(stdscr, 0);
    wprintw(stdscr, "Current terminal size: y = %d\tx = %d\n", nlines, ncols);
    wprintw(stdscr, "\tUse arrows to move cursor in the screen\n");
    wprintw(stdscr, "\tUse CTRL+S to prompt Save options\n");
    wprintw(stdscr, "\tUse CTRL+L to prompt Load options\n");
    wprintw(stdscr, "\tUse CTRL+Z to undo or CTRL+Y for redo\n");
    wprintw(stdscr, "\tUse CTRL+C to prompt Clear options\n");
    wprintw(stdscr, "\tUse CTRL+Q to Quit \n\n");
    attron(A_BOLD);
    wprintw(stdscr, "Press any button to continue");
    attroff(A_BOLD);
    getch();
    wclear(stdscr);
    curs_set(1);
    //create the main window
    main_w = newwin(nlines, ncols, y, x);
    raw();
    keypad(main_w, 1);
    noecho();
    nodelay(main_w, 0); //1 for more responsive and cpu intensive
    intrflush(main_w, 0);

    //program run forever until user press CTRL+Q
    while(1) {
        //get the user input
        ch = wgetch(main_w);
        //if no input (or nodelay set to 1)
        if(ch == ERR) {
            usleep(25000);
            continue;
        }
        //detect quit command
        if(ch == CTRL('q')) {
            nodelay(main_w, 0);
            wmove(main_w, 0, 0);
            wclear(main_w);
            //ask the user if he/she's sure to quit
            wprintw(main_w, "Are you sure to quit? [Y/n] ");
            ch = wgetch(main_w);
            if(ch == 'Y' || ch == 'y') {
                //free Ncurses window
                delwin(main_w);
                //free undo and redo queue
                freeQ_char(queue);
                //and exit infinite loop
                break;
            }
        }
        //resize the window
        getmaxyx(stdscr, nlines, ncols);
        switch(ch) {
            //Up Arrow
            case KEY_UP:
                if(y-1 >= 0)
                    y--;
                break;
            //Down Arrow
            case KEY_DOWN:
                if(y+1 < nlines)
                    y++;
                break;
            //Left Arrow
            case KEY_LEFT:
                if(x-1 >= 0)
                    x--;
                break;
            //Right Arrow
            case KEY_RIGHT:
                if(x+1 < ncols)
                    x++;
                break;
            //window resize management
            case KEY_RESIZE:
                getmaxyx(main_w, nlines, ncols);
                if(y >= nlines)
                    y = nlines-1;
                if(x >= ncols)
                    y = ncols-1;
                break;
            //TODO add undo e redo buttons (with push and pop)
            case CTRL('z'):
                mvwprintw(main_w, nlines-1, ncols-5, "PREV");
                //clear last input
                mvwprintw(main_w, y, x, " ");
                if(move_queue == NULL)
                    break;
                //move queue pointer to the previous input
                if(move_queue->prev != NULL) {
                    move_queue = move_queue->prev;
                    mvwprintw(main_w, nlines-1, 1, "DEBUG: qdim=%d in=%c qPrev=%c qy=%d qx=%d",
                              queue_dim, ch, move_queue->value, move_queue->y, move_queue->x);
                    //and is inside borders
                    if(move_queue->y < nlines && move_queue->x < ncols) {
                        //print the undo char
                        ch = move_queue->value;
                        y = move_queue->y;
                        x = move_queue->x;
                        wmove(main_w, y, x);
                        mvwprintw(main_w, y, x, "%c", ch);
                    }
                }
                break;
            //redo
            case CTRL('y'):
                mvwprintw(main_w, nlines-1, ncols-5, "NEXT");
                if(move_queue == NULL)
                    break;
                //move queue pointer to the next input
                if(move_queue->next != NULL) {
                    move_queue = move_queue->next;
                    mvwprintw(main_w, nlines-1, 1, "DEBUG: qdim=%d in=%c qNext=%c qy=%d qx=%d",
                              queue_dim, ch, move_queue->value, move_queue->y, move_queue->x);
                    //and is inside borders
                    if(move_queue->y < nlines && move_queue->x < ncols) {
                        //print the redo char
                        ch = move_queue->value;
                        y = move_queue->y;
                        x = move_queue->x;
                        wmove(main_w, y, x);
                        mvwprintw(main_w, y, x, "%c", ch);
                    }
                }
                break;
            //clear option
            case CTRL('C'):
                break;
            //load option
            case CTRL('L'):
                break;
            //save option
            case CTRL('S'):
                break;
            //here ascii art is printed
            default:
                if(ch < 32 || ch > 127)
                    break;
                attron(A_BOLD);
                mvwprintw(main_w, y, x, "%c", ch);
                attroff(A_BOLD);
                //add char into undo queue
                queue = pushQ_char(queue, ch, y, x);
                //start undo and redo
                move_queue = getLastQ_char(queue);
                //respect defined memory limit
                if(queue_dim >= QUEUE_LIMIT)
                    queue = popHeadQ_char(queue);
                else
                    queue_dim++;
                mvwprintw(main_w, nlines-1, 1, "DEBUG: qdim=%d in=%c", queue_dim, ch);
                break;
        }
        //move to the desired position
        wmove(main_w, y, x);
        //update window content
        wrefresh(main_w);
    }

    //stop Ncurses
    endwin();

    return 0;
}
