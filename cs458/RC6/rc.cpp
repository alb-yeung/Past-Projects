#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <math.h>

#define P32 0xb7e15163
#define Q32 0x9e3779b9

using namespace std;

int64_t mod = pow(2, 32);

/*
	why does or'ing work but adding the values not work?
*/
unsigned int rotateLeft (unsigned int val, int amt){
	if (amt == 0) return val;
	return ((val << amt)%mod) | (val >> (32 - amt));
}

unsigned int rotateRight (unsigned int val, int amt){
	if (amt == 0) return val;
	return ((val >> amt)%mod) | (val << (32 - amt));
}

unsigned int* keySchedule(int* key){
	unsigned int* L = new unsigned int[4];
	for(int i = 0; i < 4; i++){
		L[i] = key[8*i] << 4;
		L[i] += key[8*i + 1];
		L[i] += key[8*i + 2] << 12;
		L[i] += key[8*i + 3] << 8;
		L[i] += key[8*i + 4] << 20;
		L[i] += key[8*i + 5] << 16;
		L[i] += key[8*i + 6] << 28;
		L[i] += key[8*i + 7] << 24;
	}
	unsigned int* S = new unsigned int[44];
	S[0] = P32;
	for(int i = 1; i < 44; i++){
		S[i] = (S[i-1] + Q32)%mod;
	}
	unsigned int A, B;
	int i, j, v;
	A = B = i = j = 0;
	v = 3*44;
	for (int s = 1; s < v + 1; s++){
		A = S[i] = rotateLeft((S[i] + A + B)%mod, 3);
		B = L[j] = rotateLeft((L[j] + A + B)%mod, (A+B)%32);
		i = (i+1)%44;
		j = (j+1)%4;
	}
	return S;
}

int* unbyte(unsigned int* plaintext){
	int* ret = new int[32];
	for (int i = 0; i < 4; i++){
		ret[8*i]     = (plaintext[i]&(0x000000f0)) >> 4;
		ret[8*i + 1] = (plaintext[i]&(0x0000000f));
		ret[8*i + 2] = (plaintext[i]&(0x0000f000)) >> 12;
		ret[8*i + 3] = (plaintext[i]&(0x00000f00)) >> 8;
		ret[8*i + 4] = (plaintext[i]&(0x00f00000)) >> 20;
		ret[8*i + 5] = (plaintext[i]&(0x000f0000)) >> 16;
		ret[8*i + 6] = (plaintext[i]&(0xf0000000)) >> 28;
		ret[8*i + 7] = (plaintext[i]&(0x0f000000)) >> 24;
	}
	return ret;
}

int* encrypt(int* text, int* key){
	unsigned int* S = keySchedule(key);
	unsigned int* plaintext = new unsigned int[4];
	for (int i = 0; i < 4; i++){
		plaintext[i] = text[8*i] << 4;
		plaintext[i] += text[8*i + 1];
		plaintext[i] += text[8*i + 2] << 12;
		plaintext[i] += text[8*i + 3] << 8;
		plaintext[i] += text[8*i + 4] << 20;
		plaintext[i] += text[8*i + 5] << 16;
		plaintext[i] += text[8*i + 6] << 28;
		plaintext[i] += text[8*i + 7] << 24;
	}

	unsigned int t, u;
	plaintext[1] += S[0];																					//B = B + S[0]
	plaintext[3] += S[1];																					//D = D + S[1]
	for(int i = 1; i < 21; i++){																			//for i = 1 to r do
		t = plaintext[1] * (((2 * plaintext[1]) + 1));														//t = (B * (2B+1))
		t = rotateLeft(t, 5);																					    //<<< 5 = lg(32)
		u = plaintext[3] * (((2 * plaintext[3]) + 1));														//u = (D * (2D+1))
		u = rotateLeft(u, 5);
		plaintext[0] = rotateLeft(plaintext[0] ^ t, u%32) + S[2*i];
		plaintext[2] = rotateLeft(plaintext[2] ^ u, t%32) + S[2*i + 1];
		unsigned int temp = plaintext[0];
		plaintext[0] = plaintext[1];
		plaintext[1] = plaintext[2];
		plaintext[2] = plaintext[3];
		plaintext[3] = temp;
	}
	plaintext[0] += S[42];
	plaintext[2] += S[43];
	return unbyte(plaintext);
}

/*
	called plaintext instead of cipher cuz i copy pasted from encrypt and didnt want to change
*/
int* decrypt(int* text, int* key){
	unsigned int* S = keySchedule(key);
	unsigned int* plaintext = new unsigned int[4];
	for (int i = 0; i < 4; i++){
		plaintext[i] = text[8*i] << 4;
		plaintext[i] += text[8*i + 1];
		plaintext[i] += text[8*i + 2] << 12;
		plaintext[i] += text[8*i + 3] << 8;
		plaintext[i] += text[8*i + 4] << 20;
		plaintext[i] += text[8*i + 5] << 16;
		plaintext[i] += text[8*i + 6] << 28;
		plaintext[i] += text[8*i + 7] << 24;
	}

	unsigned int t, u;
	plaintext[2] -= S[43];
	plaintext[0] -= S[42];
	for(int i = 20; i > 0; i--){
		unsigned int temp = plaintext[3];
		plaintext[3] = plaintext[2];
		plaintext[2] = plaintext[1];
		plaintext[1] = plaintext[0];
		plaintext[0] = temp;
		u = rotateLeft((plaintext[3] * ((plaintext[3] * 2) + 1)), 5);
		t = rotateLeft((plaintext[1] * ((plaintext[1] * 2) + 1)), 5);
		plaintext[2] = rotateRight(plaintext[2] - S[2*i + 1], t%32) ^ u;
		plaintext[0] = rotateRight(plaintext[0] - S[2*i], u%32) ^ t;
	}
	plaintext[3] -= S[1];
	plaintext[1] -= S[0];
	return unbyte(plaintext);
}

void run(string input, string output){
	ifstream in (input);
	ofstream out (output);
	string line;
	getline(in, line);
	if (line[0] == 'E'){
		cout << "Doing encryption" << endl;
		getline(in, line);
		line = line.substr(10);
		int* plaintext = new int[32];
		for(int i = 0; i < 16; i++){
			plaintext[i*2] = stoi(line.substr(i*3 + 1, 1), 0, 16);
			plaintext[i*2 + 1] = stoi(line.substr(i*3 + 2, 1), 0, 16);
		}
		getline(in, line);
		line = line.substr(8);
		int* key = new int[32];
		for(int i = 0; i < 16; i++){
			key[i*2] = stoi(line.substr(i*3 + 1, 1), 0, 16);
			key[i*2 + 1] = stoi(line.substr(i*3 + 2, 1), 0, 16);
		}
		int* cipher = encrypt(plaintext, key);
		out << "ciphertext: ";
		for(int i = 0; i < 16; i++){
			out << hex << cipher[i*2];
			out << hex << cipher[i*2 + 1];
			out << " ";
		}
		out << "\n";
	}else if (line[0] == 'D'){
		cout << "Doing decryption" << endl;
		getline(in, line);
		line = line.substr(11);
		int* plaintext = new int[32];
		for(int i = 0; i < 16; i++){
			plaintext[i*2] = stoi(line.substr(i*3 + 1, 1), 0, 16);
			plaintext[i*2 + 1] = stoi(line.substr(i*3 + 2, 1), 0, 16);
		}
		getline(in, line);
		line = line.substr(8);
		int* key = new int[32];
		for(int i = 0; i < 16; i++){
			key[i*2] = stoi(line.substr(i*3 + 1, 1), 0, 16);
			key[i*2 + 1] = stoi(line.substr(i*3 + 2, 1), 0, 16);
		}
		int* cipher = decrypt(plaintext, key);
		out << "plaintext: ";
		for(int i = 0; i < 16; i++){
			out << hex << cipher[i*2];
			out << hex << cipher[i*2 + 1];
			out << " ";
		}
		out << "\n";
	}else{
		cout << "Input not proper" << endl;
		in.close();
		out.close();
		return;
	}
	in.close();
	out.close();
}

int main(int argc, char*argv[]){
	if (argc != 3){
		cout << "Please supply an input and output file in \n./run <input-file> <output-file> \n";
		return 0;
	}
	run(argv[1], argv[2]);
	return 0;
}