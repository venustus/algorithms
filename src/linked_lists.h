/*
 * linked_lists.h
 *
 *  Created on: May 5, 2013
 *      Author: venkat
 */


using namespace std;

#ifndef LINKED_LISTS_H_
#define LINKED_LISTS_H_

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <type_traits>
#include "linked_list_node.h"

/**
 * A linked list implementation.
 * This can be used as both double linked list or singly linked list.
 */
template <class T>
class LinkedList
{
	typedef unordered_map<T, int> HashTable;
	typedef unordered_map<T, Node<T> * > ValueHash;
	Node<T> * head;
	Node<T> * tail;
	int listSize;

	void init(vector<T> mylist, bool uniqueElements);

public:
	LinkedList();

	/**
	 * Constructs a linked list from all the elements in a given vector.
	 * Duplicate elements can be present.
	 */
	LinkedList(vector<T> mylist);

	/**
	 * Same as above, but duplicates are not taken from the list.
	 * Instead, when an element repeats, the list is made circular.
	 */
	LinkedList(vector<T> mylist, bool uniqueElements);

	/**
	 * Deletes all nodes with duplicate values and leaves only one node per value.
	 * Returns the new head of the list.
	 * Time complexity: O(n) where n is the number of elements in the list
	 * Space complexity: O(n) where n is the number of elements in the list
	 */
	Node<T> * deleteDuplicates();

	/**
	 * Deletes a single node from the list.
	 * Returns the next element.
	 * Time complexity: O(1)
	 * Space complexity: O(1)
	 */
	Node<T> * deleteNode(Node<T> *node);

	/**
	 * Returns kth element from rear end of the list.
	 * Assumes the list is a singly linked list. This method does not use
	 * the back references.
	 * Time complexity: O(n) where n is the number of elements in the list.
	 * Space complexity: O(1)
	 */
	T kthElementFromRear(int k);

	/**
	 * Appends a new node to the list.
	 * Time complexity: O(1)
	 * Space complexity: O(1)
	 */
	void append(Node<T> *node);

	/**
	 * Appends the new node at the beginning of the list and returns the new head.
	 * Time complexity: O(1)
	 * Space complexity: O(1)
	 */
	Node<T> * appendHead(Node<T> *node);

	/**
	 * Appends another list to the end of the current list.
	 * Time complexity: O(1)
	 * Space complexity: O(1)
	 */
	void appendList(LinkedList<T> * otherList);

	/**
	 * Inserts a given node next to another given node.
	 * Time complexity: O(1)
	 * Space complexity: O(1)
	 */
	void insert(Node<T> *node, Node<T> *nextTo);

	/**
	 * You can use standard [] operator to access elements by index.
	 * Time complexity: O(n)
	 * Space complexity: O(1)
	 */
	Node<T> & operator[] (int n);

	/**
	 * Compares the current linked list to other element by element
	 * and returns true only if all elements are equal.
	 * Time complexity: O(n)
	 * Space complexity: O(1)
	 */
	bool operator==(const LinkedList<T> &other);

	/**
	 * Compares the current linked list to other element by element
	 * and returns true only if all elements are not equal or number of
	 * elements is not same.
	 * Time complexity: O(n)
	 * Space complexity: O(1)
	 */
	bool operator!=(const LinkedList<T> &other);

	/**
	 * Deletes a node by taking directly the pointer for the node to be deleted.
	 * Deletes in constant time.
	 * Time complexity: O(1)
	 * Space complexity: O(1)
	 */
	void deleteNodeSingle(Node<T> *node);

	/**
	 * Rearranges elements of the linked list so that all the elements whose
	 * value is less than x are on the left of x, while all those whose value is
	 * greater than x are on the right of x.
	 * Time complexity: O(n)
	 * Space complexity: O(1)
	 */
	void rearrange(T x);

	/**
	 * Prints the linked list to standard output.
	 * Time complexity: O(n)
	 * Space complexity: O(1)
	 */
	void print();

	Node<T> * getHead();

	Node<T> * getTail();

	/**
	 * Checks if the list elements form a palindrome.
	 * Time complexity: O(n)
	 * Space complexity: O(n/2)
	 */
	bool isPalindrome();

	/**
	 * Detects a cycle in the current linked list and returns the
	 * first node in the cycle if one exists and NULL otherwise.
	 * Time complexity: O(n)
	 * Space complexity: O(1)
	 */
	Node<T> * cycleStart();

	int size();
};

template<class T>
void LinkedList<T>::init(vector<T> list, bool uniqueElements)
{
	ValueHash *hashList = new ValueHash;
	for(typename vector<T>::iterator it = list.begin(); it != list.end(); ++it)
	{
		typename ValueHash::const_iterator myValue = hashList->find(*it);
		if(myValue != hashList->end() && uniqueElements)
		{
			tail->setNext(myValue->second);
		}
		else
		{
			Node<T> *node = new Node<T>(*it);
			append(node);
			pair<T, Node<T> * > myPair = make_pair(*it, node);
			hashList->insert(myPair);
		}
	}
	delete(hashList);
}
template<class T>
LinkedList<T>::LinkedList(vector<T> list, bool uniqueElements)
{
	head = NULL;
	tail = NULL;
	listSize = 0;
	init(list, uniqueElements);
}

template<class T>
LinkedList<T>::LinkedList(vector<T> list)
{
	head = NULL;
	tail = NULL;
	listSize = 0;
	init(list, false);
}

template<typename T>
LinkedList<T>::LinkedList()
{
	head = NULL;
	tail = NULL;
	listSize = 0;
}

template<class T>
int LinkedList<T>::size()
{
	return listSize;
}

template<class T>
Node<T> * LinkedList<T>::deleteDuplicates()
{
	HashTable *hashTable = new HashTable;
	Node<T> *temp = head;
	if(!temp)
	{
		return temp;
	}
	pair<T, int> myPair = make_pair(temp->getValue(), 1);
	hashTable->insert(myPair);
	while(temp->getNext())
	{
		if(hashTable->find(temp->getNext()->getValue()) != hashTable->end())
		{
			deleteNode(temp->getNext());
		}
		else
		{
			hashTable->insert(make_pair<T, int>(temp->getNext()->getValue(), 1));
			temp = temp->getNext();
		}
		if(!temp)
		{
			break;
		}
	}
	return head;
}

template<class T>
Node<T> * LinkedList<T>::deleteNode(Node<T> * node)
{
	Node<T> *prev = node->getPrev();
	Node<T> *next = node->getNext();
	if(prev)
	{
		prev->setNext(node->getNext());
	}
	else
	{
		head = node->getNext();
	}
	if(next)
	{
		next->setPrev(node->getPrev());
	}
	else
	{
		tail = node->getPrev();
	}
	delete(node);
	return next;
}

template<class T>
T LinkedList<T>::kthElementFromRear(int k)
{
	if(!head)
	{
		return NULL;
	}
	int l = 0;
	Node<T> *ptr1 = head;
	Node<T> *ptr2 = head;
	while(ptr1)
	{
		ptr1 = ptr1->getNext();
		if(l >= k)
		{
			ptr2 = ptr2->getNext();
		}
		l++;
	}
	if(l < k)
	{
		return NULL;
	}
	return ptr2->getValue();
}

template<class T>
void LinkedList<T>::append(Node<T> * node)
{
	if(!tail)
	{
		tail = node;
		head = tail;
	}
	else
	{
		tail->setNext(node);
		node->setPrev(tail);
		tail = node;
	}
	listSize++;
}

template<class T>
Node<T> * LinkedList<T>::appendHead(Node<T> *node)
{
	if(!head)
	{
		head = node;
		tail = head;
	}
	else
	{
		node->setNext(head);
		head->setPrev(node);
		head = node;
	}
	listSize++;
	return head;
}

template<class T>
void LinkedList<T>::appendList(LinkedList<T> * otherList)
{
	if(!head)
	{
		head = otherList->getHead();
		tail = otherList->getTail();
		return;
	}
	tail->setNext(otherList->getHead());
	otherList->getHead()->setPrev(tail);
	tail = otherList->getTail();
	listSize += otherList->size();
}

template<class T>
void LinkedList<T>::insert(Node<T> *node, Node<T> *nextTo)
{
	if(nextTo && node)
	{
		if(nextTo->getNext()){
			nextTo->getNext()->setPrev(node);
		}
		node->setNext(nextTo->getNext());
		nextTo->setNext(node);
		node->setPrev(nextTo);
		listSize++;
		std::cout << "List size is now: " << listSize << std::endl;
	}
}

template<class T>
Node<T> & LinkedList<T>::operator [](int n)
{
	int i = 0;
	if(!head)
	{
		Node<T> nullNode(NULL);
		return nullNode;
	}
	Node<T> *temp = head;
	while(temp && i < n)
	{
		temp = temp->getNext();
		i++;
	}
	return *temp;
}

template<class T>
bool LinkedList<T>::operator==(const LinkedList<T> &other)
{
	Node<T> * mytrack = this->head;
	Node<T> * othertrack = other.head;
	while(mytrack && othertrack)
	{
		if(mytrack->getValue() != othertrack->getValue())
		{
			return false;
		}
		mytrack = mytrack->getNext();
		othertrack = othertrack->getNext();
	}
	if(mytrack || othertrack)
	{
		return false;
	}
	return true;
}

template<class T>
bool LinkedList<T>::operator!=(const LinkedList<T> &other)
{
	return !(*this == other);
}

template<class T>
void LinkedList<T>::deleteNodeSingle(Node<T> * node)
{
	if(!node)
	{
		return;
	}
	Node<T> *nextNode = node->getNext();
	if(nextNode)
	{
		node->setValue(nextNode->getValue());
		node->setNext(nextNode->getNext());
		if(nextNode->getNext())
		{
			nextNode->getNext()->setPrev(node);
		}
		delete(nextNode);
	}
}

template<class T>
void LinkedList<T>::rearrange(T x)
{
	Node<T> *temp = head;
	Node<T> *tailTrack = tail;
	if(!head || head == tail)
	{
		return;
	}
	while(temp && temp != tailTrack)
	{
		if(temp->getValue() >= x)
		{
			Node<T> *move = temp;
			temp = move->getNext();
			if(move->getPrev())
			{
				move->getPrev()->setNext(move->getNext());
			}
			if(temp->getNext())
			{
				move->getNext()->setPrev(move->getPrev());
			}
			tail->setNext(move);
			move->setPrev(tail);
			tail = tail->getNext();
			tail->setNext(NULL);
		}
		else
		{
			temp = temp->getNext();
		}
	}
	if(temp == tailTrack)
	{
		if(temp->getValue() >= x)
		{
			Node<T> *move = temp;
			temp = move->getNext();
			if(move->getPrev())
			{
				move->getPrev()->setNext(move->getNext());
			}
			if(temp->getNext())
			{
				move->getNext()->setPrev(move->getPrev());
			}
			tail->setNext(move);
			move->setPrev(tail);
			tail = tail->getNext();
			tail->setNext(NULL);
		}
	}
}

template<class T>
void LinkedList<T>::print()
{
	if(head)
	{
		Node<T> *temp = head;
		while(temp)
		{
			T t = temp->getValue();
			if(std::is_pointer<T>::value)
			{
				//std::cout << *t << ' ';
			}
			else
			{
				std::cout << t << ' ';
			}
			temp = temp->getNext();
		}
		std::cout << endl;
	}
}

template<class T>
Node<T> * LinkedList<T>::getHead()
{
	return head;
}

template<class T>
Node<T> * LinkedList<T>::getTail()
{
	return tail;
}

template<class T>
bool LinkedList<T>::isPalindrome()
{
	stack<Node<T> * > * elementStack = new stack<Node<T> * >;
	Node<T> * fastRunner = head;
	Node<T> * slowRunner = head;
	while(fastRunner)
	{
		elementStack->push(slowRunner);
		slowRunner = slowRunner->getNext();
		if(fastRunner->getNext())
		{
			fastRunner = fastRunner->getNext()->getNext();
		}
		else
		{
			fastRunner = NULL;
			elementStack->pop();
		}
	}
	while(slowRunner)
	{
		Node<T> *top = elementStack->top();
		elementStack->pop();
		if(slowRunner->getValue() != top->getValue())
		{
			return false;
		}
		slowRunner = slowRunner->getNext();
	}
	return true;
}

template<class T>
Node<T> * LinkedList<T>::cycleStart()
{
	Node<int> *fastRunner = head;
	Node<int> *slowRunner = head;
	while(fastRunner)
	{
		fastRunner = fastRunner->getNext()->getNext();
		slowRunner = slowRunner->getNext();
		if(fastRunner == slowRunner)
		{
			cout << "Detected a cycle" << endl;
			break;
		}
	}
	slowRunner = head;
	while(slowRunner != fastRunner)
	{
		slowRunner = slowRunner->getNext();
		fastRunner = fastRunner->getNext();
	}
	return fastRunner;
}


#endif /* LINKED_LISTS_H_ */
