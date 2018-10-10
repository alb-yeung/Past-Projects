#include <stdlib.h>
#include <stdio.h>

typedef struct _Node{
  int memPage;
  int memLoc;
  struct _Node* nextNode;
}Node;

Node* first = NULL;
Node* last = NULL;

void addNode(int a, int b){
  if (last == NULL){
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->memPage = a;
    temp->memLoc = b;
    first = temp;
    last = temp;
  }else{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->memPage = a;
    temp->memLoc = b;
    last->nextNode = temp;
    last = last->nextNode;
  }
}

void clearList(){
  if (first == NULL)
    return;
  else{
    free(first);
    first = NULL;
    last = NULL;
  }
}

void fifo(int* array, int cacheSize){
  int hits = 0;
  int hit = 0;
  int cache[cacheSize];
  int incache = 0;
  for (int i = 0; i < cacheSize; i++){
    cache[i] = -1;
  }
  for (int i = 0; i < 10000; i++){
    int temp = array[i];
    for (int j = 0; j < cacheSize; j++){
      if (temp == cache[j]){
	hits++;
	hit = 1;
	break;
      }
    }
    if (!(hit)){
      if (incache < cacheSize){
	cache[incache] = temp;
	incache++;
	addNode(temp, incache);
      }else{
	cache[(first->memLoc)] = temp;
	addNode(temp, first->memLoc);
	first = first->nextNode;
      }
    }
    hit = 0;
  }
  printf("%d Hits out of 10000 Mem Access with Cache Size of %d with FIFO\n", hits, cacheSize);
  clearList();
}

//void otherOpt(int* array, int 

void opt(int* array, int cacheSize){
  int hits = 0;
  int hit = 0;
  int cache[cacheSize];
  int used[cacheSize];
  int incache = 0;
  for (int i = 0; i < cacheSize; i++){
    cache[cacheSize] = -1;
  }
  for (int i = 0; i < 10000; i++){
    int temp = array[i];
    for (int j = 0; j < incache; j++){
      if (cache[j] == temp){
	hits++;
	hit = 1;
	break;
      }
    }
    if (!(hit)){
      if (incache < cacheSize){
	cache[incache] = temp;
	incache++;
	continue;
      }
      for (int j = 0; j < cacheSize; j++){
	used[j] = 10001;
      }
      for (int counter = i+1; counter < 10000; counter++){
	for (int j = 0; j < incache; j++){
	  if (cache[j] == array[counter] && used[j] == 10001){
	    used[j] = counter;
	  }
	}
      }
      int max = -1;
      int maxIndex = cacheSize + 1;
      for (int j = 0; j < incache; j++){
	if (used[j] > max){
	  max = used[j];
	  maxIndex = j;
	}
      }
      cache[maxIndex] = temp;
    }
    hit = 0;
  }
  printf("%d Hits out of 10000 Mem Access with Cache Size of %d with OPT\n", hits, cacheSize);
}

void lru(int* array, int cacheSize){
  int hits = 0;
  int hit = 0;
  int cache[cacheSize];
  int latestAccess[cacheSize];
  int incache = 0;
  for (int i = 0; i < cacheSize; i++){
    cache[i] = -1;
    latestAccess[i] = 0;
  }

  for (int i = 0; i < 10000; i++){
    int temp = array[i];
    for (int j = 0; j < cacheSize; j++){
      if (cache[j] == temp){
	hits++;
	hit = 1;
	latestAccess[j] = i;
	break;
      }
    }
    if (!hit){
      if (incache < cacheSize){
	cache[incache] = temp;
	incache++;
	continue;
      }
      int min = 10001;
      int minIndex = cacheSize+1;
      for (int j = 0; j < cacheSize; j++){
	if (latestAccess[j] < min){
	  min = latestAccess[j];
	  minIndex = j;
	}
      }
      cache[minIndex] = temp;
      latestAccess[minIndex] = i;
    }
    hit = 0;
  }
  printf("%d Hits out of 10000 Mem Access with Cache Size of %d with LRU\n", hits, cacheSize);
}

void rando(int* array, int cacheSize){
  int hits = 0;
  int hit = 0;
  int cache[cacheSize];
  int incache = 0;
  for (int i = 0; i < cacheSize; i++){
    cache[i] = -1;
  }
  for (int i = 0; i < 10000; i++){
    int temp = array[i];
    for (int j = 0; j < cacheSize; j++){
      if (cache[j] == temp){
	hits++;
	hit = 1;
	break;
      }
    }
    if (!hit){
      if (incache < cacheSize){
	cache[incache] = temp;
	incache++;
	continue;
      }
      cache[rand()%cacheSize] = temp;
    }
    hit = 0;
  }
  printf("%d Hits out of 10000 Mem Access with Cache Size of %d with RAND\n", hits, cacheSize);
}

void clock(int* array, int cacheSize){
  int hits = 0;
  int hit = 0;
  int cache[cacheSize];
  int bit[cacheSize];
  int counter = 0;
  int incache = 0;
  for (int i = 0; i < cacheSize; i++){
    cache[i] = -1;
    bit[i] = 0;
  }
  for (int i = 0; i < 10000; i++){
    int temp = array[i];
    /*
    if (i < cacheSize){
      cache[i] = temp;
      bit[i] = 1;
      }else{
    */
    for (int j = 0; j < cacheSize; j++){
      if (cache[j] == temp){
	hits++;
	bit[j] = 1;
	hit = 1;
	break;
      }
    }
    //}
    if (!hit){
      
      if (incache < cacheSize){
	cache[incache] = temp;
	bit[incache] = 1;
	incache++;
	continue;
      }
      
      while(bit[counter] == 1){
	bit[counter] = 0;
	counter = (counter+1)%cacheSize;
      }
      cache[counter] = temp;
      bit[counter] = 1;
    }
    hit = 0;
  }
  printf("%d Hits out of 10000 Mem Access with Cache Size of %d with CLOCK\n", hits, cacheSize);
}

int main(){
  int* arr = (int*)malloc(sizeof(int) * 10000);
  FILE* fp;
  fp = fopen("80-20.txt", "r");
  for (int i = 0; i < 10000; i++){
    fscanf(fp, "%d ", &arr[i]);
  }
  for (int i = 1; i < 21;i++){
    fifo(arr, i*5);
    rando(arr, i*5);
    clock(arr, i*5);
    lru(arr, i*5);
    opt(arr, i*5);
  }
  fclose(fp);
}
