/*
 * mystack.h
 *
 *  Created on: Jul 23, 2013
 *      Author: venkat
 */

#include <queue>

#ifndef MYSTACK_H_
#define MYSTACK_H_

/**
 * Implements a stack using two queues.
 */
template<class T>
class MyStack
{
	std::queue<T> * queue1;
	std::queue<T> * queue2;
public:
	MyStack();
	void push(T val);
	void pop();
	T top();
	bool empty();
};

template<class T>
MyStack<T>::MyStack()
{
	queue1 = new std::queue<T>;
	queue2 = new std::queue<T>;
}

template<class T>
void MyStack<T>::push(T val)
{
	// we always push on empty queue transfer all the elements
	// in the non-empty queue into the originally empty queue
	std::queue<T> * pushqueue = (queue1->empty())?queue1:queue2;
	std::queue<T> * transferqueue = (queue1->empty())?queue2:queue1;
	pushqueue->push(val);
	while(!transferqueue->empty())
	{
		T front = transferqueue->front();
		transferqueue->pop();
		pushqueue->push(front);
	}
}

template<class T>
void MyStack<T>::pop()
{
	// pop always happens from the non-empty queue
	if(!queue1->empty())
	{
		queue1->pop();
	}
	queue2->pop();
}

template<class T>
T MyStack<T>::top()
{
	if(!queue1->empty())
	{
		return queue1->front();
	}
	return queue2->front();
}

template<class T>
bool MyStack<T>::empty()
{
	return queue1->empty() && queue2->empty();
}


#endif /* MYSTACK_H_ */
