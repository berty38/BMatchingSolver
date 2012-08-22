/*
 * WeightOracle.h
 *
 *  Created on: Dec 1, 2010
 *      Author: bert
 *
 * WeightOracle objects are used to return weight values
 * given indices, they also store the index cache for the
 * maximum weights
 * Subclasses will implement different types of weights for
 * different edge definitions such as bipartite graphs or
 * unipartite graphs, with edge weights either explicitly
 * stored or via a weight function
 */

#ifndef WEIGHTORACLE_H_
#define WEIGHTORACLE_H_
#include "utils.h"
#include <pthread.h>
#include "IntDoubleMap.h"

/*!
 * Size of weight lookup cache
 */
#define LOOKUP_CACHE_SIZE 100

/*!
 * \class WeightOracle WeightOracle.h
 * \brief Superclass for weight oracles that provide weights for edges
 *
 * Subclasses can implement different weight functions between nodes etc.
 */
class WeightOracle {
public:
	WeightOracle();
	virtual ~WeightOracle();

	/*!
	 * Computes the lookup index for the top few weights of each node
	 */
	void computeIndex();

	/*!
	 * returns the index of the rank'th greatest weight for the row'th node
	 * \param[in] row row index to look up
	 * \param[in] rank rank of element to look up
	 * \return index of the rank'th greatest weight for the row'th node
	 */
	int getWeightIndex(int row, int rank);

	/*!
	 * returns the rank'th greatest weight for the row'th node
	 * \param[in] row row index to look up
	 * \param[in] rank rank of the element to look up
	 * \return weight of the rank'th greatest weight of row'th node
	 */
	double getIndexedWeight(int row, int rank);

	/*!
	 * returns the weight between the row'th and col'th nodes, checking
	 * cache first, and if not in cache, calls computeWeight
	 * \param[in] row row or id of first node
	 * \param[in] col col or id of second node
	 * \return weight of edge between first and second node
	 */
	double getWeight(int row, int col);

	/*!
	 * returns the weight between the row'th and col'th nodes
	 * \param[in] row row or id of first node
	 * \param[in] col col or id of second node
	 * \return weight of edge between first and second node
	 */
	virtual double computeWeight(int row, int col);

	/*!
	 * returns the number of nodes
	 * \return total number of nodes
	 */
	virtual int getSize();

	/*!
	 * returns the size of the indexed cache of top few weights of each node
	 * \returns the size of the indexed cache of top few weights of each node
	 */
	int getCacheSize();

	/*!
	 * sets the size of the indexed cache of top few weights
	 * \param[in] c size of the indexed cache of top few weights
	 */
	void setCacheSize(int c);


	/*!
	 * prints text describing statistics collected by both caches
	 */
	void printStatsString();

private:
	bool indexComputed;
	int cacheSize;
	int indexSize;
	int ** index;
	double ** cache;
	int numThreads;

	IntDoubleMap ** maps;
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
	 * interval between rows this thread is responsible for
	 */
	int interval;
	/*!
	 * address of weight cache
	 */
	double ** cache;
	/*!
	 * address of index cache
	 */
	int ** index;

	/*!
	 * total number of nodes
	 */
	int size;

	/*!
	 * size of cache
	 */
	int cacheSize;

	/*!
	 * Calling Weight Oracle
	 */
	WeightOracle * wo;
} WOThreadParam;

void * WOThreadedUpdateRows(void * v);

#endif /* WEIGHTORACLE_H_ */
