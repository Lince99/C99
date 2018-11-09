CC=gcc
RM=rm -f

SRC=multi_sort.c
EXC=multi_sort

all: clean compile run

compile:
	$(CC) -o $(EXC) $(SRC)

clean:
	reset
	ls -la --color
	$(RM) $(EXC)

run:
	./$(EXC)
