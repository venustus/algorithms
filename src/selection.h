/*
 * selection.h
 *
 *  Created on: Aug 3, 2013
 *      Author: venkat
 */

#include <iostream>
#include "sorting.h"

#ifndef SELECTION_H_
#define SELECTION_H_

template<typename T>
T randomSelect(std::vector<T> * input, int start, int end, int order)
{
	if(start == end)
	{
		return input->at(start);
	}
	int pivotIndex = start + (rand() % (int)(end - start + 1));
	int pivotFinalPos = partition(input, pivotIndex, start, end);
	if(pivotFinalPos + 1 - start == order)
	{
		return input->at(pivotFinalPos);
	}
	else if(pivotFinalPos + 1 - start > order)
	{
		return randomSelect(input, start, pivotFinalPos - 1, order);
	}
	else
	{
		return randomSelect(input, pivotFinalPos + 1, end, order + start - pivotFinalPos - 1);
	}
}

template<typename T>
T randomSelect(std::vector<T> * input, int order)
{
	return randomSelect(input, 0, input->size() - 1, order);
}

#endif /* SELECTION_H_ */
