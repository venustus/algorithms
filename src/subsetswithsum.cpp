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

std::set<int> * getSubsetsWithHalfSum(std::vector<int> * arr, int k)
{
	tr1::unordered_map<int, std::set<int> * > * results =
			new tr1::unordered_map<int, std::set<int> * >;
	int sum = 0;
	// compute the sum and results
	for(std::vector<int>::iterator it = arr->begin(); it != arr->end(); ++it)
	{
		std::set<int> * singleElemSubset = new std::set<int>;
		singleElemSubset->insert(*it);
		sum += *it;
		if((*it) > (k/2))
		{
			continue;
		}
		(*results)[(*it)] = singleElemSubset;
		for(tr1::unordered_map<int, std::set<int> * >::iterator it1 = results->begin();
				it1 != results->end(); ++it1)
		{
			if((it1->first == (*it)) || (it1->first + (*it) > k/2))
			{
				continue;
			}

			std::set<int> * existingSubset = it1->second;
			std::set<int>::iterator it2 = existingSubset->find(*it);
			if(it2 != existingSubset->end())
			{
				continue;
			}
			std::set<int> * newSubset = new std::set<int>;
			newSubset->insert(existingSubset->begin(), existingSubset->end());
			newSubset->insert(*it);
			std::cout << "Assigning the following set to sum " << (it1->first + (*it)) << std::endl;
			printSet(newSubset);
			(*results)[(it1->first + (*it))] = newSubset;
		}
	}
	std::cout << "Total sum is: " << sum << std::endl;
	if(sum%2 != 0)
	{
		return new std::set<int>;
	}
	try
	{
		std::set<int> * halfSumSubset = (*results)[sum/2];
		delete results;
		return halfSumSubset;
	}
	catch(const std::out_of_range& oor)
	{
		return new std::set<int>;
	}
}
