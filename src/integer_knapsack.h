/*
 * integer_knapsack.h
 *
 *  Created on: Sep 22, 2013
 *      Author: venkat
 */

#ifndef INTEGER_KNAPSACK_H_
#define INTEGER_KNAPSACK_H_

#include <vector>

/**
 * Problem:
 * Given a set of valuable items each of which has a weight and a value
 * given by arrays weights and values respectively, find out the
 * maximum value obtainable by selecting items to pick in a knapsack,
 * while still keeping the total weight of selected items to be at most c.
 * This is also called as 0/1 knapsack problem or Integer knapsack problem.
 */
int getMaximumValueForKnapSack(std::vector<int>& values, std::vector<int>& weights, int c);


#endif /* INTEGER_KNAPSACK_H_ */
