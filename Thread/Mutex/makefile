#Basso Nicola 4^AI

EXC=orderMutex

GCC=gcc -pthread

all: compile run

compile:
	@$(GCC) -o $(EXC) $(EXC).c
	@strip $(EXC)

run:
	@./$(EXC)

clean:
	@clear
	@rm $(EXC)
