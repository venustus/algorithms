/*
 * subsetswithsum.h
 *
 *  Created on: Sep 1, 2013
 *      Author: venkat
 */

#ifndef SUBSETSWITHSUM_H_
#define SUBSETSWITHSUM_H_

using namespace std;

#include <set>
#include <vector>

/**
 * Problem:
 * Given an array of non-negative integers, find a subset for which
 * sum of all integers in the set equals a given value k.
 *
 */
std::set<int> * getSubsetsWithSum(std::vector<int> * arr, int k);

#endif /* SUBSETSWITHSUM_H_ */
