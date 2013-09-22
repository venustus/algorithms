/*
 * lss.cpp
 *
 *  Created on: Sep 7, 2013
 *      Author: venkat
 */

#include <vector>
#include <limits>
#include "lss.h"

/**
 * Retrieves the sub array with largest sum in a given integer array.
 * Algorithm:
 * 1) Start with first element and do a linear sweep of the array.
 * 2) At each step, compute and keep track of the maximum sum of any sub-array
 *    ending at the current position. max(i) can be computed based on max(i-1) as follows:
 *    2.1) If max(i-1) is negative, then we don't need its contribution. Set max(i) to just a[i].
 *    2.2) Otherwise, set max(i) to a[i] + max(i).
 * 3) At each step keep track of a running maxSoFar (and its indexes). If max(i) exceeds
 *    maxSoFar at any point, reset maxSoFar to max(i). Also reset the indexes.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
void getLargestSumSubsequence(std::vector<int> &a, int& startIndex, int& endIndex)
{
	int maxSoFar = std::numeric_limits<int>::min();
	int currentMax = a[0];
	int maxSoFarStartIndex = 0, maxSoFarEndIndex = 0;
	int currentStartIndex = 0, currentEndIndex = 0;
	for(int i = 1;i < a.size();i++)
	{
		if(currentMax < 0)
		{
			currentMax = a[i];
			currentStartIndex = i;
			currentEndIndex = i;
		}
		else
		{
			currentMax = currentMax + a[i];
			currentEndIndex = i;
		}
		if(maxSoFar < currentMax)
		{
			maxSoFar = currentMax;
			maxSoFarStartIndex = currentStartIndex;
			maxSoFarEndIndex = currentEndIndex;
		}
	}
	startIndex = maxSoFarStartIndex;
	endIndex = maxSoFarEndIndex;
}
