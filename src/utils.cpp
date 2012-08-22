/*
 * utils.cpp
 *
 *  Created on: Dec 3, 2010
 *      Author: bert
 */
#include <iostream>
#include <fstream>
using namespace std;

namespace utils {
	/**
	 * file tools for reading and writing matrices and arrays
	 */

	/**
	 * Takes a file and reads the input as a matrix of values
	 */
	void readDoubleMatrix(const char * filename, double **mat, int rows, int cols) {
		ifstream fin;

		fin.open(filename, ifstream::in);
		if (!fin.is_open()) {
			cout << "Error opening " << filename << endl;
		}

		int i, j;
		for (i = 0; i < rows; i++) {
			for (j = 0; j < cols; j++) {
				fin >> mat[i][j];
			}
		}
		fin.close();
	}

	void readIntMatrix(const char * filename, int **mat, int rows, int cols) {
		FILE *fin = fopen(filename, "r");

		int i, j;
		for (i = 0; i < rows; i++) {
			for (j = 0; j < cols; j++) {
				double num;
				fscanf(fin, "   %lf", &num);
				mat[i][j] = (int)(num);
			}
			fscanf(fin, "\n");
		}

		fclose(fin);
	}

	/**
	 * Takes a file and reads the input as a full column of values
	 */
	void readDoubleArray(const char *filename, double *col, int size)
	{
		FILE *fin = fopen(filename, "r");
		int i;
		for(i = 0;i < size;i++){
			fscanf(fin, "   %lf\n", &col[i]);
		}
		fclose(fin);
	}

	void readIntArray(const char *filename, int *col, int size)
	{
		FILE *fin = fopen(filename, "r");
		int i;
		for(i = 0;i < size;i++){
			double num;
			fscanf(fin, "   %lf\n", &num);
			col[i] = (int)(num);
		}
		fclose(fin);
	}

	/**
	 * Prints a matrix of doubles
	 */
	void printDoubleMatrix(double **mat, int rows, int cols)
	{
		int i, j;
		for(i = 0;i < rows;i++){
			for(j = 0;j < cols;j++)
				std::cout << mat[i][j] << " ";

			std::cout << std::endl;
		}
	}

	/**
	 * Prints an array of ints
	 */
	void printIntArray(int *A, int size)
	{
		int i;
		for(i = 0;i < size;i++)
			std::cout << A[i] << " ";

		std::cout << std::endl;
	}
	/**
	 * Prints an array of doubles
	 */
	void printDoubleArray(double *A, int size)
	{
		int i;
		for(i = 0;i < size;i++)
			std::cout << A[i] << " ";

		std::cout << std::endl;
	}
	void allocateDoubleRows(double **mat, int rows, int cols) {
		for (int i = 0; i < rows; i++)
			mat[i] = new double[cols];
	}
	void allocateIntRows(int **mat, int rows, int cols) {
		for (int i = 0; i < rows; i++)
			mat[i] = new int[cols];
	}
	void clearDoubleArray(double *A, int size)
	{
		int i;
		for(i = 0; i < size; i++)
			A[i] = 0;

	}
	void clearIntArray(int *A, int size)
	{
		int i;
		for(i = 0; i < size; i++)
			A[i] = 0;

	}
	void copyDoubleArray(double *A, double *B, int size)
	{
		int i;
		for(i = 0; i < size; i++)
			B[i] = A[i];

	}
	/**
	 * finds the median of the beginning, middle and end entries. swaps with
	 * first element and returns value
	 */
	double medianOfThree(double *X, int *inds, int N)
	{
		int I[3];
		I[0] = 0;
		I[1] = N / 2;
		I[2] = N - 1;
		int i, j;
		for(i = 0; i < 3; i++)
			for(j = i + 1; j < 3; j++)
				if(X[I[i]] < X[I[j]]){
					int tmp = I[i];
					I[i] = I[j];
					I[j] = tmp;
				}


		// now median should be I[1]
		i = I[1];
		double tmp_d = X[i];
		int tmp_i = inds[i];
		X[i] = X[0];
		inds[i] = inds[0];
		X[0] = tmp_d;
		inds[0] = tmp_i;
		return X[0];
	}


	/**
	 * finds the median of the beginning, middle and end entries. swaps with
	 * first element and returns value
	 */
	long double medianOfThree(long double *X, int *inds, int N)
	{
		int I[3];
		I[0] = 0;
		I[1] = N / 2;
		I[2] = N - 1;
		int i, j;
		for(i = 0; i < 3; i++)
			for(j = i + 1; j < 3; j++)
				if(X[I[i]] < X[I[j]]){
					int tmp = I[i];
					I[i] = I[j];
					I[j] = tmp;
				}


		// now median should be I[1]
		i = I[1];
		double tmp_d = X[i];
		int tmp_i = inds[i];
		X[i] = X[0];
		inds[i] = inds[0];
		X[0] = tmp_d;
		inds[0] = tmp_i;
		return X[0];
	}


	/**
	 * Quicksorts a double array and an int array according to the double values
	 */
	void indexSort(double *X, int *inds, int N)
	{
		int i, j, tmp;
		double pivot, t;
		if(N <= 1)
			return;

		/* Partition */
		pivot = medianOfThree(X, inds, N);
		i = 0;
		j = N;
		for(;;){
			while(X[++i] > pivot && i < N){
			}
			while(X[--j] < pivot){
			}
			if(i >= j)
				break;

			/* swap */
			t = X[i];
			X[i] = X[j];
			X[j] = t;
			/* swap indices */
			tmp = inds[i];
			inds[i] = inds[j];
			inds[j] = tmp;
		}
		t = X[i - 1];
		X[i - 1] = X[0];
		X[0] = t;
		tmp = inds[i - 1];
		inds[i - 1] = inds[0];
		inds[0] = tmp;
		indexSort(X, inds, i - 1);
		indexSort(X + i, inds + i, N - i);
	}

	/**
	 * Quicksorts a double array and an int array according to the double values
	 */
	void indexSort(long double *X, int *inds, int N)
	{
		int i, j, tmp;
		double pivot, t;
		if(N <= 1)
			return;

		/* Partition */
		pivot = medianOfThree(X, inds, N);
		i = 0;
		j = N;
		for(;;){
			while(X[++i] > pivot && i < N){
			}
			while(X[--j] < pivot){
			}
			if(i >= j)
				break;

			/* swap */
			t = X[i];
			X[i] = X[j];
			X[j] = t;
			/* swap indices */
			tmp = inds[i];
			inds[i] = inds[j];
			inds[j] = tmp;
		}
		t = X[i - 1];
		X[i - 1] = X[0];
		X[0] = t;
		tmp = inds[i - 1];
		inds[i - 1] = inds[0];
		inds[0] = tmp;
		indexSort(X, inds, i - 1);
		indexSort(X + i, inds + i, N - i);
	}


	/**
	 * Quickselects a double array and an int array according to the double values
	 * The array will be ordered such that the first k elements are the largest k elements
	 * But those k elements may not be in order
	 */
	void indexSelect(double *X, int *inds, int N, int k)
	{
		int i, j, tmp;
		double pivot, t;
		if(N <= 1)
			return;

		/* Partition */
		pivot = medianOfThree(X, inds, N);
		i = 0;
		j = N;
		for(;;){
			while(X[++i] > pivot && i < N){
			}
			while(X[--j] < pivot){
			}
			if(i >= j)
				break;

			/* swap */
			t = X[i];
			X[i] = X[j];
			X[j] = t;
			/* swap indices */
			tmp = inds[i];
			inds[i] = inds[j];
			inds[j] = tmp;
		}
		t = X[i - 1];
		X[i - 1] = X[0];
		X[0] = t;
		tmp = inds[i - 1];
		inds[i - 1] = inds[0];
		inds[0] = tmp;
		if(k < i){
			//printf("Recursing left k %d, i-1 %d\n", k, i-1);
			indexSelect(X, inds, i - 1, k);
		}else
			if(k > i){
				//printf("Recursing right k %d, i-1 %d\n", k, i-1);
				indexSelect(X + i, inds + i, N - i, k - i);
			}

	}

	/**
	 * Quicksorts an int array from least to greatest
	 */
	void sortInts(int *X, int N)
	{
		int i, j;
		int pivot, t;
		if(N <= 1)
			return;

		/* Partition */
		pivot = X[0];
		i = 0;
		j = N;
		for(;;){
			while(X[++i] < pivot && i < N){
			}
			while(X[--j] > pivot){
			}
			if(i >= j)
				break;

			/* swap */
			t = X[i];
			X[i] = X[j];
			X[j] = t;
		}
		t = X[i - 1];
		X[i - 1] = X[0];
		X[0] = t;
		sortInts(X, i - 1);
		sortInts(X + i, N - i);
	}


	/**
	 * Creates index array (from zero to size)
	 */
	int *indexArray(int size)
	{
		int *A = new int[size];
		int i;
		for(i = 0;i < size;i++)
			A[i] = i;

		return A;
	}
	int hashInsert(int x, int *hashTable, int capacity, int size)
	{
		int i = 1;
		int index = x % capacity;
		while(hashTable[index] != 0){
			if(hashTable[index] == x)
				return 1;

			index = (index + i++) % capacity;
		}
		hashTable[index] = x;
		return 0;
	}

	int hashIsMember(int x, int *hashTable, int capacity, int size)
	{
		int i = 1;
		int index = x % capacity;
		while(hashTable[index] != 0){
			if(hashTable[index] == x)
				return 1;

			index = (index + i++) % capacity;
		}
		return 0;
	}

	/**
	 * Checks if x is in A, where A must be a sorted int array.
	 */
	int sortedIsMember(int *A, int size, int x)
	{
		if(size == 0)
			return 0;

		int median = (int)(size) / 2;

		if (x > A[median])
			return sortedIsMember(A + median + 1, size - median - 1, x);
		else if (x < A[median])
			return sortedIsMember(A, median, x);

		return 1;
	}


	int arrayMin(double * A, int size) {
		int ret = 0;
		for (int i = 0; i < size; i++)
			if (A[i] < A[ret])
				ret = i;
		return ret;
	}


	int arrayMin(long double * A, int size) {
		int ret = 0;
		for (int i = 0; i < size; i++)
			if (A[i] < A[ret])
				ret = i;
		return ret;
	}


}
