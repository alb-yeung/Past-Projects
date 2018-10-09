#include "Predictor.h"

using namespace std;

int main(int argc, char* argv[]){
  //cout << "adf" << endl;
	if (argc != 3){
		cout << "Please use ./predictors <input-file> <output-file>" << endl;
		return 1;
	}
  Predictor a = Predictor(argv[1], argv[2]);
  a.read();
  return 0;
}
