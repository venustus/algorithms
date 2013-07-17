/*
 * stack_min.h
 *
 *  Created on: May 29, 2013
 *      Author: venkat
 */

#include <stack>
using namespace std;

#ifndef STACK_MIN_H_
#define STACK_MIN_H_


/**
 * A stack which can retrieve minimum element in constant time
 * in addition to all standard stack operations.
 * Time complexity: O(1) for all operations
 * Space complexity: O(n) where n is the number of elements in stack
 */
template<class T>
class StackWithMin: public stack<T>
{
	typedef stack<T> super;
	stack<T> *minStack;

public:
	StackWithMin();

	void push(T data);

	void pop();

	T min();

	T top();
};

template<class T>
StackWithMin<T>::StackWithMin(): super()
{
	minStack = new stack<T>;
}

template<class T>
void StackWithMin<T>::push(T data)
{
	if(minStack->empty()){
		minStack->push(data);
	}
	else
	{
		if(minStack->top() > data)
		{
			minStack->push(data);
		}
	}
	super::push(data);
}

template<class T>
void StackWithMin<T>::pop()
{
	if(super::top() == minStack->top())
	{
		minStack->pop();
	}
	super::pop();
}

template<class T>
T StackWithMin<T>::min()
{
	return minStack->top();
}

template<class T>
T StackWithMin<T>:: top()
{
	return super::top();
}



#endif /* STACK_MIN_H_ */
