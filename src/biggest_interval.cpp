/*
 * biggest_interval.cpp
 *
 *  Created on: Sep 20, 2013
 *      Author: venkat
 */

#include <vector>
#include <tr1/unordered_map>
#include "biggest_interval.h"

/**
 * Find biggest contigous interval among a given list of unsorted numbers.
 * For example, for {10, 1, 3, 4, 5, 2, 7}, the answer is (1, 5).
 *
 * Algorithm:
 * 1) Put all the elements in the array into a hash map.
 * 2) Retrieve each element in the hashmap and find out if succeeding and preceding
 *    numbers are in the hash map. Repeat until we find a break.
 * 3) If the discovered range is larger than a running max range, update running max range.
 * 4) Repeat step (2) until the hash map has 0 elements.
 *
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
int findBiggestContiguousInterval(std::vector<int>& in, int& min, int& max)
{
	std::tr1::unordered_map<int, bool> * inputSet = new std::tr1::unordered_map<int, bool>;
	for(int i = 0; i < in.size(); i++)
	{
		inputSet->insert(std::make_pair(in[i], true));
	}
	min = 0;
	max = -1;
	int maxRange = 0;
	while(inputSet->size() > 0)
	{
		std::tr1::unordered_map<int, bool>::const_iterator it = inputSet->begin();
		int currentInt = it->first;
		inputSet->erase(it);
		int currentSetSize = 1;
		int currentRangeMin = currentInt;
		int currentRangeMax = currentInt;
		int i = 1;
		while(true)
		{
			std::tr1::unordered_map<int, bool>::const_iterator it1 = inputSet->find(currentInt + (i++));
			if(it1 == inputSet->end())
			{
				break;
			}
			currentSetSize++;
			currentRangeMax = it1->first;
			inputSet->erase(it1);
		}
		i = 1;
		while(true)
		{
			std::tr1::unordered_map<int, bool>::const_iterator it1 = inputSet->find(currentInt - (i++));
			if(it1 == inputSet->end())
			{
				break;
			}
			currentSetSize++;
			currentRangeMin = it1->first;
			inputSet->erase(it1);
		}
		if(currentSetSize > maxRange)
		{
			maxRange = currentSetSize;
			min = currentRangeMin;
			max = currentRangeMax;
		}
	}
	return maxRange;
}


