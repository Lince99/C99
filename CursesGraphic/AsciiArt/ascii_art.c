/* Copyright (C) 2019  Lince99
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see http://www.gnu.org/licenses .
 */

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/queue_char.h"
#include "include/curses_manager.h"

//signatures
int isAlphaNum(int ch);



int main(int argc, char *argv[]) {
    WINDOW *main_w;
    q_char* queue = NULL;
    q_char* move_queue = NULL;
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
    draw_borders(stdscr);
    curs_set(0);
    noecho();
    raw();
    keypad(stdscr, 1);
    nodelay(stdscr, 0);
    mvwprintw(stdscr, 1, 1, "Current terminal size: y = %d\tx = %d", nlines, ncols);
    mvwprintw(stdscr, 2, 1, "\tUse arrows to move cursor in the screen");
    mvwprintw(stdscr, 3, 1, "\tUse CTRL+S to prompt Save options");
    mvwprintw(stdscr, 4, 1, "\tUse CTRL+L to prompt Load options");
    mvwprintw(stdscr, 5, 1, "\tUse CTRL+Z to undo or CTRL+Y for redo");
    mvwprintw(stdscr, 6, 1, "\tUse CTRL+C to prompt Clear options");
    mvwprintw(stdscr, 7, 1, "\tUse CTRL+Q to Quit");
    attron(A_BOLD);
    mvwprintw(stdscr, 7, 1, "Press any button to continue");
    attroff(A_BOLD);
    getch();
    wclear(stdscr);
    curs_set(1);
    //create the main window
    main_w = newwin(nlines, ncols, y, x);
    raw();
    keypad(main_w, 1);
    noecho();
    nodelay(main_w, 0); //1 for more responsive but cpu intensive
    intrflush(main_w, 0);
    draw_borders(main_w);

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
                wclear(main_w);
                draw_borders(main_w);
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
                if(!isAlphaNum(ch))
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

/*
 * return 1 if it's a printable character, else return 0
 */
int isAlphaNum(int ch) {

    //Ascii table 0-127
    if(ch >= 32 || ch <= 126)
        return 1;
    //extended AScii table 128-255
    if((ch == 128) || (ch >= 130 || ch <= 140) || (ch == 142) ||
       (ch >= 130 || ch <= 140) || (ch >= 130 || ch <= 140) ||
       (ch == 142) || (ch >= 145 || ch <= 156) || (ch == 158) ||
       (ch == 159) || (ch >= 161 || ch <= 172) ||
       (ch >= 174 || ch <= 183) || (ch >= 185 || ch <= 255))
        return 1;

    //non-printable character
    return 0;
}
