#Copyright (c) 2019 Lince99 under MIT license

CC=gcc

# name of the source (include folders if the source isn't in the current dir)
SRC=menu_matrix.c
# name of the executable
EXC=menu_matrix



all: compile run

compile:
	@$(CC) -o $(EXC) $(SRC) -lncurses
	@strip $(EXC)

clean_reset:
	@rm -f $(EXC)
	@reset && clear

run:
	@./$(EXC)
