/*
 * median.cpp
 *
 *  Created on: Sep 18, 2013
 *      Author: venkat
 */

#include <vector>
#include <cmath>
#include "median.h"

/**
 * Given two sorted arrays, gets median of the combined array.
 * Algorithm:
 * 1) Compare median of 1st array to median of 2nd array. Call these m1 and m2
 *    and the respective indexes as i1 and i2.
 * 2) If m1 < m2, then the median of the combined array cannot lie in (0, i1) or (i2, len(arr2)).
 *    This will reduce the overall size of the problem in half.
 * 3) Construct sub-arrays with the indexes given in previous step and go to step (1).
 *
 * Time complexity: O(log (m + n)) where m and n are sizes of arrays a and b.
 * Space complexity: O(1)
 */
int getMedianOfSortedArrays(std::vector<int>& a, std::vector<int>& b)
{
	int firstIndex = (a.size() % 2 == 0)? (a.size() / 2 - 1):(a.size() / 2);
	int secondIndex = (b.size() % 2 == 0)? (b.size() / 2 - 1):(b.size() / 2);

	if(std::abs((int)(a.size() - b.size())) > 1)
	{
		return -1;
	}
	if(a.size() == 1 || b.size() == 1)
	{
		if(a.size() == b.size())
		{
			return a[0];
		}
		else if(a.size() > 1)
		{
			if(a[1] < b[0])
			{
				return a[1];
			}
			else
			{
				return b[0];
			}
		}
		else {
			if(b[1] < a[0])
			{
				return b[1];
			}
			else
			{
				return a[0];
			}
		}
	}

	if(a[firstIndex] == b[secondIndex])
	{
		return a[firstIndex];
	}
	else if(a[firstIndex] < b[secondIndex])
	{
		std::vector<int> a1(a.begin() + firstIndex, a.end());
		std::vector<int> b1(b.begin(), b.begin() + secondIndex + 1);
		return getMedianOfSortedArrays(a1, b1);
	}
	else
	{
		std::vector<int> a1(a.begin(), a.begin() + firstIndex + 1);
		std::vector<int> b1(b.begin() + secondIndex, b.end());
		return getMedianOfSortedArrays(b1, a1);
	}
}

