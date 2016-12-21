#include "syscalls.h"

typedef unsigned long int uintptr; /* size_t equivalent */
typedef long int intptr; /* ssize_t equivalent */

#define internal static /* makes finding static functions easier,
                           rather than static variables */

void *syscall3(uintptr number,
               void *arg1,
               void *arg2,
               void *arg3
);

#define stdout 1

internal intptr write(int fd, void const *data, uintptr nbytes)
{
   return (intptr)syscall3(
         SYS_write, /* WRITE syscall number */
         (void*)(intptr)fd, /* double cast for explicit resize */
         (void*)data,
         (void*)nbytes
   );
}

internal uintptr strlen(char const *str)
{
   char const *p;
   for (p = str; *p; ++p);
   return p - str;
}

internal uintptr puts(char const *str)
{
   return write(stdout, str, strlen(str));
}

int main(int argc, char *argv[])
{
   puts("hello\n");
   return 0;
}
