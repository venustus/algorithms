/*
 * steps_to_permutation.h
 *
 *  Created on: Sep 20, 2013
 *      Author: venkat
 */

#ifndef STEPS_TO_PERMUTATION_H_
#define STEPS_TO_PERMUTATION_H_

#include <vector>

struct SwapStep
{
	int srcValue;
	int destValue;
};

/**
 * Problem:
 * Given two integer arrays containing elements 0 .. n - 1, but not necessarily
 * in same order, print/return the list of swaps to be done to convert
 * the array a into array b.
 *
 * Condition:
 * Swaps can only be done with '0'.
 */
std::vector<SwapStep> * getStepsToPermutation(std::vector<int> &a, std::vector<int> &b);


#endif /* STEPS_TO_PERMUTATION_H_ */
