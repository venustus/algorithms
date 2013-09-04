/*
 * lis.cpp
 *
 *  Created on: Sep 2, 2013
 *      Author: venkat
 */

#include <vector>
#include <set>
#include "lis.h"

int binarySearch(std::vector<int> * input, std::vector<int> * m, int nextInput)
{
	int start = 0, end = m->size() - 1;
	while(start < end)
	{
		int middleIndex = start + (end - start) / 2;
		if(nextInput == input->at(m->at(middleIndex)))
		{
			return middleIndex;
		}
		if(nextInput < input->at(m->at(middleIndex)))
		{
			end = middleIndex - 1;
		}
		else
		{
			start = middleIndex + 1;
		}
	}
	return start;
}

int getLongestIncreasingSubsequence(std::vector<int> * input)
{
	std::vector<int> * m = new std::vector<int>;
	std::vector<int> * p = new std::vector<int>;
	p->push_back(-1);
	std::vector<int> * result = new std::vector<int>;
	for(std::vector<int>::iterator it = input->begin(); it != input->end(); ++it)
	{
		int nextInput = *it;
		if(m->empty() || nextInput < input->at(m->at(0)))
		{
			if(m->empty())
			{
				m->push_back(it - input->begin());
			}
			else
			{
				(*m)[0] = it - input->begin();
			}
		}
		else if(nextInput > input->at(m->at(m->size() - 1)))
		{
			p->push_back(m->at(m->size() - 1));
			m->push_back(it - input->begin());
		}
		else
		{
			int newIndex = binarySearch(input, m, nextInput);
			m->at(newIndex) = it - input->begin();
		}
	}
	return m->size();
}


