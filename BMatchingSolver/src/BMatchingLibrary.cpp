/*
 * BMatchingSolver.cpp
 *
 *  Created on: Dec 8, 2010
 *      Author: bert
 */

#include <iostream>
#include <time.h>
#include "BMatchingLibrary.h"

using namespace std;

SparseMatrix<bool> *bmatchingLibrary::bMatchBipartiteMatrixSparse(int rows,
		int cols, double **W, int *brows, int *bcols) {
	return bMatchBipartiteMatrixSparse(rows, cols, W, brows, bcols,
			DEFAULT_MAX_ITERS);
}

SparseMatrix<bool> *bmatchingLibrary::bMatchBipartiteMatrixSparse(int rows,
		int cols, double **W, int *brows, int *bcols, int maxIters) {
	return bMatchBipartiteMatrixCache(rows, cols, W, brows, bcols, rows + cols,
			maxIters);
}

SparseMatrix<bool> *bmatchingLibrary::bMatchBipartiteMatrixCache(int rows,
		int cols, double **W, int *brows, int *bcols, int cacheSize,
		int maxIters, bool verbose, int numThreads) {
	int * b = cat(brows, bcols, rows, cols);
	WeightOracle * wo = new BipartiteMatrixOracle(W, rows, cols);
	wo->setCacheSize(cacheSize);
	SparseMatrix<bool> * ret = solveBMatchingSparse(wo, b, maxIters, verbose, numThreads);
	delete[] (b);
	delete (wo);
	return ret;
}

bool **bmatchingLibrary::bMatchBipartiteEuclidean(int rows, int cols, int d,
		double **X, double **Y, int *brows, int *bcols) {
	return bMatchBipartiteEuclidean(rows, cols, d, X, Y, brows, bcols,
			DEFAULT_MAX_ITERS);
}

SparseMatrix<bool> *bmatchingLibrary::bMatchBipartiteEuclideanSparse(int rows,
		int cols, int d, double **X, double **Y, int *brows, int *bcols) {
	return bMatchBipartiteEuclideanSparse(rows, cols, d, X, Y, brows, bcols,
			DEFAULT_MAX_ITERS);
}

SparseMatrix<bool> *bmatchingLibrary::bMatchBipartiteEuclideanSparse(int rows,
		int cols, int d, double **X, double **Y, int *brows, int *bcols,
		int maxIters) {
	return bMatchBipartiteEuclideanCache(rows, cols, d, X, Y, brows, bcols,
			rows + cols, maxIters);
}

SparseMatrix<bool> *bmatchingLibrary::bMatchBipartiteEuclideanCache(int rows,
		int cols, int d, double **X, double **Y, int *brows, int *bcols,
		int cacheSize, int maxIters, bool verbose, int numThreads) {
	int * b = cat(brows, bcols, rows, cols);
	WeightFunction * wf = new EuclideanDistance();
	WeightOracle * wo = new BipartiteFunctionOracle(X, Y, wf, rows, cols, d);
	wo->setCacheSize(cacheSize);
	SparseMatrix<bool> * ret = solveBMatchingSparse(wo, b, maxIters, verbose, numThreads);
	delete[] (b);
	delete(wf);
	delete(wo);
	return ret;
}

SparseMatrix<bool> *bmatchingLibrary::bMatchBipartiteInnerProductSparse(
		int rows, int cols, int d, double **X, double **Y, int *brows,
		int *bcols) {
	return bMatchBipartiteInnerProductSparse(rows, cols, d, X, Y, brows, bcols,
			DEFAULT_MAX_ITERS);
}

SparseMatrix<bool> *bmatchingLibrary::bMatchBipartiteInnerProductSparse(
		int rows, int cols, int d, double **X, double **Y, int *brows,
		int *bcols, int maxIters) {
	return bMatchBipartiteInnerProductCache(rows, cols, d, X, Y, brows, bcols,
			rows + cols, maxIters);
}

SparseMatrix<bool> *bmatchingLibrary::bMatchBipartiteInnerProductCache(
		int rows, int cols, int d, double **X, double **Y, int *brows,
		int *bcols, int cacheSize, int maxIters, bool verbose, int numThreads) {
	int * b = cat(brows, bcols, rows, cols);
	WeightFunction * wf = new InnerProduct();
	WeightOracle * wo = new BipartiteFunctionOracle(X, Y, wf, rows, cols, d);
	wo->setCacheSize(cacheSize);
	SparseMatrix<bool> * ret = solveBMatchingSparse(wo, b, maxIters, verbose, numThreads);
	delete[] (b);
	delete(wf);
	delete(wo);
	return ret;
}

SparseMatrix<bool> *bmatchingLibrary::bMatchMatrixSparse(int size, double **W,
		int *b) {
	return bMatchMatrixSparse(size, W, b, DEFAULT_MAX_ITERS);
}

SparseMatrix<bool> *bmatchingLibrary::bMatchMatrixSparse(int size, double **W,
		int *b, int maxIters) {
	return bMatchMatrixCache(size, W, b, size, maxIters);
}

SparseMatrix<bool> *bmatchingLibrary::bMatchMatrixCache(int size, double **W,
		int *b, int cacheSize, int maxIters, bool verbose, int numThreads) {
	WeightOracle * wo = new MatrixOracle(size, W);
	wo->setCacheSize(cacheSize);
	SparseMatrix<bool> * ret = solveBMatchingSparse(wo, b, maxIters, verbose, numThreads);
	delete (wo);
	return ret;
}

SparseMatrix<bool> *bmatchingLibrary::bMatchEuclideanSparse(int size, int d,
		double **X, int *b) {
	return bMatchEuclideanSparse(size, d, X, b, DEFAULT_MAX_ITERS);
}

SparseMatrix<bool> *bmatchingLibrary::bMatchEuclideanSparse(int size, int d,
		double **X, int *b, int maxIters) {
	return bMatchEuclideanCache(size, d, X, b, size, maxIters);
}

SparseMatrix<bool> *bmatchingLibrary::bMatchEuclideanCache(int size, int d,
		double **X, int *b, int cacheSize, int maxIters, bool verbose, int numThreads) {
	WeightFunction * wf = new EuclideanDistance();
	WeightOracle * wo = new FunctionOracle(X, wf, size, d);
	wo->setCacheSize(cacheSize);
	SparseMatrix<bool> * ret = solveBMatchingSparse(wo, b, maxIters, verbose, numThreads);
	delete (wf);
	delete (wo);
	return ret;
}

SparseMatrix<bool> *bmatchingLibrary::bMatchInnerProductSparse(int size, int d,
		double **X, int *b) {
	return bMatchInnerProductSparse(size, d, X, b, DEFAULT_MAX_ITERS);
}

SparseMatrix<bool> *bmatchingLibrary::bMatchInnerProductSparse(int size, int d,
		double **X, int *b, int maxIters) {
	return bMatchInnerProductCache(size, d, X, b, size, maxIters);
}

SparseMatrix<bool> *bmatchingLibrary::bMatchInnerProductCache(int  size, int d,
		double **X, int *b, int cacheSize, int maxIters, bool verbose, int numThreads) {
	WeightFunction * wf = new InnerProduct();
	WeightOracle * wo = new FunctionOracle(X, wf, size, d);
	wo->setCacheSize(cacheSize);
	SparseMatrix<bool> * ret = solveBMatchingSparse(wo, b, maxIters, verbose, numThreads);
	delete (wf);
	delete (wo);
	return ret;
}

// nonsparse versions

bool **bmatchingLibrary::bMatchBipartiteInnerProduct(int rows, int cols, int d,
		double **X, double **Y, int *brows, int *bcols) {
	return bMatchBipartiteInnerProduct(rows, cols, d, X, Y, brows, bcols,
			DEFAULT_MAX_ITERS);
}

bool **bmatchingLibrary::bMatchMatrix(int size, double **W, int *b,
		int maxIters) {
	SparseMatrix<bool> * solution = bMatchMatrixSparse(size, W, b, maxIters);
	bool ** ret = convertToBool(solution);
	delete (solution);
	return ret;

}

bool **bmatchingLibrary::bMatchEuclidean(int size, int d, double **X, int *b) {
	return bMatchEuclidean(size, d, X, b, DEFAULT_MAX_ITERS);
}

bool **bmatchingLibrary::bMatchInnerProduct(int size, int d, double **X, int *b) {
	return bMatchInnerProduct(size, d, X, b, DEFAULT_MAX_ITERS);
}

bool **bmatchingLibrary::bMatchBipartiteMatrix(int rows, int cols, double **W,
		int *brows, int *bcols) {
	return bMatchBipartiteMatrix(rows, cols, W, brows, bcols, DEFAULT_MAX_ITERS);
}

bool **bmatchingLibrary::bMatchEuclidean(int size, int d, double **X, int *b,
		int maxIters) {
	SparseMatrix<bool> * solution = bMatchEuclideanSparse(size, d, X, b,
			maxIters);
	bool ** ret = convertToBool(solution);
	delete (solution);
	return ret;
}

bool **bmatchingLibrary::bMatchBipartiteMatrix(int rows, int cols, double **W,
		int *brows, int *bcols, int maxIters) {
	SparseMatrix<bool> * solution = bMatchBipartiteMatrixSparse(rows, cols, W,
			brows, bcols, maxIters);
	bool ** ret = convertToBool(solution);
	delete (solution);
	return ret;
}

bool **bmatchingLibrary::bMatchBipartiteEuclidean(int rows, int cols, int d,
		double **X, double **Y, int *brows, int *bcols, int maxIters) {
	SparseMatrix<bool> * solution = bMatchBipartiteEuclideanSparse(rows, cols,
			d, X, Y, brows, bcols, maxIters);
	bool ** ret = convertToBool(solution);
	delete (solution);
	return ret;
}

bool **bmatchingLibrary::bMatchMatrix(int size, double **W, int *b) {
	return bMatchMatrix(size, W, b, DEFAULT_MAX_ITERS);
}

bool **bmatchingLibrary::bMatchBipartiteInnerProduct(int rows, int cols, int d,
		double **X, double **Y, int *brows, int *bcols, int maxIters) {
	SparseMatrix<bool> * solution = bMatchBipartiteInnerProductSparse(rows,
			cols, d, X, Y, brows, bcols, maxIters);
	bool ** ret = convertToBool(solution);
	delete (solution);
	return ret;
}

bool **bmatchingLibrary::bMatchInnerProduct(int size, int d, double **X,
		int *b, int maxIters) {
	SparseMatrix<bool> * solution = bMatchInnerProductSparse(size, d, X, b,
			maxIters);
	bool ** ret = convertToBool(solution);
	delete (solution);
	return ret;
}

bool **bmatchingLibrary::convertToBool(SparseMatrix<bool> * solution) {
	int rows = solution->getRowCount();
	int cols = solution->getColCount();
	bool ** ret = new bool*[rows];
	for (int i = 0; i < rows; i++) {
		ret[i] = new bool[cols];
		std::fill(ret[i], ret[i] + cols, false);
	}
	int * nzrows = solution->getRows();
	int * nzcols = solution->getCols();
	for (int i = 0; i < solution->getNNz(); i++) {
		ret[nzrows[i]][nzcols[i]] = true;
	}

	return ret;
}

SparseMatrix<bool> *bmatchingLibrary::solveBMatchingSparse(WeightOracle *wo,
		int *b, int maxIters, bool verbose, int numThreads) {
	time_t start, end;
	time(&start);
	wo->computeIndex();
	time(&end);
	if (verbose) {
		cout << "Computing cache took " << difftime(end, start) << " s. Starting belief propagation..." << endl;
	}
	BMatchingProblem * bmatching = new BMatchingProblem(wo, wo->getSize(), b, verbose);
	bmatching->setMaxIter(maxIters);
	SparseMatrix<bool> * solution;
	solution = bmatching->solve(numThreads);
	delete (bmatching);

	if (verbose) {
		wo->printStatsString();
	}

	return solution;
}

int *bmatchingLibrary::cat(int *a, int *b, int aSize, int bSize) {
	int * ret = new int[aSize + bSize];
	for (int i = 0; i < aSize; i++)
		ret[i] = a[i];
	for (int i = 0; i < bSize; i++)
		ret[aSize + i] = b[i];
	return ret;
}

