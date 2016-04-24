#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#define OFFSET 'A'
#define ALPHABET_SIZE 26

#if STANDALONE
void usage() {
   printf("Usage: vigs [ -v ] [ -d ] key [ infile [ outfile ] ]");
}
#endif

int mod(int a, int b) {
   int r = a % b;
   return r < 0 ? r + b : r;
}

int vigs(char **argv) {

   int verbose = 0, decrypt = 0;
   int infd = 0, outfd = 0;
   int keylen = 0, i = 0;
   unsigned char x, c;
   char *key = NULL, *infile = NULL, *outfile = NULL;

   while (*++argv) {
      if (!strcmp(*argv, "-v")) {
         verbose = 1;
      }
      else if (!strcmp(*argv, "-d")) {
         decrypt = 1;
      }
      else if (!key) {
         key = *argv;
      }
      else if (!infile) {
         infile = *argv;
      }
      else if (!outfile) {
         outfile = *argv;
      }
      else {
#if STANDALONE
         usage();
#endif
         return 1;
      }
   }

   if (!key) {
#if STANDALONE
      fprintf(stderr, "No key specified\n");
      usage();
#endif
      return 1;
   }

   while (key[keylen]) {
      if (!isalpha(key[keylen])) {
#if STANDALONE
         fprintf(stderr, "Key must be alphabetic\n");
         usage();
#endif
         return 1;
      }
      key[keylen] = toupper(key[keylen]);
      key[keylen] = key[keylen] - OFFSET;
      keylen++;
   }

   if (verbose) {
      printf("V: %d\n", verbose);
      printf("D: %d\n", decrypt);
      if (infile)
         printf("I: %s\n", infile);
      if (outfile)
         printf("O: %s\n", outfile);
   }

   if (infile) {
      infd = open(infile, O_RDONLY);
      if (infd == -1) {
#if STANDALONE
         fprintf(stderr, "Error reading from file %s\n", infile);
         usage();
#endif
         return 1;
      }
      dup2(infd, 0);
   }

   if (outfile) {
      outfd = open(outfile, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
      if (outfd == -1) {
#if STANDALONE
         fprintf(stderr, "Error writing to file %s\n", outfile);
         usage();
#endif
         return 1;
      }
      dup2(outfd, 1);
   }

   for (i = 0; scanf("%c", &c) != EOF;) {
      if (isalpha(c)) {
         x = key[i++ % keylen];
         c = toupper(c);
         c -= OFFSET;
         if (decrypt)
            c = mod((c - x), ALPHABET_SIZE);
         else
            c = mod((c + x), ALPHABET_SIZE);
         c += OFFSET;
      }
      putchar(c);
   }

   if (infile)
      close(infd);
   
   if (outfile)
      close(outfd);

   return 0;
}

#if STANDALONE
int main(int argc, char **argv) {
   return vigs(argv);
}
#endif
