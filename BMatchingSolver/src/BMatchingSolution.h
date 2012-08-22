/*
 * BMatchingSolution.h
 *
 *  Created on: Apr 8, 2011
 *      Author: bert
 */

#ifndef BMATCHINGSOLUTION_H_
#define BMATCHINGSOLUTION_H_

#include "SparseMatrix.h"

template <class T>
class BMatchingSolution: public SparseMatrix<T> {
public:
	BMatchingSolution();
	BMatchingSolution(int *nzRows, int *nzCols, T *nz, int rows, int cols, int nnz);

	virtual ~BMatchingSolution();

	int getIterations();

	void setIterations(int iters);

private:
	int iterations;
};

template<class T> BMatchingSolution<T>::BMatchingSolution() {
	iterations = 0;
}

template<class T> BMatchingSolution<T>::BMatchingSolution(int *nzRows, int *nzCols, T *nz, int rows, int cols, int nnz) : SparseMatrix<T>(nzRows, nzCols, nz, rows, cols, nnz) {
	iterations = 0;
}

template<class T> BMatchingSolution<T>::~BMatchingSolution() {
}

template<class T> int BMatchingSolution<T>::getIterations() {
	return iterations;
}

template<class T> void BMatchingSolution<T>::setIterations(int iter) {
	iterations = iter;
}

#endif /* BMATCHINGSOLUTION_H_ */
