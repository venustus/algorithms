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
#include "word_chain.h"

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
		graph->bfs(1, bfsOrder);
		EXPECT_EQ(bfslist.at(0), bfsOrder->at(0));
		EXPECT_EQ(bfslist.at(3), bfsOrder->at(3));
		graph->reset();

		static const int arr_dfs[] = {1, 2, 4, 3};
		std::vector<int> dfslist(arr_dfs, arr_dfs + sizeof(arr_dfs)/sizeof(arr_dfs[0]));
		std::vector<int> * dfsOrder = new std::vector<int>;
		std::vector<int> * topoOrder = new std::vector<int>(4, 0);
		graph->dfs(1, dfsOrder, topoOrder);
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
		EXPECT_EQ(2, minCut);

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
//			std::cout << "Number of vertices: " << graph->getVertices()->size() << std::endl;
//			std::cout << "Number of edges: " << graph->getEdges()->size() << std::endl;
			minCut = kragersMinCut(graph);
//			std::cout << "Mincut: " << minCut << std::endl;
            ASSERT_EQ(17, minCut);
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

        std::unordered_map<int, int> expectedShortestPaths;
        expectedShortestPaths[1] = 0;
        expectedShortestPaths[2] = 2;
        expectedShortestPaths[3] = 5;
        expectedShortestPaths[4] = 1;
        expectedShortestPaths[5] = 6;
        expectedShortestPaths[6] = 10;

		std::vector<DijkstraNode<int> > * shortestPaths = graph->findShortestPaths(graph->getNodeForVertex(1));
		for(std::vector<DijkstraNode<int> >::iterator it = shortestPaths->begin(); it != shortestPaths->end(); ++it)
		{
			DijkstraNode<int> dNode = *it;
            ASSERT_EQ(expectedShortestPaths[dNode.getNode()->getValue()], dNode.getScore());
//			std::cout << "Shortest path to node " << dNode.getNode()->getValue() << " is " << dNode.getScore() << std::endl;
		}
	}
    
    TEST(GraphTests, ConnectedComponentsTest)
    {
        Graph<int> * graph = new Graph<int>(false);
		graph->addEdge(1, 2);
		graph->addEdge(1, 3);
		graph->addEdge(2, 4);
		graph->addEdge(3, 4);
        graph->addVertex(5);

        std::set<std::set<int> * > * comps = graph->getConnectedComponents();
        EXPECT_EQ(2, comps->size());
    }

	TEST(GraphTests, WordChainTest)
	{
		static const std::string str_arr[] = {"rainbow", "flipkart", "armour", "magenta", "telecom" };
		std::vector<std::string> str_list(str_arr, str_arr + sizeof(str_arr)/sizeof(str_arr[0]));

		std::vector<std::string> topoOrder = findWordChain(str_list);

		static const std::string result_arr[] = {"flipkart", "telecom", "magenta", "armour", "rainbow"};
		std::vector<std::string> result_list(result_arr, result_arr + sizeof(result_arr)/sizeof(result_arr[0]));
		EXPECT_EQ(result_list, topoOrder);

		static const std::string str_arr1[] = {"something", "machine", "elephant", "television", "rain" };
		std::vector<std::string> str_list1(str_arr1, str_arr1 + sizeof(str_arr1)/sizeof(str_arr1[0]));

        std::vector<std::string> results = findWordChain2(str_list);
        EXPECT_EQ(result_list, results);

        results = findWordChain2(str_list1);
        EXPECT_EQ(0, results.size());

        static const std::string str_arr2[] = {"rainbow", "flipkart", "tremor", "magnet", "telecom" };
        std::vector<std::string> str_list2(str_arr2, str_arr2 + sizeof(str_arr2)/sizeof(str_arr2[0]));

        static const std::string result_arr1[] = {"flipkart", "telecom", "magnet", "tremor", "rainbow"};
        std::vector<std::string> result_list1(result_arr1, result_arr1 + sizeof(result_arr1)/sizeof(result_arr1[0]));

        results = findWordChain2(str_list2);
        EXPECT_EQ(result_list1, results);
	}
}


