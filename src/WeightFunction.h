/*
 * WeightFunction.h
 *
 *  Created on: Dec 2, 2010
 *      Author: bert
 *
 *      WeightFunctions must have a method getWeight that returns the
 *      weight between two node descriptor vectors. This is implemented as
 *      an object superclass to allow for future weight functions that may
 *      require state information, though the default weight functions need no state.
 */

#ifndef WEIGHTFUNCTION_H_
#define WEIGHTFUNCTION_H_

/*!
 * \class WeightFunction WeightFunction.h
 * \brief Weight function superclass
 * Objects of this class contain a method that computes an edge weight given the node descriptors
 */
class WeightFunction {
public:
	WeightFunction();
	virtual ~WeightFunction();

	/*!
	 * returns the weight between nodes with descriptors x and y of dimensionality d
	 * \param[in] x vector descriptor for first node
	 * \param[in] y vector descriptor for second node
	 * \param[in] d dimensionality of vector descriptors (length of vectors)
	 * \return weight between first and second nodes
	 */
	virtual double getWeight(double * x, double *y, int d);
};

#endif /* WEIGHTFUNCTION_H_ */
