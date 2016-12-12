CC=gcc
RM=rm
CCOPTS=-Wall -Wpedantic -Wshadow -fno-strict-aliasing -march=native -flto -std=c11 # -Werror
DEVOPS=-g -O0
PRODOPTS=-Os -O2
PROFOPTS=-g -pg

TARG=minijit

.PHONY: clean

default: all

all: $(TARG)

minijit: minijit.c
	$(CC) $(CCOPTS) $(DEVOPS) -o $(TARG) $(TARG).c

prof:
	$(CC) $(CCOPTS) $(PRODOPTS) $(PROFOPTS) -o $(TARG) $(TARG).c

release: minijit.c
	$(CC) $(CCOPTS) $(PRODOPTS) -o $(TARG) $(TARG).c

clean:
	$(RM) $(TARG)
