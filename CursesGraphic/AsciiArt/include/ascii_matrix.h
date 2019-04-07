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

#ifndef ASCII_MATRIX_H
#define ASCII_MATRIX_H

#include <stdlib.h>

//signatures
int isAlphaNum(int);
int** init_matrix(int, int);
int** resize_matrix_lines(int**, int, int);
int** resize_matrix_cols(int**, int, int);
void print_matrix(WINDOW*, int**, int, int);



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

/*
 * allocate a new matrix
 */
int** init_matrix(int y, int x) {
    int** mat = NULL;
    int i = 0;

    if(y <= 0 || x <= 0)
        return NULL;
    mat = (int**) calloc(y, sizeof(int));
    if(mat == NULL)
        return NULL;
    for(i = 0; i < y; i++) {
        mat[i] = (int*) calloc(x, sizeof(int));
        if(mat[i] == NULL)
            return NULL;
    }

    return mat;
}

/*
 * resize the matrix with new y size
 */
int** resize_matrix_lines(int** mat, int y, int x) {

    if(y <= 0 || x <= 0)
        return NULL;
    if(mat == NULL)
        return init_matrix(y, x);
    mat = (int**) realloc(mat, y*sizeof(int));

    return mat;
}

/*
 * resize the matrix with new x size
 */
int** resize_matrix_cols(int** mat, int y, int x) {
    int i = 0;

    if(y <= 0 || x <= 0)
        return NULL;
    if(mat == NULL)
        return init_matrix(y, x);
    for(i = 0; i < y; i++) {
        mat[i] = (int*) realloc(mat, x*sizeof(int));
        if(mat[i] == NULL)
            return NULL;
    }

    return mat;
}

/*
 * print matrix content inside the "win" ncurses window
 * "border" is how many char has to skip to print content
 */
void print_matrix(WINDOW* win, int** matrix, int mat_y, int mat_x) {
    int y, x;
    int nlines, ncols;

    if(win == NULL)
        return;
    getmaxyx(win, nlines, ncols);
    for(y = 1; y < nlines-1 && y < mat_y; y++) {
        for(x = 1; x < ncols-1 && x < mat_x; x++) {
            if(matrix[y-1][x-1] != 0)
                mvwprintw(win, y, x, "%c", matrix[y-1][x-1]);
            else
                mvwprintw(win, y, x, " ");
        }
    }

}

/*
 * save matrix to filename, return 0 on success, 1 on NULL found, 2 I/O error
 */
int matrix_to_file(int** matrix, int mat_y, int mat_x, char* filename) {
    FILE* fp = NULL;
    int y, x;

    if(matrix == NULL || filename == NULL)
        return 1;
    fp = fopen(filename, "w+");
    if(fp == NULL)
        return 2;
    //print to file matrix content
    for(y = 0; y < mat_y; y++) {
        for(x = 0; x < mat_x; x++) {
            if(matrix[y][x] == 0)
                fprintf(fp, " ");
            else
                fprintf(fp, "%c", matrix[y][x]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    return 0;
}

//-----------------------------------TODO-------------------------------------//
/*
 * return a pointer to the matrix, and mat_y, mat_x via reference
 */
/*int** file_to_matrix(char* filename, int* mat_y, int* mat_x) {
    FILE* fp = NULL;
    int** matrix = NULL;
    int ch = 0;
    int y, x;

    if(filename == NULL) {
        *mat_y = -1;
        *mat_x = -1;
        return NULL;
    }
    fp = fopen(filename, "r");
    if(fp == NULL) {
        *mat_y = -1;
        *mat_x = -1;
        return NULL;
    }
    //read file content
    while((ch = fgetc(fp)) != EOF) {
        if(ch == '\n')
            *mat_y++;
        else
            *mat_x++;
    }

    fclose(fp);

    return matrix;
}*/

#endif //ASCII_MATRIX_H
