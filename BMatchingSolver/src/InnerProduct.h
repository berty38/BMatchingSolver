/*
 * InnerProduct.h
 *
 *  Created on: Dec 8, 2010
 *      Author: bert
 *      WeightFunction that returns the inner product
 *      between two node descriptor vectors.
 */

#ifndef INNERPRODUCT_H_
#define INNERPRODUCT_H_

#include "WeightFunction.h"

/*!
 * \class InnerProduct InnerProduct.h
 * \brief Weight function that computes the inner product between node descriptor vectors
 */
class InnerProduct: public WeightFunction {
public:
	InnerProduct();
	virtual ~InnerProduct();

	double getWeight(double *x, double *y, int d);
};

#endif /* INNERPRODUCT_H_ */
