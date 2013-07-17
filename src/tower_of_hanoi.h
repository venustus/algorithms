/*
 * tower_of_hanoi.h
 *
 *  Created on: Jun 2, 2013
 *      Author: venkat
 */

#include <stack>

using namespace std;

#ifndef TOWER_OF_HANOI_H_
#define TOWER_OF_HANOI_H_

template<class T>
class TowerOfHanoi
{
	stack<T> ** towers;
	int targetTower;

	void solveRecurse(stack<T> * source, stack<T> * target, stack<T> * buffer, int numDisks);

public:
	TowerOfHanoi(stack<T> &first, int tgt);

	stack<T> * solve();
};


template<class T>
TowerOfHanoi<T>::TowerOfHanoi(stack<T> &first, int tgt)
{
	towers = new stack<T> *[3];
	towers[0] = &first;
	towers[1] = new stack<T>;
	towers[2] = new stack<T>;
	targetTower = tgt;
}

template<class T>
stack<T> * TowerOfHanoi<T>::solve()
{
	int bufferTower = 0;
	switch(targetTower)
	{
	case 1:
		bufferTower = 2;
		break;
	case 2:
		bufferTower = 1;
		break;
	default:
		bufferTower = 1;
		break;
	}
	solveRecurse(towers[0], towers[targetTower], towers[bufferTower], towers[0]->size());
	return towers[targetTower];
}

template<class T>
void TowerOfHanoi<T>::solveRecurse(stack<T> * source,
								   stack<T> * target,
								   stack<T> * buffer,
								   int numDisks)
{
	if(numDisks == 2)
	{
		buffer->push(source->top());
		source->pop();
		target->push(source->top());
		source->pop();
		target->push(buffer->top());
		buffer->pop();
		return;
	}
	solveRecurse(source, buffer, target, numDisks - 1);
	target->push(source->top());
	source->pop();
	solveRecurse(buffer, target, source, numDisks - 1);
}

#endif /* TOWER_OF_HANOI_H_ */
