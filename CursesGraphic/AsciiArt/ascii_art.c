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
#include "include/ascii_matrix.h"

unsigned short int TERM_HAS_COLORS = 0;
unsigned short int TAB_COUNT = 4;



int main(int argc, char *argv[]) {
    WINDOW *main_w;
    q_char* queue = NULL;
    q_char* move_queue = NULL;
    int ncols = 0;
    int nlines = 0;
    int x = 0;
    int y = 0;
    //user input var
    int ch = 0;
    int usr_req = 0;
    //char* usr_str = NULL;
    int** matrix = NULL;
    int mat_y = 0;
    int mat_x = 0;

    //initialize Ncurses
    initscr();
    //initialize color pairs
    TERM_HAS_COLORS = init_colors();

    //get current terminal window max coordinates
    getmaxyx(stdscr, nlines, ncols);
    //Minimum terminal size requirement
    if(ncols <= 36 || nlines <= 10) {
        mvwprintw(stdscr, 0, 0, "TOO SMALL!");
        endwin();
        return 2;
    }
    //print general info
    draw_borders(stdscr);
    curs_set(0);
    noecho();
    keypad(stdscr, 1);
    nodelay(stdscr, 0);
    mvwprintw(stdscr, 1, 1, " Use arrows to move the cursor");
    mvwprintw(stdscr, 2, 1, " Use CTRL+S to Save");
    mvwprintw(stdscr, 3, 1, " Use CTRL+L to Load file");
    mvwprintw(stdscr, 4, 1, " Use CTRL+Z to undo");
    mvwprintw(stdscr, 5, 1, " Use CTRL+Y for redo");
    mvwprintw(stdscr, 6, 1, " Use CTRL+C to Clear the screen");
    mvwprintw(stdscr, 7, 1, " Use CTRL+Q to Quit");
    if(TERM_HAS_COLORS)
        mvwprintw(stdscr, 8, 1, "\tUse CTRL+1..8 to use colors");
    attron(A_BOLD);
    mvwprintw(stdscr, 9, 1, "Press any button to continue");
    attroff(A_BOLD);
    getch();
    wclear(stdscr);
    //create the main window
    main_w = newwin(nlines, ncols, y, x);
    raw();
    nonl();
    keypad(main_w, 1);
    nodelay(main_w, 0); //1 for more responsive but cpu intensive
    intrflush(main_w, 0); //1 to inherit from tty drive
    curs_set(1);
    draw_borders(main_w);
    //start cursor position
    y = 1; //(int)nlines/2;
    x = 1; //(int)ncols/2;
    wmove(main_w, y, x);
    //init ascii art matrix
    mat_y = nlines-1;
    mat_x = ncols-1;
    matrix = init_matrix(mat_y, mat_x);
    //error on malloc
    if(matrix == NULL) {
        wattr_on(main_w, COLOR_PAIR(1), NULL);
        mvwprintw(stdscr, 0, 0, "Error on matrix allocation! Exiting");
        wattr_off(main_w, COLOR_PAIR(1), NULL);
        wgetch(main_w);
        endwin();
        return 1;
    }

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
            wclear(main_w);
            draw_borders(main_w);
            //ask the user if he/she's sure to quit
            wattr_on(main_w, A_BOLD, NULL);
            wattr_on(main_w, COLOR_PAIR(1), NULL);
            mvwprintw(main_w, 1, 1, "Are you sure you want to quit? [Y/n]");
            wattr_off(main_w, COLOR_PAIR(1), NULL);
            wattr_off(main_w, A_BOLD, NULL);
            usr_req = wgetch(main_w);
            if(usr_req == 'Y' || usr_req == 'y') {
                //free Ncurses window
                delwin(main_w);
                //free undo and redo queue
                freeQ_char(queue);
                //free ascii matrix
                free(matrix);
                //and exit infinite loop
                break;
            }
            wclear(main_w);
            draw_borders(main_w);
        }
        //resize the window UNCOMMENT THIS IF KEY_RESIZE doesn't work
        //getmaxyx(stdscr, nlines, ncols);
        switch(ch) {
            //return to start coordinates
            case KEY_HOME:
                x = 1;
                y = 1;
                break;
            //Up Arrow
            case KEY_UP:
                if(y-1 >= 1)
                    y--;
                break;
            //Down Arrow or enter
            case KEY_DOWN:
                if(y+1 < nlines-1)
                    y++;
                break;
            //Left Arrow or backspace
            case KEY_LEFT:
                if(x-1 >= 1)
                    x--;
                break;
            //Right Arrow
            case KEY_RIGHT:
                if(x+1 < ncols-1)
                    x++;
                break;
            //tab will do the same as KEY_RIGHT, but for TAB_COUNT times
            case KEY_STAB:
                mvwprintw(main_w, 1, 1, "TAB PRESSED!");
                wgetch(main_w);
                for(int tab_c = 0; tab_c < TAB_COUNT-1; tab_c++) {
                    if(x+1 < ncols-1)
                        x++;
                    else
                        break;
                }
                break;
            //window resize management
            case KEY_RESIZE:
                getmaxyx(main_w, nlines, ncols);
                if(y >= nlines-1)
                    y = nlines-1;
                if(x >= ncols-1)
                    y = ncols-1;
                wclear(main_w);
                draw_borders(main_w);
                //update ascii matrix size (only bigger, not smaller)
                if(nlines-1 > mat_y)
                    matrix = resize_matrix(matrix, &mat_y, &mat_x,
                                                   nlines-1, mat_x);
                if(ncols-1 > mat_x)
                    matrix = resize_matrix(matrix, &mat_y, &mat_x,
                                                   mat_y, ncols-1);
                break;
            //undo
            case CTRL('z'):
                //clear last input
                mvwprintw(main_w, y, x, " ");
                //remove from matrix
                matrix[y-1][x-1] = 0;
                //check if there is a queue
                if(move_queue == NULL)
                    break;
                //move queue pointer to the previous input
                if(move_queue->prev != NULL) {
                    move_queue = move_queue->prev;
                    //and is inside borders
                    if(move_queue->y < nlines-1 && move_queue->x < ncols-1) {
                        //print the undo char
                        ch = move_queue->value;
                        y = move_queue->y;
                        x = move_queue->x;
                        wmove(main_w, y, x);
                        mvwprintw(main_w, y, x, "%c", ch);
                        //update matrix content
                        matrix[y-1][x-1] = ch;
                    }
                }
                break;
            //redo
            case CTRL('y'):
                if(move_queue == NULL)
                    break;
                //move queue pointer to the next input
                if(move_queue->next != NULL) {
                    move_queue = move_queue->next;
                    //and is inside borders
                    if(move_queue->y < nlines-1 && move_queue->x < ncols-1) {
                        //print the redo char
                        ch = move_queue->value;
                        y = move_queue->y;
                        x = move_queue->x;
                        wmove(main_w, y, x);
                        mvwprintw(main_w, y, x, "%c", ch);
                        //update matrix content
                        matrix[y-1][x-1] = ch;
                    }
                }
                break;
            //clear option
            case CTRL('C'):
                wclear(main_w);
                draw_borders(main_w);
                //free undo and redo queue
                mvwprintw(main_w, 1, 1, "Also clear undo queue? [Y/n]");
                wrefresh(main_w);
                usr_req = wgetch(main_w);
                if((usr_req == 'Y' || usr_req == 'y') && queue != NULL) {
                    freeQ_char(queue);
                    move_queue = NULL;
                    queue_dim = 0;
                    mvwprintw(main_w, 2, 1, "Undo queue clear");
                    wrefresh(main_w);
                    wgetch(main_w);
                }
                //remove matrix content
                free(matrix);
                matrix = NULL;
                //and re-init ascii art matrix
                getmaxyx(main_w, nlines, ncols);
                mat_y = nlines-1;
                mat_x = ncols-1;
                matrix = init_matrix(mat_y, mat_x);
                mvwprintw(main_w, 3, 1, "New matrix created");
                wrefresh(main_w);
                wgetch(main_w);
                //update the screen
                wclear(main_w);
                draw_borders(main_w);
                break;
            //TODO READ STRING, LOAD MATRIX FROM FILE
            /*
            //load option
            case CTRL('L'):
                wclear(main_w);
                draw_borders(main_w);
                //request file name from user
                mvwprintw(main_w, 1, 1, "Load filename:\n");
                usr_str = get_input_str(main_w);
                free(matrix);
                matrix = file_to_matrix(usr_str, &mat_y, &mat_x);
                if(matrix != NULL)
                    mvwprintw(main_w, 1, 1, "Ascii art \"%s\" load!", usr_str);
                else {
                    mat_y = nlines-1;
                    mat_x = ncols-1;
                    matrix = init_matrix(mat_y, mat_x);
                }
                wgetch(main_w);
                break;
            //save option
            case CTRL('S'):
                nodelay(main_w, 0);
                wclear(main_w);
                draw_borders(main_w);
                //request file name from user
                mvwprintw(main_w, 1, 1, "Save filename:\n");
                usr_str = get_input_str(main_w);
                free(matrix);
                if(matrix_to_file(matrix, mat_y, mat_x, usr_str))
                    mvwprintw(main_w, 1, 1, "Ascii art saved!");
                else {
                    wattr_on(main_w, COLOR_PAIR(1), NULL);
                    mvwprintw(stdscr, 0, 0, "Error on Ascii art save!");
                    wattr_off(main_w, COLOR_PAIR(1), NULL);
                }
                wgetch(main_w);
                break;
            */
            //here ascii art is printed
            default:
                if(!isAlphaNum(ch))
                    break;
                attron(A_BOLD);
                draw_borders(main_w);
                mvwprintw(main_w, mat_y, mat_x-7, "[%d] %c", (int)ch, ch);
                wrefresh(main_w);
                attroff(A_BOLD);
                /*if(matrix == NULL)
                    matrix = init_matrix(mat_y, mat_x);*/
                //save char into ascii matrix
                matrix[y-1][x-1] = ch;
                //add char into undo queue
                queue = pushQ_char(queue, ch, y, x);
                mvwprintw(main_w, (int)mat_y/2, (int)mat_x/2, "After-push");
                wrefresh(main_w);
                sleep(1);
                //start undo and redo
                if(move_queue == NULL)
                    mvwprintw(main_w, (int)mat_y/2, (int)mat_x/2, "MOVE_QUEUE NULL!");
                else
                    mvwprintw(main_w, (int)mat_y/2, (int)mat_x/2, "move_queue not null!");
                if(queue == NULL)
                    mvwprintw(main_w, (int)(mat_y/2)-1, (int)mat_x/2, "QUEUE NULL!");
                else
                    mvwprintw(main_w, (int)mat_y/2, (int)mat_x/2, "queue not null!");
                wrefresh(main_w);
                sleep(1);
                move_queue = getLastQ_char(queue);
                mvwprintw(main_w, (int)mat_y/2, (int)mat_x/2, "After get last");
                wrefresh(main_w);
                sleep(1);
                //respect defined memory limit
                if(queue_dim >= QUEUE_LIMIT)
                    queue = popHeadQ_char(queue);
                else
                    queue_dim++;
                mvwprintw(main_w, mat_y, 1, "[%d]", queue_dim);
                break;
        }
        print_matrix(main_w, matrix, mat_y, mat_x);
        //move to the desired position
        wmove(main_w, y, x);
        //update window content
        wrefresh(main_w);
    }

    //stop Ncurses
    endwin();

    return 0;
}
