/*
 * BMatchingSolver.h
 *
 * Default solver functions for BMatch library.
 *
 *  Created on: Dec 8, 2010
 *      Author: bert
 *
 *      A number of helper functions that construct the
 *      appropriate objects to solve b-matching and executes
 *      the solver using standard weight functions.
 *
 */


#ifndef BMATCHINGLIBRARY_H_
#define BMATCHINGLIBRARY_H_

#define DEFAULT_THREADS 6

#include "WeightOracle.h"
#include "SparseMatrix.h"
#include "BipartiteFunctionOracle.h"
#include "BipartiteMatrixOracle.h"
#include "FunctionOracle.h"
#include "MatrixOracle.h"
#include "EuclideanDistance.h"
#include "InnerProduct.h"
#include "BeliefPropagator.h"
#include "BMatchingProblem.h"

/*!
 * \namespace bmatchingLibrary
 * \brief functions to solve many standard b-matching problems
 *
 * Contains helper functions that construct the appropriate objects
 * to solve b-matching and executes the solver using standard weight functions
 */
namespace bmatchingLibrary {

	//methods below return sparse ij objects

	/*!
	 * solves a bipartite matching given the explicit weight matrix
	 * \param[in] rows total number of rows (number of nodes in first bipartition)
	 * \param[in] cols total number of columns (number of nodes in second bipartition)
	 * \param[in] W weight matrix
	 * \param[in] brows int vector of target degrees for rows (first bipartition)
	 * \param[in] bcols int vector of target degrees for columns (second bipartition)
	 * \param[in] cacheSize number of entries to cache per row
	 * \param[in] maxIters maximum iterations before aborting optimization
	 * \param[in] verbose whether to print status
	 * \returns A boolean SparseMatrix containing the matched elements of the b-matching adjacency matrix
	 */
	SparseMatrix<bool> * bMatchBipartiteMatrixCache(int rows, int cols, double ** W, int * brows, int *bcols, int cacheSize, int maxIters, bool verbose = false, int numThreads = DEFAULT_THREADS);
	/*!
	 * solves a bipartite matching given the explicit weight matrix
	 * \param[in] rows total number of rows (number of nodes in first bipartition)
	 * \param[in] cols total number of columns (number of nodes in second bipartition)
	 * \param[in] W weight matrix
	 * \param[in] brows int vector of target degrees for rows (first bipartition)
	 * \param[in] bcols int vector of target degrees for columns (second bipartition)
	 * \param[in] maxIters maximum iterations before aborting optimization
	 * \returns A boolean SparseMatrix containing the matched elements of the b-matching adjacency matrix
	 */
	SparseMatrix<bool> * bMatchBipartiteMatrixSparse(int rows, int cols, double ** W, int * brows, int *bcols, int maxIters);
	/*!
	 * solves a bipartite matching given the explicit weight matrix
	 * \param[in] rows total number of rows (number of nodes in first bipartition)
	 * \param[in] cols total number of columns (number of nodes in second bipartition)
	 * \param[in] W weight matrix
	 * \param[in] brows int vector of target degrees for rows (first bipartition)
	 * \param[in] bcols int vector of target degrees for columns (second bipartition)
	 * \returns A boolean SparseMatrix containing the matched elements of the b-matching adjacency matrix
	 */
	SparseMatrix<bool> * bMatchBipartiteMatrixSparse(int rows, int cols, double ** W, int * brows, int *bcols);
	/*!
	 * solves a bipartite matching given the explicit weight matrix
	 * \param[in] rows total number of rows (number of nodes in first bipartition)
	 * \param[in] cols total number of columns (number of nodes in second bipartition)
	 * \param[in] W weight matrix
	 * \param[in] brows int vector of target degrees for rows (first bipartition)
	 * \param[in] bcols int vector of target degrees for columns (second bipartition)
	 * \param[in] maxIters maximum iterations before aborting optimization
	 * \returns A boolean matrix containing true for the matched elements of the b-matching adjacency matrix
	 */
	bool ** bMatchBipartiteMatrix(int rows, int cols, double ** W, int * brows, int *bcols, int maxIters);
	/*!
	 * solves a bipartite matching given the explicit weight matrix
	 * \param[in] rows total number of rows (number of nodes in first bipartition)
	 * \param[in] cols total number of columns (number of nodes in second bipartition)
	 * \param[in] W weight matrix
	 * \param[in] brows int vector of target degrees for rows (first bipartition)
	 * \param[in] bcols int vector of target degrees for columns (second bipartition)
	 * \returns A boolean matrix containing true for the matched elements of the b-matching adjacency matrix
	 */
	bool ** bMatchBipartiteMatrix(int rows, int cols, double ** W, int * brows, int *bcols);

	/*!
	 * solves a bipartite matching with negative Euclidean weights given the node descriptors
	 * \param[in] rows total number of rows (number of nodes in first bipartition)
	 * \param[in] cols total number of columns (number of nodes in second bipartition)
	 * \param[in] d dimensionality of descriptor vectors
	 * \param[in] X node descriptor matrix with each row as vector descriptor of a node, first bipartition
	 * \param[in] Y node descriptor matrix with each row as vector descriptor of a node, second bipartition
	 * \param[in] brows int vector of target degrees for rows (first bipartition)
	 * \param[in] bcols int vector of target degrees for columns (second bipartition)
	 * \param[in] cacheSize number of entries per row to cache
	 * \param[in] maxIters maximum iterations before aborting optimization
	 * \param[in] verbose whether to print status
	 *
	 * \returns A boolean SparseMatrix containing the matched elements of the b-matching adjacency matrix
	 */
	SparseMatrix<bool> * bMatchBipartiteEuclideanCache(int rows, int cols, int d, double ** X, double ** Y, int * brows, int * bcols, int cacheSize, int maxIters, bool verbose = false, int numThreads = DEFAULT_THREADS);
	/*!
	 * solves a bipartite matching with negative Euclidean weights given the node descriptors
	 * \param[in] rows total number of rows (number of nodes in first bipartition)
	 * \param[in] cols total number of columns (number of nodes in second bipartition)
	 * \param[in] d dimensionality of descriptor vectors
	 * \param[in] X node descriptor matrix with each row as vector descriptor of a node, first bipartition
	 * \param[in] Y node descriptor matrix with each row as vector descriptor of a node, second bipartition
	 * \param[in] brows int vector of target degrees for rows (first bipartition)
	 * \param[in] bcols int vector of target degrees for columns (second bipartition)
	 * \param[in] maxIters maximum iterations before aborting optimization
	 * \returns A boolean SparseMatrix containing the matched elements of the b-matching adjacency matrix
	 */
	SparseMatrix<bool> * bMatchBipartiteEuclideanSparse(int rows, int cols, int d, double ** X, double ** Y, int * brows, int * bcols, int maxIters);
	/*!
	 * solves a bipartite matching with negative Euclidean weights given the node descriptors
	 * \param[in] rows total number of rows (number of nodes in first bipartition)
	 * \param[in] cols total number of columns (number of nodes in second bipartition)
	 * \param[in] d dimensionality of descriptor vectors
	 * \param[in] X node descriptor matrix with each row as vector descriptor of a node, first bipartition
	 * \param[in] Y node descriptor matrix with each row as vector descriptor of a node, second bipartition
	 * \param[in] brows int vector of target degrees for rows (first bipartition)
	 * \param[in] bcols int vector of target degrees for columns (second bipartition)
	 * \returns A boolean SparseMatrix containing the matched elements of the b-matching adjacency matrix
	 */
	SparseMatrix<bool> * bMatchBipartiteEuclideanSparse(int rows, int cols, int d, double ** X, double ** Y, int * brows, int * bcols);
	/*!
	 * solves a bipartite matching with negative Euclidean weights given the node descriptors
	 * \param[in] rows total number of rows (number of nodes in first bipartition)
	 * \param[in] cols total number of columns (number of nodes in second bipartition)
	 * \param[in] d dimensionality of descriptor vectors
	 * \param[in] X node descriptor matrix with each row as vector descriptor of a node, first bipartition
	 * \param[in] Y node descriptor matrix with each row as vector descriptor of a node, second bipartition
	 * \param[in] brows int vector of target degrees for rows (first bipartition)
	 * \param[in] bcols int vector of target degrees for columns (second bipartition)
	 * \param[in] maxIters maximum iterations before aborting optimization
	 * \returns A boolean matrix containing true at the matched elements of the b-matching adjacency matrix
	 */
	bool ** bMatchBipartiteEuclidean(int rows, int cols, int d, double ** X, double ** Y, int * brows, int * bcols, int maxIters);
	/*!
	 * solves a bipartite matching with negative Euclidean weights given the node descriptors
	 * \param[in] rows total number of rows (number of nodes in first bipartition)
	 * \param[in] cols total number of columns (number of nodes in second bipartition)
	 * \param[in] d dimensionality of descriptor vectors
	 * \param[in] X node descriptor matrix with each row as vector descriptor of a node, first bipartition
	 * \param[in] Y node descriptor matrix with each row as vector descriptor of a node, second bipartition
	 * \param[in] brows int vector of target degrees for rows (first bipartition)
	 * \param[in] bcols int vector of target degrees for columns (second bipartition)
	 * \returns A boolean matrix containing true at the matched elements of the b-matching adjacency matrix
	 */
	bool ** bMatchBipartiteEuclidean(int rows, int cols, int d, double ** X, double ** Y, int * brows, int * bcols);

	/*!
	 * solves a bipartite matching with inner product weights given the node descriptors
	 * \param[in] rows total number of rows (number of nodes in first bipartition)
	 * \param[in] cols total number of columns (number of nodes in second bipartition)
	 * \param[in] d dimensionality of descriptor vectors
	 * \param[in] X node descriptor matrix with each row as vector descriptor of a node, first bipartition
	 * \param[in] Y node descriptor matrix with each row as vector descriptor of a node, second bipartition
	 * \param[in] brows int vector of target degrees for rows (first bipartition)
	 * \param[in] bcols int vector of target degrees for columns (second bipartition)
	 * \param[in] cacheSize number of elements per row to cache
	 * \param[in] maxIters maximum iterations before aborting optimization
	 * \param[in] verbose whether to print status
	 * \returns A boolean SparseMatrix containing the matched elements of the b-matching adjacency matrix
	 */
	SparseMatrix<bool> * bMatchBipartiteInnerProductCache(int rows, int cols, int d, double ** X, double ** Y, int * brows, int * bcols, int cacheSize, int maxIters, bool verbose = false, int numThreads = DEFAULT_THREADS);
	/*!
	 * solves a bipartite matching with inner product weights given the node descriptors
	 * \param[in] rows total number of rows (number of nodes in first bipartition)
	 * \param[in] cols total number of columns (number of nodes in second bipartition)
	 * \param[in] d dimensionality of descriptor vectors
	 * \param[in] X node descriptor matrix with each row as vector descriptor of a node, first bipartition
	 * \param[in] Y node descriptor matrix with each row as vector descriptor of a node, second bipartition
	 * \param[in] brows int vector of target degrees for rows (first bipartition)
	 * \param[in] bcols int vector of target degrees for columns (second bipartition)
	 * \param[in] maxIters maximum iterations before aborting optimization
	 * \returns A boolean SparseMatrix containing the matched elements of the b-matching adjacency matrix
	 */
	SparseMatrix<bool> * bMatchBipartiteInnerProductSparse(int rows, int cols, int d, double ** X, double ** Y, int * brows, int * bcols, int maxIters);
	/*!
	 * solves a bipartite matching with inner product weights given the node descriptors
	 * \param[in] rows total number of rows (number of nodes in first bipartition)
	 * \param[in] cols total number of columns (number of nodes in second bipartition)
	 * \param[in] d dimensionality of descriptor vectors
	 * \param[in] X node descriptor matrix with each row as vector descriptor of a node, first bipartition
	 * \param[in] Y node descriptor matrix with each row as vector descriptor of a node, second bipartition
	 * \param[in] brows int vector of target degrees for rows (first bipartition)
	 * \param[in] bcols int vector of target degrees for columns (second bipartition)
	 * \returns A boolean SparseMatrix containing the matched elements of the b-matching adjacency matrix
	 */
	SparseMatrix<bool> * bMatchBipartiteInnerProductSparse(int rows, int cols, int d, double ** X, double ** Y, int * brows, int * bcols);
	/*!
	 * solves a bipartite matching with inner product weights given the node descriptors
	 * \param[in] rows total number of rows (number of nodes in first bipartition)
	 * \param[in] cols total number of columns (number of nodes in second bipartition)
	 * \param[in] d dimensionality of descriptor vectors
	 * \param[in] X node descriptor matrix with each row as vector descriptor of a node, first bipartition
	 * \param[in] Y node descriptor matrix with each row as vector descriptor of a node, second bipartition
	 * \param[in] brows int vector of target degrees for rows (first bipartition)
	 * \param[in] bcols int vector of target degrees for columns (second bipartition)
	 * \param[in] maxIters maximum iterations before aborting optimization
	 * \returns A boolean matrix containing true at the matched elements of the b-matching adjacency matrix
	 */
	bool ** bMatchBipartiteInnerProduct(int rows, int cols, int d, double ** X, double ** Y, int * brows, int * bcols, int maxIters);
	/*!
	 * solves a bipartite matching with inner product weights given the node descriptors
	 * \param[in] rows total number of rows (number of nodes in first bipartition)
	 * \param[in] cols total number of columns (number of nodes in second bipartition)
	 * \param[in] d dimensionality of descriptor vectors
	 * \param[in] X node descriptor matrix with each row as vector descriptor of a node, first bipartition
	 * \param[in] Y node descriptor matrix with each row as vector descriptor of a node, second bipartition
	 * \param[in] brows int vector of target degrees for rows (first bipartition)
	 * \param[in] bcols int vector of target degrees for columns (second bipartition)
	 * \returns A boolean matrix containing true at the matched elements of the b-matching adjacency matrix
	 */
	bool ** bMatchBipartiteInnerProduct(int rows, int cols, int d, double ** X, double ** Y, int * brows, int * bcols);

	/*!
	 * solves a unipartite matching given explicit weight matrix
	 * \param[in] size total number of nodes
	 * \param[in] W weight matrix
	 * \param[in] b int vector of target degrees for each node
	 * \param[in] maxIters maximum iterations before aborting optimization
	 * \param[in] cacheSize number of entries per row to cache
	 * \param[in] verbose whether to print status
	 * \returns A boolean SparseMatrix containing the matched elements of the b-matching adjacency matrix
	 */
	SparseMatrix<bool> * bMatchMatrixCache(int size, double ** W, int * b, int cacheSize, int maxIters, bool verbose = false, int numThreads = DEFAULT_THREADS);
	/*!
	 * solves a unipartite matching given explicit weight matrix
	 * \param[in] size total number of nodes
	 * \param[in] W weight matrix
	 * \param[in] b int vector of target degrees for each node
	 * \param[in] maxIters maximum iterations before aborting optimization
	 * \returns A boolean SparseMatrix containing the matched elements of the b-matching adjacency matrix
	 */
	SparseMatrix<bool> * bMatchMatrixSparse(int size, double ** W, int * b, int maxIters);
	/*!
	 * solves a unipartite matching given explicit weight matrix
	 * \param[in] size total number of nodes
	 * \param[in] W weight matrix
	 * \param[in] b int vector of target degrees for each node
	 * \returns A boolean SparseMatrix containing the matched elements of the b-matching adjacency matrix
	 */
	SparseMatrix<bool> * bMatchMatrixSparse(int size, double ** W, int * b);
	/*!
	 * solves a unipartite matching given explicit weight matrix
	 * \param[in] size total number of nodes
	 * \param[in] W weight matrix
	 * \param[in] b int vector of target degrees for each node
	 * \param[in] maxIters maximum iterations before aborting optimization
	 * \returns A boolean matrix containing true at the matched elements of the b-matching adjacency matrix
	 */
	bool ** bMatchMatrix(int size, double ** W, int * b, int maxIters);
	/*!
	 * solves a unipartite matching given explicit weight matrix
	 * \param[in] size total number of nodes
	 * \param[in] W weight matrix
	 * \param[in] b int vector of target degrees for each node
	 * \returns A boolean matrix containing true at the matched elements of the b-matching adjacency matrix
	 */
	bool ** bMatchMatrix(int size, double ** W, int * b);

	/*!
	 * solves a unipartite matching with negative Euclidean weights given the node descriptors
	 * \param[in] size total number of nodes
	 * \param[in] d dimensionality of descriptor vectors
	 * \param[in] X node descriptor matrix with each row as vector descriptor of a node
	 * \param[in] b int vector of target degrees for all nodes
	 * \param[in] cacheSize number of entries per row to cache
	 * \param[in] maxIters maximum iterations before aborting optimization
	 * \param[in] verbose whether to print status
	 * \returns A boolean SparseMatrix containing the matched elements of the b-matching adjacency matrix
	 */
	SparseMatrix<bool> * bMatchEuclideanCache(int size, int d, double ** X, int * b, int cacheSize, int maxIters, bool verbose = false, int numThreads = DEFAULT_THREADS);
	/*!
	 * solves a unipartite matching with negative Euclidean weights given the node descriptors
	 * \param[in] size total number of nodes
	 * \param[in] d dimensionality of descriptor vectors
	 * \param[in] X node descriptor matrix with each row as vector descriptor of a node
	 * \param[in] b int vector of target degrees for all nodes
	 * \param[in] maxIters maximum iterations before aborting optimization
	 * \returns A boolean SparseMatrix containing the matched elements of the b-matching adjacency matrix
	 */
	SparseMatrix<bool> * bMatchEuclideanSparse(int size, int d, double ** X, int * b, int maxIters);
	/*!
	 * solves a unipartite matching with negative Euclidean weights given the node descriptors
	 * \param[in] size total number of nodes
	 * \param[in] d dimensionality of descriptor vectors
	 * \param[in] X node descriptor matrix with each row as vector descriptor of a node
	 * \param[in] b int vector of target degrees for all nodes
	 * \returns A boolean SparseMatrix containing the matched elements of the b-matching adjacency matrix
	 */
	SparseMatrix<bool> * bMatchEuclideanSparse(int size, int d, double ** X, int * b);
	/*!
	 * solves a unipartite matching with negative Euclidean weights given the node descriptors
	 * \param[in] size total number of nodes
	 * \param[in] d dimensionality of descriptor vectors
	 * \param[in] X node descriptor matrix with each row as vector descriptor of a node
	 * \param[in] b int vector of target degrees for all nodes
	 * \param[in] maxIters maximum iterations before aborting optimization
	 * \returns A boolean matrix containing true at the matched elements of the b-matching adjacency matrix
	 */
	bool ** bMatchEuclidean(int size, int d, double ** X, int * b, int maxIters);
	/*!
	 * solves a unipartite matching with negative Euclidean weights given the node descriptors
	 * \param[in] size total number of nodes
	 * \param[in] d dimensionality of descriptor vectors
	 * \param[in] X node descriptor matrix with each row as vector descriptor of a node
	 * \param[in] b int vector of target degrees for all nodes
	 * \returns A boolean matrix containing true at the matched elements of the b-matching adjacency matrix
	 */
	bool ** bMatchEuclidean(int size, int d, double ** X, int * b);

	/*!
	 * solves a unipartite matching with negative inner product weights given the node descriptors
	 * \param[in] size total number of nodes
	 * \param[in] d dimensionality of descriptor vectors
	 * \param[in] X node descriptor matrix with each row as vector descriptor of a node
	 * \param[in] b int vector of target degrees for all nodes
	 * \param[in] cacheSize number of entries per row to cache
	 * \param[in] maxIters maximum iterations before aborting optimization
	 * \param[in] verbose whether to print status
	 * \returns A boolean SparseMatrix containing the matched elements of the b-matching adjacency matrix
	 */
	SparseMatrix<bool> * bMatchInnerProductCache(int size, int d, double ** X, int * b, int cacheSize, int maxIters, bool verbose = false, int numThreads = DEFAULT_THREADS);
	/*!
	 * solves a unipartite matching with negative inner product weights given the node descriptors
	 * \param[in] size total number of nodes
	 * \param[in] d dimensionality of descriptor vectors
	 * \param[in] X node descriptor matrix with each row as vector descriptor of a node
	 * \param[in] b int vector of target degrees for all nodes
	 * \param[in] maxIters maximum iterations before aborting optimization
	 * \returns A boolean SparseMatrix containing the matched elements of the b-matching adjacency matrix
	 */
	SparseMatrix<bool> * bMatchInnerProductSparse(int size, int d, double ** X, int * b, int maxIters);
	/*!
	 * solves a unipartite matching with negative inner product weights given the node descriptors
	 * \param[in] size total number of nodes
	 * \param[in] d dimensionality of descriptor vectors
	 * \param[in] X node descriptor matrix with each row as vector descriptor of a node
	 * \param[in] b int vector of target degrees for all nodes
	 * \returns A boolean SparseMatrix containing the matched elements of the b-matching adjacency matrix
	 */
	SparseMatrix<bool> * bMatchInnerProductSparse(int size, int d, double ** X, int * b);
	/*!
	 * solves a unipartite matching with negative inner product weights given the node descriptors
	 * \param[in] size total number of nodes
	 * \param[in] d dimensionality of descriptor vectors
	 * \param[in] X node descriptor matrix with each row as vector descriptor of a node
	 * \param[in] b int vector of target degrees for all nodes
	 * \param[in] maxIters maximum iterations before aborting optimization
	 * \returns A boolean matrix containing true at the matched elements of the b-matching adjacency matrix
	 */
	bool ** bMatchInnerProduct(int size, int d, double ** X, int * b, int maxIters);
	/*!
	 * solves a unipartite matching with negative inner product weights given the node descriptors
	 * \param[in] size total number of nodes
	 * \param[in] d dimensionality of descriptor vectors
	 * \param[in] X node descriptor matrix with each row as vector descriptor of a node
	 * \param[in] b int vector of target degrees for all nodes
	 * \returns A boolean matrix containing true at the matched elements of the b-matching adjacency matrix
	 */
	bool ** bMatchInnerProduct(int size, int d, double ** X, int * b);


	// helper functions below

	/*!
	 * solves a b-matching given the weight oracle and degree constraints
	 * \param[in] wo weight oracle for edge weights of graph
	 * \param[in] b int vector of target degrees for nodes
	 * \param[in] maxIters maximum iterations before aborting optimization
	 * \param[in] verbose whether to print status
	 * \return A boolean SparseMatrix containing matched elements of the b-matching adjacency matrix
	 */
	SparseMatrix<bool> * solveBMatchingSparse(WeightOracle * wo, int * b, int maxIters, bool verbose = false, int numThreads = DEFAULT_THREADS);

	/*!
	 * converts a SparseMatrix object to a full boolean matrix
	 * \param[in] solution pointer to solution SparseMatrix
	 * \return the b-matching adjacency matrix as a boolean matrix
	 */
	bool ** convertToBool(SparseMatrix<bool> * solution);

	/*!
	 * concatonates two vectors
	 * \param[in] a first vector
	 * \param[in] b second vector
	 * \param[in] aSize length of a
	 * \param[in] bSize length of b
	 * \return a new vector of length (aSize + bSize) containing a copy of a concatenated with a copy of b
	 */
	int * cat(int * a, int * b, int aSize, int bSize);
}

#endif /* BMATCHINGLIBRARY_H_ */
