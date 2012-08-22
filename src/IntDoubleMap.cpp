/*
 * IntDoubleMap.cpp
 *
 *  Created on: Dec 3, 2010
 *      Author: bert
 */

#include "IntDoubleMap.h"
#include <iostream>
using namespace std;

IntDoubleMap::~IntDoubleMap() {
	delete[](table);
	delete[](filled);
	delete[](value);
	pthread_mutex_destroy(&tableMutex);
	pthread_mutex_destroy(&counterMutex);
}

IntDoubleMap::IntDoubleMap(int capacity) {
	init(capacity);
	pthread_mutex_init(&tableMutex, NULL);
	pthread_mutex_init(&counterMutex, NULL);
	hits = 0;
	misses = 0;
}

void IntDoubleMap::init(int capacity) {
	//cout << "initializing table of size " << capacity << endl;
	tableSize = capacity;
	table = new int[capacity];
	value = new double[capacity];
	filled = new bool[capacity];
	fill(filled, filled+capacity, false);
	size = 0;
}

bool IntDoubleMap::find(int x, double * y) {
	if (tableSize == 0) {
		pthread_mutex_lock(&counterMutex);
		misses += 1.0;
		pthread_mutex_unlock(&counterMutex);
		return false;
	}
	int index = getIndex(x);
	if (filled[index] && table[index] == x) {
		*y = value[index];
		pthread_mutex_lock(&counterMutex);
		hits += 1.0;
		pthread_mutex_unlock(&counterMutex);
		return true;
	}
	pthread_mutex_lock(&counterMutex);
	misses += 1.0;
	pthread_mutex_unlock(&counterMutex);
	return false;
}

void IntDoubleMap::insert(int x, double y) {
	pthread_mutex_lock(&tableMutex);
	insertHelper(x, y);
	pthread_mutex_unlock(&tableMutex);
}

int IntDoubleMap::insertHelper(int x, double y) {
	int index = getIndex(x);
	if (table[index] != x || !filled[index])
		size++;
	table[index] = x;
	filled[index] = true;
	value[index] = y;
	return index;
}

int IntDoubleMap::getSize() {
	return size;
}

double IntDoubleMap::getHits() {
	return hits;
}

double IntDoubleMap::getMisses() {
	return misses;
}

int IntDoubleMap::hash_function(int x) {
	return x;
}

int IntDoubleMap::getIndex(int x) {
	int index = (hash_function(x) % tableSize + tableSize) % tableSize;
	return index;
}
