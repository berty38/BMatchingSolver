/*
 * EuclideanDistance.cpp
 *
 *  Created on: Dec 8, 2010
 *      Author: bert
 */

#include "EuclideanDistance.h"
#include <math.h>

EuclideanDistance::EuclideanDistance() {

}

EuclideanDistance::~EuclideanDistance() {
}

double EuclideanDistance::getWeight(double *x, double *y, int d) {
	double distance = 0;
	for (int i = 0; i < d; i++) {
		double difference = x[i] - y[i];
		distance += difference * difference;
	}
	if (distance != distance)
		return 0;
	return -sqrt(distance);
}


