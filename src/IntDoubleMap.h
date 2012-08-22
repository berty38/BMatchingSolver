/*
 * intDoubleMap.h
 *
 *  Created on: Dec 3, 2010
 *      Author: bert
 *      A lightweight hash set class specifically designed to store integers.
 */

#ifndef INTDOUBLEMAP_H_
#define INTDOUBLEMAP_H_

#include <pthread.h>

/*!
 * \class IntDoubleMap IntDoubleMap.h
 * \brief Lightweight hash set class for storing ints
 *  Simple hash table with quadratic probing
 */
class IntDoubleMap {
public:
	/*!
	 * \param[in] capacity Initial maximum size of hash set
	 */
	IntDoubleMap(int capacity);
	virtual ~IntDoubleMap();

	/*!
	 * returns the number of elements stored in hash table
	 * \returns the number of elements stored in hash table
	 */
	int getSize();

	/*!
	 * inserts x into hash table, returns whether x was inserted
	 * deletes least recently used element
	 * \param[in] x key to put into map
	 * \param[in] y value to insert into map
	 */
	void insert(int x, double y);

	/*!
	 * returns value of key x in table
	 * \returns value of key, -1 if not in array
	 */
	bool find(int x, double * y);

	/*!
	 * \returns total number of calls to find that hit
	 */
	double getHits();

	/*!
	 * \returns total number of calls to find that missed
	 */
	double getMisses();

private:
	int * table;
	double * value;
	bool * filled;
	int size;
	int lastIndex;
	int tableSize;
	int maxSize;
	double hits;
	double misses;

	void init(int capacity);

	int insertHelper(int x, double y);
	int hash_function(int x);
	int getIndex(int i);

	pthread_mutex_t tableMutex;
	pthread_mutex_t counterMutex;
};

#endif /* INTDOUBLEMAP_H_ */
