/*
 * IndexHeap.cpp
 *
 *  Created on: Jan 29, 2011
 *      Author: bert
 */

#include "IndexHeap.h"
#include <limits.h>
#include <math.h>
#include <iostream>

using namespace std;

IndexHeap::IndexHeap() {
}

IndexHeap::IndexHeap(int cap) {
	capacity = cap;
	size = 0;
	keys = new long double[cap];
	vals = new int[cap];
}

IndexHeap::~IndexHeap() {
	// do nothing. it's the user's responsibility to delete the arrays... for now
}

void IndexHeap::insert(long double key, int value) {
	//cout << "Inserting " << key << " size " << size << endl;
	if (size > 0 && key < keys[0])
		return;
	if (size == capacity || size == 0) {
		keys[0] = key;
		vals[0] = value;
		//cout << "keys[0] " << keys[0] << endl;
		percDown(0);
		//cout << "keys[0] " << keys[0] << " after percdown" << endl;
		if (size == 0)
			size ++;
	} else {
		keys[size] = key;
		vals[size] = value;
		size++;
		percUp(size-1);
	}
}

void IndexHeap::deleteMin() {
	swap(0, size-1);
	size--;
	percDown(0);
}

long double IndexHeap::minKey() {
	if (size > 0)
		return keys[0];
	else
		return INFINITY;
}

int IndexHeap::minVal() {
	return vals[0];
}

long double *IndexHeap::getDoubleArray() {
	return keys;
}

int *IndexHeap::getIntArray() {
	return vals;
}

void IndexHeap::percDown(int i) {
	//cout << "percDown size " << size << " index " << i << endl;
	if (i < size) {
		int li = leftChild(i);
		int ri = rightChild(i);
		long double left = -INFINITY, right = -INFINITY;
		if (li < size)
			left = keys[li];
		if (ri < size)
			right = keys[ri];

		if (li >= size && ri >= size)
			return;

		if (keys[i] > left || keys[i] > right) {
			if (left < right || (left < keys[i] && ri >= size)) {
				swap(i, li);
				percDown(li);
			} else if (ri < size) {
				swap(i, ri);
				percDown(ri);
			}
		}
	}
}

void IndexHeap::percUp(int i) {
	if (i > 0) {
		int pi = parent(i);
		if (keys[i] > keys[pi]) {
			swap(i, pi);
			percUp(pi);
		}
	}
}

int IndexHeap::parent(int i) {
	return (i+1) / 2 - 1;
}

int IndexHeap::leftChild(int i) {
	return (i+1) * 2 - 1;
}

int IndexHeap::rightChild(int i) {
	return (i+1) * 2;
}

void IndexHeap::swap(int i, int j) {
	//cout << "Swapping " << i << " and " << j << endl;
	long double tmpd = keys[i];
	int tmpi = vals[i];
	keys[i] = keys[j];
	vals[i] = vals[j];
	keys[j] = tmpd;
	vals[j] = tmpi;
}





