/*
 * BipartiteFunctionOracle.cpp
 *
 *  Created on: Dec 8, 2010
 *      Author: bert
 */

#include <math.h>
#include <iostream>
#include "BipartiteFunctionOracle.h"

BipartiteFunctionOracle::BipartiteFunctionOracle(double **dataX, double **dataY, WeightFunction *wf, int r, int c, int d) {
	X = dataX;
	Y = dataY;
	weightFunction = wf;
	rows = r;
	cols = c;
	dimension = d;
	setCacheSize(max(rows, cols));
}

BipartiteFunctionOracle::~BipartiteFunctionOracle() {
}

int BipartiteFunctionOracle::getSize() {
	return rows + cols;
}

double BipartiteFunctionOracle::computeWeight(int row, int col) {
	if (row < rows && col < rows ||
			row >= rows && col >= rows ||
			row - rows >= cols || col - rows >= cols) {
		return -INFINITY;
	} else if (row < rows)
		return weightFunction->getWeight(X[row], Y[col - rows], dimension);
	return weightFunction->getWeight(X[col], Y[row-rows], dimension);
}

