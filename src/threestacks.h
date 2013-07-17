/*
 * threestacks.h
 *
 *  Created on: May 28, 2013
 *      Author: venkat
 */

#include <exception>
#include <cstring>
using namespace std;

#ifndef THREESTACKS_H_
#define THREESTACKS_H_

class StackEmptyException: public exception
{
	virtual const char * what() const throw()
	{
		return "Stack empty";
	}
};

template<class T>
class ThreeStack
{
	static const int DEFAULT_INIT_STACK_SIZE = 5;
	int currentArraySize;
	T *arr;
	int tops[3];

public:
	ThreeStack();

	T top(int stackNo);

	void push(int stackNo, T data);

	T pop(int stackNo);
};

template<class T>
ThreeStack<T>::ThreeStack(){
	currentArraySize = 3 * DEFAULT_INIT_STACK_SIZE;
	arr = new T[currentArraySize];
	tops[0] = -3;
	tops[1] = -2;
	tops[2] = -1;
}

template<class T>
T ThreeStack<T>::top(int stackNo)
{
	if(tops[stackNo] < 0)
	{
		throw new StackEmptyException;
	}
	return arr[tops[stackNo]];
}

template<class T>
void ThreeStack<T>::push(int stackNo, T data)
{
	int nextTop = tops[stackNo] + 3;
	if(currentArraySize <= nextTop)
	{
		T *temp = arr;
		arr = new T[2*currentArraySize];
		memcpy(temp, arr, sizeof(temp));
		delete[] temp;
	}
	arr[nextTop] = data;
	tops[stackNo] = nextTop;
}

template<class T>
T ThreeStack<T>::pop(int stackNo)
{
	int nextTop = tops[stackNo] - 3;
	if(tops[stackNo] < 0)
	{
		throw new StackEmptyException;
	}
	tops[stackNo] = nextTop;
	return arr[nextTop + 3];
}
#endif /* THREESTACKS_H_ */
