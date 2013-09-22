/*
 * lps.cpp
 *
 *  Created on: Sep 21, 2013
 *      Author: venkat
 */

#include <limits>
#include <vector>
#include "lps.h"

int computeProduct(std::vector<int>& a, int startIndex, int endIndex)
{
	int product = 1;
	for(int i = startIndex; i <= endIndex; i++)
	{
		product *= a[i];
	}
	return product;
}

/**
 * Retrieves a sub-array of a given vector which has the maximum
 * product of all sub arrays.
 * Algorithm:
 * 1) Divide the array into blocks separated by zeroes.
 * 2) For each block, count the negative numbers.
 *    2.1) If there are even number of negative numbers,
 *         just compute the whole product of the block
 *         and update a running max product if required.
 *    2.2) If there are odd number of negative numbers,
 *         keep track of first and last negative number encountered.
 *         Then compute two products of all integers ranging between
 *         first negative number and end of block, and start of block and
 *         last negative number. Take max of these two products and update
 *         max product if required.
 * 3) Return maxProduct and set start index and end index.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
int getLargestProductSubsequence(std::vector<int> &a, int& startIndex, int& endIndex)
{
	int maxStart = 0, maxEnd = 0;
	int maxProduct = std::numeric_limits<int>::min();
	int curProduct = 1;
	int negCount = 0, firstNeg = -1, lastNeg = -1;
	int blockStart = 0;
	int i = 0;
	while(i < a.size())
	{
		if(a[i] < 0)
		{
			negCount++;
			if(negCount == 1) firstNeg = i;
			lastNeg = i;
		}
		else if(a[i] == 0)
		{
			if(negCount % 2 == 0)
			{
				if(maxProduct < curProduct)
				{
					maxProduct = curProduct;
					maxStart = blockStart;
					maxEnd = i - 1;
				}
			}
			else
			{
				int firstPro = computeProduct(a, firstNeg + 1, i - 1);
				int secondPro = computeProduct(a, blockStart, lastNeg - 1);
				int maxPro = std::max(firstPro, secondPro);
				if(maxProduct < maxPro)
				{
					maxProduct = maxPro;
					if(maxPro == firstPro)
					{
						maxStart = firstNeg + 1;
						maxEnd = i - 1;
					}
					else
					{
						maxStart = blockStart;
						maxEnd = lastNeg - 1;
					}
				}
			}
			i++;
			firstNeg = -1;
			lastNeg = -1;
			negCount = 0;
			blockStart = i;
			curProduct = 1;
			continue;
		}
		curProduct *= a[i];
		i++;
	}
	if(a[i - 1] != 0)
	{
		if(negCount % 2 == 0)
		{
			if(maxProduct < curProduct)
			{
				maxProduct = curProduct;
				maxStart = blockStart;
				maxEnd = i - 1;
			}
		}
		else
		{
			int firstPro = computeProduct(a, firstNeg + 1, i - 1);
			int secondPro = computeProduct(a, blockStart, lastNeg - 1);
			int maxPro = std::max(firstPro, secondPro);
			if(maxProduct < maxPro)
			{
				maxProduct = maxPro;
				if(maxPro == firstPro)
				{
					maxStart = firstNeg + 1;
					maxEnd = i - 1;
				}
				else
				{
					maxStart = blockStart;
					maxEnd = lastNeg - 1;
				}
			}
		}
	}
	startIndex = maxStart;
	endIndex = maxEnd;
	return maxProduct;
}

