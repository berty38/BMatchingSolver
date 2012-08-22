/*
 * BipartiteMatrixOracle.h
 *
 *  Created on: Dec 3, 2010
 *      Author: bert
 *
 *      Special type of weight oracle that represents
 *      a bipartite graph, where the weight matrix is
 *      all negative infinity on the diagonal quadrants and
 *      valid on the off-diagonals
 *
 */

#ifndef KERNELMATRIXORACLE_H_
#define KERNELMATRIXORACLE_H_

#include "WeightOracle.h"
#include "utils.h"

/*!
 * \class BipartiteMatrixOracle BipartiteMatrixOracle.h
 * \brief Weight oracle that explictly stores the weight matrix for bipartite graph
 *
 */
class BipartiteMatrixOracle: public WeightOracle {
public:
	/*!
	 * \param[in] kernel the weight matrix (r x c) between bipartitions
	 * \param[in] r number of rows (number of nodes in first bipartition)
	 * \param[in] c number of columns (number of nodes in second bipartition)
	 */
	BipartiteMatrixOracle(double ** kernel, int r, int c);
	virtual ~BipartiteMatrixOracle();

	int getSize();

	double computeWeight(int row, int col);

private:
	int rows;
	int cols;
	double **K;
	int **index;
	double **cache;
};

#endif /* KERNELMATRIXORACLE_H_ */
