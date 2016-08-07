CC=gcc
CCOPTS=-Wall -Wextra -Wshadow -Werror -Wpedantic -Wstrict-overflow -std=c11 -fno-strict-aliasing -march=native
BUILDOPTS=-O3 -Os -flto
DBGOPTS=-O0 -g

make:
	$(CC) $(CCOPTS) $(DBGOPTS) -lm applicative_array.c -o test_map
prod:
	$(CC) $(CCOPTS) $(BUILDOPTS) -lm applicative_array.c -o test_map
test:
	@./test_map
show:
	gcc -E applicative_array.c
clean:
	rm test_map
