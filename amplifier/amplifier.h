/* harness
 *
 * Arguments
 *
 * void *func:
 * pointer to function which will be parallelized
 * needs to take the following arguments:
 *    unsigned int id (identifies the process, 0 through numProcs-1)
 *    int argc
 *    char **argv
 *    int fd (file descriptor to write `retSize` bytes to, effectively the return value)
 *
 * size_t retSize:
 * size in bytes of "return" value which will be written to the file descriptor
 *
 * unsigned int timeout:
 * timeout in seconds after which SIGALARM will terminate the child
 *
 * int argc:
 * char **argv:
 * argc+argv will be handed to each child, optional way to hand them additional data
 *
 * unsigned int numProcs:
 * number of children to spawn
 *
 * void *sink:
 * pointer to function which will clean up/free/handle the output
 * from all the instances of func
 * needs to take the following arguments:
 *    char **buf (pointer to `retSize*numProcs` bytes of heap space)
 *    size_t retSize (return value size in bytes)
 *    unsigned int numProcs (number of children spawned)
 *
 */

#ifndef __AMP_H
#define __AMP_H

void ProcHarness(void (*func)(unsigned int, int, char **, int), size_t retSize, unsigned int timeout, int argc, char** argv, unsigned int numProcs, void (*sink)(char**, size_t, unsigned int));

#endif
