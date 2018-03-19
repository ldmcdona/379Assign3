#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  char* a;
  char* d;
  char b[20];
  char c[5][20];
  char* e;
  int x = 0;
  int y = 0;

  a = "X";
  d = "P";
  e = " ";

  for(int i=0; i<20; i++){
    b[i] = '!';
  }
  for(int i=0; i<5; i++){
    strcpy(c[i], e);
  }
    
  printf("Enter X to end the program.\n");
  printf("Enter P to print the hash table\n");
  printf("Enter a string to hash: ");

  while(scanf("%s", b) != EOF){
    if(strcmp(a, b) == 0){
      break;
    }else if(strcmp(d, b) == 0){
      for(int i=0; i<5; i++){
        printf("hash[i] = %s\n", c[i]);
      }
    }else{
      for(int j=0; j<20; j++){
        if(b[j] != '!'){
          x += (int)b[j];
        }
      }
      y = x % 5;
      strcpy(c[y], b);
      }
      printf("You entered: '%s', which hashes to %d\n", b, y);
      for(int j=0; j<20; j++){
        b[j] = '!';
      }
      x = 0;
    printf("Enter a string to hash: ");
  }
  
  return 0;
}
