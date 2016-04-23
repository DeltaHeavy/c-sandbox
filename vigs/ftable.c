#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define OFFSET 'A'

void usage() {
   printf("Usage: ftable [ -v ] [ -s num ] [ -p num ] [ infile [ outfile ]");
}

int main(int argc, char **argv) {

   int i, verbose = 0;
   unsigned int skip = 0, period = 1;
   int infd = 0, outfd = 0;
   char *infile = NULL, *outfile = NULL;
   int *ftable = calloc(ALPHABET_SIZE, sizeof(int));
   unsigned char c;

   while (*++argv) {
      if (!strcmp(*argv, "-v")) {
         verbose = 1;
      }
      else if (!strcmp(*argv, "-s")) {
         if (argv[1] && isdigit(*(argv[1]))) {
            sscanf((*++argv), "%u", &skip);
         }
         else {
            fprintf(stderr, "-s requires an argument\n");
            usage();
            return 1;
         }
      }
      else if (!strcmp(*argv, "-p")) {
         if (argv[1] && isdigit(*(argv[1]))) {
            sscanf((*++argv), "%u", &period);
         }
         else {
            fprintf(stderr, "-p requires an argument\n");
            usage();
            return 1;
         }
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

   printf("V: %u\n", verbose);
   printf("S: %u\n", skip);
   printf("P: %u\n", period);
   if (infile)
      printf("I: %s\n", infile);
   if (outfile)
      printf("O: %s\n", outfile);

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

   while (scanf("%c", &c) != EOF) {
      if (isalpha(c)) {
         c = toupper(c);
         ftable[c - OFFSET]++;
      }
   }

   for (i = 0; i < ALPHABET_SIZE; i++) {
      printf("%c: %d\n", OFFSET + i, ftable[i]);
   }

   if (infile)
      close(infd);
   
   if (outfile)
      close(outfd);

   return 0;
}
