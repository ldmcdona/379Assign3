#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash;
int* c;

void clearTheTable() {
  for(int i=0; i<hash; i++){
    c[i] = 0;
  }
}

void initHashTable(int hashSize) {
  hash = hashSize;
  c = (int*)malloc(sizeof(int)*hash);
  clearTheTable();
}

void printTheTable() {
  for(int i=0; i<hash; i++){
    printf("hash[%d] has been hit %d times\n", i, c[i]);
  }
}

int hashf(char* toHash) {
  int x = 0;
  for(int j=0; j<strlen(toHash); j++){
    x += (int)toHash[j];
  }
  return x % hash;
}

void decrement(int boxNo) {
  c[boxNo]--;
}

void increment(int boxNo) {
  c[boxNo]++;
}

void end() {
  free(c);
}

int main() {
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
