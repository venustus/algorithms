/*
 * graph_tests.cpp
 *
 *  Created on: Aug 13, 2013
 *      Author: venkat
 */

#include "gtest/gtest.h"
#include "graph.h"
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
		EXPECT_EQ(bfslist, *bfsOrder);
		graph->reset();

		static const int arr_dfs[] = {1, 2, 4, 3};
		std::vector<int> dfslist(arr_dfs, arr_dfs + sizeof(arr_dfs)/sizeof(arr_dfs[0]));
		std::vector<int> * dfsOrder = new std::vector<int>;
		graph->dfs(dfsOrder);
		EXPECT_EQ(dfslist, *dfsOrder);
	}

	TEST(GraphTests, MinCutTest) {
		Graph<int> * graph = new Graph<int>(false);
		graph->addEdge(1, 2);
		graph->addEdge(1, 3);
		graph->addEdge(2, 4);
		graph->addEdge(3, 4);

		int minCut = findMinCut(graph);
		EXPECT_EQ(minCut, 2);
	}
}


