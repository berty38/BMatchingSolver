/*
 * IntSet.cpp
 *
 *  Created on: Dec 3, 2010
 *      Author: bert
 */

#include "IntSet.h"
#include <iostream>
using namespace std;

IntSet::IntSet() {
	init(31);
}

IntSet::~IntSet() {
	delete[](table);
	delete[](filled);
}

IntSet::IntSet(int capacity) {
	init(capacity);
}

void IntSet::init(int capacity) {
	//cout << "initializing table of size " << capacity << endl;
	tableSize = capacity;
	table = new int[capacity];
	filled = new bool[capacity];
	fill(filled, filled+capacity, false);
	size = 0;
}

bool IntSet::find(int x) {
	if (tableSize == 0)
		return false;
	int index = (hash_function(x) % tableSize + tableSize) % tableSize;
	int c = 0;
	while (filled[index] && table[index] != x) {
		index = ((index + c*c) % tableSize + tableSize) % tableSize;
		c++;
	}
	if (filled[index] && table[index] == x)
		return true;
	return false;
}

bool IntSet::insert(int x) {
	if (2*(size+1) > tableSize)
		rehash(2*tableSize);

	int index = (hash_function(x) % tableSize + tableSize) % tableSize;
	int c = 0;
	while (filled[index] && table[index] != x) {
		index = ((index + c*c) % tableSize + tableSize) % tableSize;
		c++;
	}
	if (filled[index] && table[index] == x)
		return false;
	table[index] = x;
	filled[index] = true;
	size++;
	return true;
}

int IntSet::getSize() {
	return size;
}

int IntSet::hash_function(int x) {
	return x;
}

void IntSet::rehash(int capacity) {
	int * oldTable = table;
	bool * oldFilled = filled;
	int oldTableSize = tableSize;

	table = new int[capacity];
	filled = new bool[capacity];
	memset(filled, false, capacity * sizeof(bool));
	tableSize = capacity;
	size = 0;

	for (int i = 0; i < oldTableSize; i++)
		if (oldFilled[i])
			insert(oldTable[i]);

	delete[](oldFilled);
	delete[](oldTable);
}
