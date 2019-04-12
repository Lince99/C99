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

int main() {
    int ch;

    /* Curses Initialisations */
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    printw("Welcome - Press # to Exit\n");

    while((ch = getch()) != '#') {
        switch(ch) {
            case KEY_UP:
                printw("\nUp Arrow");
                break;
            case KEY_DOWN:
                printw("\nDown Arrow");
                break;
            case KEY_LEFT:
                printw("\nLeft Arrow");
                break;
            case KEY_RIGHT:
                printw("\nRight Arrow");
                break;
            default:
                printw("\nThe pressed key is ");
                attron(A_BOLD);
                printw("%c", ch);
                attroff(A_BOLD);
                break;
        }
    }

    printw("\n\nBye Now!\n");

    refresh();
    getch();
    endwin();

    return 0;
}
