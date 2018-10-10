#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <bits/stdc++.h>
#include <vector>
//#include <algorithm>
//#include "timeProg.h"
//#include <unistd.h>

using namespace std;

/*
	Item is a simple class to hold the different items, their weights profits and ratios.
*/
class Item{
public:
	int weight;
	int profit;
	int ratio;
	Item(int w, int p){
		weight = w;
		profit = p;
		ratio = p/w;
	}
	Item(string w, string p){
		weight = stoi(w);
		profit = stoi(p);
		ratio = profit/weight;
	}
	Item(){
		weight = 0;
		profit = 0;
		ratio = 0;
	}
	/*
		These operators are overwritten to make comparing Items easier
	*/
	bool operator< (const Item& other){
		return ratio < other.ratio;
	}
	bool operator> (const Item& other){
		return ratio > other.ratio;
	}
};

/*
	ItemList is a class to mainly hold an array of Items.
*/
class ItemList{
public:
	int items;
	int size;
	//int currItem;
	Item* list;
	//vector<Item> list;
	ItemList(int i){
		items = i;
		//currItem = 0;
		size = 0;
		list = new Item[items];
		//list = vector<Item>();
	}
	ItemList(){
		items = 0;
		//list = 0;
		//currItem = 0;
	}
	/*
		add adds an Item to the list
	*/
	void add(string w, string p){
		list[size] = Item(w, p);
		//list.push_back(Item(w, p));
		size++;
	}

	/*
		print is just for testing
	*/
	void print(){
		for (int i = 0; i < size; i++){
			cout << list[i].weight << ";" << list[i].profit << ";" << list[i].ratio << endl;
		}
		cout << endl;
	}
	
	/*
		sortArr uses a bubble sort to sort the list
	*/
	void sortArr(){
		for (int i = 0; i < size; i++){
			for (int j = 0; j < size - 1; j++){
				if (list[j] < list[j+1]){
					Item temp = list[j];
					list[j] = list[j+1];
					list[j+1] = temp;
				}
			}
		}
	}

	/*
		getItem get's the indexth item of the array
	*/
	Item getItem(int index){
		return list[index];
	}
	
	/*
		calcBound calculates the current bound from a certain item
	*/
	int calcBound(int curr, int maxWeight, int currWeight, int currProfit){
		int bound = currProfit;
		for (int i = curr; i < size; i++){
			if (maxWeight < list[i].weight + currWeight){
				bound += ((maxWeight-currWeight)*list[i].profit)/list[i].weight;
				break;
			}else{
				bound += list[i].profit;
				currWeight += list[i].weight;
			}
		}
		return bound;
	}
};

/*
	TreeNode is a class to hold nodes for the Priority Queue Heap
*/
class TreeNode{
public:
	int currWeight;
	int currProfit;
	int capacity;
	int currMaxPossible;
	int currItem;
	int posInTree;
	ItemList list;
	/*
		Simple constructors
	*/
	TreeNode(int w, int p, int cap, int c, ItemList l, int pos){
		currWeight = w;
		currProfit = p;
		capacity = cap;
		currItem = c;
		list = l;
		posInTree = pos;
		calcBound();
	}
	TreeNode(){
		currWeight = 0;
		currProfit = 0;
		capacity = 0;
		currItem = 0;
	}
	
	/*
		calls calcBound of the list of items
	*/
	void calcBound(){
		currMaxPossible = list.calcBound(currItem + 1, capacity, currWeight, currProfit);
	}
	
	/*
		These functions are just for ease of comparison
	*/
	bool operator< (const TreeNode& other){
		return currMaxPossible < other.currMaxPossible;
	}
	bool operator> (const TreeNode& other){
		return currMaxPossible > other.currMaxPossible;
	}
};

/*
	PriorityQueue is a max heap used as a priority queue to search the nodes in the right order
*/
class PriorityQueue{
public:
	int items;
	int size;
	int bestSoFar = 0;
	int bestPos = 0;
	int capacity;
	int checked = 1;
	int leafs = 0;
	TreeNode* heap;
	ItemList listOfItems;
	/*
		Simple constructors
	*/	
	PriorityQueue(int i, int c, ItemList list){
		items = i;
		capacity = c;
		size = 0;
		listOfItems = list;
		heap = new TreeNode[items];
	}
	PriorityQueue(){
		items = 0;
		heap = 0;
	}

	/*
		heapifyUp keeps the heap structure from the bottom up when given an index
	*/
	void heapifyUp(int index){
		if (heap[index] > heap[index/2]){
			TreeNode temp = heap[index];
			heap[index] = heap[index/2];
			heap[index/2] = temp;
			heapifyUp(index/2);
		}
	}

	/*
		heapifyDown keeps the heap structure from the top down when given an index
	*/
	void heapifyDown(int index){
		if (index >= size || index*2 + 1 > size-1){
			return;
		}
		if (index * 2 + 2 > size-1){
			if (heap[index*2 + 1] > heap[index]){
				TreeNode temp = heap[index];
				heap[index] = heap[index * 2 + 1];
				heap[index * 2 + 1] = temp;
				heapifyDown(index*2 + 1);
			}
		}else{
			if (heap[index*2 + 1] > heap[index*2 + 2]){
				if (heap[index*2 + 1] > heap[index]){
					TreeNode temp = heap[index];
					heap[index] = heap[index * 2 + 1];
					heap[index * 2 + 1] = temp;
					heapifyDown(index*2 + 1);
				}
			}else{
				if (heap[index*2 + 2] > heap[index]){
					TreeNode temp = heap[index];
					heap[index] = heap[index * 2 + 2];
					heap[index * 2 + 2] = temp;
					heapifyDown(index*2 + 2);
				}
			}
		}
	}


	/*
		feasible checks whether a node is feasible enough to check its children
	*/
	bool feasible(){
		checked++;
		//cout << checked << " " << heap[0].currWeight << " " << heap[0].currProfit << " " << heap[0].currMaxPossible << endl;
		if (heap[0].currWeight > capacity){
			//cout << "weight > capacity" << endl;
			//dequeue();
			return false;
		}
		if (heap[0].currItem >= listOfItems.size - 1){
			if (heap[0].currProfit > bestSoFar){
				bestSoFar = heap[0].currProfit;
				bestPos = heap[0].posInTree;
			}
			return false;
		}
		if (heap[0].currMaxPossible < bestSoFar){
			//cout << "bound < best so far" << endl;
			//dequeue();
			return false;
		}
		if (heap[0].currProfit > bestSoFar){
			bestSoFar = heap[0].currProfit;
			bestPos = heap[0].posInTree;
			return true;
		}
		return true;
	}

	/*
		run is the "main" function of the PriorityQueue class
	*/
	void run(string out){
		add(listOfItems.getItem(0).weight, listOfItems.getItem(0).profit, capacity, 0, 1);
		add(0, 0, capacity, 0, 2);
		while(size > 0){
			if (feasible()){
				dequeue();
				checkChildren(size, listOfItems.getItem(heap[size].currItem + 1));
			}else{
				leafs++;
				dequeue();
			}
		}
		//cout << checked << endl;
		//cout << bestPos << endl;
		//cout << "Best: " << bestSoFar << endl;
		ofstream o(out);
		int included = 0;		//included, tmp, includedItems and includedIndex is to calculate the individual items taken
		int tmp = bestPos;
		while (tmp > 0){
			if (tmp == 1){
				included++;
				tmp = 0;
			}else if(tmp == 2){
				tmp = 0;
			}else if(tmp % 2 == 1){
				included++;
				tmp = (tmp-1)/2;
			}else{
				tmp = (tmp-2)/2;
			}
		}
		int* includedItems = new int[included];
		int includedIndex = included - 1;
		tmp = bestPos;
		while (tmp > 0){
			if (tmp == 1){
				includedItems[0] = 0;
				tmp = 0;
			}else if(tmp == 2){
				tmp = 0;
			}else if(tmp % 2 == 1){
				includedItems[includedIndex] = (int)floor(log2(tmp)) - 1;
				includedIndex--;
				tmp = (tmp-1)/2;
			}else{
				tmp = (tmp-2)/2;
			}
		}
		o << items << "," << bestSoFar << "," << included << endl;
		o << checked << "," << leafs << endl;
		
		for(int i = 0; i < included; i++){
			o << listOfItems.getItem(includedItems[i]).weight << "," << listOfItems.getItem(includedItems[i]).profit << endl;
		}
		
		o.close();
	}

	/*
		checkChildren assumes that this is only called on feasible nodes
		it first adds the left child to the queue
		and then it adds the right child to the queue
	*/	
	void checkChildren(int index, Item nextItem){
		//checkandaddleft
		int itemNum = heap[index].currItem + 1;
		int tCurrWeight = heap[index].currWeight;
		int tCurrProfit = heap[index].currProfit;
		int tCurrPos = heap[index].posInTree;
		//cout << "\t\t" << heap[index].currWeight << " " << heap[index].currProfit << " " << heap[index].currItem << " " << heap[index].currMaxPossible << endl;
		add (listOfItems.getItem(itemNum).weight + heap[index].currWeight, listOfItems.getItem(itemNum).profit + heap[index].currProfit, capacity, itemNum, heap[index].posInTree * 2 + 1);
		//checkandaddright
		add (tCurrWeight, tCurrProfit, capacity, itemNum, tCurrPos * 2 + 2);
	}


	/*
		add adds a node to the queue
	*/
	void add(int w, int p, int m, int c, int pos){
		heap[size] = TreeNode(w, p, m, c, listOfItems, pos);
		heapifyUp(size);
		size++;
	}
	/*
		dequeue moves the top node to the end of the queue and shrinks the heap by one
	*/
	void dequeue(){
		if (size <= 0){
			cout << "no items in queue" << endl;
			return;
			//return heap[0];
		}
		if (size == 1){
			size--;
			return;
			//return heap[0];
		}
		TreeNode temp = heap[0];
		size--;
		heap[0] = heap[size];
		heap[size] = temp;
		heapifyDown(0);
		//return heap[size];
	}

};

/*
	readIn is the function called by the main and sets up the ItemList and PriorityQueue
*/
void readIn(string in, string out){
	ifstream input(in);
	if (input.fail()){
		cout << "Input file not found" << endl;
		return;
	}
	int capacity = 0;
	int items = 0;
	string temp, temp2;
	getline(input, temp, ',');
	items = stoi(temp);
	getline(input, temp, '\n');
	capacity = stoi(temp);

	ItemList heap = ItemList(items);
	for (int i = 0; i < items; i++){
		getline(input, temp, ',');
		getline(input, temp2, '\n');
		heap.add(temp, temp2);
		//heap.print();
	}
	heap.sortArr();
	//heap.print();
	PriorityQueue q(items, capacity, heap);
	q.run(out);
	//heap.print();
	//cout << "Testing dequeue" << endl;
	//heap.dequeueTest();
	return;
}

int main(int argc, char* argv[]){
	if (argc != 3){
		cout << "Please use ./BestFirstSearch <input-file> <output-file>" << endl;
		return 1;
	}
	readIn(argv[1], argv[2]);
	return 0;
}