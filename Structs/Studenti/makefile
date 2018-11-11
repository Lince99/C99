CC=gcc
RM=rm -f

SRC=studenti.c
EXC=studenti

all: clean compile run

compile:
	$(CC) -o $(EXC) $(SRC)

clean:
	#reset
	#ls -la --color
	$(RM) $(EXC)

run:
	./$(EXC)
