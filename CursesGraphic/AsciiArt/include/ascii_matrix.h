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
int isAlphaNum(int ch);
int** init_matrix(int y, int x);
int** resize_matrix(int** mat, int y, int x);



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
 * resize the matrix with new y and x (doesn't care about same size)
 */
int** resize_matrix(int** mat, int y, int x) {
    int i = 0;

    if(y <= 0 || x <= 0)
        return NULL;
    if(mat == NULL)
        return init_matrix(y, x);
    mat = (int**) realloc(mat, y*sizeof(int));
    if(mat == NULL)
        return NULL;
    for(i = 0; i < y; i++) {
        mat[i] = (int*) realloc(mat, x*sizeof(int));
        if(mat[i] == NULL)
            return NULL;
    }

    return mat;
}

#endif //ASCII_MATRIX_H
