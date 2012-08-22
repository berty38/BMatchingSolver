/*
 * IndexHeap.h
 *
 *  Created on: Jan 29, 2011
 *      Author: bert
 */

#ifndef INDEXHEAP_H_
#define INDEXHEAP_H_

#include <queue>
#include <vector>

/*!
 * Special heap structure for selection
 */
class IndexHeap {
public:
	IndexHeap();

	/*!
	 * \param[in] cap capacity of heap
	 */
	IndexHeap(int cap);
	virtual ~IndexHeap();

	/*!
	 * Insert has a side effect of deleting the minimum entry if size is at capacity
	 */
	void insert(long double key, int value);

	/*!
	 * @returns the minimum double in this heap
	 */
	long double minKey();

	/*!
	 * returns the integer associated with the minimum double in the heap
	 */
	int minVal();

	/*!
	 * delete minimum element
	 */
	void deleteMin();

	/*!
	 * \returns full array of doubles
	 */
	long double * getDoubleArray();

	/*!
	 * \returns full array of ints
	 */
	int * getIntArray();

private:

	void percUp(int i );
	void percDown(int i);

	int leftChild(int i);
	int rightChild(int i);
	int parent(int i);
	void swap(int i, int j);

	long double * keys;
	int * vals;
	int size;
	int capacity;

};

#endif /* INDEXHEAP_H_ */
