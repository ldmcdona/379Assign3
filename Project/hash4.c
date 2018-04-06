/******************************************
 *
 * hash4.c - Modified 2018-04-05
 *
 * Created by:
 * Liam McDonald 1462799
 * Craig Lindsay 1391493
 *
 *
 * hash4 is a simple hash function and counting hash table 
 *
 * USEAGE:
 *
 * initialize the table using initHashTable(hashSize)
 *
 * hash a string with hashf(char*)
 *
 * increment(hash) increments the hash table
 *
 * decrement(hash) decrements the hash table
 * 
 * end() cleans up the memory for the hash table
 *
 ******************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash;
int* c;

void clearTheTable() {
  /*clears the hash table (table must be initalized first)
   *
   * Args: None
   *
   * Returns: None
   */
  for(int i=0; i<hash; i++){
    c[i] = 0;
  }
}

void initHashTable(int hashSize) {
  /* inializes the hash table of size hashSize, the maximum number of unique pages that we can have
   *
   * Args: int size of hash table to create
   *
   * Returns: None
   */
  hash = hashSize;
  c = (int*)malloc(sizeof(int)*hash);
  clearTheTable();
}

void printTheTable() {
  /* prints the contents of the table
   *
   * Args: None
   *
   * Returns: None
   */
  for(int i=0; i<hash; i++){
    printf("hash[%d] has been hit %d times\n", i, c[i]);
  }
}

void printNoOfEntrys() {
  /*prints the number of entries in the hash table that have a non-zero content
   *
   * Args: None
   *
   * Returns: None
   */
  int count = 0;
  for(int i=0; i<hash; i++) {
    if(c[i] != 0) {
      count++;
    }
  }
  printf("%i\n",count);
}

int hashf(char* toHash) {
  /*simple hash function
   *
   * Args: char* to hash
   *
   * Returns: (int) hash value of entry
   */
  int x = 0;
  for(int j=0; j<strlen(toHash); j++){
    x += (int)toHash[j];
  }
  return x % hash;
}

void decrement(int boxNo) {
  /*decrements an entry in the hash table, expects a valid hash from hashf()
   *
   * Args: (int) hash from hashf
   *
   * Returns: None
   */
  c[boxNo]--;
}

void increment(int boxNo) {
  /*increments an entry in the hash table, expects a valid hash from hashf()
   *
   * Args: (int) hash from hashf
   *
   * Returns: None
   */
  c[boxNo]++;
}

void end() {
  /* frees the hash table
   *
   * Args: None
   *
   * Returns: None
   */
  free(c);
}


int testhash() {
  /*test function for the hash table
   *
   * Args: none
   *
   * Returns: (int) 0 upon completion
   */
  int hashBuff;
  char* a;
  char* d;
  char* e;
  char* f;

  a = "X";
  d = "P";
  e = " ";
  f = "C";

  printf("Enter hash size: ");
  scanf("%d", &hashBuff);
  if(hashBuff < 1){
    printf("Invalid hash size\n");
    return 0;
  }
  initHashTable(hashBuff);
  printf("You entered %d\n", hash);

  //Specialmode
  char b[20];

  for(int i=0; i<20; i++){
    b[i] = '!';
  }
  //######

  printf("Enter X to end the program.\n");
  printf("Enter P to print the hash table\n");
  printf("Enter C to clear the hash table\n");
  printf("Begin your string with * to decrement\n");
  printf("Enter a string to hash: ");
  while(scanf("%s", b) != EOF){
    if(strcmp(a, b) == 0){
      end();
      break;
    }else if(strcmp(d, b) == 0){
      printTheTable();
    }else if(strcmp(f, b) == 0){
      clearTheTable();
    }else{
      if(b[0] == '*'){
	decrement(hashf(memmove(b, b+1, 20)));
      }else{
	increment(hashf(b));
      }
      for(int j=0; j<20; j++){
	b[j] = '!';
      }
    }
    printf("Enter a string to hash: ");
  }
  
  return 0;
}
