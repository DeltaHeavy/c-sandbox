CCOPTS=-Wall -Werror -Wpedantic -std=c11 -Wshadow -fno-strict-aliasing -Wstrict-overflow -march=native
DEVOPTS=-g -O0
PRODOPTS=-O3 -Os
STANDALONE=-DSTANDALONE

make:
	gcc $(CCOPTS) $(DEVOPTS) $(STANDALONE) vigs.c -o vigs
	gcc $(CCOPTS) $(DEVOPTS) $(STANDALONE) -lm ftable.c -o ftable
prod:
	gcc $(CCOPTS) $(PRODOPTS) $(STANDALONE) vigs.c -o vigs
	gcc $(CCOPTS) $(PRODOPTS) $(STANDALONE) -lm ftable.c -o ftable
test:
	@echo "\n\033[1mRunning" `ls -1 tests/*.sh | wc -l` "test(s)\033[0m"
	@echo "-----------------\n"
	@run-parts --regex=".*sh" tests
	@echo
	@echo "\033[32mBUILD PASSING\033[0m"
	@echo
