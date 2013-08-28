/*
 * stable_partition.cpp
 *
 *  Created on: Aug 27, 2013
 *      Author: venkat
 */

#include "stable_partition.h"

void swap(int a[], int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void merge(int a[], int startIndex, int middleIndex, int endIndex)
{
	int i = startIndex, j = middleIndex + 1;
	while(i <= middleIndex && j <= endIndex)
	{
		if(a[i] < 0)
		{
			i++;
			continue;
		}
		if(a[j] < 0)
		{
			swap(a, i++, j++);
		}
	}
}

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


