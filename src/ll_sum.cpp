/*
 * ll_sum.cpp
 *
 *  Created on: May 6, 2013
 *      Author: venkat
 */

#include <cmath>
#include "ll_sum.h"

using namespace std;

Node<int> * padzero(LinkedList<int> *a, int len)
{
	for(int i = 0; i < len; i++)
	{
		Node<int> * zeroNode = new Node<int>(0);
		a->appendHead(zeroNode);
	}
	return a->getHead();
}

LinkedList<int> * convertIntToList(int result)
{
	LinkedList<int> *resultList = new LinkedList<int>;
	while(result > 0)
	{
		Node<int> * newNode = new Node<int>(result % 10);
		resultList->appendHead(newNode);
		result = result/10;
	}
	return resultList;
}

LinkedList<int> * sum(LinkedList<int> *a, LinkedList<int> *b)
{
	int len1 = 0, len2 = 0;
	Node<int> *temp = a->getHead();
	while(temp)
	{
		temp = temp->getNext();
		len1++;
	}
	temp = b->getHead();
	while(temp) {
		temp = temp->getNext();
		len2++;
	}
	int len = std::max(len1, len2);
	if(len1 != len2)
	{
		if(len == len1)
		{
			padzero(b, len1 - len2);
		}
		else
		{
			padzero(a, len2 - len1);
		}
	}
	Node<int> *runner1 = a->getHead();
	Node<int> *runner2 = b->getHead();
	int result = 0;
	double ten = 10;
	for(int i = len; i > 0; i--)
	{
		result += (runner1->getValue() * ((int) pow(ten, (i - 1)))) +
				  (runner2->getValue() * ((int) pow(ten, (i - 1))));
		runner1 = runner1->getNext();
		runner2 = runner2->getNext();
	}
	return convertIntToList(result);
}

LinkedList<int> * sumReverse(LinkedList<int> *aList, LinkedList<int> *bList)
{
	int carry = 0;
	LinkedList<int> *sumList = new LinkedList<int>;
	Node<int> *a = aList->getHead();
	Node<int> *b = bList->getHead();
	while(a || b)
	{
		if(a)
		{
			carry += a->getValue();
			a = a->getNext();
		}
		if(b)
		{
			carry += b->getValue();
			b = b->getNext();
		}
		sumList->append(new Node<int>(carry % 10));
		carry = carry/10;
	}
	if(carry > 0)
	{
		sumList->append(new Node<int>(carry));
	}
	return sumList;
}
