/*
 * OscillationDetector.cpp
 *
 *  Created on: Dec 14, 2010
 *      Author: bert
 */

#include <math.h>
#include <iostream>
#include "OscillationDetector.h"

using namespace std;

OscillationDetector::OscillationDetector(int newLength) {
	length = newLength;
	size = 0;
	capacity = DEFAULT_CAPACITY;
	vectors = new long double*[capacity];
	for (int i = 0; i < capacity; i++)
		vectors[i] = 0;
	checkSums = new IntSet();
	warning = false;
	oscillating = false;
}

OscillationDetector::~OscillationDetector() {
	delete(checkSums);
	for (int i = 0; i < capacity; i++)
		if (vectors[i])
			delete[](vectors[i]);
	delete[](vectors);
}

/*! \brief rehashes stored states
 *
 */
void OscillationDetector::rehash() {
	long double ** oldVectors = vectors;
	capacity *= 2;
	size = 0;
	vectors = new long double*[capacity];
	for (int i = 0; i < capacity; i++)
		vectors[i] = 0;

	for (int i = 0; i < capacity / 2; i++)
		if (oldVectors[i])
			insert(hash(oldVectors[i]), oldVectors[i]);

	for (int i = 0; i < capacity / 2; i++)
		if (oldVectors[i])
			delete[](oldVectors[i]);
	delete[](oldVectors);
}


bool OscillationDetector::checkState(long double *a, long double *b) {
	long double * A = new long double[2 * length];
	memcpy(A, a, length * sizeof(long double));
	memcpy(A + length, b, length * sizeof(long double));

	int checkSum = hash(A);

	//printf("Checksum %d \n", checkSum);
//	for (int i = 0; i < length; i++)
//		cout << a[i] << " ";
//	cout << endl;

	bool newState;
	newState = checkSums->insert(checkSum);

	if (newState) {
		delete[](A);
		return false;
	}
	//cout << "Possible collision" << endl;

	// possible oscillation, check big hash table
	newState = insert(checkSum, A);

	delete[](A);

	//printf(" new state? %d \n", newState);

	if (newState)
		return false;

	if (warning) {
		oscillating = true;
		//cout << "Detected Oscillation. Exiting with solution that may not fit constraints..." << endl;
		//cout << size << " explicit states stored, " << checkSums->getSize() << " checksums stored" << endl;
		return false;
	}
	warning = true;

	return true;
}

int OscillationDetector::hash(long double * a) {
	// a should be of size 2 * length
	int val = 0;

	for (int i = 0; i < 2 * length; i++)
		val += i * (int)(a[i] * 1e6);
	return val;
}

bool OscillationDetector::insert(int checkSum, long double * a) {
	int i = quadraticProbe((checkSum % capacity + capacity) % capacity, a);
	if (vectors[i])
		return false;
	else {
		vectors[i] = new long double[2 * length];
		memcpy(vectors[i], a, 2 * length * sizeof(long double));
		size++;
		if (size > capacity / 2) {
			if (capacity > MAXIMUM_CAPACITY) {
				// reset detector
				//cout << "OscillationDetector reached maximum capacity, resetting" << endl;
				delete(checkSums);
				for (int i = 0; i < capacity; i++)
					if (vectors[i])
						delete[](vectors[i]);
				delete[](vectors);
				size = 0;
				capacity = DEFAULT_CAPACITY;
				vectors = new long double*[capacity];
				for (int i = 0; i < capacity; i++)
					vectors[i] = 0;
				checkSums = new IntSet();
			} else
				rehash();
		}
		return true;
	}
}

int OscillationDetector::quadraticProbe(int index, long double * a) {
	int i = index, c = 0;
	while(vectors[i]) {
		bool equal = true;
		for (int j = 0; j < 2 * length; j++) {
			//printf("diff[%d]: %f\n", j, fabs(a[j] - vectors[i][j]));
			if (fabs(a[j] - vectors[i][j]) > TOLERANCE) {
				equal = false;
				break;
			}
		}
		if (equal)
			break;
		i = ((i + c * c) % capacity + capacity) % capacity;
		c++;
	}
	return i;
}


