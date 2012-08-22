/*
 * SparseMatrix.h
 *
 *  Created on: Dec 2, 2010
 *      Author: bert
 *
 *      Incomplete implementation of a sparse matrix
 *      currently all it holds is the indices and the values
 *      future versions will have fast lookup methods, addition, multiplication,
 *      or will be wrappers to other more complete sparse matrix libraries
 *
 */

#ifndef SPARSEMATRIX_H_
#define SPARSEMATRIX_H_

/*!
 * \class SparseMatrix SparseMatrix.h
 * \brief Object for storing nonzero entries of a sparse matrix
 */
template <class T>
class SparseMatrix {
public:
	SparseMatrix();
	/*!
	 * \param[in] rows number of rows in matrix
	 * \param[in] cols number of columns in matrix
	 */
	SparseMatrix(int rows, int cols);

	/*!
	 * \param[in] nzRows vector of row indices of nonzeros
	 * \param[in] nzCols vector of column indices of nonzeros
	 * \param[in] nz vector of values of nonzeros
	 * \param[in] rows total number of rows
	 * \param[in] cols total number of columns
	 * \param[in] nnz total number of nonzero entries
	 */
	SparseMatrix(int *nzRows, int *nzCols, T *nz, int rows, int cols, int nnz);
	virtual ~SparseMatrix();

	/*!
	 * return vector of row indices of nonzeros
	 * \return vector of row indices of nonzeros
	 */
	int* getRows();

	/*!
	 * return vector of column indices of nonzeros
	 * \return vector of column indices of nonzeros
	 */
	int* getCols();

	/*!
	 * returns the total number of rows in matrix (size)
	 * \returns the total number of rows in matrix (size)
	 */
	int getRowCount();

	/*!
	 * returns the total number of columns in matrix
	 * \returns the total number of columns in matrix
	 */
	int getColCount();

	/*!
	 * returns the total number of nonzero elements in matrix
	 * \returns the total number of nonzero elements in matrix
	 */
	int getNNz();

	/*!
	 * returns the values of the nonzero elements
	 * \returns the values of the nonzero elements
	 */
	T * getVals();

private:
	int * nzrows;
	int * nzcols;
	int rows;
	int cols;
	int nnz;
	T * nonzeros;
};

template<class T> SparseMatrix<T>::SparseMatrix() {
}

template<class T> SparseMatrix<T>::SparseMatrix(int r, int c) {
	rows = r;
	cols = c;
}

template<class T> SparseMatrix<T>::SparseMatrix(int *nzRows, int *nzCols, T *nz, int r, int c, int n) {
	nzrows = nzRows;
	nzcols = nzCols;
	nonzeros = nz;
	rows = r;
	cols = c;
	nnz = n;
}

template<class T> SparseMatrix<T>::~SparseMatrix() {
	delete[](nzrows);
	delete[](nzcols);
	delete[](nonzeros);
}

template<class T> int SparseMatrix<T>::getRowCount() {
	return rows;
}

template<class T> int SparseMatrix<T>::getColCount() {
	return cols;
}

template<class T> int SparseMatrix<T>::getNNz() {
	return nnz;
}

template<class T> int *SparseMatrix<T>::getRows() {
	return nzrows;
}

template<class T> int *SparseMatrix<T>::getCols() {
	return nzcols;
}

template<class T> T *SparseMatrix<T>::getVals() {
	return nonzeros;
}

#endif /* SPARSEMATRIX_H_ */
