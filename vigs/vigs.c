#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#define UPPER_OFFSET 'A'
#define LOWER_OFFSET 'a'
#define ENCRYPT 0
#define DECRYPT 1

void usage() {
   printf("Usage: vigs [ -v ] [ -d ] key [ infile [ outfile ] ]");
}

int process_args(char **argv, int *verbose, int *mode, char **key, char **infile, char **outfile) {
   while (*++argv) {
      if (!strcmp(*argv, "-v")) {
         *verbose = 1;
      }
      else if (!strcmp(*argv, "-d")) {
         *mode = DECRYPT;
      }
      else if (!*key) {
         *key = *argv;
      }
      else if (!*infile) {
         *infile = *argv;
      }
      else if (!*outfile) {
         *outfile = *argv;
      }
      else {
         return 1;
      }
   }
   return 0;
}

int main(int argc, char **argv) {

   int verbose = 0, mode = ENCRYPT;
   int infd = 0, outfd = 0;
   int keylen = 0, i = 0;
   char x, c, *key = NULL, *infile = NULL, *outfile = NULL;

   if (process_args(argv, &verbose, &mode, &key, &infile, &outfile)) {
      usage();
      return 1;
   }

   if (!key) {
      fprintf(stderr, "No key specified\n");
      return 1;
   }

   while (key[keylen]) {
      if (!isalpha(key[keylen++])) {
         fprintf(stderr, "Key must be alphabetic\n");
         return 1;
      }
   }

   printf("V: %d\n", verbose);
   printf("D: %d\n", mode);
   printf("KEY: %s\n", key);
   if (infile)
      printf("IN: %s\n", infile);
   if (outfile)
      printf("OUT: %s\n", outfile);

   if (infile) {
      infd = open(infile, O_RDONLY);
      if (infd == -1) {
         fprintf(stderr, "Error reading from file %s\n", infile);
         return 1;
      }
      dup2(infd, 0);
   }

   if (outfile) {
      outfd = open(outfile, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
      if (outfd == -1) {
         fprintf(stderr, "Error writing to file %s\n", outfile);
         return 1;
      }
      dup2(outfd, 1);
   }

   for (i = 0; scanf("%c", &c) != EOF; i++) {
      x = key[i % keylen];
      if (isalpha(c)) {
         if (isupper(x)) {
            x -= UPPER_OFFSET;
         }
         else if (islower(x)) {
            x -= LOWER_OFFSET;
         }
         if (isupper(c)) {
            c -= UPPER_OFFSET;
         }
         else if (islower(c)) {
            c -= LOWER_OFFSET;
         }
         c = (c + x) % 26;
         putchar(c + UPPER_OFFSET);
      }
      else {
         putchar(c);
      }
   }

   if (infile)
      close(infd);
   
   if (outfile)
      close(outfd);

   return 0;
}
