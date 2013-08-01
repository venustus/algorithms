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
											  int &splitInversions)
{
	std::vector<T> * sortedArray = new std::vector<T>;
	int i = 0, j = 0;
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

template<typename T>
std::vector<T> * sortAndCountInversions(std::vector<T> * arr, int &count)
{
	if(arr->size() == 1)
	{
		count = 0;
		return new std::vector<T>(arr->begin(), arr->end());
	}
	std::vector<T> * firstHalf = new std::vector<T>(arr->begin(), arr->begin() + (arr->size()/2));
	std::vector<T> * secondHalf = new std::vector<T>(arr->begin() + (arr->size()/2), arr->end());
	int countFirstHalf, countSecondHalf;

	std::vector<T> * sortedFirstHalf = sortAndCountInversions(firstHalf, countFirstHalf);
	std::vector<T> * sortedSecondHalf = sortAndCountInversions(secondHalf, countSecondHalf);

	int splitInversions;
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
