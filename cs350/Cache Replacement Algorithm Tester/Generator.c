#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
  int* arr = (int*)malloc(sizeof(int) * 10000);
  FILE* fp;
  
  printf("Making no-locality\n");
  for (int i = 0; i < 10000; i++){
    arr[i] = rand()%100;
  }
  fp = fopen("No-locality.txt", "w+");
  for (int i = 0; i < 10000; i++){
    fprintf(fp, "%d\t", arr[i]);
  }
  fclose(fp);

  printf("Making 80-20\n");
  fp = fopen("80-20.txt", "w+");
  for (int i = 0; i < 10000; i++){
    if ((rand()%10) < 8){
      arr[i] = rand()%20;
    }else{
      arr[i] = (rand()%80) + 20;
    }
  }
  for (int i = 0; i < 10000; i++){
    fprintf(fp, "%d\t", arr[i]);
  }
  fclose(fp);

  printf("Making Looping\n");
  fp = fopen("Looping.txt", "w+");
  for (int i = 0; i < 10000; i++){
    arr[i] = i%50;
  }
  for (int i = 0; i < 10000; i++){
    fprintf(fp, "%d\t", arr[i]);
  }
  
  return 0;
}
