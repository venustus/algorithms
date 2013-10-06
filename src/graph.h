/*
 * graph.h
 *
 *  Created on: Jun 29, 2013
 *      Author: venkat
 */


using namespace std;
#include <iostream>
#include <tr1/unordered_map>
#include <functional>
#include <queue>
#include <vector>
#include <set>
#include <stdexcept>
#include <limits>
#include "binaryheap.h"

#ifndef GRAPH_H_
#define GRAPH_H_

enum NODE_COLOR { WHITE, GRAY, BLACK };

template<class T> class GraphEdge;

template<class T>
class GraphNode
{
	T data;
	tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * > * neighbours;
	std::set<GraphEdge<T> * > * incidentEdges;
	NODE_COLOR visited;

public:
	GraphNode(T nodeData);
	GraphNode(GraphNode<T> * copy);
	~GraphNode();

	T getValue();

	tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * > * getNeighbours();

	std::set<GraphEdge<T> * > * getIncidentEdges();

	void addNeighbour(GraphNode<T> * neighbour, GraphEdge<T> * edgeIndex);
	void addIncidentEdge(GraphEdge<T> * incidentEdge);

	NODE_COLOR getVisited();

	void setVisited(NODE_COLOR color);

	void resetVisited();
};

template<class T>
class GraphEdge
{
	std::pair<GraphNode<T> *, GraphNode<T> * > vertexPair;
	long weight;
public:
	GraphEdge(GraphNode<T> * first, GraphNode<T> * second);
	GraphEdge(GraphNode<T> * first, GraphNode<T> * second, long weight);
	~GraphEdge();
	GraphNode<T> * getFirst();
	GraphNode<T> * getSecond();
	long getWeight();
	void replaceVertex(GraphNode<T> * vertex, GraphNode<T> * replacement);
	bool operator==(const GraphEdge &other)
	{
		return (other.vertexPair.first == vertexPair.first && other.vertexPair.second == vertexPair.second) ||
				(other.vertexPair.first == vertexPair.second && other.vertexPair.second == vertexPair.first);
	}
};

/**
 * This is a wrapper over graph node which includes
 * dijkstra score so that we can easily manipulate the heap
 * when implementing dijkstra's single-source shortest
 * paths algorithm.
 */
template<class T>
class DijkstraNode
{
	GraphNode<T> * node;
	long dijkstraScore;
public:
	DijkstraNode();
	DijkstraNode(GraphNode<T> * node);
	DijkstraNode(GraphNode<T> * node, long score);
	bool operator<(const DijkstraNode<T> &other) const;
	bool operator>(const DijkstraNode<T> &other) const;
	bool operator==(const DijkstraNode<T> &other) const;
	bool operator!=(const DijkstraNode<T> &other) const;
	friend std::ostream& operator<<(std::ostream& os, const DijkstraNode<T>& obj)
	{
		os << "Node (" << obj.node->getValue() << ", " << obj.dijkstraScore << ")";
		return os;
	}
	DijkstraNode<T> & operator=(const DijkstraNode<T> &rhs);
	DijkstraNode<T>& operator-=(const DijkstraNode<T> &other);
	DijkstraNode<T>& operator+=(const DijkstraNode<T> &other);
	GraphNode<T> * getNode() const;
	long getScore();
	void setScore(long newScore);
};


template<typename T>
struct eq
{
    eq(const GraphEdge<T> * compare_to) : compare_to_(compare_to) { }
    bool operator()(GraphEdge<T> * c1) const {return  *c1 == *compare_to_;}
private:
    const GraphEdge<T> * compare_to_;
};

template<class T>
GraphEdge<T>::GraphEdge(GraphNode<T> * first, GraphNode<T> * second)
{
	vertexPair = std::make_pair(first, second);
	weight = 1;
}

template<class T>
GraphEdge<T>::GraphEdge(GraphNode<T> * first, GraphNode<T> * second, long edgeWeight)
{
	vertexPair = std::make_pair(first, second);
	weight = edgeWeight;
}

template<class T>
GraphNode<T>::~GraphNode()
{
	delete neighbours;
}

template<class T>
GraphEdge<T>::~GraphEdge()
{

}

template<class T>
void GraphEdge<T>::replaceVertex(GraphNode<T> * vertex, GraphNode<T> * replacement)
{
	if(vertex == vertexPair.first)
	{
		vertexPair.first = replacement;
	}
	else if(vertex == vertexPair.second)
	{
		vertexPair.second = replacement;
	}
}

template<class T>
GraphNode<T> * GraphEdge<T>::getFirst()
{
	return vertexPair.first;
}

template<class T>
GraphNode<T> * GraphEdge<T>::getSecond()
{
	return vertexPair.second;
}

template<class T>
long GraphEdge<T>::getWeight()
{
	return weight;
}

template<class T>
GraphNode<T>::GraphNode(T nodeData)
{
	data = nodeData;
	neighbours = new tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >;
	visited = WHITE;
	incidentEdges = new std::set<GraphEdge<T> * >;
}

template<class T>
GraphNode<T>::GraphNode(GraphNode<T> * copy)
{
	data = copy->data;
	neighbours = new tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >;
	visited = WHITE;
	incidentEdges = new std::set<GraphEdge<T> * >;
}

template<class T>
T GraphNode<T>::getValue()
{
	return data;
}

template<class T>
tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * > * GraphNode<T>::getNeighbours()
{
	return neighbours;
}

template<class T>
void GraphNode<T>::addNeighbour(GraphNode<T> * neighbour, GraphEdge<T> * edge)
{
	typename tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >::const_iterator it =
			neighbours->find(neighbour);
	if(it != neighbours->end())
	{
		std::set<GraphEdge<T> * > * edgesToNeighbour = it->second;
		edgesToNeighbour->insert(edge);
	}
	else
	{
		std::set<GraphEdge<T> * > * edgesToNeighbour = new std::set<GraphEdge<T> * >;
		edgesToNeighbour->insert(edge);
		neighbours->insert(std::make_pair(neighbour, edgesToNeighbour));
	}
}

template<class T>
void GraphNode<T>::addIncidentEdge(GraphEdge<T> * incidentEdge)
{
	incidentEdges->insert(incidentEdges->end(), incidentEdge);
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
	std::vector<GraphEdge<T> * > * edges;
	bool directed;

	void dfs_navigate(GraphNode<T> * node, std::vector<T> * dfsOrder,
					  std::vector<T> * topologicalOrder, int &topoLabel);
public:
	Graph(bool directed);
	Graph(Graph<T> * copy);
	~Graph();

	void addEdge(T a, T b);
	void addEdge(T a, T b, long weight);
	void dfs(std::vector<T> * dfsOrder, std::vector<T> * topologicalOrder);
	void bfs(std::vector<T> * bfsOrder);
	void deleteVertex(GraphNode<T> * vertex);
	bool pathExists(T a, T b);
	GraphEdge<T> * getIthEdge(int i);
	void contractEdge(int edgeIndex);
	void reset();
	GraphNode<T> * getNodeForVertex(T val);
	std::vector<GraphEdge<T> * > * getEdges();
	tr1::unordered_map<T, GraphNode<T> * > * getVertices();
	std::vector<DijkstraNode<T> > * findShortestPaths(GraphNode<T> * source);
};

template<class T>
Graph<T>::Graph(bool isDirected)
{
	vertices = new tr1::unordered_map<T, GraphNode<T> * >;
	edges = new std::vector<GraphEdge<T> * >;
	directed = isDirected;
}

template<class T>
Graph<T>::Graph(Graph<T> * copy)
{
	directed = copy->directed;
	vertices = new tr1::unordered_map<T, GraphNode<T> * >;
	edges = new std::vector<GraphEdge<T> * >;
	for(typename std::vector<GraphEdge<T> * >::iterator it = copy->getEdges()->begin(); it != copy->getEdges()->end(); ++it)
	{
		GraphEdge<T> * edge = *it;
		addEdge(edge->getFirst()->getValue(), edge->getSecond()->getValue());
	}
}

template<class T>
Graph<T>::~Graph()
{
	delete vertices;
	delete edges;
}

template<class T>
std::vector<GraphEdge<T> * > * Graph<T>::getEdges()
{
	return edges;
}

template<class T>
tr1::unordered_map<T, GraphNode<T> * > * Graph<T>::getVertices()
{
	return vertices;
}

template<class T>
GraphNode<T> * Graph<T>::getNodeForVertex(T val)
{
	try
	{
		GraphNode<T> * node = (*vertices)[val];
		return node;
	}
	catch(const std::out_of_range& oor)
	{
		return NULL;
	}
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
	addEdge(a, b ,1);
}

template<class T>
void Graph<T>::addEdge(T a, T b, long weight)
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

	tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * > * neighbours = vertex1->getNeighbours();
	typename tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >::const_iterator edgeMapIt =
			neighbours->find(vertex2);
	if(edgeMapIt == neighbours->end())
	{
		GraphEdge<T> * newEdge = new GraphEdge<T>(vertex1, vertex2, weight);
		vertex1->addNeighbour(vertex2, newEdge);
		if(!directed)
		{
			vertex2->addNeighbour(vertex1, newEdge);
		}
		else
		{
			vertex2->addIncidentEdge(newEdge);
		}
		edges->push_back(newEdge);
	}
}

template<class T>
GraphEdge<T> * Graph<T>::getIthEdge(int i)
{
	return edges->at(i);
}

template<class T>
void Graph<T>::contractEdge(int edgeIndex)
{
	GraphEdge<T> * edge = edges->at(edgeIndex);
	GraphNode<T> * firstVertex = edge->getFirst();
	GraphNode<T> * secondVertex = edge->getSecond();
	//std::cout << "Contracting edge " << firstVertex->getValue() << " -> " << secondVertex->getValue() << std::endl;
	if(secondVertex->getNeighbours()->size() > 0)
	{
		for(typename tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >::iterator it = secondVertex->getNeighbours()->begin();
				it != secondVertex->getNeighbours()->end(); ++it)
		{
			if(it->first != firstVertex)
			{
				std::set<GraphEdge<T> * > * transferringEdgeSet = it->second;
				for(typename std::set<GraphEdge<T> * >::iterator it2 = transferringEdgeSet->begin();
						it2 != transferringEdgeSet->end(); ++it2)
				{
					GraphEdge<T> * transferringEdge = *it2;
					transferringEdge->replaceVertex(secondVertex, firstVertex);
				}

				GraphNode<T> * transferringVertex = it->first;
				transferringVertex->getNeighbours()->erase(secondVertex);
				typename tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >::iterator it4 =
						transferringVertex->getNeighbours()->find(firstVertex);
				if(it4 == transferringVertex->getNeighbours()->end())
				{
					transferringVertex->getNeighbours()->insert(std::make_pair(firstVertex, transferringEdgeSet));
				}
				else
				{
					std::set<GraphEdge<T> * > * firstVertexEdgeSet = it4->second;
					firstVertexEdgeSet->insert(transferringEdgeSet->begin(), transferringEdgeSet->end());
				}

				it4 = firstVertex->getNeighbours()->find(transferringVertex);
				if(it4 == firstVertex->getNeighbours()->end())
				{
					firstVertex->getNeighbours()->insert(std::make_pair(transferringVertex, transferringEdgeSet));
				}
				else
				{
					std::set<GraphEdge<T> * > * transferringVertexEdgeSet = it4->second;
					transferringVertexEdgeSet->insert(transferringEdgeSet->begin(), transferringEdgeSet->end());
				}
			}
		}
	}
	typename std::vector<GraphEdge<T> * >::iterator it3 =
			std::find_if(edges->begin(), edges->end(), eq<T>(new GraphEdge<T>(firstVertex, secondVertex)));
	while(it3 != edges->end())
	{
		edges->erase(it3);
		it3 = std::find_if(edges->begin(), edges->end(), eq<T>(new GraphEdge<T>(firstVertex, secondVertex)));
	}
	firstVertex->getNeighbours()->erase(secondVertex);
	deleteVertex(secondVertex);
	//std::cout << "Number of vertices: " << vertices->size() << std::endl;
	//std::cout << "Number of edges: " << edges->size() << std::endl;
}

template<class T>
void Graph<T>::deleteVertex(GraphNode<T> * vertex)
{
	vertices->erase(vertex->getValue());
	delete vertex;
}

template<class T>
void Graph<T>::dfs(std::vector<T> * dfsOrder, std::vector<T> * topologicalOrder)
{
	int topoLabel = vertices->size() - 1;
	for(typename tr1::unordered_map<T, GraphNode<T> * >::iterator it = vertices->begin(); it != vertices->end(); ++it)
	{
		GraphNode<T> * node = it->second;
		if(node->getVisited() == WHITE)
		{
			dfs_navigate(node, dfsOrder, topologicalOrder, topoLabel);
		}
	}
}

template<class T>
void Graph<T>::dfs_navigate(GraphNode<T> * node, std::vector<T> * dfsOrder,
							std::vector<T> * topologicalOrder, int &topoLabel)
{
	node->setVisited(GRAY);
	cout << node->getValue() << " ";
	dfsOrder->push_back(node->getValue());
	tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * > * neighbours = node->getNeighbours();
	if(neighbours->size() > 0)
	{
		for(typename std::tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >::iterator it = neighbours->begin();
				it != neighbours->end(); ++it)
		{
			GraphNode<T> * neighbour = it->first;
			if(neighbour->getVisited() == WHITE)
			{
				dfs_navigate(neighbour, dfsOrder, topologicalOrder, topoLabel);
			}
		}
	}
	node->setVisited(BLACK);
	topologicalOrder->at(topoLabel--) = node->getValue();
}

template<class T>
bool Graph<T>::pathExists(T a, T b)
{
	typename tr1::unordered_map<T, GraphNode<T> * >::const_iterator vertex1_it = vertices->find(a);
	typename tr1::unordered_map<T, GraphNode<T> * >::const_iterator vertex2_it = vertices->find(b);

	GraphNode<T> * vertexa = vertex1_it->second;
	GraphNode<T> * vertexb = vertex2_it->second;

	std::vector<T> * path = new std::vector<T>;
	std::vector<T> * topoOrder = new std::vector<T>(vertices->size(), vertexa->getValue());
	dfs_navigate(vertexa, path, topoOrder, vertices->size());
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

			if(currNode->getNeighbours()->size() > 0)
			{
				for(typename tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >::const_iterator it = currNode->getNeighbours()->begin();
							it != currNode->getNeighbours()->end(); ++it)
				{
					GraphNode<T> * neighbour = it->first;
					if(neighbour->getVisited() == WHITE)
					{
						bfsQueue->push(neighbour);
						neighbour->setVisited(GRAY);
					}
				}
			}
			currNode->setVisited(BLACK);
		}
	}
	delete(bfsQueue);
}

template<class T>
DijkstraNode<T>::DijkstraNode()
{
	node = NULL;
	dijkstraScore = std::numeric_limits<long>::max();
}

template<class T>
DijkstraNode<T>::DijkstraNode(GraphNode<T> * n, long score)
{
	node = n;
	dijkstraScore = score;
}

template<class T>
DijkstraNode<T>::DijkstraNode(GraphNode<T> * n)
{
	node = n;
	dijkstraScore = std::numeric_limits<long>::max();
}

template<class T>
bool DijkstraNode<T>::operator<(const DijkstraNode<T> &other) const
{
	return dijkstraScore <= other.dijkstraScore;
}

template<class T>
bool DijkstraNode<T>::operator>(const DijkstraNode<T> &other) const
{
	return dijkstraScore > other.dijkstraScore;
}

template<class T>
bool DijkstraNode<T>::operator==(const DijkstraNode<T> &other) const
{
	return node == other.node;
}

template<class T>
bool DijkstraNode<T>::operator!=(const DijkstraNode<T> &other) const
{
	return node != other.node;
}

template<class T>
DijkstraNode<T>& DijkstraNode<T>::operator-=(const DijkstraNode<T> &other)
{
	this->dijkstraScore -= other.dijkstraScore;
	return *this;
}

template<class T>
DijkstraNode<T>& DijkstraNode<T>::operator+=(const DijkstraNode<T> &other)
{
	this->dijkstraScore += other.dijkstraScore;
	return *this;
}

template<class T>
inline DijkstraNode<T> operator+(DijkstraNode<T> lhs, const DijkstraNode<T>& rhs)
{
	lhs += rhs;
	return lhs;
}

template<class T>
inline DijkstraNode<T> operator-(DijkstraNode<T> lhs, const DijkstraNode<T>& rhs)
{
	lhs -= rhs;
	return lhs;
}

template<class T>
DijkstraNode<T> & DijkstraNode<T>::operator=(const DijkstraNode<T> &rhs)
{
	node = rhs.node;
	dijkstraScore = rhs.dijkstraScore;
	return *this;
}


template<class T>
GraphNode<T> * DijkstraNode<T>::getNode() const
{
	return node;
}

template<class T>
long DijkstraNode<T>::getScore()
{
	return dijkstraScore;
}

template<class T>
void DijkstraNode<T>::setScore(long newScore)
{
	dijkstraScore = newScore;
}

template<class T>
std::vector<DijkstraNode<T> > * Graph<T>::findShortestPaths(GraphNode<T> * source)
{
	std::vector<DijkstraNode<T> > * shortestPaths =
			new std::vector<DijkstraNode<T> >;
	tr1::unordered_map<GraphNode<T> *, DijkstraNode<T> > *
		nodeMapping = new tr1::unordered_map<GraphNode<T> *, DijkstraNode<T> >;

	std::vector<DijkstraNode<T> > * unprocessedElems = new std::vector<DijkstraNode<T> >;
	for(typename tr1::unordered_map<T, GraphNode<T> * >::iterator it = vertices->begin(); it != vertices->end(); ++it)
	{
		GraphNode<T> * node = it->second;
		DijkstraNode<T> dijkstraNode(node);
		if(node == source)
		{
			dijkstraNode.setScore(0);
		}
		unprocessedElems->push_back(dijkstraNode);
		nodeMapping->insert(std::make_pair(node, dijkstraNode));
	}
	BinaryHeap<DijkstraNode<T> > * heap = new BinaryHeap<DijkstraNode<T> >(unprocessedElems, false);
	while(heap->size() > 0)
	{
		DijkstraNode<T> nextNode = heap->findTop();
		shortestPaths->push_back(nextNode);
		heap->removeTop();
		GraphNode<T> * currNode = nextNode.getNode();
		currNode->setVisited(BLACK);
		for(typename tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >::const_iterator it = currNode->getNeighbours()->begin();
									it != currNode->getNeighbours()->end(); ++it)
		{
			DijkstraNode<T> affectedNode = (*nodeMapping)[it->first];
			if(affectedNode.getNode()->getVisited() == BLACK)
			{
				continue;
			}
			std::set<GraphEdge<T> * > * edges = it->second;
			long minWeight = std::numeric_limits<long>::max();
			for(typename std::set<GraphEdge<T> * >::iterator it1 = edges->begin(); it1 != edges->end(); ++it1)
			{
				if((*it1)->getWeight() < minWeight)
				{
					minWeight = (*it1)->getWeight();
				}
			}
			DijkstraNode<T> updatedNode(affectedNode.getNode(), nextNode.getScore() + minWeight);
			heap->findAndUpdateKey(affectedNode, updatedNode);
		}
	}
	return shortestPaths;
}

#endif /* GRAPH_H_ */
