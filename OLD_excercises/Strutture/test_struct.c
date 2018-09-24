/*
 * test_struct.c
 * 
 * Copyright 2017 lynx <lynx@lynx-HP-Compaq-6530b-NA407UC-ABZ>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>

int main(int argc, char **argv)
{
	typedef struct aereo {
		int matricola;
		int n_eliche;
		int peso;
		char* nome;
	} Aereo;
	
	typedef struct coso {
		int cade;
	} Trabicolo;
	
	Aereo boeing;
	Trabicolo sad;
	sad.cade = 1;
	boeing.matricola = 0;
	boeing.nome = "aereo";
	printf("Matricola= %d, nome = %s\n", boeing.matricola, boeing.nome);
	if (sad.cade == 1)
		printf("Il triste caditore...\n");
	else
		printf("wtf cadi\n");
	return 0;
}

