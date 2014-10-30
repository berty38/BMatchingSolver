/*
 * BeliefPropagator.cpp
 *
 *  Created on: Dec 2, 2010
 *      Author: bert
 */


#include <iostream>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include "BeliefPropagator.h"
#include "BMatchingSolution.h"
using namespace std;
using namespace utils;

BeliefPropagator::BeliefPropagator() {
	iter = 0;
	maxIter = DEFAULT_MAX_ITERS;
	converged = REQUIRED_ITERATIONS;
	lookups = 0;
#ifndef _no_oscillation_check
	detector = 0;
#endif
	numThreads = 6;
	alpha = 0;
	beta = 0;
	dontcare = 0;
	betaIndex = 0;
	colMatchCount = 0;
	weightOracle = 0;

	changex = 0.0;
	iterationTime = 0.0;
	violatedColumns = 0;
}

BeliefPropagator::~BeliefPropagator() {
	if (alpha)
		delete[](alpha);
	if (beta)
		delete[](beta);
	if (dontcare)
		delete[](dontcare);
	if (betaIndex)
		delete[](betaIndex);
	if (colMatchCount)
		delete[](colMatchCount);
#ifndef _no_oscillation_check
	if (detector)
		delete(detector);
#endif
    
	if (weightOracle && rowMatches && colMatches) {
		for (int i = 0; i < weightOracle->getSize(); i++) {
			if (rowMatches[i])
				delete[](rowMatches[i]);
			if (colMatches[i])
				delete[](colMatches[i]);
		}

		delete[](rowMatches);
		delete[](colMatches);
	}
}

int BeliefPropagator::getIteration() {
	return iter;
}

void BeliefPropagator::setMaxIter(int i) {
	maxIter = i;
}

SparseMatrix<bool> * BeliefPropagator::getEstimate() {
	int n = 0;
	int size = weightOracle->getSize();
	for (int i = 0; i < size; i++)
		n += b[i];

	int * nzRows = new int[n];
	int * nzCols = new int[n];
	bool * nz = new bool[n];

	int c = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < b[i]; j++) {
			nzRows[c] = i;
			nzCols[c] = rowMatches[i][j];
			nz[c] = true;
			c++;
		}
	}

	//SparseMatrix<bool> * ret = new SparseMatrix<bool>(nzRows, nzCols,  nz, size, size, n);
	BMatchingSolution<bool> * ret = new BMatchingSolution<bool>(nzRows, nzCols,  nz, size, size, n);
	ret->setIterations(getIteration());
	return ret;
}


void BeliefPropagator::setWeightOracle(WeightOracle * wo) {
	weightOracle = wo;
	int size = weightOracle->getSize();
	alpha = new belief_t[size];
	beta = new belief_t[size];
	betaIndex = new int[size];
	colMatchCount = new int[size];
	rowMatches = new int*[size];
	colMatches = new int*[size];

	for (int i = 0; i < size; i++)  {
		rowMatches[i] = 0;
		colMatches[i] = 0;
	}

	fill(colMatchCount, colMatchCount + size, 0);
	fill(beta, beta+size, 0);
	fill(alpha, alpha+size, 0);

#ifndef _no_oscillation_check
	detector = new OscillationDetector(size);
#endif
}

bool BeliefPropagator::checkConvergence() {
	//return false; // uncomment to test for memory leaks
#ifndef _no_oscillation_check
	if (iter < maxIter && !detector->isOscillating()) {
#else
    if (iter < maxIter) {
#endif
		int size = weightOracle->getSize();
		for (int i = 0; i < size; i++)
			if (!dontcare[i] && colMatchCount[i] != b[i]) {
				converged = REQUIRED_ITERATIONS;
				//cout << "Not converged because column " << i << " has " << colMatchCount[i] << " matches when b[i] is " << b[i] << endl;
				return false;
			}

		return (--converged <= 0);
	}
	return true;
}

void BeliefPropagator::updateBeliefs() {
	int size = weightOracle->getSize();
	// update alpha and beta
	// update rowmatches

	time_t start, end;
	time(&start);

	if (iter == 0)
		initBetas();

	belief_t * newAlpha = new belief_t[size];
	belief_t * newBeta = new belief_t[size];

	if (numThreads > 1) {
		// initialize threads
		threads = new pthread_t[numThreads];

		for (int t = 0; t < numThreads; t++) {
			threadParam * tp = new threadParam;
			tp->start = t;
			tp->size = size;
			tp->interval = numThreads;
			tp->newAlpha = newAlpha;
			tp->newBeta = newBeta;
			tp->bp = this;

			pthread_create(threads + t, NULL, threadedUpdateRows, tp);
		}

		for (int t = 0; t < numThreads; t++)
			pthread_join(threads[t], NULL);

		delete[](threads);
	} else
		for (int i = 0; i < size; i++)
			updateRow(newAlpha, newBeta, i);

	// measure change in alpha beta
	changex = 0;
	for (int i = 0; i < size; i++)
		changex += fabs(alpha[i] - newAlpha[i]) + fabs(beta[i] - newBeta[i]);

	delete[](alpha);
	delete[](beta);
	alpha = newAlpha;
	beta = newBeta;

	belief_t * betaCopy = new belief_t[size];
	for (int i = 0; i < size; i++) {
		betaIndex[i] = i;
		betaCopy[i] = beta[i];
	}
	indexSort(betaCopy, betaIndex, size);
	delete[](betaCopy);

	fill(colMatchCount, colMatchCount+size, 0);

	// count column matches
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < b[i]; j++) {
			int m = rowMatches[i][j];
			//if (m > 1000)
			//cout << "m = rowMatches[i][j], " << m  << " =  rowMatches["<<i<<"]["<<j<<"]"<<
			//"b[i] = "<< b[i] << endl;
			colMatchCount[m]++;
		}
	}

	violatedColumns = 0;

	for (int i = 0; i < size; i++) {
		if (iter > 0)
			delete[](colMatches[i]);
		colMatches[i] = new int[colMatchCount[i]];

		if (!dontcare[i] && colMatchCount[i] != b[i])
			violatedColumns++;
	}

	fill(colMatchCount, colMatchCount+size, 0);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < b[i]; j++) {
			int m = rowMatches[i][j];

			colMatches[m][colMatchCount[m]] = i;
			colMatchCount[m]++;
		}
	}

#ifndef _no_oscillation_check
	detector->checkState(alpha, beta);
#endif

	time(&end);

	iterationTime = difftime(end, start);

	++iter;
}

void BeliefPropagator::initBetas() {
	for (int i = 0; i < weightOracle->getSize(); i++) {
		betaIndex[i] = i;
		//cout << betaIndex[i] << " ";
	}
	//cout << endl;
}

int BeliefPropagator::updateScore(belief_t score, belief_t *bestScores, int *bestIndex,
		int minIndex, int column, int b) {

	if (score > bestScores[minIndex]) {
		bestScores[minIndex] = score;
		bestIndex[minIndex] = column;
		return arrayMin(bestScores, b);
	}
	return minIndex;
}

void BeliefPropagator::updateRow(belief_t * newAlpha, belief_t * newBeta, int i) {

	// special rules for nodes that we don't care about:
	if (dontcare[i]) {
		newAlpha[i] = 0;
		newBeta[i] = 0;
		//	b[i] = weightOracle->getSize()-1;


		// reciprocation form
		delete[](rowMatches[i]);
		b[i] = colMatchCount[i];
		rowMatches[i] = new int[b[i]];
		memcpy(rowMatches[i], colMatches[i], b[i]*sizeof(int));
		return;
	}

	int size = weightOracle->getSize();
	IntSet * matchSet = new IntSet(2 * (colMatchCount[i]+1));

	for (int j = 0; j < colMatchCount[i]; j++) {
		matchSet->insert(colMatches[i][j]);
	}

	IndexHeap * heap = new IndexHeap(b[i] + 1);
	for (int j = 0; j < b[i] + 1; j++)
		heap->insert(-INFINITY, -1);

	// sweep through betas and W

	int betaj = 0, Wj = 0, flag = 0;

	if (weightOracle->getCacheSize() == 0)
		flag = 1;

	IntSet * visited = new IntSet(4 * size);

	belief_t bound = INFINITY;
	//	while(betaj < size && bound > bestScores[minIndex]) {
	while(betaj < size && bound > heap->minKey()) {
		int column;

		// choose whether to try weight or beta index
		if (flag == 0 && weightOracle->getCacheSize()> 0) {
			column = weightOracle->getWeightIndex(i, Wj);
		} else {
			column = betaIndex[betaj];
		}

		if (visited->insert(column)) {
			belief_t myBeta, score;

			if (matchSet->find(column))
				myBeta = beta[column];
			else
				myBeta = alpha[column];

			if (flag == 0) {
				score = weightOracle->getIndexedWeight(i, Wj);
			} else {
				score = weightOracle->getWeight(i, column);
			}

			score += myBeta;

			lookups++;

			heap->insert(score, column);
		}

		if (flag == 1) {
			if (weightOracle->getCacheSize() > 0)
				bound = weightOracle->getIndexedWeight(i, Wj) + beta[betaIndex[betaj]];

			if (Wj < weightOracle->getCacheSize()-1)
				Wj++;
			betaj++;
		}

		if (Wj >= weightOracle->getCacheSize()-1)
			flag = 1;
		else
			flag = 1-flag;

		if (dontcare[i] && bound < 0)
			break;
	}

	delete(matchSet);
	delete(visited);

	// grab indices and values from heap
	belief_t * bestScores = heap->getDoubleArray();


	int * bestIndex = heap->getIntArray();
	delete(heap);

	// store top b indices
	indexSort(bestScores, bestIndex, b[i]+1);

	newAlpha[i] = -bestScores[b[i]-1];
	newBeta[i] = -bestScores[b[i]];

	sortInts(bestIndex, b[i]);

	for (int j = 0; j < b[i]; j++) {
		rowMatches[i][j] = bestIndex[j];
	}

	delete[](bestScores);
	delete[](bestIndex);
}

void BeliefPropagator::setB(int * degrees) {
	b = degrees;

	int size = weightOracle->getSize();
	dontcare = new bool[size];

	for (int i = 0; i < size; ++i) {
		if (b[i] > 0) {
			dontcare[i] = false;
		} else {
			// negative degrees mean we don't care about the match count
			b[i] = -b[i];
			dontcare[i] = true;
		}
		rowMatches[i] = new int[b[i]];
	}
}

void BeliefPropagator::setNumThreads(int num) {
	numThreads = num;
}

void * threadedUpdateRows(void *v) {
	threadParam * tp = reinterpret_cast<threadParam*>(v);
	BeliefPropagator * bp = tp->bp;
	for (int i = tp->start; i < tp->size; i += tp->interval) {
		bp->updateRow(tp->newAlpha, tp->newBeta, i);
	}
	delete(tp);
	return NULL;
}





