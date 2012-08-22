/*
 * BeliefPropagator.h
 *
 *  Created on: Dec 2, 2010
 *      Author: bert
 *
 *      Objects of this class execute belief_t propagation
 *      for b-matching.
 *
 */

#ifndef BELIEFPROPAGATOR_H_
#define BELIEFPROPAGATOR_H_

#include "utils.h"
#include "IntSet.h"
#include "IndexHeap.h"
#include "SparseMatrix.h"
#include "WeightOracle.h"

#ifndef _no_oscillation_check
#include "OscillationDetector.h"
#endif

/*!
 *  Default maximum number of iterations before giving up
 */
#define DEFAULT_MAX_ITERS 20000

/*!
 * Set data type for beliefs
 */
#define belief_t long double

/*!
 * Number of iterations of maintining a valid solution before returning solution
 */
#define REQUIRED_ITERATIONS 3

/*!
 * \class BeliefPropagator BeliefPropagator.h
 * \brief Object that maintains and updates the state of belief_t propagation
 */
class BeliefPropagator {
public:
	BeliefPropagator();
	virtual ~BeliefPropagator();

	/*!
	 * Attach a WeightOracle to this Belief Propagator
	 * \param[in] wo The weight oracle that returns the weights for this b-matching problem
	 */
	void setWeightOracle(WeightOracle * wo);

	/*!
	 * Returns whether belief_t propagation has reached a valid solution
	 * \returns whether belief_t propagation has converged
	 */
	bool checkConvergence();

	/*!
	 * Runs one iteration of belief_t propagation
	 */
	void updateBeliefs();

	/*!
	 * Returns the current estimated solution
	 *\returns current estimated solution as a pointer to a SparseMatrix
	 */
	SparseMatrix<bool> * getEstimate();

	/*!
	 * Returns the current iteration number
	 * \returns current iteration number
	 */
	int getIteration();

	/*!
	 * Set the maximum number of iterations before giving up
	 *\param[in] i new maximum iteration value
	 */
	void setMaxIter(int i);

	/*!
	 * Sets the number of threads to use during belief_t updates
	 */
	void setNumThreads(int num);

	/*!
	 * Sets the degree constraints as a single vector
	 *\param[in] degrees int array containing the target degrees for each node
	 */
	void setB(int * degrees);

	/*!
	 * Sets the degree constraints as a row vector and column vector (for bipartite case only)
	 *\param[in] brows int array of target degrees for first bipartition (row degrees)
	 *\param[in] bcols int array of target degrees for second bipartition (column degrees)
	 * prerequisite The weight oracle must be set before setB is called.
	 */
	void setB(int * brows, int * bcols);

	/*!
	 * updates the beliefs for row. Don't use this method. This is temporarily public to
	 * allow a quick multithreading patch
	 */
	void updateRow(belief_t * newAlpha, belief_t * newBeta, int i);

	/*!
	 * \returns number of columns with incorrect neighbor count
	 */
	int getViolatedColumns() { return violatedColumns; }

	/*!
	 * \returns time to compute previous iteration
	 */
	double getIterationTime() { return iterationTime; }

	/*!
	 * \returns change in beliefs in previous iteration
	 */
	belief_t getChangeX() { return changex; }

private:
	int maxIter;
	int iter;
	int lookups;
	belief_t * alpha;
	belief_t * beta;
	int * betaIndex;
	int ** rowMatches;
	int ** colMatches;
	int * colMatchCount;
	int converged;
	int numThreads;
	int * b;
	bool * dontcare;
	WeightOracle * weightOracle;

#ifndef _no_oscillation_check
    OscillationDetector * detector;
#endif

	// last iteration stats
	int violatedColumns;
	double iterationTime;
	double changex;

	pthread_t * threads;

	void initBetas();
	int updateScore(belief_t score, belief_t *bestScores, int *bestIndex,
	        int minIndex, int column, int b);
};



/*!
 * Struct for storing thread paramters
 */
typedef struct {
	/*!
	 * first row index this thread is responsible for
	 */
	int start;
	/*!
	 * interval between rows that this thread is responsible
	 */
	int interval;
	/*!
	 * total number of rows
	 */
	int size;
	/*!
	 * address of new messages
	 */
	belief_t * newAlpha;
	/*!
	 * address of new messages
	 */
	belief_t * newBeta;
	/*!
	 * belief_t propagator parent object
	 */
	BeliefPropagator * bp;
} threadParam;

void * threadedUpdateRows(void * v);

#endif /* BELIEFPROPAGATOR_H_ */

