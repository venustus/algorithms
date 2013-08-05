/*
 * sorting.h
 *
 *  Created on: Jul 28, 2013
 *      Author: venkat
 */

#include <iostream>
#include <vector>

#ifndef SORTING_H_
#define SORTING_H_

template<typename T>
std::vector<T> * merge(std::vector<T> * arr1, std::vector<T> * arr2, bool (*compare)(const void *, const void *))
{
	std::vector<T> * mergedList = new std::vector<T>;
	int i = 0, j = 0;
	while(i < arr1->size() && j < arr2->size())
	{
		if(compare(&(arr1->at(i)), &(arr2->at(j))))
		{
			mergedList->push_back(arr1->at(i));
			i++;
		}
		else
		{
			mergedList->push_back(arr2->at(j));
			j++;
		}
	}
	while(i < arr1->size())
	{
		mergedList->push_back(arr1->at(i));
		i++;
	}
	while(j < arr2->size())
	{
		mergedList->push_back(arr2->at(j));
		j++;
	}
	return mergedList;
}

/**
 * Sorts an input vector and returns the sorted list as a vector.
 * Time complexity: O(n log n)
 */
template<typename T>
std::vector<T> * mergesort(std::vector<T> * input, bool (*compare)(const void *, const void *))
{
	if(input->size() == 1)
	{
		return new std::vector<T>(*input);
	}
	std::vector<T> * firstHalf = new std::vector<T>(input->begin(), input->begin() + (input->size()/2));
	std::vector<T> * secondHalf = new std::vector<T>(input->begin() + (input->size()/2), input->end());
	std::vector<T> * sortedFirstHalf = mergesort(firstHalf, compare);
	std::vector<T> * sortedSecondHalf = mergesort(secondHalf, compare);
	std::vector<T> * mergedList = merge(sortedFirstHalf, sortedSecondHalf, compare);
	delete firstHalf;
	delete secondHalf;
	return mergedList;
}

template<typename T>
void swap(std::vector<T> * input, int i, int j)
{
	T tmp = input->at(i);
	input->at(i) = input->at(j);
	input->at(j) = tmp;
}

template<typename T>
void print(std::vector<T> * input, int start, int end)
{
	for(typename std::vector<T>::const_iterator it = input->begin() + start;
			it <= input->begin() + end; ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

template<typename T>
int partition(std::vector<T> * input, int pivotIndex, int start, int end)
{
	swap(input, start, pivotIndex);
	T pivot = input->at(start);
	int i = start + 1, j = start + 1;
	while(j <= end)
	{
		if(input->at(j) <= pivot)
		{
			swap(input, i, j);
			i++;
		}
		j++;
	}
	swap(input, i - 1, start);
	return i-1;
}

template<typename T>
void randomizedquicksort(std::vector<T> * input, int start, int end)
{
	if(start == end)
	{
		return;
	}
	int pivotIndex = start + (rand() % (int)(end - start + 1));
	int pivotFinalPos = partition(input, pivotIndex, start, end);
	if(pivotFinalPos > start)
	{
		randomizedquicksort(input, start, pivotFinalPos - 1);
	}
	if(pivotFinalPos < end)
	{
		randomizedquicksort(input, pivotFinalPos + 1, end);
	}
}

template<typename T>
void quicksort(std::vector<T> * input)
{
	randomizedquicksort(input, 0, input->size() - 1);
}


template<int> std::vector<int> * mergesort(std::vector<int> * input, bool (*compare)(const void *, const void *));



#endif /* SORTING_H_ */
