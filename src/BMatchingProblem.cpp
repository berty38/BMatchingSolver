/*
 * BMatchingProblem.cpp
 *
 *  Created on: Dec 1, 2010
 *      Author: bert
 */

#include <iostream>
#include <time.h>
#include "BMatchingProblem.h"
using namespace std;

BMatchingProblem::BMatchingProblem() {
	size = 0;
	bp = new BeliefPropagator();
	deleteB = false;
}

BMatchingProblem::BMatchingProblem(WeightOracle * wo, int n, int * degrees, bool v) {
	bp = new BeliefPropagator();
	bp->setWeightOracle(wo);
	weightOracle = wo;
	solution = 0;
	size = n;
	deleteB = false;
	b = degrees;
	bp->setB(b);
	verbose = v;
}

int BMatchingProblem::getSize() {
	return size;
}

int BMatchingProblem::getIters() {
	return bp->getIteration();
}

BMatchingProblem::~BMatchingProblem() {
	delete(bp);
	if (deleteB)
		delete[](b);
}

void BMatchingProblem::setWeightOracle(WeightOracle * wo) {
	weightOracle = wo;
	bp->setWeightOracle(wo);
	size = wo->getSize();
}

void BMatchingProblem::setSize(int n) {
	size = n;
}

WeightOracle *BMatchingProblem::getWeightOracle() {
	return weightOracle;
}

void BMatchingProblem::setB(int *br, int *bc, int rows, int cols) {
	int * degrees = new int[size];

	for (int i = 0; i < rows; i++)
		degrees[i] = br[i];
	for (int i = 0; i < cols; i++)
		degrees[rows+i] = bc[i];
	b = degrees;

	deleteB = true;

	bp->setB(b);
}

void BMatchingProblem::setB(int * degrees) {
	b = degrees;
	bp->setB(b);
	deleteB = false;
}

void BMatchingProblem::setB(int deg) {
	int * degrees = new int[size];

	for (int i = 0; i < size; ++i)
		degrees[i] = deg;

	deleteB = true;

	bp->setB(b);
}

void BMatchingProblem::setMaxIter(int i) {
	bp->setMaxIter(i);
}

SparseMatrix<bool> * BMatchingProblem::solve(int numThreads) {
	/*	while(1) {
		delete(bp);

		bp = new BeliefPropagator();
		bp->setWeightOracle(weightOracle);
		bp->setB(b);
		bp->updateBeliefs();

		solution = bp->getEstimate();
		delete(solution);
	}*/// infinite loop for testing for memory leaks

	time_t start, end;
	time(&start);

	bp->setNumThreads(numThreads);

	do {
		bp->updateBeliefs();
		if (verbose) {
			cout << "Iteration " << bp->getIteration() <<
					", dx " << bp->getChangeX() <<
					", violating columns: " << bp->getViolatedColumns() <<
					", time: " << bp->getIterationTime() << " s" << endl;
			cout.flush();
#ifdef _MEX_HACK // force matlab display to print to console after cout
			mexEvalString("drawnow");
#endif
		}
	} while (!bp->checkConvergence());

	if (solution)
		delete(solution);

	solution = bp->getEstimate();

	time(&end);
	if (verbose) {
		cout << "Finished belief propagation in " << difftime(end, start) << " seconds" << endl;
		cout.flush();
#ifdef _MEX_HACK // force matlab display to print to console after cout
		mexEvalString("drawnow");
#endif
	}

	return solution;
}

int *BMatchingProblem::getSolutionRows() {
	if (!solution)
		return 0;
	return solution->getRows();
}


int *BMatchingProblem::getSolutionCols() {
	if (!solution)
		return 0;
	return solution->getCols();
}
