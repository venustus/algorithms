/*
 * min_coins_for_sum.cpp
 *
 *  Created on: Sep 16, 2013
 *      Author: venkat
 */

#include <vector>
#include <limits>
#include <iostream>
#include "min_coins_for_sum.h"

/**
 * Problem:
 * Given a set of coins (values of the coins), find the
 * minimum number of coins needed to make up a given 'sum'.
 *
 * Approach: Dynamic Programming
 * Algorithm:
 * 1) Initialize an array m such that m[k] represents
 *    minimum number of coins needed to make up sum k.
 * 2) Recurrence relation: m[k] = min(m[k - values[i]]) + 1 where min is over all i  from 0 through n - 1
 * 3) Compute m, bottom up, incrementing i  and k at each iteration.
 * 4) Keep a running min and update it if required in each iteration of the inner for loop.
 * 5) At the end, return m[sum].
 *
 * Time complexity: O(n * sum)
 * Space complexity: O(sum)
 */
int findMinNoOfCoinsForSum(int sum, std::vector<int>& values)
{
	std::vector<int>  m(sum + 1);
	for(int i = 0; i <= sum; i++)
	{
		m[i] = 0;
	}
	for(int i = 0; i < values.size(); i++)
	{
		m[values[i]] = 1;
	}

	for(int k = 1; k <= sum; k++)
	{
		int kmin = std::numeric_limits<int>::max();
		for(int i = 0; i < values.size(); i++)
		{
			if(values[i] <= k)
			{
				if(m[k - values[i]] != 0)
				{
					kmin = std::min(kmin, m[k - values[i]] + 1);
				}
			}
		}
		if(kmin != std::numeric_limits<int>::max())
		{
			if(m[k] != 0) m[k] = std::min(kmin, m[k]);
			else m[k] = kmin;
		}
	}

	return m[sum];
}

