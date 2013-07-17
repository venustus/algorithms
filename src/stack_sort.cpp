/*
 * stack_sort.cpp
 *
 *  Created on: Jun 3, 2013
 *      Author: venkat
 */

#include "stack_sort.h"

template<class T>
void sort(stack<T> * st)
{
	stack<T> * buffer = new stack<T>;
	while(!st->empty())
	{
		while(buffer->empty() || st->top() <= buffer->top())
		{
			buffer->push(st->top());
			st->pop();
		}
		T temp = st->top();
		st->pop();
		int i = 0;
		while(!buffer->empty() && temp > buffer->top())
		{
			st->push(buffer->top());
			buffer->pop();
			i++;
		}
		buffer->push(temp);
		while(i > 0)
		{
			buffer->push(st->top());
			st->pop();
			i--;
		}
	}
	while(!buffer->empty())
	{
		st->push(buffer->top());
		buffer->pop();
	}
	delete buffer;
}

template void sort<int>(stack<int> * st);

