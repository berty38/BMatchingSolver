/*
 * WeightOracle.cpp
 *
 *  Created on: Dec 1, 2010
 *      Author: bert
 */

#include "WeightOracle.h"
#include <iostream>

using namespace utils;
using namespace std;

WeightOracle::WeightOracle() {
	indexComputed = false;
	numThreads = 6;
}

WeightOracle::~WeightOracle() {
	if (indexComputed) {
		for (int i = 0; i < indexSize; i++) {
			delete[](cache[i]);
			delete[](index[i]);
			delete(maps[i]);
		}
		delete[](index);
		delete[](cache);
		delete[](maps);
	}
}

void WeightOracle::computeIndex() {
	if (indexComputed) {
		cout << "Warning, recomputing index. This should be avoided." << endl;
		for (int i = 0; i < getSize(); i++) {
			delete[](cache[i]);
			delete[](index[i]);
			delete(maps[i]);
		}
		delete[](index);
		delete[](cache);
		delete[](maps);
	}

	// initialize weight lookup cache
	maps = new IntDoubleMap*[getSize()];
	for (int i = 0; i < getSize(); i++)
		maps[i] = new IntDoubleMap(LOOKUP_CACHE_SIZE);

	cache = new double*[getSize()];
	index = new int*[getSize()];

	indexSize = getSize();

	for (int i = 0; i < getSize(); i++) {
		cache[i] = new double[getCacheSize()];
		index[i] = new int[getCacheSize()];
	}

	if (numThreads > 1) {
		// initialize threads
		pthread_t * threads = new pthread_t[numThreads];

		for (int t = 0; t < numThreads; t++) {
			WOThreadParam * tp = new WOThreadParam;
			tp->start = t;
			tp->interval = numThreads;
			tp->size = getSize();
			tp->cacheSize = getCacheSize();
			tp->cache = cache;
			tp->index = index;
			tp->wo = this;

			pthread_create(threads + t, NULL, WOThreadedUpdateRows, tp);
		}

		for (int t = 0; t < numThreads; t++)
			pthread_join(threads[t], NULL);

		delete[](threads);
	} else {
		double * weightRow = new double[getSize()];
		int * inds = new int[getSize()];
		for (int i = 0; i < getSize(); ++i) {
			for (int j = 0; j < getSize(); ++j) {
				weightRow[j] = getWeight(i, j);
				inds[j] = j;
			}
			indexSelect(weightRow, inds, getSize(), getCacheSize());
			indexSort(weightRow, inds, getCacheSize());
			for (int j = 0; j < getCacheSize(); j++) {
				index[i][j] = inds[j];
				cache[i][j] = weightRow[j];
			}
		}
		delete[](weightRow);
		delete[](inds);
	}

	indexComputed = true;
}

double WeightOracle::getIndexedWeight(int row, int rank) {
	return cache[row][rank];
}

int WeightOracle::getWeightIndex(int row, int rank) {
	return index[row][rank];
}

int WeightOracle::getSize() {
	return 0;
}

double WeightOracle::getWeight(int row, int col) {
	double ret;
	bool hit = maps[row]->find(col, &ret);
	if (!hit) {
		ret = computeWeight(row, col);
		maps[row]->insert(col, ret);
	}
	return ret;
}

double WeightOracle::computeWeight(int row, int col) {
	return 0.0;
}

void WeightOracle::setCacheSize(int c) {
	cacheSize = c;
}

int WeightOracle::getCacheSize() {
	return cacheSize;
}

void WeightOracle::printStatsString() {
	double weightMisses = 0, weightHits = 0;
	for (int i = 0; i < getSize(); i++) {
		weightMisses += maps[i]->getMisses();
		weightHits += maps[i]->getHits();
	}
	double total = weightMisses + weightHits;
	cout << "Weight function lookups: " << total << endl;
	cout <<  weightMisses << " (" <<
			weightMisses / total << ") full, " <<
			weightHits << " (" << weightHits / total <<
			") cached" << endl;
}


void * WOThreadedUpdateRows(void * v) {
	WOThreadParam * tp = reinterpret_cast<WOThreadParam*>(v);
	double * weightRow = new double[tp->size];
	int * inds = new int[tp->size];
	for (int i = tp->start; i < tp->size; i += tp->interval) {
		for (int j = 0; j < tp->size; ++j) {
			weightRow[j] = tp->wo->computeWeight(i, j);
			inds[j] = j;
		}
		indexSelect(weightRow, inds, tp->size, tp->cacheSize);
		indexSort(weightRow, inds, tp->cacheSize);
		for (int j = 0; j < tp->cacheSize; j++) {
			tp->index[i][j] = inds[j];
			tp->cache[i][j] = weightRow[j];
		}
	}
	delete[](weightRow);
	delete[](inds);
	delete(tp);

	return NULL;
}



