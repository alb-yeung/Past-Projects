#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int vertices;
int edges;
int** matrix;
int** colors;

/*
	readIn reads in the graph from a file and stores it in the matrix.
*/
void readIn(string name){
	ifstream f(name);
	if (f.fail()){
		cout << "File not found" << endl;
    	return;
	}
	string data;
	getline(f, data, '\n');
	vertices = stoi(data);
	matrix = new int*[vertices];
	//cout << "1" << endl;
	for (int i = 0; i < vertices; i++){
		matrix[i] = new int[vertices];
	}
	//cout << "2" << endl;
	/*
	for (int i = 0; i < vertices; i++){
		for (int j = 0; j < vertices; j++)
			matrix[i][j] = numeric_limits<int>::max();
	}
	*/
	int v1;
	int v2;
	int weight;
	getline(f, data, '\n');
	edges = stoi(data);
	for (int i = 0; i < edges; i++){
		getline(f, data, ' ');
		v1 = stoi(data);
		getline(f, data, ' ');
		v2 = stoi(data);
		getline(f, data, '\n');
		weight = stoi(data);
		//cout << "v1 - " << v1 << " v2 - " << v2 << " weight - " << weight << endl;
		matrix[v1][v2] = weight;
		matrix[v2][v1] = weight;
	}
	
	for (int i = 0; i < vertices; i++){
		for (int j = 0; j < vertices; j++){
			cout << matrix[i][j] << ", ";
		}
		cout << endl;
	}
	
		
	cout << endl;
}

/*
	DisjointSet is my implementation of a disjoint set.
	It checks if the two vertices of an edge are already in the same set.
*/
class DisjointSet{
public:
	int** sets;
	int numSets;
	int maxSets;
	int* last;
	/*
		Simple constructor
	*/
	DisjointSet(int n){
		sets = new int*[n];
		last = new int[n];
		numSets = 0;
		for (int i = 0; i < n; i++){
			sets[i] = new int[n];
			last[i] = 0;
		}
		maxSets = n;
	}
	/*
		add checks if two vertices are already in the same set, and returns false if they are.
		Otherwise it adds the one extra vertex to a disjoint set or creates a new set with both vertices.
	*/
	bool add(int v1, int v2){
		if (numSets == 0){
			sets[0][0] = v1;
			sets[0][1] = v2;
			last[0] += 2;
			numSets++;
			return false;
		}
		int inFlag1 = 0;
		int inFlag2 = 0;
		for (int i = 0; i < numSets; i++){
			inFlag1 = 0;
			inFlag2 = 0;
			for (int j = 0; j < last[i]; j++){
				if (sets[i][j] == v1)
					inFlag1 = 1;
				if (sets[i][j] == v2)
					inFlag2 = 1;
			}
			if (inFlag1 == 1 && inFlag2 == 1){
				return true;
			}
			if (inFlag1 == 1){
				sets[i][last[i]] = v2;
				last[i]++;
			}else if (inFlag2 == 1){
				sets[i][last[i]] = v1;
				last[i]++;
			}
		}
		if (inFlag1 == 0 && inFlag2 == 0){
			sets[numSets][0] = v1;
			sets[numSets][1] = v2;
			last[numSets] += 2;
			numSets++;
		}
		return false;
	}
};

/*
	kruskals runs the algorithm from the data that was read in from readIn
*/
int kruskals(){
	int* v1 = new int[edges];
	int* v2 = new int[edges];
	//cout << "~" << endl;
	DisjointSet ds = DisjointSet(vertices);
	int next = 0;
	//cout << "!" << endl;
	for (int i = 0; i < vertices; i++){
		for (int j = i + 1; j < vertices; j++){
			if (matrix[i][j] != 0){
				v1[next] = i;
				v2[next] = j;
				next++;
			}
		}
	}
	//cout << "@" << endl;
	for (int i = 0; i < edges; i++){
		for (int j = 0; j < edges - 1; j++){
			if (v1[j] >= 0 && v2[j] >= 0){
				if (matrix[v1[j]][v2[j]] > matrix[v1[j+1]][v2[j+1]]){
					int tmp = v1[j];
					int tmp2 = v2[j];
					v1[j] = v1[j+1];
					v2[j] = v2[j+1];
					v1[j+1] = tmp;
					v2[j+1] = tmp2;
				}
			}
		}
	}
	/*
	for (int i = 0; i < edges; i++){
		cout << v1[i] << " " << v2[i] << " " << matrix[v1[i]][v2[i]] << endl;
	}
	*/
	cout << endl;

	int* addedVertices = new int[vertices-1];
	int addedNext = 0;

	for (int i = 0; i < edges; i++){
		if (v1[i] != v2[i]){
			if (ds.add(v1[i],v2[i])){
				continue;
			}else{
				addedVertices[addedNext] = i;
				addedNext++;
			}
		}
	}

	int sum = 0;
	for (int i = 0; i < vertices-1; i++){
		sum += matrix[v1[addedVertices[i]]][v2[addedVertices[i]]];
		cout << v1[addedVertices[i]] << " " << v2[addedVertices[i]] << " " << matrix[v1[addedVertices[i]]][v2[addedVertices[i]]] << endl;
	}
	cout << "Minimum spanning tree weight - " << sum << endl;
	return 0;
}

/*
	simple main function to call readIn and kruskals
*/
int main(int argc, char* argv[]){
	if (argc != 2){
		cout << "Use an input file" << endl;
		return 0;
	}
	readIn(argv[1]);
	kruskals();
}
