#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

class Predictor{
 public:
  Predictor(string n, string a);
  string fileName;
  string outFile;
  int tnt[2];
  //ofstream output;
  //long int add[MAX_SIZE];
  //char taken[MAX_SIZE];
  void read();
  string allTaken();
  string allNotTaken();
  string bimodalOne(int tableSize);
  string bimodalTwo(int tableSize);
  string gShare(int historyLength);
  string tournament();
};

