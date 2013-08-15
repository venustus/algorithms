/*
 * graph.h
 *
 *  Created on: Jun 29, 2013
 *      Author: venkat
 */


using namespace std;
#include <iostream>
#include <tr1/unordered_map>
#include <queue>
#include <vector>
#include <set>
#include <stdexcept>

#ifndef GRAPH_H_
#define GRAPH_H_

enum NODE_COLOR { WHITE, GRAY, BLACK };

template<class T> class GraphEdge;

template<class T>
class GraphNode
{
	T data;
	tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * > * neighbours;
	NODE_COLOR visited;

public:
	GraphNode(T nodeData);
	GraphNode(GraphNode<T> * copy);
	~GraphNode();

	T getValue();

	tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * > * getNeighbours();

	void addNeighbour(GraphNode<T> * neighbour, GraphEdge<T> * edgeIndex);

	NODE_COLOR getVisited();

	void setVisited(NODE_COLOR color);

	void resetVisited();
};

template<class T>
class GraphEdge
{
	std::pair<GraphNode<T> *, GraphNode<T> * > vertexPair;
public:
	GraphEdge(GraphNode<T> * first, GraphNode<T> * second);
	~GraphEdge();
	GraphNode<T> * getFirst();
	GraphNode<T> * getSecond();
	void replaceVertex(GraphNode<T> * vertex, GraphNode<T> * replacement);
	bool operator==(const GraphEdge &other)
	{
		return (other.vertexPair.first == vertexPair.first && other.vertexPair.second == vertexPair.second) ||
				(other.vertexPair.first == vertexPair.second && other.vertexPair.second == vertexPair.first);
	}
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
GraphNode<T>::GraphNode(T nodeData)
{
	data = nodeData;
	neighbours = new tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >;
	visited = WHITE;
}

template<class T>
GraphNode<T>::GraphNode(GraphNode<T> * copy)
{
	data = copy->data;
	neighbours = new tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >;
	visited = WHITE;
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

	void dfs_navigate(GraphNode<T> * node, std::vector<T> * dfsOrder);
public:
	Graph(bool directed);
	Graph(Graph<T> * copy);
	~Graph();

	void addEdge(T a, T b);
	void dfs(std::vector<T> * dfsOrder);
	void bfs(std::vector<T> * bfsOrder);
	void deleteVertex(GraphNode<T> * vertex);
	bool pathExists(T a, T b);
	GraphEdge<T> * getIthEdge(int i);
	void contractEdge(int edgeIndex);
	void reset();
	std::vector<GraphEdge<T> * > * getEdges();
	tr1::unordered_map<T, GraphNode<T> * > * getVertices();
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

	tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * > * neighbours = vertex1->getNeighbours();
	typename tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >::const_iterator edgeMapIt =
			neighbours->find(vertex2);
	if(edgeMapIt == neighbours->end())
	{
		GraphEdge<T> * newEdge = new GraphEdge<T>(vertex1, vertex2);
		vertex1->addNeighbour(vertex2, newEdge);
		if(!directed)
		{
			vertex2->addNeighbour(vertex1, newEdge);
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
	tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * > * neighbours = node->getNeighbours();
	if(neighbours->size() > 0)
	{
		for(typename std::tr1::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >::iterator it = neighbours->begin();
				it != neighbours->end(); ++it)
		{
			GraphNode<T> * neighbour = it->first;
			if(neighbour->getVisited() == WHITE)
			{
				dfs_navigate(neighbour, dfsOrder);
			}
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
#endif /* GRAPH_H_ */
