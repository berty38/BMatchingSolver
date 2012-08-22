/*
 * OscillationDetector.h
 *
 *  Created on: Dec 14, 2010
 *      Author: bert
 */

#ifndef OSCILLATIONDETECTOR_H_
#define OSCILLATIONDETECTOR_H_


#include "IntSet.h"


#define DEFAULT_CAPACITY 10
#define MAXIMUM_CAPACITY 500
#define TOLERANCE 1e-16

/*!
 * \class OscillationDetector OscillationDetector.h
 * \brief Agent for detecting non-converging oscillation in BP
 * Objects of this class compare state vectors to previously seen state vectors
 * If any vectors are repeating, oscillation is possible. This class uses
 * a hashed checksum to compare state vectors (cheap) then uses explicit
 * state comparisons (expensive) when collisions are detected in checksums
 */
class OscillationDetector {
public:
	/*!
	 * \param[in] newLength size of state vectors
	 */
	OscillationDetector(int newLength);
	virtual ~OscillationDetector();

	/*!
	 * Check whether state has been seen before
	 * Each state consistes of two vectors
	 * \param[in] a first state vector
	 * \param[in] b second state vector
	 * \returns whether state has been seen before within epsilon tolerance
	 */
	bool checkState(long double * a, long double * b);

	/*!
	 * Returns whether oscillation has been detected
	 * \return whether oscillation has been detected by a previous call to checkState()
	 */
	bool isOscillating() { return oscillating; }

private:

	int getCheckSum(long double * a);
	bool insert(int checkSum, long double * a);
	void rehash();
	int quadraticProbe(int index, long double * a);
	int hash(long double * a);

	bool oscillating;
	bool warning;
	IntSet * checkSums;
	int size, length, capacity;
	long double ** vectors;

};

#endif /* OSCILLATIONDETECTOR_H_ */
