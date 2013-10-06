/*
 * stable_partition.cpp
 *
 *  Created on: Aug 27, 2013
 *      Author: venkat
 */

#include <iostream>
#include "stable_partition.h"

void swap(int a[], int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void print(int *a, int i, int j)
{
	for(int start = i; start <= j; start++)
	{
		std::cout << a[start] << " ";
	}
	std::cout << std::endl;
}

void reverse(int a[], int startIndex, int endIndex)
{
	while(startIndex < endIndex)
	{
		swap(a, startIndex++, endIndex--);
	}
}

void merge(int a[], int startIndex, int middleIndex, int endIndex)
{
	int i = startIndex;
	while(i <= middleIndex && a[i] < 0) i++;
	if(i > middleIndex)
	{
		// no positive integers in the left half
		// nothing to merge - we are already good
		return;
	}
	int j = middleIndex + 1;
	while(j <= endIndex && a[j] < 0) j++;
	if(j == middleIndex + 1)
	{
		// no negative integers in the right half
		// we are already good
		return;
	}
	if(j == i + 2)
	{
		// only two elements in array
		// just swap'em
		swap(a, i, j - 1);
		return;
	}
	int leftLen = middleIndex + 1 - i;
	int rightLen = j - middleIndex - 1;
	reverse(a, i, j - 1);
	reverse(a, i, i + rightLen - 1);
	reverse(a, j - leftLen, j - 1);
}


/**
 * Partitions array a into negative integers and positive integers
 * such that all negative integers precede all positive integers.
 * The relative ordering among negative integers and among positive
 * integers is retained.
 *
 * Paradigm: Divide and Conquer
 * Algorithm:
 * 1) Divide the array into two halves.
 * 2) Partition the left half and right half recursively.
 * 3) Consider the stretch from left mid-point to the right mid-point.
 * 4) Reverse this stretch and then reverse the first half and then
 *    reverse the right half.
 *
 * Time complexity: O(n log n)
 * Space complexity: O(1)
 */
void stablePartition(int a[], int startIndex, int endIndex)
{
	if(startIndex == endIndex)
	{
		return;
	}
	int middleIndex = startIndex + (endIndex - startIndex)/2;
	stablePartition(a, startIndex, middleIndex);
	stablePartition(a, middleIndex + 1, endIndex);
	merge(a, startIndex, middleIndex, endIndex);
}


