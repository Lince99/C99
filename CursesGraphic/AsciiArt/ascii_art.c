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
    char* usr_str = NULL;
    int** matrix = NULL;
    int mat_y = 0;
    int mat_x = 0;

    //initialize Ncurses
    initscr();
    //get current terminal window max coordinates
    getmaxyx(stdscr, nlines, ncols);
    //TODO add minimum terminal size requirement

    //print general info
    draw_borders(stdscr);
    curs_set(0);
    noecho();
    raw();
    keypad(stdscr, 1);
    nodelay(stdscr, 0);
    mvwprintw(stdscr, 1, 1, "\tUse arrows to move cursor in the screen");
    mvwprintw(stdscr, 2, 1, "\tUse CTRL+S to prompt Save options");
    mvwprintw(stdscr, 3, 1, "\tUse CTRL+L to prompt Load options");
    mvwprintw(stdscr, 4, 1, "\tUse CTRL+Z to undo or CTRL+Y for redo");
    mvwprintw(stdscr, 5, 1, "\tUse CTRL+C to prompt Clear options");
    mvwprintw(stdscr, 6, 1, "\tUse CTRL+Q to Quit");
    attron(A_BOLD);
    mvwprintw(stdscr, 8, 1, "Press any button to continue");
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
    intrflush(main_w, 0); //1 to inherit from tty driver
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
        attron(COLOR_RED);
        mvwprintw(stdscr, 0, 0, "Error on matrix allocation! Exiting...");
        attroff(COLOR_RED);
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
            mvwprintw(main_w, 1, 1, "Are you sure to quit? [Y/n]");
            ch = wgetch(main_w);
            if(ch == 'Y' || ch == 'y') {
                //free Ncurses window
                delwin(main_w);
                //free undo and redo queue
                freeQ_char(queue);
                //free ascii matrix
                if(matrix != NULL)
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
            //Up Arrow
            case KEY_UP:
                if(y-1 >= 1)
                    y--;
                break;
            //Down Arrow
            case KEY_DOWN:
                if(y+1 < nlines-1)
                    y++;
                break;
            //Left Arrow
            case KEY_LEFT:
                if(x-1 >= 1)
                    x--;
                break;
            //Right Arrow
            case KEY_RIGHT:
                if(x+1 < ncols-1)
                    x++;
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
                if(nlines-1 > mat_y) {
                    mat_y = nlines-1;
                    matrix = resize_matrix_lines(matrix, mat_y, mat_x);
                }
                if(ncols-1 > mat_x) {
                    mat_x = ncols-1;
                    matrix = resize_matrix_cols(matrix, mat_y, mat_x);
                }
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
                mvwprintw(main_w, 1, 1, "Clear undo/redo queue? [Y/n]");
                ch = wgetch(main_w);
                if(ch == 'Y' || ch == 'y') {
                    freeQ_char(queue);
                    move_queue = NULL;
                    //remove matrix content
                    if(matrix != NULL)
                        free(matrix);
                    //and re-init ascii art matrix
                    mat_y = nlines-1;
                    mat_x = ncols-1;
                    matrix = init_matrix(mat_y, mat_x);
                }
                wclear(main_w);
                draw_borders(main_w);
                break;
            //load option
            case CTRL('L'):
                nodelay(main_w, 0);
                wclear(main_w);
                draw_borders(main_w);
                //request file name from user
                mvwprintw(main_w, 1, 1, "Enter the filename:");
                /*curs_set(1);
                echo();
                mvwgetnstr(main_w, 2, 1, usr_str, 64);
                noecho();
                curs_set(0);*/
                break;
            //save option
            case CTRL('S'):
                nodelay(main_w, 0);
                wclear(main_w);
                draw_borders(main_w);
                //request file name from user
                mvwprintw(main_w, 1, 1, "Enter the filename:");
                /*curs_set(1);
                echo();
                mvwgetnstr(main_w, 2, 1, usr_str, 64);
                noecho();
                curs_set(0);*/
                mvwprintw(main_w, 1, 1, "Ascii art saved!");
                break;
            //here ascii art is printed
            default:
                if(!isAlphaNum(ch))
                    break;
                //attron(A_BOLD);
                //mvwprintw(main_w, y, x, "%c", ch);
                //attroff(A_BOLD);
                //save char into ascii matrix
                matrix[y-1][x-1] = ch;
                //add char into undo queue
                queue = pushQ_char(queue, ch, y, x);
                //start undo and redo
                move_queue = getLastQ_char(queue);
                //respect defined memory limit
                if(queue_dim >= QUEUE_LIMIT)
                    queue = popHeadQ_char(queue);
                else
                    queue_dim++;
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
