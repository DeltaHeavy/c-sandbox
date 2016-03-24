CC=gcc
OPTS=-Wall -Werror --std=c11
BUILDOPTS=-O3
DEBUGOPTS=-DDEV -g

make:
	$(CC) $(OPTS) $(DEBUGOPTS) amplifier.c -o Amplifier.o
opt:
	$(CC) $(OPTS) $(BUILDOPTS) amplifier.c -o Amplifier.o
test:
	@./Amplifier.o
