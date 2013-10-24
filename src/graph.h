/*
 * graph.h
 *
 *  Created on: Jun 29, 2013
 *      Author: venkat
 */


#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <queue>
#include <vector>
#include <stack>
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
	std::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * > * neighbours;
	std::set<GraphEdge<T> * > * incidentEdges;
	NODE_COLOR visited;

public:
	GraphNode(T nodeData);
	GraphNode(GraphNode<T> * copy);
	~GraphNode();

	T getValue();

	std::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * > * getNeighbours();
    std::set<GraphEdge<T> * > * getIncidentEdges();
    int getInDegree();
    int getOutDegree();
    
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
    std::string label;
public:
	GraphEdge(GraphNode<T> * first, GraphNode<T> * second);
	GraphEdge(GraphNode<T> * first, GraphNode<T> * second, long weight);
    GraphEdge(GraphNode<T> * first, GraphNode<T> * second, long weight, std::string label);
	~GraphEdge();
	GraphNode<T> * getFirst();
	GraphNode<T> * getSecond();
	long getWeight();
    std::string getLabel();
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
    label = "";
}

template<class T>
GraphEdge<T>::GraphEdge(GraphNode<T> * first, GraphNode<T> * second, long edgeWeight)
{
	vertexPair = std::make_pair(first, second);
	weight = edgeWeight;
    label = "";
}

template<class T>
GraphEdge<T>::GraphEdge(GraphNode<T> * first, GraphNode<T> * second, long edgeWeight, std::string l)
{
    vertexPair = std::make_pair(first, second);
    weight = edgeWeight;
    label = l;
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
std::string GraphEdge<T>::getLabel()
{
    return label;
}


template<class T>
GraphNode<T>::GraphNode(T nodeData)
{
	data = nodeData;
	neighbours = new std::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >;
	visited = WHITE;
	incidentEdges = new std::set<GraphEdge<T> * >;
}

template<class T>
GraphNode<T>::GraphNode(GraphNode<T> * copy)
{
	data = copy->data;
	neighbours = new std::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >;
	visited = WHITE;
	incidentEdges = new std::set<GraphEdge<T> * >;
}

template<class T>
T GraphNode<T>::getValue()
{
	return data;
}

template<class T>
std::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * > * GraphNode<T>::getNeighbours()
{
	return neighbours;
}

template<class T>
int GraphNode<T>::getInDegree()
{
    return incidentEdges->size();
}

template<class T>
int GraphNode<T>::getOutDegree()
{
    return neighbours->size();
}

template<class T>
void GraphNode<T>::addNeighbour(GraphNode<T> * neighbour, GraphEdge<T> * edge)
{
	typename std::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >::const_iterator it =
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
std::set<GraphEdge<T> * > * GraphNode<T>::getIncidentEdges()
{
    return incidentEdges;
}

template<class T>
void GraphNode<T>::resetVisited()
{
	visited = WHITE;
}


template<class T>
class Graph
{
	std::unordered_map<T, GraphNode<T> * > * vertices;
	std::vector<GraphEdge<T> * > * edges;
	bool directed;

    void dfs_reverse(std::vector<T> * dfsOrder, std::vector<GraphNode<T> * > * topologicalOrder);
	void dfs_navigate(GraphNode<T> * node, std::vector<T> * dfsOrder,
					  std::vector<T> * topologicalOrder, int &topoLabel);
    void dfs_navigate_reverse(GraphNode<T> * node, std::vector<T> * dfsOrder,
                              std::vector<GraphNode<T> * > * topologicalOrder, int &topoLabel);
    void dfs_navigate_reverse_iter(GraphNode<T> * node, std::vector<T> * dfsOrder,
                                   std::vector<GraphNode<T> * > * topologicalOrder, int &topoLabel);
	std::vector<std::set<T> * > * getConnectedComponentsUndirected();
    std::vector<std::set<T> * > * getStronglyConnectedComponents(int numComps);
    std::vector<GraphNode<T> * > * getEulerianPathUndirected();
    std::vector<GraphNode<T> * > * getEulerianPathDirected();
    void bfs(GraphNode<T> * start, std::vector<T> * bfsOrder);
public:
	Graph(bool directed);
	Graph(Graph<T> * copy);
	~Graph();

	void addEdge(T a, T b);
	void addEdge(T a, T b, long weight);
    void addEdge(T a, T b, long weight, std::string label);
    void addVertex(T a);
    void removeEdge(T a, T b);
    void removeEdge(GraphNode<T> * a, GraphNode<T> * b);
	void dfs(std::vector<T> * dfsOrder, std::vector<T> * topologicalOrder);
    void dfs(T start, std::vector<T> * dfsOrder, std::vector<T> * topologicalOrder);
	void bfs(std::vector<T> * bfsOrder);
    void bfs(T start, std::vector<T> * bfsOrder);
	void deleteVertex(GraphNode<T> * vertex);
	bool pathExists(T a, T b);
	std::vector<std::set<T> * > * getConnectedComponents(int numComps);
    std::vector<GraphNode<T> * > * getEulerianPath();
	GraphEdge<T> * getIthEdge(int i);
	void contractEdge(int edgeIndex);
	void reset();
	GraphNode<T> * getNodeForVertex(T val);
	std::vector<GraphEdge<T> * > * getEdges();
	std::unordered_map<T, GraphNode<T> * > * getVertices();
	std::vector<DijkstraNode<T> > * findShortestPaths(GraphNode<T> * source);
};

template<class T>
Graph<T>::Graph(bool isDirected)
{
	vertices = new std::unordered_map<T, GraphNode<T> * >;
	edges = new std::vector<GraphEdge<T> * >;
	directed = isDirected;
}

template<class T>
Graph<T>::Graph(Graph<T> * copy)
{
	directed = copy->directed;
	vertices = new std::unordered_map<T, GraphNode<T> * >;
	edges = new std::vector<GraphEdge<T> * >;
	for(typename std::vector<GraphEdge<T> * >::iterator it = copy->getEdges()->begin(); it != copy->getEdges()->end(); ++it)
	{
		GraphEdge<T> * edge = *it;
		addEdge(edge->getFirst()->getValue(), edge->getSecond()->getValue(), edge->getWeight(), edge->getLabel());
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
std::unordered_map<T, GraphNode<T> * > * Graph<T>::getVertices()
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
	for(typename std::unordered_map<T, GraphNode<T> * >::iterator it = vertices->begin(); it != vertices->end(); ++it)
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
void Graph<T>::addEdge(T a, T b, long weight, std::string label)
{
	GraphNode<T> * vertex1, * vertex2;
	typename std::unordered_map<T, GraphNode<T> * >::const_iterator vertex1_it = vertices->find(a);
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

	typename std::unordered_map<T, GraphNode<T> * >::const_iterator vertex2_it = vertices->find(b);
	if(vertex2_it == vertices->end())
	{
		vertex2 = new GraphNode<T>(b);
		std::pair<T, GraphNode<T> * > vertex2_pair(b, vertex2);
		vertices->insert(vertex2_pair);
	}
	else
	{
		vertex2 = vertex2_it->second;
	}

	std::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * > * neighbours = vertex1->getNeighbours();
	typename std::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >::const_iterator edgeMapIt =
			neighbours->find(vertex2);
	if(edgeMapIt == neighbours->end())
	{
		GraphEdge<T> * newEdge = new GraphEdge<T>(vertex1, vertex2, weight, label);
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
void Graph<T>::addEdge(T a, T b, long weight)
{
    addEdge(a, b, weight, "");
}

template<class T>
void Graph<T>::addVertex(T a)
{
    GraphNode<T> * vertex = new GraphNode<T>(a);
    std::pair<T, GraphNode<T> * > vertex_pair(a, vertex);
    vertices->insert(vertex_pair);
}

template<class T>
void Graph<T>::removeEdge(GraphNode<T> * vertex1, GraphNode<T> * vertex2)
{
    std::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * > * neighbours = vertex1->getNeighbours();
    neighbours->erase(vertex2);
    if(!directed)
    {
        neighbours = vertex2->getNeighbours();
        neighbours->erase(vertex1);
    }
    for(typename std::vector<GraphEdge<T> * >::iterator it = edges->begin(); it != edges->end();)
    {
        GraphEdge<T> * currEdge = *it;
        if(currEdge->getFirst() == vertex1 && currEdge->getSecond() == vertex2 ||
                (!directed && currEdge->getFirst() == vertex2 && currEdge->getSecond() == vertex1))
        {
            it = edges->erase(it);
        }
        else
        {
            ++it;
        }
    }
}
     
template<class T>
void Graph<T>::removeEdge(T a, T b)
{
    GraphNode<T> * vertex1, * vertex2;
    typename std::unordered_map<T, GraphNode<T> * >::const_iterator vertex1_it = vertices->find(a);
    typename std::unordered_map<T, GraphNode<T> * >::const_iterator vertex2_it = vertices->find(b);
    if(vertex1_it == vertices->end() || vertex2_it == vertices->end())
	{
		return;
    }
	else
	{
        removeEdge(vertex1_it->second, vertex2_it->second);
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
//	std::cout << "Contracting edge " << firstVertex->getValue() << " -> " << secondVertex->getValue() << std::endl;
	if(secondVertex->getNeighbours()->size() > 0)
	{
		for(typename std::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >::iterator it = secondVertex->getNeighbours()->begin();
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
				typename std::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >::iterator it4 =
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
	for(typename std::unordered_map<T, GraphNode<T> * >::iterator it = vertices->begin(); it != vertices->end(); ++it)
	{
		GraphNode<T> * node = it->second;
		if(node->getVisited() == WHITE)
		{
			dfs_navigate(node, dfsOrder, topologicalOrder, topoLabel);
		}
	}
}

template<class T>
void Graph<T>::dfs_reverse(std::vector<T> * dfsOrder, std::vector<GraphNode<T> * > * topologicalOrder)
{
    int topoLabel = vertices->size() - 1;
    for(typename std::unordered_map<T, GraphNode<T> * >::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        GraphNode<T> * node = it->second;
        if(node->getVisited() == WHITE)
        {
            dfs_navigate_reverse_iter(node, dfsOrder, topologicalOrder, topoLabel);
        }
    }
}
        
template<class T>
void Graph<T>::dfs(T start, std::vector<T> * dfsOrder, std::vector<T> * topologicalOrder)
{
    int topoLabel = vertices->size() - 1;
    GraphNode<T> * node = vertices->at(start);
    dfs_navigate(node, dfsOrder, topologicalOrder, topoLabel);
}

template<class T>
void Graph<T>::dfs_navigate_reverse_iter(GraphNode<T> * node, std::vector<T> * dfsOrder,
                                         std::vector<GraphNode<T> * > * topologicalOrder, int &topoLabel)
{
    std::stack<GraphNode<T> * > * dfsStack = new std::stack<GraphNode<T> * >;
    dfsStack->push(node);
    while(!dfsStack->empty())
    {
        GraphNode<T> * currNode = dfsStack->top();
        dfsStack->pop();
        dfsOrder->push_back(currNode->getValue());
        if(currNode->getVisited() == WHITE)
        {
            currNode->setVisited(GRAY);
            dfsStack->push(currNode);
        }
        else if(currNode->getVisited() == GRAY)
        {
            currNode->setVisited(BLACK);
            topologicalOrder->at(topoLabel--) = currNode;
            continue;
        }
        std::set<GraphEdge<T> * > * incidentEdges = currNode->getIncidentEdges();
        if(incidentEdges->size() > 0)
        {
            for(typename std::set<GraphEdge<T> * >::iterator it = incidentEdges->begin();
                it != incidentEdges->end(); ++it)
            {
                GraphEdge<T> * edge = *it;
                GraphNode<T> * otherVertex = edge->getFirst();
                if(otherVertex->getVisited() == WHITE)
                {
                    dfsStack->push(otherVertex);
                }
            }
        }
    }
    delete dfsStack;
}

template<class T>
void Graph<T>::dfs_navigate_reverse(GraphNode<T> * node, std::vector<T> * dfsOrder,
                                    std::vector<GraphNode<T> * > * topologicalOrder, int &topoLabel)
{
    node->setVisited(GRAY);
    dfsOrder->push_back(node->getValue());
    std::set<GraphEdge<T> * > * incidentEdges = node->getIncidentEdges();
    if(incidentEdges->size() > 0)
    {
        for(typename std::set<GraphEdge<T> * >::iterator it = incidentEdges->begin();
            it != incidentEdges->end(); ++it)
        {
            GraphEdge<T> * edge = *it;
            GraphNode<T> * otherVertex = edge->getFirst();
            if(otherVertex->getVisited() == WHITE)
            {
                dfs_navigate_reverse(otherVertex, dfsOrder, topologicalOrder, topoLabel);
            }
        }
    }
    node->setVisited(BLACK);
    topologicalOrder->at(topoLabel--) = node;
}

template<class T>
void Graph<T>::dfs_navigate(GraphNode<T> * node, std::vector<T> * dfsOrder,
							std::vector<T> * topologicalOrder, int &topoLabel)
{
	node->setVisited(GRAY);
	dfsOrder->push_back(node->getValue());
	std::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * > * neighbours = node->getNeighbours();
	if(neighbours->size() > 0)
	{
		for(typename std::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >::iterator it = neighbours->begin();
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
	typename std::unordered_map<T, GraphNode<T> * >::const_iterator vertex1_it = vertices->find(a);
	typename std::unordered_map<T, GraphNode<T> * >::const_iterator vertex2_it = vertices->find(b);

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
void Graph<T>::bfs(T start, std::vector<T> * bfsOrder)
{
    GraphNode<T> * node = vertices->at(start);
    bfs(node, bfsOrder);
}
        
template<class T>
void Graph<T>::bfs(GraphNode<T> * start, std::vector<T> * bfsOrder)
{
    std::queue<GraphNode<T> * > * bfsQueue = new std::queue<GraphNode<T> * >;
    bfsQueue->push(start);
    start->setVisited(GRAY);
    while(!bfsQueue->empty())
    {
        GraphNode<T> * currNode = bfsQueue->front();
        bfsQueue->pop();
//        std::cout << currNode->getValue() << " ";
        bfsOrder->push_back(currNode->getValue());
        
        if(currNode->getNeighbours()->size() > 0)
        {
            for(typename std::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >::const_iterator it = currNode->getNeighbours()->begin();
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

template<class T>
void Graph<T>::bfs(std::vector<T> * bfsOrder)
{
	std::queue<GraphNode<T> * > * bfsQueue = new std::queue<GraphNode<T> * >;
	typename std::unordered_map<T, GraphNode<T> * >::iterator it;
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
//			std::cout << currNode->getValue() << " ";
			bfsOrder->push_back(currNode->getValue());

			if(currNode->getNeighbours()->size() > 0)
			{
				for(typename std::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >::const_iterator it = currNode->getNeighbours()->begin();
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

/**
 * Retrieves strongly connected components of a graph.
 *
 * Algorithm:
 * The algorithm is different for directed graphs and undirected graphs.
 * For undirected graphs, we perform a normal DFS on each unvisited
 * vertex and group together all the nodes visited in one DFS call.
 *
 * Time complexity: O(n) where n is the number of vertices in the graph.
 * Space complexity: O(1)
 *
 * For directed graphs, we follow kosaraju's algorithm for retrieving
 * strongly connected components.
 */
template<class T>
std::vector<std::set<T> * > * Graph<T>::getConnectedComponents(int numComps)
{
	if(!directed)
	{
		return getConnectedComponentsUndirected();
	}
	else
	{
        return getStronglyConnectedComponents(numComps);
	}
}

/**
 * Problem:
 * Get the set of connected components in an undirected graph.
 * A connected component of an undirected graph is a subset of vertices
 * with the property that start from any vertex in this subset
 * we can reach all the other vertices in the same subset.
 *
 * Idea: DFS discovers everything findable and nothing more.
 *       Do DFS repeatedly to find connected components.
 * Algorithm:
 * 1) For each vertex in the graph, run DFS starting
 *    from that vertex if that vertex is not visited yet.
 * 2) Group all vertices visited in a single invocation of DFS
 *    into a connected component.
 * 3) Return all groups of vertices as a set.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template<class T>
std::vector<std::set<T> * > * Graph<T>::getConnectedComponentsUndirected()
{
	std::vector<std::set<T> * > * components = new std::vector<std::set<T> * >;
	std::vector<T> topologicalOrder;
	int topoLabel = vertices->size() - 1;
    topologicalOrder.resize(vertices->size());
	for(typename std::unordered_map<T, GraphNode<T> * >::iterator it = vertices->begin(); it != vertices->end(); ++it)
	{
		GraphNode<T> * node = it->second;
		if(node->getVisited() == WHITE)
		{
			std::set<T> * currComponent = new std::set<T>;
			std::vector<T> dfsOrder;
			dfs_navigate(node, &dfsOrder, &topologicalOrder, topoLabel);
			currComponent->insert(dfsOrder.begin(), dfsOrder.end());
			components->push_back(currComponent);
		}
	}
	return components;
}

/**
 * Problem:
 * Get the set of strongly connected components in a directed graph.
 * A strongly connected component of a directed graph is a subset of vertices
 * with the property that start from any vertex in this subset
 * we can reach all the other vertices in the same subset.
 *
 * Idea: We use Kosaraju's algorithm to find strongly connected components.
 * Algorithm:
 * 1) Run a specialized version of dfs_navigate called 'dfs_navigate_reverse'
 *    which navigates edges in reverse (that is it picks incident edges instead of
 *    neighbours. Also compute the finishing times while doing this DFS.
 * 2) Now run a second DFS (this time normally) while picking the vertices
 *    in the decreasing order of finishing times.
 * 3) Every iteration in the second DFS loop outputs a strongly
 *    connected component.
 */
template<class T>
std::vector<std::set<T> * > * Graph<T>::getStronglyConnectedComponents(int numComps)
{
    std::vector<std::set<T> * > * components = new std::vector<std::set<T> * >;
    std::vector<GraphNode<T> * > topologicalOrder;
    int topoLabel = vertices->size() - 1;
    topologicalOrder.resize(vertices->size());

    std::vector<T> dfsOrder;
    dfs_reverse(&dfsOrder, &topologicalOrder);
    reset();
    for(typename std::vector<GraphNode<T> * >::iterator it = topologicalOrder.begin(); it != topologicalOrder.end(); ++it)
    {
        GraphNode<T> * node = *it;
        if(node->getVisited() == WHITE)
        {
            std::set<T> * currComponent = new std::set<T>;
            std::vector<T> bfsOrder;
            bfs(node, &bfsOrder);
            currComponent->insert(bfsOrder.begin(), bfsOrder.end());
            components->push_back(currComponent);
            //numComps--;
            //if(numComps == 0) break;
        }
    }
    return components;
}

template<class T>
std::vector<GraphNode<T> * > * Graph<T>::getEulerianPath()
{
    if(directed)
    {
        return getEulerianPathDirected();
    }
    else
    {
        return getEulerianPathUndirected();
    }
}

template<class T>
std::vector<GraphNode<T> * > * Graph<T>::getEulerianPathUndirected()
{
    std::stack<GraphNode<T> * > * st = new std::stack<GraphNode<T> * >;
    return NULL;
}

/**
 * Problem:
 * Find a eulerian path in a directed graph.
 * A eulerian path is a series of vertices which can be traversed
 * by following the respective edges where each edge is traversed
 * only once and all edges are traversed.
 *
 * Algorithm:
 * 1) Loop through all the vertices and find the vertices
 *    having in-degree not equal to their out-degree.
 * 2) If there are exactly 2 vertices of 0 vertices having
 *    in-degree not equal to the out-degree, then the graph
 *    has a eulerian path. Otherwise no eulerian path is possible
 *    and hence return NULL.
 * 3) If there are two vertices whose in-degree is not equal to
 *    the out-degree, then one of them will have in-degree less
 *    than out-degree and that'll be the start vertex.
 *    The other vertex will have in-degree greater than out-degree
 *    and that'll be the end vertex.
 * 4) If there are 0 vertices whose in-degree is not equal to the
 *    out-degree then start at any arbitrary vertex.
 * 5) If there is at least one out-going edge from the current
 *    vertex, then push the current vertex onto the stack,
 *    remove the edge from the graph and then set current vertex
 *    as the head of the out-going edge.
 * 6) If there are no out-going edges from the current vertex,
 *    add the current vertex to the eulerian path and pop it
 *   from the stack.
 * 7) When the stack is empty and the current vertex has no
 *    more neighbours the loop ends. The eulerian path vector
 *    has the vertices in reverse order. Reverse the vector
 *    and return.
 *
 * Time complexity: O(m + n)
 * Space complexity: O(n)
 */
template<class T>
std::vector<GraphNode<T> * > * Graph<T>::getEulerianPathDirected()
{
    std::stack<GraphNode<T> * > * st = new std::stack<GraphNode<T> * >;
    std::vector<GraphNode<T> * > * eulerianPath = new std::vector<GraphNode<T> * >;
    GraphNode<T> * startVertex = NULL, * endVertex = NULL;
    GraphNode<T> * currentVertex = NULL;
    for(typename std::unordered_map<T, GraphNode<T> * >::iterator it = vertices->begin(); it != vertices->end(); ++it)
    {
        GraphNode<T> * v = it->second;
        if(v->getInDegree() > v->getOutDegree())
        {
            if(endVertex != NULL)
            {
                // more than one vertex has its in degree greater than out degree
                // eulerian path not possible
                return NULL;
            }
            endVertex = v;
        }
        if(v->getInDegree() < v->getOutDegree())
        {
            if(startVertex != NULL)
            {
                // more than one vertex has its in degree less than out degree
                // eulerian path not possible
                return NULL;
            }
            startVertex = v;
        }
    }
    if(startVertex == NULL && endVertex == NULL)
    {
        startVertex = vertices->begin()->second;
    }
    else if(startVertex == NULL || endVertex == NULL)
    {
        return NULL;
    }
    currentVertex = startVertex;
    while(currentVertex->getNeighbours()->size() > 0 ||
            !st->empty())
    {
        if(currentVertex->getNeighbours()->size() == 0)
        {
            eulerianPath->push_back(currentVertex);
            currentVertex = st->top();
            st->pop();
        }
        else
        {
            st->push(currentVertex);
            typename std::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >::iterator it =
                currentVertex->getNeighbours()->begin();
            GraphNode<T> * otherVertex = it->first;
            removeEdge(currentVertex, otherVertex);
            currentVertex = otherVertex;
        }
    }
    eulerianPath->push_back(currentVertex);
    delete st;
    std::reverse(eulerianPath->begin(), eulerianPath->end());
    return eulerianPath;
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

/**
 * Given this graph, find shortest paths to all other vertices from a given
 * source vertex. (Single source shortest paths problem).
 *
 * Approach: Dijkstra's shortest paths algorithm (Greedy)
 *
 * Data structure:
 * We maintain a heap of Dijkstra nodes where each Dijkstra node
 * contains a pointer to the original graph node and has a score called
 * Dijkstra score.
 *
 * At any given point in the algorithm, the Dijkstra score stands for
 * the shortest path from the source vertex to that node where
 * all the vertices in the shortest path are from the currently processed
 * set. Dijkstra algorithm, at any arbitrary iteration, divides the set of
 * vertices into processed set and unprocessed set. The processed set of
 * vertices have their shortest paths already discovered, while shortest paths for unprocessed
 * set of vertices are not yet finalized.
 *
 * Algorithm:
 * 1) Build a binary min-heap of all Dijkstra nodes in the graph. Initially
 *    the Dijkstra score of all nodes is +(infinity) except the source vertex
 *    for which the Dijkstra score will be 0.
 * 2) While the heap is non-empty, pop out the minimum element in the heap
 *    and add the popped out node to the result where its Dijkstra score
 *    equals the shortest path from source to that vertex.
 * 3) When a vertex is popped out from unprocessed node set and consumed into
 *    processed element set, we need to update teh Dijkstra score for some
 *    vertices in the graph which share an edge with the just consumed element.
 *    The new Dijkstra score will be the Dijkstra score of the consumed element
 *    + the edge weight of the edge from the consumed element to the node in question.
 *    If the new Dijkstra score is less than the nodes' existing Dijkstra score,
 *    update the Dijkstra score of that node in the heap.
 * 4) Algorithm halts when the heap is empty. At that point, all the shortest
 *    paths have been discovered.
 *
 * Time complexity: O(m log n)
 *      There are O(n + m) heap operations and assuming n = O(m), so there are
 *      O(m) heap operations each taking O(log n). So time complexity is O(m log n)
 * Space complexity: O(n)
 */
template<class T>
std::vector<DijkstraNode<T> > * Graph<T>::findShortestPaths(GraphNode<T> * source)
{
	std::vector<DijkstraNode<T> > * shortestPaths =
			new std::vector<DijkstraNode<T> >;
	std::unordered_map<GraphNode<T> *, DijkstraNode<T> > *
		nodeMapping = new std::unordered_map<GraphNode<T> *, DijkstraNode<T> >;

	std::vector<DijkstraNode<T> > * unprocessedElems = new std::vector<DijkstraNode<T> >;
	for(typename std::unordered_map<T, GraphNode<T> * >::iterator it = vertices->begin(); it != vertices->end(); ++it)
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
		for(typename std::unordered_map<GraphNode<T> *, std::set<GraphEdge<T> * > * >::const_iterator it = currNode->getNeighbours()->begin();
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
