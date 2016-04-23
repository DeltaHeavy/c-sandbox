DEVOPTS=-Wall -Werror -Wpedantic -ansi
CCOPTS=-O3

make:
	gcc $(CCOPTS) $(DEVOPTS) vigs.c -o vigs
	gcc $(CCOPTS) $(DEVOPTS) ftable.c -o ftable
test:
	@echo "\n\033[1mRunning" `ls -1 tests/*.sh | wc -l` "test(s)\033[0m"
	@echo "-----------------\n"
	@run-parts --regex=".*sh" tests
	@echo
	@echo "\033[32mBUILD PASSING\033[0m"
	@echo
