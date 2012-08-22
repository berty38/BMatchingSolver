/*
 * BipartiteMatrixOracle.cpp
 *
 *  Created on: Dec 3, 2010
 *      Author: bert
 */

#include <math.h>
#include <iostream>
#include "BipartiteMatrixOracle.h"

using namespace utils;
using namespace std;

BipartiteMatrixOracle::BipartiteMatrixOracle(double **kernel, int r, int c) {
	K = kernel;
	rows = r;
	cols = c;
	setCacheSize(max(rows, cols));
}

BipartiteMatrixOracle::~BipartiteMatrixOracle() {
}

int BipartiteMatrixOracle::getSize() {
	return rows + cols;
}

double BipartiteMatrixOracle::computeWeight(int row, int col) {
	if (row < rows && col < rows ||
			row >= rows && col >= rows ||
			row - rows >= cols || col - rows >= cols)
		return -INFINITY;
	else if (row < rows)
		return K[row][col - rows];
	return K[col][row - rows];
}


