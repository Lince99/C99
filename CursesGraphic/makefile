CC=gcc
RM=rm -f

SRC=variousCurses.c
EXC=variousCurses

all: compile run

compile:
	$(CC) -o $(EXC) $(SRC) -lncurses

clean:
	reset
	$(RM) $(EXC)

run:
	./$(EXC)
