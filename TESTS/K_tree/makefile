#Basso Nicola
#aka Lince99

CC=gcc
RM=rm -f

#name of the source (include folders if the source isn't in the current dir)
SRC=ktree.c
#add user params after the name of the executable
EXC=ktree
#compile params like optimization or other platform targeting
PAR=-O2 -Wall

all: clean compile run

help:
	@echo "\nUse make [option]:\n"
	@echo "help \n\tshow this help"
	@echo "compile \n\tcompile from the source and strip it"
	@echo "clean \n\tremove the executable file and reset the terminal"
	@echo "run \n\trun the program (if already compiled) with | less\n"

compile:
	@$(CC) -o $(EXC) $(SRC) $(PAR)
	@strip $(EXC)

clean:
	@$(RM) $(EXC)
	@reset && clear

run:
	@./$(EXC)

run_less:
	@./$(EXC) | less -r -q -s -C
