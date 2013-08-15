/*
 * mincut.h
 *
 *  Created on: Aug 11, 2013
 *      Author: venkat
 */

#include "graph.h"

#ifndef MINCUT_H_
#define MINCUT_H_

/**
 * Returns the number of edges in one of the minimum cuts of a given graph.
 * This function computes the minimum cut using Kragers' randomized min-cut algorithm.
 * At each iteration, we choose uniformly at random one of the remaining edges and then
 * contract the edge such that the two vertices forming the edge are fused together.
 * We repeat the edge contraction until we have only 2 vertices left.
 */
template<typename T>
int findMinCut(Graph<T> * graph)
{
	std::vector<GraphEdge<T> * > * edges = graph->getEdges();
	while(graph->getVertices()->size() > 2)
	{
		int selectedEdgeIndex = (rand() % (int)(edges->size()));
		graph->contractEdge(selectedEdgeIndex);
	}
	return edges->size();
}

template<typename T>
int kragersMinCut(Graph<T> * graph)
{
	Graph<T> * copy = new Graph<T>(graph);
	int globalMinCut = std::numeric_limits<int>::max();
	int count = 0;
	while(count++ < 40000)
	{
		int minCut = findMinCut(copy);
		std::cout << "Found min cut in trial " << count << " to be " << minCut << std::endl;
		if(minCut < globalMinCut)
		{
			globalMinCut = minCut;
		}
		delete copy;
		copy = new Graph<T>(graph);
	}
	return globalMinCut;
}



#endif /* MINCUT_H_ */
