void *syscall5(void* number,
               void *arg1,
               void *arg2,
               void *arg3,
               void *arg4,
               void *arg5
);

typedef unsigned long int uintptr; /* size_t equivalent */
typedef long int intptr; /* ssize_t equivalent */

static intptr write(int fd, void const *data, uintptr nbytes)
{
   return (intptr)syscall5(
         (void*)1, /* WRITE syscall number */
         (void*)(intptr)fd, /* double cast for explicit resize */
         (void*)data,
         (void*)nbytes,
         0, /* ignored */
         0  /* ignored */
   );
}

int main(int argc, char *argv[])
{
   write(1, "hello\n", 6);

   return 0;
}
