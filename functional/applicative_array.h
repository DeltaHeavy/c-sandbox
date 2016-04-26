#define TOKENPASTE(x, y) x ## y

#define APPLICATIVE_ARRAY(T) TOKENPASTE(applicative_array_, T)

void APPLICATIVE_ARRAY(TYPE)(TYPE *arr, int n, TYPE f(TYPE)) {
   int i;
   for (i = 0; i < n; i++) {
      arr[i] = f(arr[i]);
   }
}
