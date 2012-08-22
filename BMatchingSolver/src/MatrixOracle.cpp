/*
 * MatrixOracle.cpp
 *
 *  Created on: Dec 8, 2010
 *      Author: bert
 */

#include "MatrixOracle.h"
#include <math.h>

MatrixOracle::MatrixOracle(int n, double ** w) {
	size = n;
	weights = w;
	selfLoops = false;
}

MatrixOracle::~MatrixOracle() {
}

int MatrixOracle::getSize() {
	return size;
}

double MatrixOracle::computeWeight(int row, int col) {
	if (!selfLoops && row == col ||
			row >= size || col >= size)
		return -INFINITY;
	return weights[row][col];
}




