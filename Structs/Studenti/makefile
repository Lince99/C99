#Basso Nicola
#4^AI
#sono disponibili: all, compile, clean, run

CC=gcc
RM=rm -f

SRC=studenti.c
EXC=studenti

all: compile run

compile:
	$(CC) -o $(EXC) $(SRC)
	strip $(EXC)

clean:
	#reset
	$(RM) $(EXC)
	$(RM) *.txt

run:
	./$(EXC)
