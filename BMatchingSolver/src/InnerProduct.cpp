/*
 * InnerProduct.cpp
 *
 *  Created on: Dec 8, 2010
 *      Author: bert
 */

#include "InnerProduct.h"

InnerProduct::InnerProduct() {
}

InnerProduct::~InnerProduct() {
}

double InnerProduct::getWeight(double *x, double *y, int d) {
	double ret = 0;
	for (int i = 0; i < d; i++)
		ret += x[i] * y[i];
	if (ret != ret)
		return 0;
	return ret;
}
