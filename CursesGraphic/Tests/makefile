#Copyright (c) 2019 Lince99 under MIT license

CC=gcc
RM=rm -f

# name of the source (include folders if the source isn't in the current dir)
SRC=pong_game.c
# name of the executable
EXC=pong_game
# params used in the program
PARAMS=
# compile params like optimization or other platform targeting
C_PAR=-Os -Wall -fdiagnostics-color=auto

# - - - infoes - - -
C_INFO=-fdiagnostics-color=auto
#-ftime-report
#-fopt-info
#-fdump-statistics -fstack-usage ( -fstats for C++)
#-aux-info signatures.txt
#-fdiagnostics-color=auto
#-fdiagnostics-parseable-fixits -fdiagnostics-generate-patch

# - - - optimizations - - -
C_OPT=-faggressive-loop-optimizations -fcombine-stack-adjustments
C_OPT+= -fexpensive-optimizations -falign-functions -falign-jumps
C_OPT+= -falign-labels -falign-loops -floop-nest-optimize -floop-nest-optimize
C_OPT+= -foptimize-strlen -ftree-loop-optimize -fpredictive-commoning

# - - - folding optimizations - - -
C_FOLD_OPT=-fipa-icf -fipa-icf-functions -fipa-icf-variables -fipa-reference
C_FOLD_OPT+= -fipa-pta -foptimize-sibling-calls -freorder-blocks
C_FOLD_OPT+= -freorder-functions



all: clean_reset compile run

all_opt: clean_reset compile_optimize run_less

help:
	@echo "\nUse make [option]:\n"
	@echo "help \n\tshow this help"
	@echo "compile \n\tcompile from the source and strip it"
	@echo "compile_info \n\tcompile and show compilation/linking stuffs"
	@echo "compile_optimize \n\tcompile and try to use built-in optimizers"
	@echo "cron_time \n\tcompile and exec with timing for stats"
	@echo "clean \n\tremove executable"
	@echo "clean_reset \n\tremove executable AND clear the terminal"
	@echo "run \n\texecute the program"
	@echo "rul_less \n\texecute the program under less for more readability"

compile:
	@$(CC) -o $(EXC) $(SRC) -lncurses
	@strip $(EXC)

compile_info:
	@$(CC) -o $(EXC) $(SRC) $(C_PAR) $(C_INFO) -lncurses
	@strip $(EXC)

compile_optimize:
	@$(CC) -o $(EXC) $(SRC) $(C_PAR) $(C_OPT) $(C_FOLD_OPT) -lncurses
	@strip $(EXC)

cron_time:
	@time -p $(CC) -o $(EXC) $(SRC) $(C_PAR)
	@time -p ./$(EXC)

clean:
	@$(RM) $(EXC)

clean_reset:
	@$(RM) $(EXC)
	@reset && clear

run:
	@./$(EXC) $(PARAMS)

run_less:
	@./$(EXC) $(PARAMS) | less -Cqrs
