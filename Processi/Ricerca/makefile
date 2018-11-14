CC=gcc
RM=rm -f

SRC=multi_search.c
EXC=multi_search

all: clean compile run

compile:
	$(CC) -o $(EXC) $(SRC)

clean:
	#reset
	#ls -la --color
	$(RM) $(EXC)

run:
	./$(EXC)
