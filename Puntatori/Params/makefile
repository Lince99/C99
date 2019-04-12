CC=gcc
RM=rm -f

SRC=params_manage.c
EXC=params_manage

all: compile run

compile:
	$(CC) -o $(EXC) $(SRC)

clean:
	reset
	$(RM) $(EXC)

run:
	./$(EXC)
