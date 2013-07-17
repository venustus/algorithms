/*
 * ll_sum.h
 *
 *  Created on: Jul 17, 2013
 *      Author: venkat
 */

#include "linked_lists.h"

using namespace std;

#ifndef LL_SUM_H_
#define LL_SUM_H_

Node<int> * padzero(LinkedList<int> *a, int len);

LinkedList<int> * convertIntToList(int result);

/**
 * Adds two linked lists of integers considering them as numbers.
 * For example (6 -> 3 -> 4) + (7 -> 1 -> 2) = (1 -> 3 -> 4 -> 6)
 * Returns the resulting linked list.
 */
LinkedList<int> * sum(LinkedList<int> *a, LinkedList<int> *b);

/**
 * Adds two linked lists of integers considering them as numbers in reverse order.
 * That is units place comes first in the list followed by tens place etc.
 * For example (4 -> 3 -> 6) + (2 -> 1 -> 7) = (6 -> 4 -> 3 -> 1)
 */
LinkedList<int> * sumReverse(LinkedList<int> *aList, LinkedList<int> *bList);

#endif /* LL_SUM_H_ */
