#Copyright (c) 2019 Lince99 under MIT license

CC=gcc

# name of the source (include folders if the source isn't in the current dir)
SRC=input_test.c
# name of the executable
EXC=input_test



all: clean_reset compile run

compile:
	@$(CC) -o $(EXC) $(SRC) -lncurses
	@strip $(EXC)

clean_reset:
	@rm -f $(EXC)
	@reset && clear

run:
	@./$(EXC)
