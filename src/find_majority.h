/*
 * find_majority.h
 *
 *  Created on: Sep 23, 2013
 *      Author: venkat
 */

#ifndef FIND_MAJORITY_H_
#define FIND_MAJORITY_H_

#include <iostream>
#include <cstdlib>

/**
 * Problem:
 * Given an array of elements, find an element which occurs in majority
 * that is that occurs more than half the time.
 *
 * Algorithm:
 * 1) Iterate through all the elements of the array one by one.
 * 2) Keep a count of repetitions. Whenever an element is same as previous one,
 *    increment the count. Whenever an element is different from previous,
 *    decrement it. If the count goes below zero, floor it to zero.
 * 3) Once we iterate through all the array, if the count is zero,
 *    then no element is in majority (if an element is in majority, then
 *    at least one repetition would be there).
 * 4) If the count is > 0, however, it could be because of the last element
 *    being different from the penultimate one or because there is a majority element.
 * 5) If count > 0, the current element outstanding would be the majority element.
 * 6) Confirm this once by iterating through the array once more and counting
 *    the number of occurrences of the current element.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template<class T>
T findMajority(std::vector<T>& input)
{
	int cnt = 0;
	T prev = input.front();
	for(typename std::vector<T>::iterator it = input.begin() + 1; it != input.end(); ++it)
	{
		if(prev == *it)
		{
			cnt++;
		}
		else
		{
			prev = *it;
			if(cnt != 0)
			{
				cnt--;
			}
		}
	}
	if(cnt > 0)
	{
		cnt = 0;
		for(typename std::vector<T>::iterator it = input.begin(); it != input.end(); ++it)
		{
			if(*it == prev)
			{
				cnt++;
			}
		}
		if(cnt > (input.size() / 2))
		{
			return prev;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}

#endif /* FIND_MAJORITY_H_ */
