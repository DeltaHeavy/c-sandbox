#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#define OFFSET 'A'
#define ENCRYPT 0
#define DECRYPT 1
#define ALPHABET_SIZE 26

void usage() {
   printf("Usage: vigs [ -v ] [ -d ] key [ infile [ outfile ] ]");
}

int mod(int a, int b)
{
   int r = a % b;
   return r < 0 ? r + b : r;
}

int main(int argc, char **argv) {

   int verbose = 0, mode = ENCRYPT;
   int infd = 0, outfd = 0;
   int keylen = 0, i = 0;
   unsigned char x, c;
   char *key = NULL, *infile = NULL, *outfile = NULL;

   while (*++argv) {
      if (!strcmp(*argv, "-v")) {
         verbose = 1;
      }
      else if (!strcmp(*argv, "-d")) {
         mode = DECRYPT;
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
         usage();
         return 1;
      }
   }

   if (!key) {
      fprintf(stderr, "No key specified\n");
      usage();
      return 1;
   }

   while (key[keylen]) {
      if (!isalpha(key[keylen])) {
         fprintf(stderr, "Key must be alphabetic\n");
         usage();
         return 1;
      }
      key[keylen] = toupper(key[keylen]);
      key[keylen] = key[keylen] - OFFSET;
      keylen++;
   }

   if (verbose) {
      printf("V: %d\n", verbose);
      printf("D: %d\n", mode);
      if (infile)
         printf("I: %s\n", infile);
      if (outfile)
         printf("O: %s\n", outfile);
   }

   if (infile) {
      infd = open(infile, O_RDONLY);
      if (infd == -1) {
         fprintf(stderr, "Error reading from file %s\n", infile);
         usage();
         return 1;
      }
      dup2(infd, 0);
   }

   if (outfile) {
      outfd = open(outfile, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
      if (outfd == -1) {
         fprintf(stderr, "Error writing to file %s\n", outfile);
         usage();
         return 1;
      }
      dup2(outfd, 1);
   }

   for (i = 0; scanf("%c", &c) != EOF;) {
      if (isalpha(c)) {
         x = key[i++ % keylen];
         c = toupper(c);
         c -= OFFSET;
         if (mode)
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
