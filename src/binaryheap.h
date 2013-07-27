/*
 * binaryheap.h
 *
 *  Created on: Jul 25, 2013
 *      Author: venkat
 */

#include <vector>
#include <functional>
#include "binarytree.h"

#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_


/**
 * Binary max heap data structure.
 * Provides constant time look up for maximum element and
 * logarithmic time implementations for insertion, removal
 * and increase key operations.
 *
 * This implementation derives from BinaryTree and uses
 * a tree data structure to store its nodes. So, it takes O(n)
 * extra space and does not change/need the original array
 * used to construct the heap.
 *
 * But an alternative implementation that solely depends on
 * the input array and does not need any additional space
 * can exist (and should be used for any production code)
 * with minor changes to this implementation.
 * (You only need to change getParent, getLeft and getRight
 * methods).
 */
template<class T>
class BinaryHeap: public BinaryTree<T>
{
	bool maxHeap;
	tr1::function<bool(T, T)> compareObj;
	void heapify(TreeNode<T> * node);
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
	void enhanceKey(TreeNode<T> * node, int by);

	int size();
};

template<class T>
BinaryHeap<T>::BinaryHeap(std::vector<T> * arr, bool isMaxHeap): BinaryTree<T>(arr)
{
	if(isMaxHeap)
	{
		compareObj = std::greater<T>();
	}
	else
	{
		compareObj = std::less<T>();
	}
	if(arr->size() > 0)
	{
		for(int i = std::floor(arr->size()/2); i >= 0; i--)
		{
			heapify(BinaryTree<T>::nodeArray->at(i));
		}
	}
	maxHeap = isMaxHeap;
}

template<class T>
void BinaryHeap<T>::heapify(TreeNode<T> * node)
{
	while(node)
	{
		TreeNode<T> * largest = node;
		if(node->getLeft() && compareObj((*(node->getLeft())).getValue(), (*node).getValue()))
		{
			largest = node->getLeft();
		}
		if(node->getRight() && compareObj((*(node->getRight())).getValue(), (*largest).getValue()))
		{
			largest = node->getRight();
		}
		if(largest != node)
		{
			T tmp = largest->getValue();
			largest->setValue(node->getValue());
			node->setValue(tmp);
			node = largest;
		}
		else
		{
			break;
		}
	}
}

template<class T>
void BinaryHeap<T>::insert(T val)
{
	TreeNode<T> * newNode = new TreeNode<T>(val);
	BinaryTree<T>::appendNode(newNode);
	TreeNode<T> * parent = newNode->getParent();
	while(parent)
	{
		if(compareObj(newNode->getValue(), parent->getValue()))
		{
			T tmp = newNode->getValue();
			newNode->setValue(parent->getValue());
			parent->setValue(tmp);
			newNode = parent;
			parent = parent->getParent();
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
	if(BinaryTree<T>::root)
	{
		return BinaryTree<T>::root->getValue();
	}
	else
	{
		return NULL;
	}
}

template<class T>
void BinaryHeap<T>::removeTop()
{
	if(BinaryTree<T>::nodeArray == NULL || BinaryTree<T>::nodeArray->size() == 0)
	{
		return;
	}
	if(BinaryTree<T>::nodeArray->size() == 1)
	{
		BinaryTree<T>::nodeArray->pop_back();
		return;
	}
	T tmp = BinaryTree<T>::nodeArray->at(0)->getValue();
	BinaryTree<T>::nodeArray->at(0)->setValue(BinaryTree<T>::nodeArray->at(BinaryTree<T>::nodeArray->size() - 1)->getValue());
	BinaryTree<T>::nodeArray->at(BinaryTree<T>::nodeArray->size() - 1)->setValue(tmp);
	TreeNode<T> * lastNode = BinaryTree<T>::nodeArray->at(BinaryTree<T>::nodeArray->size() - 1);
	TreeNode<T> * parent = lastNode->getParent();
	if(parent->getLeft() == lastNode)
	{
		parent->setLeft(NULL);
	}
	else
	{
		parent->setRight(NULL);
	}
	BinaryTree<T>::nodeArray->pop_back();
	heapify(BinaryTree<T>::root);
}

template<class T>
void BinaryHeap<T>::enhanceKey(TreeNode<T> * node, int by)
{
	if(maxHeap)
	{
		node->setValue(node->getValue() + by);
	}
	else
	{
		node->setValue(node->getValue() - by);
	}
	TreeNode<T> * parent = node->getParent();
	while(parent)
	{
		if(compareObj(node->getValue(), parent->getValue()))
		{
			T tmp = node->getValue();
			node->setValue(parent->getValue());
			parent->setValue(tmp);
			node = parent;
			parent = parent->getParent();
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
	return BinaryTree<T>::nodeArray->size();
}

#endif /* BINARYHEAP_H_ */
