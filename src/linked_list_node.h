/*
 * linked_list_node.h
 *
 *  Created on: May 13, 2013
 *      Author: venkat
 */

#ifndef LINKED_LIST_NODE_H_
#define LINKED_LIST_NODE_H_

using namespace std;

template <class T>
class Node
{
	T val;
	Node *next;
	Node *prev;

public:
	Node(T val, Node *next, Node *prev);

	Node(T val);


	Node<T> * getNext();

	Node<T> * getPrev();

	void setNext(Node<T> *next);

	void setPrev(Node<T> *prev);

	T getValue();

	void setValue(T val);
};

template<class T>
Node<T>::Node(T val, Node<T> *next, Node<T> *prev)
{
	this->val = val;
	this->next = next;
	this->prev = prev;
}

template<class T>
Node<T>::Node(T val)
{
	this->val = val;
	this->next = NULL;
	this->prev = NULL;
}

template<class T>
Node<T> * Node<T>::getNext()
{
	return next;
}

template<class T>
Node<T> * Node<T>::getPrev()
{
	return prev;
}

template<class T>
void Node<T>::setNext(Node<T> * next)
{
	this->next = next;
}

template<class T>
void Node<T>::setPrev(Node<T> * prev)
{
	this->prev = prev;
}

template<class T>
T Node<T>::getValue()
{
	return val;
}

template<class T>
void Node<T>::setValue(T val)
{
	this->val = val;
}

#endif /* LINKED_LIST_NODE_H_ */
