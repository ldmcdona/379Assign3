/******************************************
 *
 * valws379.c - Modified 2018-04-05
 *
 * Created by:
 * Craig Lindsay 1391493
 * Liam McDonald 1462799
 *
 * USEAGE:
 * called via a bash script which parses the args for this program
 *
 * prints the number of pages in use for a given program using a sliding window
 * of size windowSize
 *
 ******************************************
 */

#define _POSIX_SOURCE
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include "linklist.c"
#include "hash4.c"

FILE * gnuplotPipe;

int digitsToInclude(int pgSize) {
  /* maps the page size of the os (given by the user) to a count of digits in
   * the memory pointer that are refering to the page
   *
   * Args: (int) page size
   *
   * Returns: (int) digits in memory pointer that refer to page
   */
  if (pgSize <= 16) {return 7;}
  else if (pgSize <= 256) {return 6;}
  else if (pgSize <= 4096) {return 5;}
  else {return 4;}
}

static void sigHandler(int signo) {
  /* Basic signal handler provides handling for SIGINT
   *
   * SIGINT exits the program
   *
   * Args:
   *     signo(int): interger representing the signal recieved
   *
   * Returns: void
   */

  if (signo == SIGINT) {
    end();
    fprintf(gnuplotPipe, "e");
    exit(0);
  }
}


int main(int argc, char* argv[])
{
  /* MAIN
   * prints the number of pages in use by the os while executing a program
   * every time an instruction is run
   *
   * Args:
   *     pageSize: size of each page in memory
   *     windowSize: size of sliding window to report on
   *     (optional) -i: ignores instructions
   *
   * Returns: int success status
   */
  int windowSize = atoi(argv[2]);
  int pgSize = atoi(argv[1]);
  printf("%i, %i\n", windowSize, pgSize);
  
  initHashTable(windowSize);

  char* buffer = NULL;
  size_t  n = 1024;
  buffer = malloc(n);

  char* type = "A";
  char* mem = NULL;
  size_t m = 10;
  mem = malloc(m);
  int hashVal;

  int DTI = digitsToInclude(pgSize);

  gnuplotPipe = popen ("gnuplot", "w");
  fprintf(gnuplotPipe, "set terminal pngcairo  transparent enhanced font 'arial,10' fontscale 1.0 size 600, 400\n");
  fprintf(gnuplotPipe, "set output 'test.png'\n");
  fprintf(gnuplotPipe, "plot '-' \n");

  struct sigaction sig_action;
  sig_action.sa_handler = &sigHandler;
  sigaction(SIGINT, &sig_action, NULL);

  long counter = 0;
  while(getline(&buffer, &n, stdin) != -1) {
    //parse the sting, making it come in tuple form
    
    type = strtok(buffer, " ");
    if (strcmp(type, "I") == 0 && argc == 4) {
      // restart the loop in the case of type == i
      continue;
    }
    mem = strtok(NULL, ",");
    if(mem[0] == ' ') {
      memmove(mem, mem+1, m);
    }
    mem[DTI] = '\0';
    hashVal  = hashf(mem);
    increment(hashVal);
    addEntry(hashVal);
    //printf("+%i ", hashVal);
    
    
    
    if(counter > windowSize) {
      //Decremnt last item in box
      hashVal = delFirstEntryAndReturnHash();
      decrement(hashVal);
      //printf("-%i ", hashVal);
    }
    hashVal = NoOfEntrys();
    printf("%i\n", hashVal);
    fprintf(gnuplotPipe, "%li %i\n", counter, hashVal);
    counter++;
  }
  end();
  fprintf(gnuplotPipe, "e");
}
