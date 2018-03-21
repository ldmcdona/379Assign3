#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  int hash;
  char* a;
  char* d;
  char* e;
  int x = 0;
  int y = 0;

  a = "X";
  d = "P";
  e = " ";

  printf("Enter hash size: ");
  scanf("%d", &hash);
  if(hash < 1){
    printf("Invalid hash size\n");
    return 0;
  }
  printf("You entered %d\n", hash);

  char b[20];
  int c[hash];

  for(int i=0; i<20; i++){
    b[i] = '!';
  }
  for(int i=0; i<hash; i++){
    c[i] = 0;
  }
    
  printf("Enter X to end the program.\n");
  printf("Enter P to print the hash table\n");
  printf("Enter a string to hash: ");

  while(scanf("%s", b) != EOF){
    if(strcmp(a, b) == 0){
      break;
    }else if(strcmp(d, b) == 0){
      for(int i=0; i<hash; i++){
        printf("hash[%d] has been hit %d times\n", i, c[i]);
      }
    }else{
      for(int j=0; j<20; j++){
        if(b[j] != '!'){
          x += (int)b[j];
        }
      }
      y = x % hash;
      c[y]++;
      printf("You entered: '%s', which hashes to %d\n", b, y);
    }
    for(int j=0; j<20; j++){
      b[j] = '!';
    }
    x = 0;
    printf("Enter a string to hash: ");
  }
  
  return 0;
}
