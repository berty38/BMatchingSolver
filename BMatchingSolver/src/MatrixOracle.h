/*
 * MatrixOracle.h
 *
 *  Created on: Dec 8, 2010
 *      Author: bert
 *      A special type of WeightOracle that explicitly stores the
 *      weight matrix between all pairs of nodes, and weight lookups
 *      are simply matrix lookups.
 */

#include "WeightOracle.h"

#ifndef MATRIXORACLE_H_
#define MATRIXORACLE_H_


/*!
 * \class MatrixOracle MatrixOracle.h
 * \brief Weight oracle that explicitly stores weight matrix of unipartite graph
 */
class MatrixOracle: public WeightOracle {
public:
	/*!
	 * \param[in] n total number of nodes
	 * \param[in] w weight matrix. Entry w[i][j] is the weight between node i and node j
	 */
	MatrixOracle(int n, double ** w);
	virtual ~MatrixOracle();

	int getSize();

	double computeWeight(int row, int col);

private:
	int size;
	double ** weights;
	bool selfLoops;
};

#endif /* MATRIXORACLE_H_ */
