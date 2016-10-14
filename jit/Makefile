CC=gcc
CCOPTS=-Wall -Wpedantic -Wshadow -fno-strict-aliasing -march=native -flto -std=c11
DEVOPS=-g -O0
PRODOPTS=-Os -O2

TARG=minijit

.PHONY: clean

default: all

all: $(TARG)

minijit: minijit.c
	gcc $(CCOPTS) $(DEVOPS) -o $(TARG) $(TARG).c

release: minijit.c
	gcc $(CCOPTS) $(PRODOPTS) -o $(TARG) $(TARG).c

clean:
	rm $(TARG)
