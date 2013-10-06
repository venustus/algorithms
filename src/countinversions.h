/*
 * countinversions.h
 *
 *  Created on: Jul 30, 2013
 *      Author: venkat
 */

#ifndef COUNTINVERSIONS_H_
#define COUNTINVERSIONS_H_

template<typename T>
std::vector<T> * mergeAndCountSplitInversions(std::vector<T> * sortedFirstHalf,
											  std::vector<T> * sortedSecondHalf,
											  long long int &splitInversions)
{
	std::vector<T> * sortedArray = new std::vector<T>;
	int i = 0, j = 0;
	splitInversions = 0;
	while(i < sortedFirstHalf->size() && j < sortedSecondHalf->size())
	{
		if(sortedFirstHalf->at(i) < sortedSecondHalf->at(j))
		{
			sortedArray->push_back(sortedFirstHalf->at(i));
			i++;
		}
		else
		{
			sortedArray->push_back(sortedSecondHalf->at(j));
			j++;
			splitInversions += (sortedFirstHalf->size() - i);
		}
	}
	while(i < sortedFirstHalf->size())
	{
		sortedArray->push_back(sortedFirstHalf->at(i));
		i++;
	}
	while(j < sortedSecondHalf->size())
	{
		sortedArray->push_back(sortedSecondHalf->at(j));
		j++;
	}
	return sortedArray;
}

/**
 * Problem:
 * Sort an array 'arr' and also count the number of inversions in the array.
 * An inversion is any pair of elements a[i], a[j] such that a[i] < a[j], but i > j.
 *
 * Paradigm: Divide and conquer
 * Algorithm:
 * 1) Divide the array into two halves.
 * 2) Recursively, sort and count inversions in the left half and right half.
 * 3) Now that the left half is sorted and right half is sorted,
 *    merge both the halves into a single sorted array while also counting
 *    split inversions.
 * 4) Merging is trivial just like in merge sort. When comparing an element a[i]
 *    with an element a[j] where i and j are indexes in left half and right
 *    half respectively, if a[i] > a[j], merge routine picks a[j], but at the same
 *    time increments the split inversion count by (number of elements in right half - j).
 * 5) Sum up the total number of inversions - inversions from left half, inversions from
 *    right half and the number of split inversions counted by merge routine.
 * 6) Return the sorted array and the count of split inversions.
 *
 * Time complexity: O(n log n)
 * Space complexity: O(n)
 */
template<typename T>
std::vector<T> * sortAndCountInversions(std::vector<T> * arr, long long int &count)
{
	if(arr->size() == 1)
	{
		count = 0;
		return new std::vector<T>(arr->begin(), arr->end());
	}
	std::vector<T> * firstHalf = new std::vector<T>(arr->begin(), arr->begin() + (arr->size()/2));
	std::vector<T> * secondHalf = new std::vector<T>(arr->begin() + (arr->size()/2), arr->end());
	long long int countFirstHalf, countSecondHalf;

	std::vector<T> * sortedFirstHalf = sortAndCountInversions(firstHalf, countFirstHalf);
	std::vector<T> * sortedSecondHalf = sortAndCountInversions(secondHalf, countSecondHalf);

	long long int splitInversions;
	std::vector<T> * sortedArray = mergeAndCountSplitInversions(sortedFirstHalf,
																sortedSecondHalf,
																splitInversions);
	delete firstHalf;
	delete sortedFirstHalf;
	delete secondHalf;
	delete sortedSecondHalf;
	count = countFirstHalf + countSecondHalf + splitInversions;
	return sortedArray;
}


#endif /* COUNTINVERSIONS_H_ */
