CC=gcc
OPTS=-Wall -Werror --std=c11
BUILDOPTS=-O3
DEBUGOPTS=-DDEV -g

make:
	$(CC) $(OPTS) $(DEBUGOPTS) amplifier.c -o amplifier.o
opt:
	$(CC) $(OPTS) $(BUILDOPTS) amplifier.c -o amplifier.o
test:
	@./amplifier.o
