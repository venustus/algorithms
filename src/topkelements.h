/*
 * topkelements.h
 *
 *  Created on: Jul 27, 2013
 *      Author: venkat
 */

#ifndef TOPKELEMENTS_H_
#define TOPKELEMENTS_H_

template<typename T>
BinaryHeap<T> * findTopk(std::vector<T> * allElements, int k)
{
	// for finding top k elements we need a minheap
	BinaryHeap<T> * heap = new BinaryHeap<T>(new std::vector<T>, false);
	for(typename std::vector<T>::iterator it = allElements->begin(); it != allElements->end(); ++it)
	{
		T val = *it;
		if(heap->findTop())
		{
			if(heap->findTop() < val)
			{
				if(heap->size() == k)
				{
					heap->removeTop();
				}
				heap->insert(val);
			}
		}
		else
		{
			heap->insert(val);
		}
	}
	return heap;
}

template BinaryHeap<int> * findTopk(std::vector<int> *, int);
#endif /* TOPKELEMENTS_H_ */
