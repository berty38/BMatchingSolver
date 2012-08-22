/*
 * FunctionOracle.cpp
 *
 *  Created on: Dec 8, 2010
 *      Author: bert
 */

#include "FunctionOracle.h"
#include <math.h>

FunctionOracle::FunctionOracle(double **X, WeightFunction *wf, int n, int d) {
	selfLoops = false;
	size = n;
	dimension = d;
	weightFunction = wf;
	data = X;
}

FunctionOracle::~FunctionOracle() {
}

double FunctionOracle::computeWeight(int row, int col) {
	if (!selfLoops && row == col ||
			row >= size || col >= size)
		return -INFINITY;
	return weightFunction->getWeight(data[row], data[col], dimension);
}


int FunctionOracle::getSize() {
	return size;
}

