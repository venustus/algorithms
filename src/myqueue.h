/*
 * myqueue.h
 *
 *  Created on: Jun 2, 2013
 *      Author: venkat
 */

#include <stack>
#include <exception>

using namespace std;

#ifndef MYQUEUE_H_
#define MYQUEUE_H_

class EmptyQueueException: public exception
{
	virtual const char * what() const throw()
	{
		return "Queue is empty";
	}
};

template<class T>
class MyQueue
{
	stack<T> * newest;
	stack<T> * oldest;

public:
	MyQueue();

	void queue(T data);
	T dequeue();
	T peek();
};

template<class T>
MyQueue<T>::MyQueue()
{
	newest = new stack<T>;
	oldest = new stack<T>;
}

template<class T>
void MyQueue<T>::queue(T data)
{
	newest->push(data);
}

template<class T>
T MyQueue<T>::dequeue()
{
	T top = peek();
	oldest->pop();
	return top;
}

template<class T>
T MyQueue<T>::peek()
{
	if(oldest->empty()){
		while(!newest->empty())
		{
			oldest->push(newest->top());
			newest->pop();
		}
	}
	if(oldest->empty())
	{
		throw new EmptyQueueException;
	}
	return oldest->top();
}


#endif /* MYQUEUE_H_ */
