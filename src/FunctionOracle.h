/*
 * FunctionOracle.h
 *
 *  Created on: Dec 8, 2010
 *      Author: bert
 *
 *      A special class of WeightOracle that returns
 *      weights as the a function of node descriptors.
 *      This class represents a unipartite graph, such that
 *      any two nodes return a valid weight.
 */

#ifndef FUNCTIONORACLE_H_
#define FUNCTIONORACLE_H_

#include "WeightOracle.h"
#include "WeightFunction.h"

/*!
 * \class FunctionOracle FunctionOracle.h
 * \brief Weight oracle that returns weights computed via a function between node descriptors of a unipartite graph
 */
class FunctionOracle: public WeightOracle {
public:
	/*!
	 * \param[in] X matrix (n x d) whose rows are node desciptors
	 * \param[in] wf WeightFunction object that computes weights between nodes
	 * \param[in] n total number of nodes
	 * \param[in] d dimensionality of node descriptors (length of vectors)
	 */
	FunctionOracle(double ** X, WeightFunction * wf, int n, int d);
	virtual ~FunctionOracle();

	int getSize();

	double computeWeight(int row, int col);

private:
	double ** data;
	int size;
	int dimension;
	WeightFunction * weightFunction;

	bool selfLoops;
};

#endif /* FUNCTIONORACLE_H_ */
