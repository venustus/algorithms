/*
 * stack_sort.h
 *
 *  Created on: Jun 3, 2013
 *      Author: venkat
 */

#include <stack>

using namespace std;

#ifndef STACK_SORT_H_
#define STACK_SORT_H_

/**
 * Sorts a stack with only using one additional stack.
 * Time complexity: Worst case O(n^2), Best case O(n), Average case O(n^2)
 */
template<typename T>
void sort(stack<T> * st);


#endif /* STACK_SORT_H_ */
