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

/**
 * Same as randomized quick sort except that the pivot index is naively
 * chosen to be the first element of the input array.
 */
template<typename T>
void naivequicksort(std::vector<T> * input, int start, int end, int &numberOfComparisons)
{
	if(start == end)
	{
		return;
	}
	int pivotIndex = start;
	int pivotFinalPos = partition(input, pivotIndex, start, end);
	if(pivotFinalPos > start)
	{
		numberOfComparisons += pivotFinalPos - start;
		naivequicksort(input, start, pivotFinalPos - 1, numberOfComparisons);
	}
	if(pivotFinalPos < end)
	{
		numberOfComparisons += end - pivotFinalPos;
		naivequicksort(input, pivotFinalPos + 1, end, numberOfComparisons);
	}
}

template<typename T>
void naivequicksort2(std::vector<T> * input, int start, int end, int &numberOfComparisons)
{
	if(start == end)
	{
		return;
	}
	int pivotIndex = end;
	int pivotFinalPos = partition(input, pivotIndex, start, end);
	if(pivotFinalPos > start)
	{
		numberOfComparisons += pivotFinalPos - start;
		naivequicksort2(input, start, pivotFinalPos - 1, numberOfComparisons);
	}
	if(pivotFinalPos < end)
	{
		numberOfComparisons += end - pivotFinalPos;
		naivequicksort2(input, pivotFinalPos + 1, end, numberOfComparisons);
	}
}

template<typename T>
int medianof3(int start, T a, int middle, T b, int end,  T c)
{
	if(a <= b)
	{
		if(c <= a) return start;
		else if(c >= b) return middle;
		else return end;
	}
	else
	{
		// b < a
		if(c <= b) return middle;
		else if (c >= a) return start;
		else return end;
	}
}

template<typename T>
void medianof3quicksort(std::vector<T> * input, int start, int end, int &numberOfComparisons)
{
	if(start == end)
	{
		return;
	}
	int pivotIndex = medianof3(start, input->at(start), start + (end - start)/2, input->at(start + (end - start)/2), end, input->at(end));
	int pivotFinalPos = partition(input, pivotIndex, start, end);
	if(pivotFinalPos > start)
	{
		numberOfComparisons += pivotFinalPos - start;
		medianof3quicksort(input, start, pivotFinalPos - 1, numberOfComparisons);
	}
	if(pivotFinalPos < end)
	{
		numberOfComparisons += end - pivotFinalPos;
		medianof3quicksort(input, pivotFinalPos + 1, end, numberOfComparisons);
	}
}

template<typename T>
void quicksort(std::vector<T> * input)
{
	randomizedquicksort(input, 0, input->size() - 1);
}


template<int> std::vector<int> * mergesort(std::vector<int> * input, bool (*compare)(const void *, const void *));



#endif /* SORTING_H_ */
