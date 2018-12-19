CC = gcc
RM = rm -f

SRC = test_pipe.c
EXC = test_pipe

all: compile run

compile:
	$(CC) -o $(EXC) $(SRC)

clean:
	reset
	$(RM) $(EXC)

run:
	./$(EXC)
