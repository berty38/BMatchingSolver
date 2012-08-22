/*
 * BipartiteFunctionOracle.h
 *
 *  Created on: Dec 8, 2010
 *      Author: bert
 *
 *      Special class of WeightOracle that returns as weights the
 *      result of a function of the two node descriptors. This particular
 *      class represents a bipartite graph so weights within any
 *      bipartition will return negative infinite weight.
 */

#ifndef BIPARTITEFUNCTIONORACLE_H_
#define BIPARTITEFUNCTIONORACLE_H_

#include "WeightOracle.h"
#include "WeightFunction.h"

/*!
 * \class BipartiteFunctionOracle BipartiteFunctionOracle.h
 * \brief weight oracle for bipartite graphs with weight function
 *
 * Special subclass of weight oracles meant for bipartite graphs with weights
 * defined by a function between node descriptors,
 * which are represented such that nodes within each bipartition have negative-infinite
 * weight between each other
 */
class BipartiteFunctionOracle: public WeightOracle {
public:

	/*!
	 * \param[in] dataX matrix (r x d) whose rows are the vector descriptors of the first bipartition
	 * \param[in] dataY matrix (c x d) whose rows are the vector descriptors of the second bipartition
	 * \param[in] wf function mapping node pair descriptors to weight value (e.g., negative Euclidean distance)
	 * \param[in] r count of rows (number of nodes in first bipartition)
	 * \param[in] c count of columns (number of nodes in second bipartition)
	 * \param[in] d dimensionality of vector descriptors
	 */
	BipartiteFunctionOracle(double **dataX, double **dataY, WeightFunction *wf, int r, int c, int d);
	virtual ~BipartiteFunctionOracle();

	/*!
	 * returns the number of nodes in the graph
	 * \returns the number of nodes in the graph
	 */
	int getSize();

	/*!
	 * Get the weight between nodes
	 * \returns the weight between the "row"th node and the "col"th node
	 */
	double computeWeight(int row, int col);

private:
	WeightFunction * weightFunction;
	int rows;
	int cols;
	int dimension;
	double ** X;
	double ** Y;

};

#endif /* BIPARTITEFUNCTIONORACLE_H_ */
