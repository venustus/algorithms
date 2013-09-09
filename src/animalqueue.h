/*
 * animalqueue.h
 *
 *  Created on: Jun 8, 2013
 *      Author: venkat
 */

#include "linked_lists.h"
#include "animal.h"

using namespace std;

#ifndef ANIMALQUEUE_H_
#define ANIMALQUEUE_H_

/**
 * Problem statement:
 * Implement a queue data structure that can support the
 * following operations:
 * 1) A dog or cat can be queued while queueing.
 * 2) If a request for dequeueing dog or cat arrives,
 * 	  the earliest queued dog or cat must be dequeued.
 * 3) If a request for dequeueing 'any' arrives, then
 *    the earliest animal queued, must be dequeued.
 *    (both among cats and dogs).
 */

template<class T>
class QueueElement
{
	int order;
	T val;
public:
	QueueElement(int order, const T &val);

	int getOrder();

	T * getValue();
};

/**
 * Algorithm and Data structure:
 * We maintain two independent linked lists for dogs and cats.
 * When queueing a cat or dog, we queue a wrapper class
 * containing the time of arrival and the animal itself. That is
 * we associate an integer with each incoming animal.
 * When asked to dequeue either a cat or dog, we dequeue
 * from the respective queues.
 * When asked to dequeue any animal, we compare the time of
 * arrival of the tails of both queues and dequeue the animal
 * with earlier time of arrival.
 *
 * Time complexity:
 * 1) queueDog: O(1)
 * 2) queueCat: O(1)
 * 3) dequeueDog: O(1)
 * 4) dequeueCat: O(1)
 * 5) dequeueAny: O(1)
 *
 * Space complexity: O(m + n) where m is the number of dogs
 * queued and n is the number of cats queued over a period of
 * time.
 * Individual operations take constant amount of space.
 */
class AnimalQueue
{
	int order;
	LinkedList<QueueElement<Dog> * > * dogQueue;
	LinkedList<QueueElement<Cat> * > * catQueue;

public:
	AnimalQueue();
	~AnimalQueue();

	void queueDog(const Dog &d);

	void queueCat(const Cat &c);

	Animal * dequeueAny();

	Dog * dequeueDog();

	Cat * dequeueCat();

};


template<class T>
QueueElement<T>::QueueElement(int o, const T &v): val(v)
{
	order = o;
}

template<class T>
int QueueElement<T>::getOrder()
{
	return order;
}

template<class T>
T * QueueElement<T>::getValue()
{
	return &val;
}

AnimalQueue::AnimalQueue()
{
	order = 0;
	dogQueue = new LinkedList<QueueElement<Dog> * >;
	catQueue = new LinkedList<QueueElement<Cat> * >;
}

AnimalQueue::~AnimalQueue()
{
	delete dogQueue;
	delete catQueue;
}

void AnimalQueue::queueDog(const Dog &d)
{
	QueueElement<Dog> * newEle = new QueueElement<Dog>(order++, d);
	Node<QueueElement<Dog> * > *newNode = new Node<QueueElement<Dog> * >(newEle);
	dogQueue->append(newNode);
}

void AnimalQueue::queueCat(const Cat &c)
{
	QueueElement<Cat> *newEle = new QueueElement<Cat>(order++, c);
	Node<QueueElement<Cat> * > *newNode = new Node<QueueElement<Cat> * >(newEle);
	catQueue->append(newNode);
}

Cat * AnimalQueue::dequeueCat()
{
	Node<QueueElement<Cat> * > *tail = catQueue->getTail();
	if(tail)
	{
		Cat *tailCat = tail->getValue()->getValue();
		catQueue->deleteNode(tail);
		return tailCat;
	}
	else
	{
		return NULL;
	}
}

Dog * AnimalQueue::dequeueDog()
{
	Node<QueueElement<Dog> * > *tail = dogQueue->getTail();
	if(tail)
	{
		Dog *tailDog = tail->getValue()->getValue();
		dogQueue->deleteNode(tail);
		return tailDog;
	}
	else
	{
		return NULL;
	}
}

Animal * AnimalQueue::dequeueAny()
{
	Node<QueueElement<Dog> * > *dogTail = dogQueue->getTail();
	Node<QueueElement<Cat> * > *catTail = catQueue->getTail();
	if(dogTail->getValue()->getOrder() < catTail->getValue()->getOrder())
	{
		Animal *a = catTail->getValue()->getValue();
		catQueue->deleteNode(catTail);
		return a;
	}
	else
	{
		Animal *a = dogTail->getValue()->getValue();
		dogQueue->deleteNode(dogTail);
		return a;
	}
}



#endif /* ANIMALQUEUE_H_ */
