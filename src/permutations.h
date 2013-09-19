/*
 * permutations.h
 *
 *  Created on: Sep 19, 2013
 *      Author: venkat
 */

#ifndef PERMUTATIONS_H_
#define PERMUTATIONS_H_

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>

template<typename T>
std::set<std::vector<T> * > * getAllPermutations(std::vector<T> * input)
{
	/* Print path vector to console */
	std::set<std::vector<T> * > * perms = new std::set<std::vector<T> * >;

	if(input->size() == 1)
	{
		perms->insert(input);
		return perms;
	}
	std::vector<T> * subVector = new std::vector<T>(input->begin() + 1, input->end());
	std::set<std::vector<T> * > * subPerms = getAllPermutations(subVector);
	for(typename std::set<std::vector<T> * >::iterator it = subPerms->begin(); it != subPerms->end(); ++it)
	{
		std::vector<T> * subPerm = *it;
		for(int i = 0; i <= subPerm->size(); i++)
		{
			std::vector<T> * newPerm  = new std::vector<T>;
			if(i > 0)
			{
				for(typename std::vector<T>::const_iterator it1 = subPerm->begin(); it1 != subPerm->begin() + i; ++it1)
				{
					newPerm->push_back(*it1);
				}
			}
			newPerm->push_back(input->at(0));
			if(i < subPerm->size())
			{
				for(typename std::vector<T>::const_iterator it1 = subPerm->begin() + i; it1 != subPerm->end(); ++it1)
				{
					newPerm->push_back(*it1);
				}
			}
			perms->insert(newPerm);
		}
	}
	return perms;
}


#endif /* PERMUTATIONS_H_ */
