#define _POSIX_SOURCE
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "linklist.c"
#include "hash4.c"

int digitsToInclude(int pgSize) {
  if (pgSize <= 16) {return 7;}
  else if (pgSize <= 256) {return 6;}
  else if (pgSize <= 4096) {return 5;}
  else {return 4;}
}

int main(int argc, char* argv[])
{
  //testLL();
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

  int counter = 0;
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
    
    counter++;
    
    if(counter > windowSize) {
      //Decremnt last item in box
      hashVal = delFirstEntryAndReturnHash();
      decrement(hashVal);
      //printf("-%i ", hashVal);
      counter--;
    }
    printNoOfEntrys();
  }
  end();
}
