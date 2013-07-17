/*
 * graph.h
 *
 *  Created on: Jun 29, 2013
 *      Author: venkat
 */


using namespace std;

#include <tr1/unordered_map>
#include <queue>
#include "linked_lists.h"

#ifndef GRAPH_H_
#define GRAPH_H_

enum NODE_COLOR { WHITE, GRAY, BLACK };

template<class T>
class GraphNode
{
	T data;
	LinkedList<GraphNode<T> * > * neighbours;
	NODE_COLOR visited;

public:
	GraphNode(T nodeData);

	T getValue();

	LinkedList<GraphNode<T> * > * getNeighbours();

	void addNeighbour(GraphNode<T> * neighbour);

	NODE_COLOR getVisited();

	void setVisited(NODE_COLOR color);
};

template<class T>
GraphNode<T>::GraphNode(T nodeData)
{
	data = nodeData;
	neighbours = new LinkedList<GraphNode<T> * >;
	visited = WHITE;
}

template<class T>
T GraphNode<T>::getValue()
{
	return data;
}

template<class T>
LinkedList<GraphNode<T> * > * GraphNode<T>::getNeighbours()
{
	return neighbours;
}

template<class T>
void GraphNode<T>::addNeighbour(GraphNode<T> * neighbour)
{
	neighbours->append(new Node<GraphNode<T> * >(neighbour));
}

template<class T>
NODE_COLOR GraphNode<T>::getVisited()
{
	return visited;
}

template<class T>
void GraphNode<T>::setVisited(NODE_COLOR color)
{
	visited = color;
}

template<class T>
class Graph
{
	tr1::unordered_map<T, GraphNode<T> * > * vertices;
	bool directed;

	void dfs_navigate(GraphNode<T> * node);
public:
	Graph(bool directed);

	void addEdge(T a, T b);
	void dfs();
	void bfs();
	bool pathExists(T a, T b);
};

template<class T>
Graph<T>::Graph(bool isDirected)
{
	vertices = new tr1::unordered_map<T, GraphNode<T> * >;
	directed = isDirected;
}

template<class T>
void Graph<T>::addEdge(T a, T b)
{
	GraphNode<T> * vertex1, * vertex2;
	typename tr1::unordered_map<T, GraphNode<T> * >::const_iterator vertex1_it = vertices->find(a);
	if(vertex1_it == vertices->end())
	{
		vertex1 = new GraphNode<T>(a);
		pair<T, GraphNode<T> * > vertex1_pair(a, vertex1);
		vertices->insert(vertex1_pair);
	}
	else
	{
		vertex1 = vertex1_it->second;
	}

	typename tr1::unordered_map<T, GraphNode<T> * >::const_iterator vertex2_it = vertices->find(b);
	if(vertex2_it == vertices->end())
	{
		vertex2 = new GraphNode<T>(b);
		pair<T, GraphNode<T> * > vertex2_pair(b, vertex2);
		vertices->insert(vertex2_pair);
	}
	else
	{
		vertex2 = vertex2_it->second;
	}

	vertex1->addNeighbour(vertex2);
	if(directed == false)
	{
		vertex2->addNeighbour(vertex1);
	}
}

template<class T>
void Graph<T>::dfs()
{
	for(typename tr1::unordered_map<T, GraphNode<T> * >::iterator it = vertices->begin(); it != vertices->end(); ++it)
	{
		GraphNode<T> * node = it->second;
		if(node->getVisited() == WHITE)
		{
			dfs_navigate(node);
		}
	}
}

template<class T>
void Graph<T>::dfs_navigate(GraphNode<T> * node)
{
	node->setVisited(GRAY);
	cout << node->getValue() << " ";
	LinkedList<GraphNode<T> * > * neighbours = node->getNeighbours();
	Node<GraphNode<T> * > * head = neighbours->getHead();
	while(head)
	{
		GraphNode<T> * neighbour = head->getValue();
		if(neighbour->getVisited() == WHITE)
		{
			dfs_navigate(neighbour);
		}
		head = head->getNext();
	}
	node->setVisited(BLACK);
}

template<class T>
bool Graph<T>::pathExists(T a, T b)
{
	typename tr1::unordered_map<T, GraphNode<T> * >::const_iterator vertex1_it = vertices->find(a);
	typename tr1::unordered_map<T, GraphNode<T> * >::const_iterator vertex2_it = vertices->find(b);

	GraphNode<T> * vertexa = vertex1_it->second;
	GraphNode<T> * vertexb = vertex2_it->second;

	dfs_navigate(vertexa);
	if(vertexb->getVisited() == WHITE)
	{
		return false;
	}
	else
	{
		return true;
	}
}

template<class T>
void Graph<T>::bfs()
{
	queue<GraphNode<T> * > * bfsQueue = new queue<GraphNode<T> * >;
	typename tr1::unordered_map<T, GraphNode<T> * >::iterator it;
	for(it = vertices->begin(); it != vertices->end(); ++it)
	{
		GraphNode<T> * node = it->second;
		if(node->getVisited() == WHITE)
		{
			bfsQueue->push(node);
			node->setVisited(GRAY);
		}
		while(!bfsQueue->empty())
		{
			GraphNode<T> * currNode = bfsQueue->front();
			bfsQueue->pop();
			cout << currNode->getValue() << " ";
			Node<GraphNode<T> * > * head = currNode->getNeighbours()->getHead();
			while(head)
			{
				if(head->getValue()->getVisited() == WHITE)
				{
					bfsQueue->push(head->getValue());
					head->getValue()->setVisited(GRAY);
				}
				head = head->getNext();
			}
			currNode->setVisited(BLACK);
		}
	}
	delete(bfsQueue);
}
#endif /* GRAPH_H_ */
