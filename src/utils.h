/*
 * utils.h
 *
 *  Created on: Dec 3, 2010
 *      Author: bert
 *
 *      A bunch of helper functions used throughout b-matching library.
 */

#ifndef UTILS_H_
#define UTILS_H_

using namespace std;

namespace utils {

	// Takes a file and reads the input as a matrix of values
	void readDoubleMatrix(const char * filename, double **mat, int rows, int cols);
	void readIntMatrix(char * filename, int **mat, int rows, int cols);

	// Takes a file and reads the input as a full column of values
	void readDoubleArray(const char * filename, double *col, int size);
	void readIntArray(const char * filename, int *col, int size);

	// Prints a double matrix to std out
	void printDoubleMatrix(double** mat, int rows, int cols);

	// Prints an array to std out
	void printIntArray(int * A, int size);
	void printDoubleArray(double * A, int size);

	// allocate each row of an array of pointers
	void allocateDoubleRows(double **mat, int rows, int cols);
	void allocateIntRows(int **mat, int rows, int cols);

	// clears an array to all zeros
	void clearDoubleArray(double * A, int size);
	void clearIntArray(int * A, int size);

	// copies a double array into another
	void copyDoubleArray(double * A, double * B, int size);

	// Quicksorts a double array and an int array according to the double values
	void indexSort(double * X, int * inds, int N);
	// Quicksorts a long double array and an int array according to the double values
	void indexSort(long double * X, int * inds, int N);

	// Quickselects a double array and int array according to the double values
	void indexSelect(double * X, int * inds, int N, int k);

	// Quicksorts an array of ints
	void sortInts(int * X, int N);

	// Creates an array of indicies
	int * indexArray(int size);

	// finds the index of the minimum value of an array of doubles
	int arrayMin(double * A, int size);

	// finds the index of the minimum value of an array of long doubles
	int arrayMin(long double * A, int size);

}

#endif /* UTILS_H_ */
