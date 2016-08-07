CC=gcc
CCOPTS=-Wall -Wextra -Wshadow -Werror -Wpedantic -Wstrict-overflow -std=c11 -fno-strict-aliasing -march=native
BUILDOPTS=-O3 -Os -flto
DEBUGOPTS=-DDEV -O0 -g

make:
	$(CC) $(CCOPTS) $(DEBUGOPTS) amplifier.c -o amplifier.o
opt:
	$(CC) $(CCOPTS) $(BUILDOPTS) amplifier.c -o amplifier.o
test:
	@./amplifier.o
