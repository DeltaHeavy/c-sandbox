#include <stdio.h>
#include <stdlib.h>

void applicative_array_int(int *arr, int n, int f(int)) {
   int i;
   for (i = 0; i < n; i++) {
      arr[i] = f(arr[i]);
   }
}

int dbl(int a) {
   return a * 2;
}

int main() {
   int i;
   int *test;

   test = calloc(8, sizeof(int));
   for (i = 0; i < 8; i++)
      test[i] = i+1;

   for (i = 0; i < 8; i++)
      printf("%d\n", test[i]);

   applicative_array_int(test, 8, dbl);
   printf("\n");

   for (i = 0; i < 8; i++)
      printf("%d\n", test[i]);
   return 0;
}
