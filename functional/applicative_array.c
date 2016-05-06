#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 8

typedef long double long_double;
typedef long long long_long;

#define TYPE char
#include "applicative_array.h"
#undef TYPE

#define TYPE short
#include "applicative_array.h"
#undef TYPE

#define TYPE int
#include "applicative_array.h"
#undef TYPE

#define TYPE float
#include "applicative_array.h"
#undef TYPE

#define TYPE double
#include "applicative_array.h"
#undef TYPE

#define TYPE long
#include "applicative_array.h"
#undef TYPE

#define TYPE long_double
#include "applicative_array.h"
#undef TYPE

#define TYPE long_long
#include "applicative_array.h"
#undef TYPE

#define TYPE size_t
#include "applicative_array.h"
#undef TYPE

#define TYPE ptrdiff_t
#include "applicative_array.h"
#undef TYPE

int dbl(int a) {
   return 2*a;
}

double e(double r) {
   return exp(r);
}

int main() {
   int i, *test;
   double *foo;
   test = calloc(SIZE, sizeof(int));
   fprintf(stderr, "Array of ints 1 to 8, function dbl\n");
   for (i = 0; i < SIZE; i++) {
      test[i] = i+1;
      printf("%4d ", test[i]);
   }
   printf("\n");

   applicative_array_int(test, SIZE, dbl);
   
   for (i = 0; i < SIZE; i++) {
      printf("%4d ", test[i]);
   }
   printf("\n");
   free(test);
   
   printf("\n");
   fprintf(stderr, "Array of doubles 0.00 to 7.00, function exp\n");
   foo = calloc(SIZE, sizeof(double));
   for (i = 0; i < SIZE; i++) {
      foo[i] = i;
      printf("%10.4f ", foo[i]);
   }
   printf("\n");

   applicative_array_double(foo, SIZE, e);
   
   for (i = 0; i < SIZE; i++) {
      printf("%10.4f ", foo[i]);
   }
   printf("\n");
   free(foo);
   return 0;
}
