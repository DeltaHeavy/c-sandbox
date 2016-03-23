#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

/* A parallelizable function matches the following specifications
 * Arguments
 * int id (used as an indentifier)
 * int argc (used as argument count)
 * char **argv (argument vector)
 * int fd (fd to write output to)
 *
 * It can have any side effects
 * It will be terminated by alarm at some timeout set by the parent
 * 
 * It is only expected to write retSize bytes to file descriptor fd
 * so you can run it on any normal function as long as you
 * write(fout, &foo, retSize) somewhere in there
 *
 * The idea is you write a function (e.g. test, below)
 * which follows the above specification,
 * and a call to harness like
 * harness(func, retSize, timeout, argc, argv, numProcs, sink)
 *
 * e.g. harness(test, sizeof(int), 1, 0, NULL, 8, sink);
 *
 * where func is the function name, retSize is the size in bytes of the output,
 * timeout is the timeout in seconds for each process,
 * argc and argv can be used to pass through arguments,
 * numProcs which tells the harness how many children to spawn
 * and sink (e.g. print or sum below), which takes a pointer to the heap memory allocated by harness
 * intended to do any cleanup or resolution of the data
 * sink is responsible for freeing the memory, although this can be left for the caller
 *
 * Given all these conditions,
 * harness will automagically run numProcs processes,
 * all running the function func with optional copies of argc+argv
 * gather up their output, and handle it nicely via its sink
 *
 * if you want to access that data, retrieve it from sink
 * Other methods will likely lead to use-after-free
 *
 */

#ifdef DEBUG
void test(unsigned int id, int argc, char **argv, int fd) {
   int buf = id;

   switch (id) {
      case 0:
         break;
      case 1:
         printf("\033[31m");
         break;
      case 2:
         printf("\033[32m");
         break;
      case 3:
         printf("\033[33m");
         break;
      case 4:
         printf("\033[34m");
         break;
      case 5:
         printf("\033[35m");
         break;
      case 6:
         printf("\033[36m");
         break;
      case 7:
         printf("\033[37m");
         break;
   }
   printf("EXAMPLE\033[0m\n");
   write(fd, &buf, sizeof(int));
}

void print(char **buf, size_t retSize, unsigned int numProcs) {
   int i;
   for (i = 0; i < numProcs; i++)
      printf("%d\n", (*buf)[i*retSize]);
   
   free(*buf);
   *buf = NULL;
}

void sum(char **buf, size_t retSize, unsigned int numProcs) {
   int i, j = 0;
   for (i = 0; i < numProcs; i++)
      j += (int) (*buf)[i*retSize];
   
   printf("Total: %d\n", j);
   free(*buf);
   *buf = NULL;
}
#endif

void harness(void *func, size_t retSize, unsigned int timeout, int argc, char **argv, unsigned int numProcs, void *sink) {
   unsigned int i;
   char *buf = calloc(retSize, numProcs);
   int *retTable = calloc(sizeof(int), numProcs);
   pid_t *pidTable = calloc(sizeof(pid_t), numProcs);
   int fds[2];

   pipe(fds);

   for (i = 0; i < numProcs; i++) {
      if (fork() == 0) {
         close(*fds);
         alarm(timeout);
         ((void (*)(unsigned int,int,char**,int))func)(i,argc,argv,fds[1]);
         alarm(0);
         read(*fds, buf + (i*retSize), retSize);
         close(fds[1]);
         exit(0);
      }
   }

   close(fds[1]);
   
   for (i = 0; i < numProcs; i++) {
      if (read(*fds, buf + (i*retSize), retSize) == -1)
         perror(strerror(errno));
   }

   close(*fds);

   for (i = 0; i < numProcs; i++) {
      pidTable[i] = wait(retTable + i);  
   }

   for (i = 0; i < numProcs; i++) {
      if (WIFEXITED(retTable[i]) && WEXITSTATUS(retTable[i]) != 0)
         printf("Process %d failed\n", pidTable[i]);
   }
   ((void (*)(char**,size_t,unsigned int))sink)(&buf, retSize, numProcs);
}

#ifdef DEBUG
int main(int argc, char **argv) {
   printf("Example 1, all return id, sink = print:\n");
   harness(test, sizeof(int), 10, argc, argv, 8, print);
   printf("\nExample 2, all return id, sink = sum:\n");
   harness(test, sizeof(int), 10, argc, argv, 8, sum);

   return 0;
}
#else
int main() {
   return 0;
}
#endif
