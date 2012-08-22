/*
 * BMatchingProblem.h
 *
 *  Created on: Dec 1, 2010
 *      Author: bert
 *
 *      Objects of this class represent a b-matching
 *      problem, which stores the problem parameters
 *      and the solution, once it is found.
 */


#ifndef BMATCHINGPROBLEM_H_
#define BMATCHINGPROBLEM_H_

#define DEFAULT_THREADS 6

#ifdef _MEX_HACK // force matlab display to print to console after cout
#include "mex.h"
#endif
#include "SparseMatrix.h"
#include "WeightOracle.h"
#include "BeliefPropagator.h"

/*!
 * \class BMatchingProblem BMatchingProblem.h
 * \brief Object representing a b-matching problem
 */
class BMatchingProblem {
public:
	BMatchingProblem();
	/*!
	 * \param[in] wo weight oracle that provides edge weights
	 * \param[in] size total number of nodes for this problem
	 * \param[in] b array of target degrees for each node
	 * \param[in] verbose whether to print status
	 *
	 */
	BMatchingProblem(WeightOracle * wo, int size, int * b, bool verbose);
	virtual ~BMatchingProblem();

	/*!
	 * Sets the WeightOracle for this problem
	 * \param[in] wo weight oracle that provides edge weights
	 */
	void setWeightOracle(WeightOracle * wo);

	/*!
	 * Sets the number of nodes in the problem
	 * \param[in] n new number of nodes in graph
	 */
	void setSize(int n);

	/*!
	 * sets the degree constraints, all nodes must have degree b
	 * \param[in] b target degree for ALL nodes
	 */
	void setB(int b);

	/*!
	 * sets the degree constraints as a single vector
	 * \param[in] degrees new vector of target degrees for each node
	 */
	void setB(int * degrees);

	/*!
	 * sets the degree constraints for a bipartite graph
	 * \param[in] br target degrees for first bipartition (along rows)
	 * \param[in] bc target degrees for second bipartition (along columns)
	 * \param[in] rows total number of rows (number of nodes in first bipartition)
	 * \param[in] cols total number of columns (number of nodes in second bipartition)
	 */
	void setB(int *br, int *bc, int rows, int cols);

	/*!
	 * sets the maximum number of iterations to try
	 * \param[in] i maximum number of iterations
	 */
	void setMaxIter(int i);

	/*!
	 * returns the weightOracle
	 * \returns weight oracle
	 */
	WeightOracle * getWeightOracle();

	/*!
	 * returns the number of nodes
	 * \returns number of nodes in graph
	 */
	int getSize();

	/*!
	 * Run the solver until completion
	 */
	SparseMatrix<bool> * solve(int numThreads = DEFAULT_THREADS);

	/*!
	 * Returns the row indices of the matched pairs
	 * \return vector of row indices of matched edges
	 */
	int * getSolutionRows();

	/*!
	 * Returns the column indicies of the matched pairs
	 * \return vector of column indices of matched edges
	 */
	int * getSolutionCols();

	/*!
	 * returns the number of iterations run so far
	 * \return number of iterations so far
	 */
	int getIters();

private:
	WeightOracle * weightOracle;
	int size;
	int * b;
	bool deleteB;
	bool verbose;
	BeliefPropagator * bp;
	SparseMatrix<bool> * solution;
};

#endif /* BMATCHINGPROBLEM_H_ */
