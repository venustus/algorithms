/*
 * integer_knapsack.cpp
 *
 *  Created on: Sep 22, 2013
 *      Author: venkat
 */

#include <vector>
#include <iostream>
#include "integer_knapsack.h"

/**
 * Problem:
 * Given a set of valuable items each of which has a weight and a value
 * given by arrays weights and values respectively, find out the
 * maximum value obtainable by selecting items to pick in a knapsack,
 * while still keeping the total weight of selected items to be at most c.
 * This is also called as 0/1 knapsack problem or Integer knapsack problem.
 *
 * Algorithm:
 * 1) Intialize a 2D array m, such that m[i][j] represents
 *    the maximum value obtainable by including items from 0 through i
 *    and not exceeding the maximum weight of j.
 * 2) m[0][j] = 0 for all j and m[i][0] = values[0] for all i.
 * 3) Compute the array m in a bottom-up fashion with two loops one
 *    going from 1 through c and the other over the values array
 *    using recurrence relation: M[i][j] = max(M[i][j - 1], M[i - weights[i]][j - 1]).
 *    (We either don't include the ith item in the knapsack in which case we pick up
 *     the optimal solution for the sub array OR we include the ith item, and pick up
 *     the optimal solution for a smaller capacity).
 * 4) Return m[c][n - 1]
 *
 * Time complexity: O(nc)
 * Space complexity: O(nc)
 */
int getMaximumValueForKnapSack(std::vector<int>& values, std::vector<int>& weights, int c)
{
	std::vector<std::vector<int> > m;
	m.resize(c + 1);
	for(int i = 0; i <=c; i++)
	{
		m[i].resize(values.size());
		if(weights[0] <= i)
		{
			m[i][0] = values[0];
		}
		else
		{
			m[i][0] = 0;
		}
	}
	for(int j = 0; j < values.size(); j++)
	{
		m[0][j] = 0;
	}

	for(int i = 1; i <= c; i++)
	{
		for(int j = 1; j < values.size(); j++)
		{
			if(i < weights[j])
			{
				m[i][j] = m[i][j - 1];
			}
			else
			{
				m[i][j] = std::max(m[i][j - 1], m[i - weights[j]][j - 1] + values[j]);
			}
		}
	}
	return m[c][values.size() - 1];
}


