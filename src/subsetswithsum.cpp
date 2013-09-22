/*
 * subsetswithsum.cpp
 *
 *  Created on: Sep 1, 2013
 *      Author: venkat
 */

#include <set>
#include <vector>
#include <iostream>
#include <tr1/unordered_map>
#include <stdexcept>
#include "subsetswithsum.h"

using namespace std;

void printSet(std::set<int> * s)
{
	for(std::set<int>::iterator it = s->begin(); it != s->end(); ++it)
	{
		std::cout << *it << ", ";
	}
	std::cout << std::endl;
}

/**
 * Problem:
 * Given an array of non-negative integers, find a subset for which
 * sum of all integers in the set equals a given value k.
 *
 * Approach: Dynamic Programming
 * Algorithm:
 * 1) Initialize a 2D array m such that m[i][j] contains a pointer to a subset
 *    whose sum is j or NULL if no such subset exists including only elements
 *    from 0 through i in array 'arr'.
 * 2) Set m[i][arr[i]]] = {arr[i]} for all i from 0 through n - 1
 * 3) Recurrence relation: m[i][sum] = either m[i - 1][sum] or {m[i - 1][sum - arr[i]], arr[i]}
 * 4) Compute m bottom up, by having two loops one on 'sum' going from 1 through k and another
 *    on the input array going from 1 through arr->size().
 * 5) At the end, return m[arr->size() - 1][k]
 *
 * Time complexity: O(k*n)
 * Space complexity: O(k*n)
 *
 * Note: This problem is NP-complete. Because 'k' is exponential in n.
 */
std::set<int> * getSubsetsWithSum(std::vector<int> * arr, int k)
{
	std::vector<std::vector<std::set<int> * > * > * m = new std::vector<std::vector<std::set<int> * > * >;
	m->resize(arr->size());
	for(int i = 0; i < m->size(); i++)
	{
		std::vector<std::set<int> * > * newVector = new std::vector<std::set<int> * >;
		newVector->resize(k + 1);
		(*newVector)[arr->at(i)] = new std::set<int>;
		(*newVector)[arr->at(i)]->insert(arr->at(i));
		(*m)[i] = newVector;
	}
	// compute the sum and results
	for(int i = 1; i < arr->size(); i++)
	{
		for(int sum = 1; sum <= k; sum++)
		{
			std::set<int> * s = (*(*m)[i - 1])[sum];
			if(s)
			{
				(*(*m)[i])[sum] = s;
			}
			if(arr->at(i) > sum)
			{
				continue;
			}
			s = (*(*m)[i - 1])[sum - arr->at(i)];
			if(!s)
			{
				continue;
			}
			std::set<int> * newSet = new std::set<int>(*s);
			newSet->insert(arr->at(i));
			(*(*m)[i])[sum] = newSet;
		}
	}

	return (*(*m)[arr->size() - 1])[k];
}
