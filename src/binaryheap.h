/*
 * binaryheap.h
 *
 *  Created on: Jul 25, 2013
 *      Author: venkat
 */


using namespace std;

#include <vector>
#include <tr1/functional>
#include <tr1/unordered_map>

#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_


/**
 * Binary max heap or min heap data structure.
 * Provides constant time look up for maximum element (or minimum element) and
 * logarithmic time implementations for insertion, removal
 * and increase key operations.
 *
 * The heap is backed by an array where indexes are used
 * to track parent-child relationships.
 *
 * See documentation for individual methods for algorithm
 * and complexity analysis.
 */
template<class T>
class BinaryHeap
{
	std::vector<T> * array;
	tr1::function<bool(T, T)> compareObj;
	bool maxHeap;
	void heapify(int index);
	int getParentIndex(int i);
	int getLeftChild(int i);
	int getRightChild(int i);
public:
	BinaryHeap(std::vector<T> * arr, bool maxHeap);
	~BinaryHeap();
	T findTop();
	void removeTop();
	void insert(T val);
	void enhanceKey(int index, T by);
	void findAndUpdateKey(T key, T newKey);
	int find(T key);
	int size();
	std::vector<T> * getNodeArray();
};

/**
 * Constructs a binary heap from an array.
 * @param arr the array from which the heap must be initialized.
 *            heap is maintained in place - array is modified
 *            to satisfy heap property.
 * @param isMaxHeap pass true if you want a max heap - that is
 * 		  the maximum element at the top. Otherwise the minimum
 * 		  element would be at the top.
 *
 * Time complexity: O(n)
 * 				    This is achieved by continuously heapifying
 * 				    non-leaf elements only. In a full binary tree
 * 				    there will be approximately only n/2 non-leaf
 * 				    elements. Doing some math, this will turn out
 * 				    to be O(n) overall.
 * Space complexity: O(1) - uses no extra space other than the
 * 					 array passed as input.
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
BinaryHeap<T>::~BinaryHeap()
{
	// nothing to clean up as array comes from outside
}

/**
 * Heapifies or bubbles down heap element at index
 * iteratively till we reach a NULL pointer or
 * the node fits in exactly satisfying heap property.
 * Algorithm:
 * 1) Pick the largest of the current element, left child
 *    and right child.
 * 2) If largest is the same element heap property is satisfied
 *    already. Exit the sub-routine.
 * 3) Else exchange the largest element with the current and
 *    go to step 1 again.
 * 4) If an element has no children, then exit.
 *
 * Time complexity: O(log n)
 * Space complexity: O(1)
 */
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

/**
 * Inserts a new element in the heap.
 * This inserts the element at the bottom of the heap
 * and bubbles it up until it fits into the heap property
 * or we reach the root.
 *
 * Time complexity: O(log n)
 * Space complexity: O(1)
 */
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

/**
 * Returns the maximum or minimum element.
 * This is nothing but the first element in the array
 * (or the root of the heap).
 *
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
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

/**
 * Searches the heap for a given key and
 * returns the array index if found or -1
 * if not found.
 * This essentially does a linear search on
 * the underlying array.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template<class T>
int BinaryHeap<T>::find(T key)
{
	for(typename std::vector<T>::iterator it = array->begin(); it != array->end(); ++it)
	{
		if(*it == key)
		{
			return it - array->begin();
		}
	}
	return -1;
}

/**
 * Removes the maximum or minimum element from the heap.
 * This does it by exchanging the last element of the array
 * with the root, removing the last element and then calling
 * heapify on new root.
 *
 * Time complexity: O(log n)
 * Space complexity: O(1)
 */
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

/**
 * Searches the heap for a given key and
 * enhances the key to a new value 'newKey'.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template<class T>
void BinaryHeap<T>::findAndUpdateKey(T key, T newKey)
{
	int index = find(key);
	if(maxHeap && newKey > array->at(index))
	{
		enhanceKey(index, newKey);
	}
	else if(!maxHeap && newKey < array->at(index))
	{
		enhanceKey(index, newKey);
	}
}

/**
 * Enhances the key of an element at given index to
 * 'dest'. If it is a max heap, this means key is increased
 * to 'dest' wile if it is a min heap, key is decreased to dest.
 * It is assumed that the new key 'dest' is more than the old key
 * if it is max heap or new key 'dest' is less than the old key
 * if it is min heap.
 *
 * This follows the bubble-up approach. After updating the key,
 * the heap property may be disturbed in one of the parents. So
 * we just traverse the heap upwards towards the root and keep
 * exchanging the parent and child as long as heap property is
 * dissatisfied.
 *
 * Time complexity: O(log n)
 * Space complexity: O(1)
 */
template<class T>
void BinaryHeap<T>::enhanceKey(int index, T dest)
{
	T initialValue = array->at(index);
	array->at(index) = dest;
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

/**
 * Returns the size of the heap.
 */
template<class T>
int BinaryHeap<T>::size()
{
	return array->size();
}

/**
 * Returns the underlying array which backs the heap.
 */
template<class T>
std::vector<T> * BinaryHeap<T>::getNodeArray()
{
	return array;
}

#endif /* BINARYHEAP_H_ */
