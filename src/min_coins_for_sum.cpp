/*
 * min_coins_for_sum.cpp
 *
 *  Created on: Sep 16, 2013
 *      Author: venkat
 */

#include <vector>
#include <limits>
#include "min_coins_for_sum.h"

int findMinNoOfCoinsForSum(int sum, std::vector<int>& values)
{
	int minSoFar = std::numeric_limits<int>::max();
	std::vector<std::vector<int> >  m(values.size());
	for(int i = 0; i < values.size(); i++)
	{
		std::vector<int> m_i(sum + 1);
		m[i] = m_i;
		for(int j = 0; j <= sum; j++)
		{
			m[i][j] = -1;
		}
		m[i][values[i]] = 1;
	}
	for(int i = 1; i < values.size(); i++)
	{
		if(m[i - 1][sum] >= 0 || m[i - 1][sum - values[i]] >= 0)
		{
			if(m[i - 1][sum] >= 0 && m[i - 1][sum - values[i]] >=0)
			{
				m[i][sum] = std::min(m[i - 1][sum], 1 + m[i - 1][sum - values[i]]);
			}
			else if(m[i - 1][sum] >= 0)
			{
				m[i][sum] = m[i - 1][sum];
			}
			else
			{
				m[i][sum] = 1 + m[i - 1][sum - values[i]];
			}
			if(minSoFar > m[i][sum])
			{
				minSoFar = m[i][sum];
			}
		}
	}
	if(minSoFar == std::numeric_limits<int>::max())
	{
		return -1;
	}
	return minSoFar;
}

