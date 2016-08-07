CC=gcc
CCOPTS=-Wall -Wextra -Wshadow -Werror -Wpedantic -Wstrict-overflow -std=c11 -fno-strict-aliasing -march=native
BUILDOPTS=-O3 -Os -flto
DEBUGOPTS=-O0 -g
TEST=-DDEV

make:
	$(CC) $(CCOPTS) $(DEBUGOPTS) $(TEST) amplifier.c -o amplifier.o
opt:
	$(CC) $(CCOPTS) $(BUILDOPTS) $(TEST) amplifier.c -o amplifier.o
test:
	@./amplifier.o
