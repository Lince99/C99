CC = gcc
RM = rm -f

SRC = multi_auto_search.c
EXC = multi_auto_search
EXP_EXT = .csv

all: compile run

compile:
	$(CC) -o $(EXC) $(SRC)

clean:
	reset
	$(RM) $(EXC)
	$(RM) *$(EXP_EXT)
	#$(RM) exports/*$(EXP_EXT)

run:
	./$(EXC)
