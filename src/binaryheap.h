/*
 * binaryheap.h
 *
 *  Created on: Jul 25, 2013
 *      Author: venkat
 */

#include <vector>
#include <functional>

using namespace std;

#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_


/**
 * Binary max heap data structure.
 * Provides constant time look up for maximum element and
 * logarithmic time implementations for insertion, removal
 * and increase key operations.
 *
 */
template<class T>
class BinaryHeap
{
	std::vector<T> * array;
	bool maxHeap;
	tr1::function<bool(T, T)> compareObj;
	void heapify(int index);
	int getParentIndex(int i);
	int getLeftChild(int i);
	int getRightChild(int i);
public:
	BinaryHeap(std::vector<T> * arr, bool maxHeap);

	/**
	 * Complexity: O(1)
	 */
	T findTop();

	/**
	 * Complexity: O(log n)
	 */
	void removeTop();

	/**
	 * Complexity: O(log n)
	 */
	void insert(T val);

	/**
	 * Complexity: O(log n)
	 */
	void enhanceKey(int index, T by);

	/**
	 * Complexity: O(n)
	 */
	int find(T key);

	int size();

	std::vector<T> * getNodeArray();
};

/**
 * Constructs a binary heap from an array in O(n) time.
 */
template<class T>
BinaryHeap<T>::BinaryHeap(std::vector<T> * arr, bool isMaxHeap)
{
	if(isMaxHeap)
	{
		compareObj = std::greater<T>();
	}
	else
	{
		compareObj = std::less<T>();
	}
	array = arr;
	if(array->size() > 0)
	{
		for(int i = std::floor(arr->size()/2) - 1; i >= 0; i--)
		{
			heapify(i);
		}
	}
	maxHeap = isMaxHeap;
}

template<class T>
void BinaryHeap<T>::heapify(int index)
{
	int temp = index;
	while(temp >= 0)
	{
		T largest = array->at(temp);
		int leftChildIndex = getLeftChild(temp);
		int rightChildIndex = getRightChild(temp);
		int largestIndex = temp;
		if(leftChildIndex > 0 &&
				compareObj(array->at(leftChildIndex), largest))
		{
			largest = array->at(leftChildIndex);
			largestIndex = leftChildIndex;
		}
		if(rightChildIndex > 0 && compareObj(array->at(rightChildIndex), largest))
		{
			largest = array->at(rightChildIndex);
			largestIndex = rightChildIndex;
		}
		if(largest != array->at(temp))
		{
			T tmp = largest;
			array->at(largestIndex) = array->at(temp);
			array->at(temp) = tmp;
			temp = largestIndex;
		}
		else
		{
			break;
		}
	}
}

template<class T>
int BinaryHeap<T>::getParentIndex(int i)
{
	if(i%2 == 0)
	{
		return ((i / 2) - 1);
	}
	else
	{
		return i / 2;
	}
}

template<class T>
int BinaryHeap<T>::getLeftChild(int i)
{
	if(((2 * i) + 1) < array->size())
	{
		return 2 * i + 1;
	}
	else
	{
		return -1;
	}
}

template<class T>
int BinaryHeap<T>::getRightChild(int i)
{
	if(((2 * i) + 2) < array->size())
	{
		return 2 * i + 2;
	}
	else
	{
		return -1;
	}
}

template<class T>
void BinaryHeap<T>::insert(T val)
{
	array->push_back(val);
	int parentIndex = getParentIndex(array->size() - 1);
	int currentIndex = array->size() - 1;
	while(parentIndex >= 0)
	{
		if(compareObj(array->at(currentIndex), array->at(parentIndex)))
		{
			T tmp = array->at(currentIndex);
			array->at(currentIndex) = array->at(parentIndex);
			array->at(parentIndex) = tmp;
			currentIndex = parentIndex;
			parentIndex = getParentIndex(currentIndex);
		}
		else
		{
			break;
		}
	}
}

template<class T>
T BinaryHeap<T>::findTop()
{
	if(array->size() > 0)
	{
		return array->at(0);
	}
	else
	{
		return NULL;
	}
}

template<class T>
int BinaryHeap<T>::find(T key)
{
	for(typename std::vector<T>::iterator it = array->begin(); it != array->end(); ++it)
	{
		if(key == *it)
		{
			return it - array->begin();
		}
	}
	return -1;
}

template<class T>
void BinaryHeap<T>::removeTop()
{
	if(array->size() == 0)
	{
		return;
	}
	if(array->size() == 1)
	{
		array->pop_back();
		return;
	}
	T tmp = array->at(0);
	array->at(0) = array->at(array->size() - 1);
	array->at(array->size() - 1) = tmp;
	array->pop_back();
	heapify(0);
}

template<class T>
void BinaryHeap<T>::enhanceKey(int index, T by)
{
	if(maxHeap)
	{
		array->at(index) = array->at(index) + by;
	}
	else
	{
		array->at(index) = array->at(index) - by;
	}
	int parentIndex = getParentIndex(index);
	int currentIndex = index;
	while(parentIndex >= 0)
	{
		if(compareObj(array->at(currentIndex), array->at(parentIndex)))
		{
			T tmp = array->at(currentIndex);
			array->at(currentIndex) = array->at(parentIndex);
			array->at(parentIndex) = tmp;
			currentIndex = parentIndex;
			parentIndex = getParentIndex(currentIndex);
		}
		else
		{
			break;
		}
	}
}

template<class T>
int BinaryHeap<T>::size()
{
	return array->size();
}

template<class T>
std::vector<T> * BinaryHeap<T>::getNodeArray()
{
	return array;
}

#endif /* BINARYHEAP_H_ */
