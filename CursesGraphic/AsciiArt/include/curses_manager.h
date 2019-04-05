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

#ifndef CURSES_MANAGER_H
#define CURSES_MANAGER_H

#include <curses.h>

//manage Ctrl+other buttons
#ifndef CTRL
    #define CTRL(c) ((c) & 037)
#endif

//signatures
void draw_borders(WINDOW *screen);



void draw_borders(WINDOW *screen) {
    int x = 0;
    int y = 0;
    int i = 0;

    getmaxyx(screen, y, x);
    //check color
    if(!has_colors()) {
        mvwprintw(screen, (int)y/2, (int)x/2, "NO COLOR SUPPORT!");
    }
    else {
        //https://www.linuxjournal.com/content/programming-color-ncurses
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        attron(COLOR_PAIR(1));
    }
    //http://melvilletheatre.com/articles/ncurses-extended-characters/index.html
    //corners
    mvwaddch(screen, 0, 0, ACS_ULCORNER);
    mvwaddch(screen, y-1, 0, ACS_LLCORNER);
    mvwaddch(screen, 0, x-1, ACS_URCORNER);
    mvwaddch(screen, y-1, x-1, ACS_LRCORNER);
    //left and right
    for (i = 1; i < (y-1); i++) {
        mvwaddch(screen, i, 0, ACS_VLINE);
        mvwaddch(screen, i, x-1, ACS_VLINE);
    }
    //top and bottom
    for (i = 1; i < (x-1); i++) {
        mvwaddch(screen, 0, i, ACS_HLINE);
        mvwaddch(screen, y-1, i, ACS_HLINE);
    }
    attroff(COLOR_PAIR(1));

}

#endif //CURSES_MANAGER_H
