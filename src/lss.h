/*
 * lss.h
 *
 *  Created on: Sep 7, 2013
 *      Author: venkat
 */

#ifndef LSS_H_
#define LSS_H_

#include <vector>

/**
 * Problem Statement:
 * Given an integer array which can hold any integers,
 * retrieve a sub array that has the largest sum.
 */
void getLargestSumSubsequence(std::vector<int> &a, int& startIndex, int& endIndex);

/**
 * Problem Statement:
 * Given an integer array which can hold any integers,
 * retrieve a sub array that has the largest product.
 */
int getLargestProductSubsequence(std::vector<int> &a, int& startIndex, int& endIndex);

#endif /* LSS_H_ */
