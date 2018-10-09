#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char*argv[]){
  FILE * fd;
  int c;
  char* input;
  int* tnt = {0,0};
  char buf[1024]; 
  scanf("%s",&input);
  fd = fopen(input, "r");
  if (fd){
    while ((c = getc(fd)) != EOF){
      
    }
    fclose(fd);
  }
}
