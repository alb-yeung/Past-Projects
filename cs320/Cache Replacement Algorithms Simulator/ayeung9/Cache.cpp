#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

char* loadStore;
long* addr;
int totalLines;
ofstream out;

void directMapped(int cacheSize){
  //cout << "Doing direct mapped cache with size " << cacheSize << "... ";
  int size = cacheSize/32;
  unsigned int* cache = new unsigned int[size];
  char* valid = new char[size];
  int hits = 0;
  for (int i = 0; i < size; i++){
    valid[i] = 0;
  }
  for (int i = 0; i < totalLines; i++){
    char curr = loadStore[i];
    long currAddr = addr[i];
    if (cache[(currAddr/32)%size] == currAddr/32 && valid[(currAddr/32)%size] != 0){
      hits++;
      continue;
    }
    if (valid[(currAddr/32)%size] == 0){
      valid[(currAddr/32)%size] = 'a';
      cache[(currAddr/32)%size] = currAddr/32;
      continue;
    }
    if (cache[(currAddr/32)%size] == currAddr/32){
      hits++;
    }else{
      cache[(currAddr/32)%size] = currAddr/32;
    }
  }
  //cout << "Done" << endl;
  cout << "Hits: " << hits << endl;
  out << hits << ";" << totalLines << " ";
}

void setAssociative(int ways){
  //cout << "Doing set associative cache with ways " << ways << "... ";
  int sets = (16*1024)/(ways*32);
  unsigned int** cache = new unsigned int*[sets];
  int** order = new int*[sets];
  int prevOrder;
  char** valid = new char*[sets];
  int hits = 0;
  for (int i = 0; i < sets; i++){
    cache[i] = new unsigned int[ways];
    valid[i] = new char[ways];
    order[i] = new int[ways];
    for (int j = 0; j < ways; j++){
      valid[i][j] = 0;
      order[i][j] = 0;
    }
  }

  for (int i = 0; i < totalLines; i++){
    char curr = loadStore[i];
    long currAddr = addr[i];
    int validFlag = 0;
    int hitFlag = 0;
    int beforeValid = 0;

    for (int j = 0; j < ways; j++){
      if (cache[(currAddr/32)%sets][j] == currAddr/32 && valid[(currAddr/32)%sets][j] != 0){
        hitFlag = 1;
        hits++;
        prevOrder = order[(currAddr/32)%sets][j];
        for (int k = 0; k < ways; k++){
          if (order[(currAddr/32)%sets][k] < prevOrder){
            order[(currAddr/32)%sets][k]++;
          }
        }
        order[(currAddr/32)%sets][j] = 0;
        beforeValid = 1;
        break;
      }
    }
    if (beforeValid == 0){
      for (int j = 0; j < ways; j++){
        if (valid[(currAddr/32)%sets][j] == 0){
          validFlag = 1;
          cache[(currAddr/32)%sets][j] = currAddr/32;
          valid[(currAddr/32)%sets][j] = 'a';
          for (int k = 0; k < ways; k++){
            order[(currAddr/32)%sets][k]++;
          }
          order[(currAddr/32)%sets][j] = 0;
          break;
        }
      }

      if (validFlag == 0){
          for (int j = 0; j < ways; j++){
            if (order[(currAddr/32)%sets][j] >= ways-1){
              cache[(currAddr/32)%sets][j] = currAddr/32;
              prevOrder = order[(currAddr/32)%sets][j];
              for (int k = 0; k < ways; k++){
                if (order[(currAddr/32)%sets][k] < prevOrder){
                  order[(currAddr/32)%sets][k]++;
                }
              }
              order[(currAddr/32)%sets][j] = 0;
              break;
            }
          }
      }
    }
  }
  //cout << "Done" << endl;
  cout << "Hits: " << hits << endl;
  out << hits << ";" << totalLines << " ";
}

void fullAssociativeLRU(){
  //cout << "Doing fully associative cache ... ";
  int ways = (16*1024)/32;
  unsigned int* cache = new unsigned int[ways];
  char* valid = new char[ways];
  int* order = new int[ways];
  int prevOrder;
  int hits = 0;
  for (int i = 0; i < ways; i++){
    valid[i] = 0;
    order[i] = 0;
  }
  for (int i = 0; i < totalLines; i++){
    char curr = loadStore[i];
    long currAddr = addr[i];
    int validFlag = 0;
    int hitFlag = 0;

    for (int j = 0; j < ways; j++){
      if (valid[j] == 0){
        valid[j] = 'a';
        cache[j] = currAddr/32;
        order[j] = 0;
        validFlag = 1;
        for (int k = 0; k < ways; k++){
          if (k != j){
            order[j]++;
          }
        }
        continue;
      }
    }

    if (validFlag == 0){
      for (int j = 0; j < ways; j++){
        if (cache[j] == currAddr/32){
          hits++;
          prevOrder = order[j];
          for (int k = 0; k < ways; k++){
            if (k != j){
              if (order[k] < prevOrder){
                order[k]++;
              }
            }
          }
          order[j] = 0;
          cache[j] = currAddr/32;
          hitFlag = 1;
          break;
        }
      }

      if (hitFlag == 0){
        for (int j = 0; j < ways; j++){
          if (order[j] >= ways-1){
            prevOrder = order[j];
            for (int k = 0; k < ways; k++){
              if (order[k] < prevOrder){
                order[k]++;
              }
            }
            order[j] = 0;
            cache[j] = currAddr/32;
            break;
          }
        }
      }
    }
  }
  //cout << "Done" << endl;
  cout << "Hits: " << hits << endl;
  out << hits << ";" << totalLines << " ";
}

int hotColdLRU(int* arr){
  int steps = 9;
  int start = 0;
  for (int i = 0; i < steps; i++){
    if (arr[start] == 0){
      start = (2*start) + 2;
    }else{
      start = (2*start) + 1;
    }
  }
  start -= 511;
  //cout << start << endl;
  return start;
}

void setHotCold(int* &arr, int index){
  int tIndex = index + 511;
  while (tIndex > 0){
    if (tIndex%2 == 1){
      arr[tIndex/2] = 0;
      tIndex = tIndex/2;
    }else{
      arr[(tIndex/2) - 1] = 1;
      tIndex = (tIndex/2) - 1;
    }
  }
}

void fullAssociativeHotCold(){
  int ways = (16*1024)/32;
  unsigned int* cache = new unsigned int[ways];
  char* valid = new char[ways];
  int* hotCold = new int[ways-1];
  //char* hotCold = new char[(2*ways)-1];
  int hits = 0;

  for (int i = 0; i < ways-1; i++){
    valid[i] = 0;
    hotCold[i] = 0;
  }
  valid[ways-1] = 0;
  for (int i = 0; i < totalLines; i++){
    char curr = loadStore[i];
    long currAddr = addr[i];
    int validFlag = 0;
    int beforeValid = 0;

    for (int j = 0; j < ways; j++){
      if (cache[j] == currAddr/32 && valid[j] != 0){
        hits++;
        setHotCold(hotCold, j);
        beforeValid = 1;
        break;
      }
    }

    if (beforeValid == 0){
      for (int j = 0; j < ways; j++){
        if (valid[j] == 0){
          valid[j] = 1;
          cache[j] = currAddr/32;
          setHotCold(hotCold, j);
          validFlag = 1;
          break;
        }
      }

      if (validFlag == 0){
        int tmp = hotColdLRU(hotCold);
        cache[tmp] = currAddr/32;
        setHotCold(hotCold, tmp);
      }
    }
  }
  cout << "Hits: " << hits << endl;
  out << hits << ";" << totalLines << " ";
}

void setAssociativeNoWrite(int ways){
  int sets = (16*1024)/(ways*32);
  unsigned int** cache = new unsigned int*[sets];
  int** order = new int*[sets];
  int prevOrder;
  char** valid = new char*[sets];
  int hits = 0;
  for (int i = 0; i < sets; i++){
    cache[i] = new unsigned int[ways];
    valid[i] = new char[ways];
    order[i] = new int[ways];
    for (int j = 0; j < ways; j++){
      valid[i][j] = 0;
      order[i][j] = 0;
    }
  }

  for (int i = 0; i < totalLines; i++){
    char curr = loadStore[i];
    long currAddr = addr[i];
    int validFlag = 0;
    int hitFlag = 0;
    int beforeValid = 0;

    for (int j = 0; j < ways; j++){
      if (cache[(currAddr/32)%sets][j] == currAddr/32 && valid[(currAddr/32)%sets][j] != 0){
        hitFlag = 1;
        hits++;
        prevOrder = order[(currAddr/32)%sets][j];
        for (int k = 0; k < ways; k++){
          if (order[(currAddr/32)%sets][k] < prevOrder){
            order[(currAddr/32)%sets][k]++;
          }          }
        order[(currAddr/32)%sets][j] = 0;
        beforeValid = 1;
        break;
      }
    }
    if (curr == 'L'){
    if (beforeValid == 0){
      for (int j = 0; j < ways; j++){
        if (valid[(currAddr/32)%sets][j] == 0){
          validFlag = 1;
          cache[(currAddr/32)%sets][j] = currAddr/32;
          valid[(currAddr/32)%sets][j] = 'a';
          for (int k = 0; k < ways; k++){
            order[(currAddr/32)%sets][k]++;
          }
          order[(currAddr/32)%sets][j] = 0;
          break;
        }
      }

      if (validFlag == 0){
          for (int j = 0; j < ways; j++){
            if (order[(currAddr/32)%sets][j] >= ways-1){
              cache[(currAddr/32)%sets][j] = currAddr/32;
              prevOrder = order[(currAddr/32)%sets][j];
              for (int k = 0; k < ways; k++){
                if (order[(currAddr/32)%sets][k] < prevOrder){
                  order[(currAddr/32)%sets][k]++;
                }
              }
              order[(currAddr/32)%sets][j] = 0;
              break;
            }
          }
        }
      }
    }
  }
  cout << "Hits: " << hits << endl;
  out << hits << ";" << totalLines << " ";
}

void setAssociativePrefetch(int ways){
  int sets = (16*1024)/(ways*32);
  unsigned int** cache = new unsigned int*[sets];
  int** order = new int*[sets];
  int prevOrder;
  char** valid = new char*[sets];
  int hits = 0;
  for (int i = 0; i < sets; i++){
    cache[i] = new unsigned int[ways];
    valid[i] = new char[ways];
    order[i] = new int[ways];
    for (int j = 0; j < ways; j++){
      valid[i][j] = 0;
      order[i][j] = 0;
    }
  }

  for (int i = 0; i < totalLines; i++){
    char curr = loadStore[i];
    long currAddr = addr[i];
    int validFlag = 0;
    int hitFlag = 0;
    //int nextHit = 0;
    int beforeValid = 0;

    for (int j = 0; j < ways; j++){
      if (cache[(currAddr/32)%sets][j] == currAddr/32 && valid[(currAddr/32)%sets][j] != 0){
        hitFlag = 1;
        hits++;
        prevOrder = order[(currAddr/32)%sets][j];
        for (int k = 0; k < ways; k++){
          if (order[(currAddr/32)%sets][k] < prevOrder){
            order[(currAddr/32)%sets][k]++;
          }
        }
        order[(currAddr/32)%sets][j] = 0;
        beforeValid = 1;
        break;
      }
    }
    if (beforeValid == 0){
      for (int j = 0; j < ways; j++){
        if (valid[(currAddr/32)%sets][j] == 0){
          validFlag = 1;
          cache[(currAddr/32)%sets][j] = currAddr/32;
          valid[(currAddr/32)%sets][j] = 'a';
          for (int k = 0; k < ways; k++){
            order[(currAddr/32)%sets][k]++;
          }
          order[(currAddr/32)%sets][j] = 0;
          break;
        }
      }

      if (validFlag == 0){
          for (int j = 0; j < ways; j++){
            if (order[(currAddr/32)%sets][j] >= ways-1){
              cache[(currAddr/32)%sets][j] = currAddr/32;
              prevOrder = order[(currAddr/32)%sets][j];
              for (int k = 0; k < ways; k++){
                if (order[(currAddr/32)%sets][k] < prevOrder){
                  order[(currAddr/32)%sets][k]++;
                }
              }
              order[(currAddr/32)%sets][j] = 0;
              break;
            }
          }
      }
    }

    currAddr += 32;
    validFlag = 0;
    hitFlag = 0;
    beforeValid = 0;

    for (int j = 0; j < ways; j++){
      if (cache[(currAddr/32)%sets][j] == currAddr/32 && valid[(currAddr/32)%sets][j] != 0){
        hitFlag = 1;
        //hits++;
        prevOrder = order[(currAddr/32)%sets][j];
        for (int k = 0; k < ways; k++){
          if (order[(currAddr/32)%sets][k] < prevOrder){
            order[(currAddr/32)%sets][k]++;
          }
        }
        order[(currAddr/32)%sets][j] = 0;
        beforeValid = 1;
        break;
      }
    }
    if (beforeValid == 0){
      for (int j = 0; j < ways; j++){
        if (valid[(currAddr/32)%sets][j] == 0){
          validFlag = 1;
          cache[(currAddr/32)%sets][j] = currAddr/32;
          valid[(currAddr/32)%sets][j] = 'a';
          for (int k = 0; k < ways; k++){
            order[(currAddr/32)%sets][k]++;
          }
          order[(currAddr/32)%sets][j] = 0;
          break;
        }
      }

      if (validFlag == 0){
          for (int j = 0; j < ways; j++){
            if (order[(currAddr/32)%sets][j] >= ways-1){
              cache[(currAddr/32)%sets][j] = currAddr/32;
              prevOrder = order[(currAddr/32)%sets][j];
              for (int k = 0; k < ways; k++){
                if (order[(currAddr/32)%sets][k] < prevOrder){
                  order[(currAddr/32)%sets][k]++;
                }
              }
              order[(currAddr/32)%sets][j] = 0;
              break;
            }
          }
      }
    }

  }
  cout << "Hits: " << hits << endl;
  out << hits << ";" << totalLines << " ";
}

void setAssociativeMissPrefetch(int ways){
  int sets = (16*1024)/(ways*32);
  unsigned int** cache = new unsigned int*[sets];
  int** order = new int*[sets];
  int prevOrder;
  char** valid = new char*[sets];
  int hits = 0;
  for (int i = 0; i < sets; i++){
    cache[i] = new unsigned int[ways];
    valid[i] = new char[ways];
    order[i] = new int[ways];
    for (int j = 0; j < ways; j++){
      valid[i][j] = 0;
      order[i][j] = 0;
    }
  }

  for (int i = 0; i < totalLines; i++){
    char curr = loadStore[i];
    long currAddr = addr[i];
    int validFlag = 0;
    int hitFlag = 0;
    int beforeValid = 0;
    int missed = 0;

    for (int j = 0; j < ways; j++){
      if (cache[(currAddr/32)%sets][j] == currAddr/32 && valid[(currAddr/32)%sets][j] != 0){
        hitFlag = 1;
        hits++;
        prevOrder = order[(currAddr/32)%sets][j];
        for (int k = 0; k < ways; k++){
          if (order[(currAddr/32)%sets][k] < prevOrder){
            order[(currAddr/32)%sets][k]++;
          }
        }
        order[(currAddr/32)%sets][j] = 0;
        beforeValid = 1;
        break;
      }
    }
    if (beforeValid == 0){
      missed = 1;
      for (int j = 0; j < ways; j++){
        if (valid[(currAddr/32)%sets][j] == 0){
          validFlag = 1;
          cache[(currAddr/32)%sets][j] = currAddr/32;
          valid[(currAddr/32)%sets][j] = 'a';
          for (int k = 0; k < ways; k++){
            order[(currAddr/32)%sets][k]++;
          }
          order[(currAddr/32)%sets][j] = 0;
          break;
        }
      }

      if (validFlag == 0){
          for (int j = 0; j < ways; j++){
            if (order[(currAddr/32)%sets][j] >= ways-1){
              cache[(currAddr/32)%sets][j] = currAddr/32;
              prevOrder = order[(currAddr/32)%sets][j];
              for (int k = 0; k < ways; k++){
                if (order[(currAddr/32)%sets][k] < prevOrder){
                  order[(currAddr/32)%sets][k]++;
                }
              }
              order[(currAddr/32)%sets][j] = 0;
              break;
            }
          }
      }
    }
    if (missed){
      currAddr += 32;
      hitFlag = 0;
      beforeValid = 0;
      validFlag = 0;
    for (int j = 0; j < ways; j++){
      if (cache[(currAddr/32)%sets][j] == currAddr/32 && valid[(currAddr/32)%sets][j] != 0){
        hitFlag = 1;
        //hits++;
        prevOrder = order[(currAddr/32)%sets][j];
        for (int k = 0; k < ways; k++){
          if (order[(currAddr/32)%sets][k] < prevOrder){
            order[(currAddr/32)%sets][k]++;
          }
        }
        order[(currAddr/32)%sets][j] = 0;
        beforeValid = 1;
        break;
      }
    }
    if (beforeValid == 0){
      for (int j = 0; j < ways; j++){
        if (valid[(currAddr/32)%sets][j] == 0){
          validFlag = 1;
          cache[(currAddr/32)%sets][j] = currAddr/32;
          valid[(currAddr/32)%sets][j] = 'a';
          for (int k = 0; k < ways; k++){
            order[(currAddr/32)%sets][k]++;
          }
          order[(currAddr/32)%sets][j] = 0;
          break;
        }
      }

      if (validFlag == 0){
          for (int j = 0; j < ways; j++){
            if (order[(currAddr/32)%sets][j] >= ways-1){
              cache[(currAddr/32)%sets][j] = currAddr/32;
              prevOrder = order[(currAddr/32)%sets][j];
              for (int k = 0; k < ways; k++){
                if (order[(currAddr/32)%sets][k] < prevOrder){
                  order[(currAddr/32)%sets][k]++;
                }
              }
              order[(currAddr/32)%sets][j] = 0;
              break;
            }
          }
        }
      }
    }
  }
  cout << "Hits: " << hits << endl;
  out << hits << ";" << totalLines << " ";
}

void read(string inFile){
  ifstream f(inFile);
  if (f.fail()){
    cout << "File not found" << endl;
    return;
  }
  int lines = 0;
  string data;
  stringstream stream;
  string temp;
  int loads = 0;
  int stores = 0;
  char* fix;
  for (getline(f, data, '\n'); data != ""; getline(f, data, '\n')){
    lines++;
  }
  totalLines = lines;
  f.clear();
  f.seekg(0, ios::beg);
  cout << "lines:" << lines << endl;
  loadStore = new char[lines];
  addr = new long[lines];
  for (int i = 0; i < lines; i++){
    getline(f, data, ' ');
    if (data[0] == 'L'){
      loads++;
      loadStore[i] = 'L';
    }else{
      stores++;
      loadStore[i] = 'S';
    }
    getline(f, data, '\n');
    fix = new char[data.size() + 1];
    copy(data.begin(), data.end(), fix);
    fix[data.size()] = '\0';
    addr[i] = strtoul(fix, NULL, 0);
  }
  cout << "Loads: " << loads << " Stores: " << stores << endl;
}

int main(int argc, char*argv[]){
  if (argc == 3){
    read(argv[1]);
    out = ofstream(argv[2]);
    
    directMapped(1024);
    directMapped(4*1024);
    directMapped(16*1024);
    directMapped(32*1024);
    cout << endl;
    out << endl;
    setAssociative(2);
    setAssociative(4);
    setAssociative(8);
    setAssociative(16);
    cout << endl;
    out << endl;
    fullAssociativeLRU();
    cout << endl;
    out << endl;
    fullAssociativeHotCold();
    cout << endl;
    out << endl;
    setAssociativeNoWrite(2);
    setAssociativeNoWrite(4);
    setAssociativeNoWrite(8);
    setAssociativeNoWrite(16);
    cout << endl;
    out << endl;
    setAssociativePrefetch(2);
    setAssociativePrefetch(4);
    setAssociativePrefetch(8);
    setAssociativePrefetch(16);
    cout << endl;
    out << endl;
    setAssociativeMissPrefetch(2);
    setAssociativeMissPrefetch(4);
    setAssociativeMissPrefetch(8);
    setAssociativeMissPrefetch(16);
  }
  return 0;
}
