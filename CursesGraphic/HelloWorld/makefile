#Copyright (c) 2019 Lince99 under MIT license

CC=gcc

# name of the source (include folders if the source isn't in the current dir)
SRC=hello_world.c
# name of the executable
EXC=hello_world



all: compile run

compile:
	@$(CC) -o $(EXC) $(SRC) -lncurses
	@strip $(EXC)

clean_reset:
	@rm -f $(EXC)
	@reset && clear

run:
	@./$(EXC)
