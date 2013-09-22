/*
 * steps_to_permutation.cpp
 *
 *  Created on: Sep 20, 2013
 *      Author: venkat
 */

#include <vector>
#include <iostream>
#include <stdexcept>
#include "steps_to_permutation.h"

void swap(std::vector<int>& arr, int srcIndex, int destIndex, std::vector<SwapStep>& steps)
{
	SwapStep ss;
	ss.srcValue = arr[srcIndex];
	ss.destValue = arr[destIndex];
	int temp = arr[srcIndex];
	arr[srcIndex] = arr[destIndex];
	arr[destIndex] = temp;
	steps.push_back(ss);
	std::cout << "Swap " << ss.srcValue << " with " << ss.destValue << std::endl;
}

void swap(std::vector<int>& arr, int srcIndex, int destIndex, int zeroIndex, std::vector<SwapStep>& steps)
{
	if(destIndex == srcIndex)
	{
		return;
	}
	if(arr[srcIndex] == 0 ||  arr[destIndex] == 0)
	{
		swap(arr, srcIndex, destIndex, steps);
		return;
	}
	swap(arr, srcIndex, zeroIndex, steps);
	swap(arr, destIndex, srcIndex, steps);
	swap(arr, destIndex, zeroIndex, steps);
}

std::vector<SwapStep> * getStepsToPermutation(std::vector<int> &a, std::vector<int> &b)
{
	std::vector<SwapStep> * steps = new std::vector<SwapStep>;
	if(a.size() != b.size())
	{
		throw std::invalid_argument("Arrays a and b must be of same length");
	}
	int * bpos = new int[b.size()];
	int currZeroIndex = 0;
	for(int i = 0; i < b.size(); i++)
	{
		bpos[b[i]] = i;
		if(a[i] == 0)
		{
			currZeroIndex = i;
		}
	}
	for(int i = 0; i < a.size(); i++)
	{
		swap(a, i, bpos[a[i]], currZeroIndex, *steps);
	}
	for(int i = 0; i < a.size(); i++)
	{
		swap(a, i, bpos[a[i]], currZeroIndex, *steps);
	}
	return steps;
}

