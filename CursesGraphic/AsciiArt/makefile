#Copyright (c) 2019 Lince99 under MIT license

CC=gcc -Wall

# name of the source (include folders if the source isn't in the current dir)
SRC=ascii_art.c
# name of the executable
EXC=ascii_art



all: clean_screen compile run clean

compile:
	@$(CC) -o $(EXC) $(SRC) -lncurses
	@strip $(EXC)

clean:
	@rm $(EXC)

clean_screen:
	@reset && clear

run:
	./$(EXC)
