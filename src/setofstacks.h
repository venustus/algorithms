/*
 * setofstacks.h
 *
 *  Created on: May 30, 2013
 *      Author: venkat
 */

#include <vector>

using namespace std;
#ifndef SETOFSTACKS_H_
#define SETOFSTACKS_H_

template<class T>
class SetOfStacks
{
	unsigned int threshold;
	vector<stack<T> * > *stacks;
public:
	SetOfStacks(unsigned int threshold);

	void push(T data);

	void pop();

	T top();
};

template<class T>
SetOfStacks<T>::SetOfStacks(unsigned int th)
{
	threshold = th;
	stacks = new vector<stack<T> * >;
	stacks->push_back(new stack<T>);
}

template<class T>
void SetOfStacks<T>::push(T data)
{
	stack<T> * lastStack = stacks->at(stacks->size() - 1);
	if(lastStack->size() == threshold)
	{
		lastStack = new stack<T>;
		stacks->push_back(lastStack);
	}
	lastStack->push(data);
}

template<class T>
void SetOfStacks<T>::pop()
{
	stack<T> * lastStack = stacks->at(stacks->size() - 1);
	if(stacks->size() == 1 && lastStack->empty())
	{
		throw new StackEmptyException;
	}
	if(lastStack->empty()) {
		stacks->pop_back();
		lastStack = stacks->at(stacks->size() - 1);
	}
	lastStack->pop();
}

template<class T>
T SetOfStacks<T>::top()
{
	stack<T> * lastStack = stacks->at(stacks->size() - 1);
	if(lastStack->empty() && stacks->size() == 1)
	{
		throw new StackEmptyException;
	}
	if(lastStack->empty())
	{
		stacks->pop_back();
		lastStack = stacks->at(stacks->size() - 1);
	}
	return lastStack->top();
}

#endif /* SETOFSTACKS_H_ */
