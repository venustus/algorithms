/*
 * lrucache.h
 *
 *  Created on: Sep 9, 2013
 *      Author: venkat
 */

#ifndef LRUCACHE_H_
#define LRUCACHE_H_

#include "linked_lists.h"

using namespace std;

template<class K, class V>
class CacheItem
{
	K key;
	V value;
public:
	CacheItem();
	CacheItem(K key, V value);
	K getKey();
	V getValue();
	template<typename S, typename T>
	friend std::ostream& operator<<(std::ostream& out, CacheItem<S, T> &ref)
	{
		out << ref.getValue();
		return out;
	}
};

template<class K, class V>
CacheItem<K, V>::CacheItem()
{

}

template<class K, class V>
CacheItem<K, V>::CacheItem(K k, V v)
{
	key = k;
	value = v;
}

template<class K, class V>
K CacheItem<K, V>::getKey()
{
	return key;
}

template<class K, class V>
V CacheItem<K, V>::getValue()
{
	return value;
}

template<class K, class V>
class CacheBackend
{
public:
	virtual ~CacheBackend()
	{

	}
	virtual V fetchFromBackend(K key) = 0;
};

template<class K, class V>
class LRUCache
{
	LinkedList<CacheItem<K, V> * > * cacheQueue;
	std::unordered_map<K, Node<CacheItem<K, V> * > * > * items;
	CacheBackend<K, V> * backend;
	int capacity;
public:
	LRUCache(int capacity, CacheBackend<K, V> * backend);
	~LRUCache();
	V find(K key);
};

template<class K, class V>
LRUCache<K, V>::LRUCache(int c, CacheBackend<K, V> * backendImpl)
{
	capacity = c;
	backend = backendImpl;
	cacheQueue = new LinkedList<CacheItem<K, V> * >;
	items = new std::unordered_map<K, Node<CacheItem<K, V> * > * >;
}

template<class K, class V>
LRUCache<K, V>::~LRUCache()
{
	delete cacheQueue;
	delete items;
}

template<class K, class V>
V LRUCache<K, V>::find(K key)
{
	typename std::unordered_map<K, Node<CacheItem<K, V> * > * >::const_iterator it = items->find(key);
	if(it == items->end())
	{
		V value = backend->fetchFromBackend(key);
		CacheItem<K, V> * ci = new CacheItem<K, V>(key, value);
		Node<CacheItem<K, V> * > * newNode = new Node<CacheItem<K, V> * >(ci);
		std::cout << "Queue capacity is: " << cacheQueue->size() << std::endl;
		if(cacheQueue->size() >= capacity)
		{
			std::cout << "Deleting node " << cacheQueue->getTail() << std::endl;
			cacheQueue->deleteNode(cacheQueue->getTail());
		}
		cacheQueue->appendHead(newNode);
		(*items)[key] = newNode;
		cacheQueue->print();
		return value;
	}
	else
	{
		Node<CacheItem<K, V> * > * foundNode = it->second;
		Node<CacheItem<K, V> * > * newNode = new Node<CacheItem<K, V> * >(foundNode->getValue());
		cacheQueue->deleteNode(foundNode);
		cacheQueue->appendHead(newNode);
		(*items)[key] = newNode;
		cacheQueue->print();
		return newNode->getValue()->getValue();
	}
}
#endif /* LRUCACHE_H_ */
