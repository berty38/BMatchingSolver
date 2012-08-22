/*
 * intSet.h
 *
 *  Created on: Dec 3, 2010
 *      Author: bert
 *      A lightweight hash set class specifically designed to store integers.
 */

#ifndef INTSET_H_
#define INTSET_H_

/*!
 * \class IntSet IntSet.h
 * \brief Lightweight hash set class for storing ints
 *  Simple hash table with quadratic probing
 */
class IntSet {
public:
	IntSet();
	/*!
	 * \param[in] capacity Initial maximum size of hash set
	 */
	IntSet(int capacity);
	virtual ~IntSet();

	/*!
	 * returns the number of elements stored in hash table
	 * \returns the number of elements stored in hash table
	 */
	int getSize();

	/*!
	 * inserts x into hash table, returns whether x was inserted
	 * \param[in] x value to insert into set
	 * \return whether x was successfully inserted. If x is already in table, returns false
	 */
	bool insert(int x);

	/*!
	 * returns whether x is in hash table
	 * \returns whether x is in hash table
	 */
	bool find(int x);

private:
	int size;
	int * table;
	bool * filled;
	int tableSize;

	void init(int capacity);
	int hash_function(int x);
	int quadratic_probe(int i);
	void rehash(int capacity);
};

#endif /* INTSET_H_ */
