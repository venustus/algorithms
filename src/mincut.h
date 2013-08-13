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
	std::vector<std::pair<GraphNode<T> *, GraphNode<T> * > > * edges = graph->getEdges();
	while(edges->size() > 2)
	{
		int selectedEdgeIndex = (rand() % (int)(edges->size()));
		graph->contractEdge(selectedEdgeIndex);
	}
	return edges->size();
}



#endif /* MINCUT_H_ */
