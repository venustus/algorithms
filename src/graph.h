/*
 * graph.h
 *
 *  Created on: Jun 29, 2013
 *      Author: venkat
 */


using namespace std;

#include <tr1/unordered_map>
#include <queue>
#include <vector>
#include <set>

#ifndef GRAPH_H_
#define GRAPH_H_

enum NODE_COLOR { WHITE, GRAY, BLACK };

template<class T>
class GraphNode
{
	T data;
	std::set<GraphNode<T> * > * neighbours;
	NODE_COLOR visited;

public:
	GraphNode(T nodeData);

	T getValue();

	std::set<GraphNode<T> * > * getNeighbours();

	void addNeighbour(GraphNode<T> * neighbour);

	NODE_COLOR getVisited();

	void setVisited(NODE_COLOR color);

	void resetVisited();
};

template<class T>
GraphNode<T>::GraphNode(T nodeData)
{
	data = nodeData;
	neighbours = new std::set<GraphNode<T> * >;
	visited = WHITE;
}

template<class T>
T GraphNode<T>::getValue()
{
	return data;
}

template<class T>
std::set<GraphNode<T> * > * GraphNode<T>::getNeighbours()
{
	return neighbours;
}

template<class T>
void GraphNode<T>::addNeighbour(GraphNode<T> * neighbour)
{
	neighbours->insert(neighbour);
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
void GraphNode<T>::resetVisited()
{
	visited = WHITE;
}


template<class T>
class Graph
{
	tr1::unordered_map<T, GraphNode<T> * > * vertices;
	std::vector<std::pair<GraphNode<T> *, GraphNode<T> * > > * edges;
	bool directed;

	void dfs_navigate(GraphNode<T> * node, std::vector<T> * dfsOrder);
public:
	Graph(bool directed);

	void addEdge(T a, T b);
	void dfs(std::vector<T> * dfsOrder);
	void bfs(std::vector<T> * bfsOrder);
	void deleteVertex(GraphNode<T> * vertex);
	bool pathExists(T a, T b);
	std::pair<GraphNode<T> *, GraphNode<T> * > getIthEdge(int i);
	void contractEdge(int edgeIndex);
	void reset();
	std::vector<std::pair<GraphNode<T> *, GraphNode<T> * > > * getEdges();
	tr1::unordered_map<T, GraphNode<T> * > * getVertices();
};

template<class T>
Graph<T>::Graph(bool isDirected)
{
	vertices = new tr1::unordered_map<T, GraphNode<T> * >;
	edges = new std::vector<std::pair<GraphNode<T> *, GraphNode<T> * > >;
	directed = isDirected;
}

template<class T>
std::vector<std::pair<GraphNode<T> *, GraphNode<T> * > > * Graph<T>::getEdges()
{
	return edges;
}

template<class T>
tr1::unordered_map<T, GraphNode<T> * > * Graph<T>::getVertices()
{
	return vertices;
}

template<class T>
void Graph<T>::reset()
{
	for(typename tr1::unordered_map<T, GraphNode<T> * >::iterator it = vertices->begin(); it != vertices->end(); ++it)
	{
		it->second->resetVisited();
	}
}

template<class T>
void Graph<T>::addEdge(T a, T b)
{
	GraphNode<T> * vertex1, * vertex2;
	typename tr1::unordered_map<T, GraphNode<T> * >::const_iterator vertex1_it = vertices->find(a);
	if(vertex1_it == vertices->end())
	{
		vertex1 = new GraphNode<T>(a);
		std::pair<T, GraphNode<T> * > vertex1_pair(a, vertex1);
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
	edges->push_back(std::make_pair(vertex1, vertex2));
	if(!directed)
	{
		vertex2->addNeighbour(vertex1);
	}
}

template<class T>
std::pair<GraphNode<T> *, GraphNode<T> * > Graph<T>::getIthEdge(int i)
{
	return edges->at(i);
}

template<class T>
void Graph<T>::contractEdge(int edgeIndex)
{
	std::pair<GraphNode<T> *, GraphNode<T> * > edge = edges->at(edgeIndex);
	GraphNode<T> * firstVertex = edge.first;
	GraphNode<T> * secondVertex = edge.second;
	for(typename std::set<GraphNode<T> * >::iterator it = secondVertex->getNeighbours()->begin();
			it != secondVertex->getNeighbours()->end(); ++it)
	{
		if(*it != firstVertex)
		{
			firstVertex->addNeighbour(*it);
			if(!directed)
			{
				(*it)->addNeighbour(firstVertex);
			}
			edges->push_back(std::make_pair(firstVertex, *it));
		}
	}
	deleteVertex(secondVertex);
	edges->erase(edges->begin() + edgeIndex);
}

template<class T>
void Graph<T>::deleteVertex(GraphNode<T> * vertex)
{
	std::set<GraphNode<T> * > * neighbours = vertex->getNeighbours();

	for(typename std::set<GraphNode<T> * >::iterator it = neighbours->begin();
			it != neighbours->end(); ++it)
	{
		std::set<GraphNode<T> * > * neighboursOfNeighbour = (*it)->getNeighbours();
		for(typename std::set<GraphNode<T> * >::iterator it2 = neighboursOfNeighbour->begin();
				it2 != neighboursOfNeighbour->end(); )
		{
			if((*it2) == vertex)
			{
				neighboursOfNeighbour->erase(it2++);
				break;
			}
			else
			{
				++it2;
			}
		}
	}
	vertices->erase(vertex->getValue());
}

template<class T>
void Graph<T>::dfs(std::vector<T> * dfsOrder)
{
	for(typename tr1::unordered_map<T, GraphNode<T> * >::iterator it = vertices->begin(); it != vertices->end(); ++it)
	{
		GraphNode<T> * node = it->second;
		if(node->getVisited() == WHITE)
		{
			dfs_navigate(node, dfsOrder);
		}
	}
}

template<class T>
void Graph<T>::dfs_navigate(GraphNode<T> * node, std::vector<T> * dfsOrder)
{
	node->setVisited(GRAY);
	cout << node->getValue() << " ";
	dfsOrder->push_back(node->getValue());
	std::set<GraphNode<T> * > * neighbours = node->getNeighbours();
	for(typename std::set<GraphNode<T> * >::iterator it = neighbours->begin();
			it != neighbours->end(); ++it)
	{
		GraphNode<T> * neighbour = *it;
		if(neighbour->getVisited() == WHITE)
		{
			dfs_navigate(neighbour, dfsOrder);
		}
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

	std::vector<T> * path = new std::vector<T>;
	dfs_navigate(vertexa, path);
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
void Graph<T>::bfs(std::vector<T> * bfsOrder)
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
			bfsOrder->push_back(currNode->getValue());
			std::set<GraphNode<T> * > * neighbours = currNode->getNeighbours();

			for(typename std::set<GraphNode<T> * >::iterator it = neighbours->begin();
					it != neighbours->end(); ++it)
			{
				GraphNode<T> * neighbour = *it;
				if(neighbour->getVisited() == WHITE)
				{
					bfsQueue->push(neighbour);
					neighbour->setVisited(GRAY);
				}
			}
			currNode->setVisited(BLACK);
		}
	}
	delete(bfsQueue);
}
#endif /* GRAPH_H_ */
