/*
 * graph_tests.cpp
 *
 *  Created on: Aug 13, 2013
 *      Author: venkat
 */

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "gtest/gtest.h"
#include "graph.h"
#include "binaryheap.h"
#include "mincut.h"

namespace {
	class GraphTests : public ::testing::Test {

	};

	TEST(GraphTests, TraversalTests) {
		Graph<int> * graph = new Graph<int>(false);
		graph->addEdge(1, 2);
		graph->addEdge(1, 3);
		graph->addEdge(2, 4);
		graph->addEdge(3, 4);

		static const int arr_bfs[] = {1, 2, 3, 4};
		std::vector<int> bfslist(arr_bfs, arr_bfs + sizeof(arr_bfs)/sizeof(arr_bfs[0]));
		std::vector<int> * bfsOrder = new std::vector<int>;
		graph->bfs(bfsOrder);
		EXPECT_EQ(bfslist.at(0), bfsOrder->at(0));
		EXPECT_EQ(bfslist.at(3), bfsOrder->at(3));
		graph->reset();

		static const int arr_dfs[] = {1, 2, 4, 3};
		std::vector<int> dfslist(arr_dfs, arr_dfs + sizeof(arr_dfs)/sizeof(arr_dfs[0]));
		std::vector<int> * dfsOrder = new std::vector<int>;
		std::vector<int> * topoOrder = new std::vector<int>(4, 0);
		graph->dfs(dfsOrder, topoOrder);
		EXPECT_EQ(dfslist.at(0), dfsOrder->at(0));
		EXPECT_EQ(dfslist.at(2), dfsOrder->at(2));

		Graph<int> * directedGraph = new Graph<int>(true);
		directedGraph->addEdge(1, 2);
		directedGraph->addEdge(1, 3);
		directedGraph->addEdge(2, 4);
		directedGraph->addEdge(3, 4);
		static const int arr_topo[] = {1, 3, 2, 4};
		std::vector<int> topolist(arr_topo, arr_topo + sizeof(arr_topo)/sizeof(arr_topo[0]));
		directedGraph->dfs(dfsOrder, topoOrder);
		EXPECT_EQ(topolist.at(0), topoOrder->at(0));
		EXPECT_EQ(topolist.at(3), topoOrder->at(3));
	}

	std::vector<std::string> split(const std::string &s, char delim, std::vector<std::string> &elems) {
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim))
		{
			if(item.length() > 0)
			{
				elems.push_back(item);
			}
		}
		return elems;
	}

	TEST(GraphTests, MinCutTest) {
		Graph<int> * graph = new Graph<int>(false);
		graph->addEdge(1, 2);
		graph->addEdge(1, 3);
		graph->addEdge(2, 4);
		graph->addEdge(3, 4);

		int minCut = findMinCut(graph);
		EXPECT_EQ(minCut, 2);

		delete graph;
		graph = new Graph<int>(false);
		std::ifstream graphInput("/Users/venkat/Documents/Projects/cplusplus/Algorithms/cpluspluspractice/src/kargerMinCut.txt");
		if(graphInput.is_open())
		{
			while(graphInput.good())
			{
				std::string line;
				getline(graphInput, line);
				std::vector<std::string> parts;
				split(line, '\t', parts);
				int startVertex;
				std::istringstream buffer(parts.at(0));
				buffer >> startVertex;
				for(std::vector<std::string>::iterator it = parts.begin() + 1; it != parts.end(); ++it)
				{
					std::istringstream buffer2(*it);
					int vertexValue;
					buffer2 >> vertexValue;
					graph->addEdge(startVertex, vertexValue);
				}
			}
			graphInput.close();
			std::cout << "Number of vertices: " << graph->getVertices()->size() << std::endl;
			std::cout << "Number of edges: " << graph->getEdges()->size() << std::endl;
			minCut = kragersMinCut(graph);
			std::cout << "Mincut: " << minCut << std::endl;
		}
	}

	TEST(GraphTests, ShortestPathsTest) {
		Graph<int> * graph = new Graph<int>(true);
		graph->addEdge(1, 2, 2);
		graph->addEdge(1, 4, 1);
		graph->addEdge(2, 3, 3);
		graph->addEdge(2, 4, 7);
		graph->addEdge(2, 5, 4);
		graph->addEdge(3, 5, 6);
		graph->addEdge(3, 6, 5);
		graph->addEdge(4, 5, 9);
		graph->addEdge(5, 6, 10);

		std::vector<DijkstraNode<int> > * shortestPaths = graph->findShortestPaths(graph->getNodeForVertex(1));
		for(std::vector<DijkstraNode<int> >::iterator it = shortestPaths->begin(); it != shortestPaths->end(); ++it)
		{
			DijkstraNode<int> dNode = *it;
			std::cout << "Shortest path to node " << dNode.getNode()->getValue() << " is " << dNode.getScore() << std::endl;
		}
	}
}


