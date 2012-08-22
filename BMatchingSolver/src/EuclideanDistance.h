/*
 * EuclideanDistance.h
 *
 *  Created on: Dec 8, 2010
 *      Author: bert
 *
 *      WeightFunction that returns the negative Euclidean
 *      distance between two node descriptor vectors.
 */

#ifndef EUCLIDEANDISTANCE_H_
#define EUCLIDEANDISTANCE_H_

#include "WeightFunction.h"

/*!
 * \class EuclideanDistance EuclideanDistance.h
 * \brief Weight function that returns negative Euclidean distance
 */
class EuclideanDistance: public WeightFunction {
public:
	EuclideanDistance();
	virtual ~EuclideanDistance();

	double getWeight(double * x, double *y, int d);
};

#endif /* EUCLIDEANDISTANCE_H_ */
