#include "Predictor.h"

using namespace std;

Predictor::Predictor(string n, string a){
  fileName = n;
  outFile = a;
}

void Predictor::read(){
  ofstream output(outFile);
  output << allTaken();
  output << endl;
  cout << "Done with all taken" << endl;

  output << allNotTaken();
  output << endl;
  cout << "Done with all not taken" << endl;
  
  output << bimodalOne(16);
  output << bimodalOne(32);
  output << bimodalOne(128);
  output << bimodalOne(256);
  output << bimodalOne(512);
  output << bimodalOne(1024);
  output << bimodalOne(2048);
  output << endl;
  cout << "Done with all bimodal with one history bit" << endl;
  
  output << bimodalTwo(16);
  output << bimodalTwo(32);
  output << bimodalTwo(128);
  output << bimodalTwo(256);
  output << bimodalTwo(512);
  output << bimodalTwo(1024);
  output << bimodalTwo(2048);
  output << endl;
  cout << "Done with all bimodal with two history bits" << endl;

  output << gShare(3);
  output << gShare(4);
  output << gShare(5);
  output << gShare(6);
  output << gShare(7);
  output << gShare(8);
  output << gShare(9);
  output << gShare(10);
  output << gShare(11);
  output << endl;
  cout << "Done with all gshares" << endl;
  output << tournament();
  cout << "Done with tournament" << endl;
  output.close();
}

string Predictor::allTaken(){
  ifstream f(fileName);
  //ofstream output(outFile);
  string ret;
  if (f.fail()){
    cout << "File not found" << endl;
    return "";
  }
  //ofstream out(outFile);
  int lines=0;
  stringstream stream;
  string tempTaken;
  string data;
  int counter = 0;
  
  for (getline(f, data, '\n'); data != ""; getline(f, data, '\n')){
  	lines++;
    stream = stringstream(data);
    getline(stream, tempTaken, ' ');
    getline(stream, tempTaken, ' ');
    if (tempTaken == "T")
      counter ++;
  }
  ret = to_string(counter) + "," + to_string(lines) + "; ";
  f.close();
  //out.close();
  return ret;
}

string Predictor::allNotTaken(){
  ifstream f(fileName);
  //ofstream output(outFile);
  string ret;
  if (f.fail()){
    cout << "File not found" << endl;
    return "";
  }
  //ofstream out(outFile);
  int lines = 0;
  stringstream stream;
  string temp;
  unsigned int ttemp;
  string tempTaken;
  string data;
  int counter = 0;
  
  for (getline(f, data, '\n'); data != ""; getline(f, data, '\n')){
  	lines++;
    stream = stringstream(data);
    getline(stream, tempTaken, ' ');
    getline(stream, tempTaken, ' ');
    if (tempTaken == "NT")
      counter ++;
  }
  ret = to_string(counter) + "," + to_string(lines) + "; ";
  f.close();
  return ret;
}

string Predictor::bimodalOne(int tableSize){
  char prediction[tableSize];
  for (int i = 0; i < tableSize; i++){
    prediction[i] = 'T';
  }
  ifstream f(fileName);
  if (f.fail()){
    cout << "File not found" << endl;
    return "";
  }
  string ret;
  //ofstream output(outFile);
  //ofstream out(outFile);
  int lines = 0;
  stringstream stream;
  unsigned long addr;
  string tempTaken;
  string data;
  int counter = 0;
  char* fix;
  int index = 0;
  for (getline(f, data, '\n'); data != ""; getline(f, data, '\n')){
  	lines++;
    stream = stringstream(data);
    
    getline(stream, tempTaken, ' ');
    fix = new char[tempTaken.size() + 1];
    copy(tempTaken.begin(), tempTaken.end(), fix);
    fix[tempTaken.size()] = '\0';
    addr = strtoul(fix, NULL, 0);
    
    getline(stream, tempTaken, ' ');
    if (prediction[addr%tableSize] == 'T' && tempTaken == "T")
      counter++;
    else if (prediction[addr%tableSize] == 'N' && tempTaken == "NT")
      counter++;
    else{
      if (tempTaken == "T")
	prediction[addr%tableSize] = 'T';
      else prediction[addr%tableSize] = 'N';
    }
  }
  ret = (to_string(counter)) + "," + (to_string(lines)) + "; ";
  f.close();
  return ret;
  //out.close();
}

string Predictor::bimodalTwo(int tableSize){
  char prediction[tableSize];
  for (int i = 0; i < tableSize; i++){
    prediction[i] = 'D';
  }
  /*
    A = NN
    B = NT
    C = TN
    D = TT
   */
  ifstream f(fileName);
  if (f.fail()){
    cout << "File not found" << endl;
    return "";
  }
  string ret;
  //ofstream output(outFile);
  //ofstream out(outFile);
  int lines = 0;
  stringstream stream;
  unsigned long addr;
  string tempTaken;
  string data;
  int counter = 0;
  char* fix;
  for (getline(f, data, '\n'); data != ""; getline(f, data, '\n')){
  	lines++;
    stream = stringstream(data);
    
    getline(stream, tempTaken, ' ');
    fix = new char[tempTaken.size() + 1];
    copy(tempTaken.begin(), tempTaken.end(), fix);
    fix[tempTaken.size()] = '\0';
    addr = strtoul(fix, NULL, 0);
    
    getline(stream, tempTaken, ' ');
    if (prediction[addr%tableSize] == 'A'){
      if (tempTaken == "NT")
	counter++;
      else prediction[addr%tableSize]++;
    }else if (prediction[addr%tableSize] == 'B'){
      if (tempTaken == "NT"){
	counter++;
	prediction[addr%tableSize]--;
      }else prediction[addr%tableSize]++;
    }else if (prediction[addr%tableSize] == 'C'){
      if (tempTaken == "T"){
	counter++;
	prediction[addr%tableSize]++;
      }else prediction[addr%tableSize]--;
    }else{
      if (tempTaken == "T")
	counter++;
      else prediction[addr%tableSize]--;
    }
  }
  ret = (to_string(counter)) + "," + (to_string(lines)) + "; ";
  f.close();
  return ret;
  //out.close();
}

string Predictor::gShare(int historyLength){
  char prediction[2048];
  for (int i = 0; i < 2048; i++){
    prediction[i] = 'D';
  }
  ifstream f(fileName);
  if (f.fail()){
    cout << "File not found" << endl;
    return "";
  }
  //ofstream output(outFile);
  string ret;
  //ofstream out(outFile);
  int lines = 0;
  stringstream stream;
  unsigned long addr;
  string tempTaken;
  string data;
  int counter = 0;
  char* fix;
  int index = 0;
  int history = 0;
  int bitamt = 1;
  for (int i = 0; i < historyLength; i++){
  	bitamt *= 2;
  }

  for (getline(f, data, '\n'); data != ""; getline(f, data, '\n')){
  	lines++;
    stream = stringstream(data);
    
    getline(stream, tempTaken, ' ');
    fix = new char[tempTaken.size() + 1];
    copy(tempTaken.begin(), tempTaken.end(), fix);
    fix[tempTaken.size()] = '\0';
    addr = strtoul(fix, NULL, 0);
    
    index = addr%2048;
    history = history%bitamt;
    index = index ^ history;
    
    getline(stream, tempTaken, ' ');
    if (prediction[index] == 'A'){
      if (tempTaken == "NT")
		counter++;
      else prediction[index]++;
    }else if (prediction[index] == 'B'){
      if (tempTaken == "NT"){
		counter++;
		prediction[index]--;
      }else prediction[index]++;
    }else if (prediction[index] == 'C'){
      if (tempTaken == "T"){
		counter++;
		prediction[index]++;
      }else prediction[index]--;
    }else{
      if (tempTaken == "T")
		counter++;
      else prediction[index]--;
    }
    if (tempTaken == "T"){
      history <<= 1;
      history += 1;
    }else
      history <<= 1;
  }
  ret = (to_string(counter)) + "," + (to_string(lines)) + "; ";
  f.close();
  return ret;
  //out.close();
}

string Predictor::tournament(){
	ifstream f(fileName);
  	if (f.fail()){
    	cout << "File not found" << endl;
    	return "";
  	}
  	string ret;
  	//ofstream output(outFile);
  	//ofstream out(outFile);
  	int lines = 0;
  	stringstream stream;
  	string tempTaken;
  	string data;
  	int counter = 0;
  	unsigned long addr;
	char* fix;
  
  	//For bimodal
  	int tableSize = 2048;
  	char prediction[2048];
  	for (int i = 0; i < 2048; i++){
  		prediction[i] = 'D';
  	}
  	//For gshare
  	int index;
  	int history = 0;
  	char gprediction[2048];
  	for (int i = 0; i < 2048; i++){
  		gprediction[i] = 'D';
  	}

  	//overall choice
  	char selector[2048];
  	for (int i = 0; i < 2048; i++){
  		selector[i] = 'D';
  	}
  	/*
	A = BB
	B = BG
	C = GB
	D = GG
  	*/
	for (getline(f, data, '\n'); data != ""; getline(f, data, '\n')){
		lines++;
		stream = stringstream(data);
		getline(stream, tempTaken, ' ');
    	fix = new char[tempTaken.size() + 1];
	    copy(tempTaken.begin(), tempTaken.end(), fix);
	    fix[tempTaken.size()] = '\0';
	    addr = strtoul(fix, NULL, 0);

    	index = addr%2048;
    	history = history%2048;
    	index = index ^ history;

    	getline(stream, tempTaken, ' ');

    	if (selector[addr%tableSize] == 'A' || selector[addr%tableSize] == 'B'){
    		if (tempTaken == "T"){
    			if ((prediction[addr%tableSize] == 'C') || (prediction[addr%tableSize] == 'D')){
    				counter++;
    			}
    		}else{
    			if ((prediction[addr%tableSize] == 'A') || (prediction[addr%tableSize] == 'B')){
    				counter++;
    			}
    		}
    	}else{
    		if (tempTaken == "NT"){
    			if ((gprediction[index] == 'A') || (gprediction[index] == 'B')){
    				counter++;
    			}
    		}else{
    			if ((gprediction[index] == 'C') || (gprediction[index] == 'D')){
    				counter++;
    			}
    		}
    	}
		
		if ((gprediction[index] == 'A') || (gprediction[index] == 'B')){
			if ((prediction[addr%tableSize] == 'C') || (prediction[addr%tableSize] == 'D')){
				if (tempTaken == "T"){ //bi right gshare wrong
					if (selector[addr%tableSize] != 'A')
						selector[addr%tableSize]--;
				}else{ //bi wrong gshare right
					if (selector[addr%tableSize] != 'D')
						selector[addr%tableSize]++;
				}
			}
		}else if((gprediction[index] == 'C') || (gprediction[index] == 'D')){
			if ((prediction[addr%tableSize] == 'A') || (prediction[addr%tableSize] == 'B')){
				if (tempTaken == "T"){
					if (selector[addr%tableSize] != 'D')
						selector[addr%tableSize]++;
				}else{
					if (selector[addr%tableSize] != 'A')
						selector[addr%tableSize]--;
				}
			}
		}

		if (prediction[addr%tableSize] == 'A'){
	      if (tempTaken != "NT")
	      	prediction[addr%tableSize]++;
	    }else if (prediction[addr%tableSize] == 'B'){
	      if (tempTaken == "NT"){
			prediction[addr%tableSize]--;
	      }else prediction[addr%tableSize]++;
	    }else if (prediction[addr%tableSize] == 'C'){
	      if (tempTaken == "T"){
			prediction[addr%tableSize]++;
	      }else prediction[addr%tableSize]--;
	    }else{
	      if (tempTaken != "T")
	      	prediction[addr%tableSize]--;
	    }

    	if (gprediction[index] == 'A'){
	      if (tempTaken != "NT")
	    	gprediction[index]++;
	    }else if (gprediction[index] == 'B'){
	      if (tempTaken == "NT"){
			gprediction[index]--;
	      }else gprediction[index]++;
	    }else if (gprediction[index] == 'C'){
	      if (tempTaken == "T"){
			gprediction[index]++;
	      }else gprediction[index]--;
	    }else{
	      if (tempTaken != "T")
	      	gprediction[index]--;
	    }
	    if (tempTaken == "T"){
	      history <<= 1;
	      history += 1;
	    }else
	      history <<= 1;
  	}
  	ret = to_string(counter) + "," + to_string(lines) + "; ";
  	f.close();
  	return ret;
  	//out.close();
}