#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "amplifier.h"

/*
 * A parallelized function is only expected to write retSize
 * bytes to file descriptor fd
 *
 * so you can run it on any normal
 * function as long as you
 * write(fout, &foo, retSize) somewhere in there
 * if it returns, harness will throw the return value on the ground
 *
 * The idea is you write a function (e.g. test, below)
 * which follows the above specification,
 * and a call to harness like
 * harness(func, retSize, timeout, argc, argv, numProcs, sink)
 *
 * e.g. harness(test, sizeof(int), 1, 0, NULL, 8, sink);
 *
 * harness will automagically run numProcs processes,
 * all running the function func with optional copies of argc+argv
 * gather up their output, and handle it nicely via its sink
 *
 * if you want to access that data, retrieve it from sink
 * Other methods will likely lead to use-after-free
 *
 */

#ifdef DEV
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

void email(unsigned int id, int argc, char **argv, int fd) {
   execlp("echo", "echo", "exec mailx", NULL);
}

/* Returns int just as an example that it can */
int print(char **buf, size_t retSize, unsigned int numProcs) {
   int i;
   for (i = 0; i < numProcs; i++)
      printf("%d\n", (*buf)[i*retSize]);
   
   free(*buf);
   *buf = NULL;
   return 0;
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
   char *buf;
   int *retTable = NULL; 
   pid_t *pidTable;
   int fds[2];

   if (numProcs) {
      retTable = calloc(sizeof(int), numProcs);
      pidTable = calloc(sizeof(pid_t), numProcs);
   }
   else
      return;

   if (retSize && numProcs) {
      buf = calloc(retSize, numProcs);
   }

   pipe(fds);

   for (i = 0; i < numProcs; i++) {
      if (fork() == 0) {
         close(*fds);
         alarm(timeout);
         ((void (*)(unsigned int,int,char**,int))func)(i,argc,argv,fds[1]);
         alarm(0);
         if (retSize)
            read(*fds, buf + (i*retSize), retSize);
         close(fds[1]);
         exit(0);
      }
   }

   close(fds[1]);
   
   if (retSize)
      for (i = 0; i < numProcs; i++)
         if (read(*fds, buf + (i*retSize), retSize) == -1)
            perror(strerror(errno));

   close(*fds);

   for (i = 0; i < numProcs; i++)
      pidTable[i] = wait(retTable + i);  

   for (i = 0; i < numProcs; i++)
      if (WIFEXITED(retTable[i]) && WEXITSTATUS(retTable[i]) != 0)
         printf("Process %d failed\n", pidTable[i]);

   if (sink)
      ((void (*)(char**,size_t,unsigned int))sink)(&buf, retSize, numProcs);
}

#ifdef DEV
int main(int argc, char **argv) {
   printf("Example 1, all return id, sink = print:\n");
   harness(test, sizeof(int), 10, argc, argv, 8, print);
   printf("\nExample 2, all return id, sink = sum:\n");
   harness(test, sizeof(int), 10, argc, argv, 8, sum);
   printf("\nExample 3, none return (all procs exec), sink = NULL:\n");
   harness(email, 0, 10, 0, NULL, 8, NULL);

   return 0;
}
#else
int main() {
   return 0;
}
#endif
