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
#include <unordered_map>
#include <functional>
#include <regex>
#include "gtest/gtest.h"
#include "graph.h"
#include "mincut.h"
#include "word_chain.h"

namespace std {
    template <>
    struct hash<DijkstraNode<int> >
    {
    public:
        std::size_t operator()(const DijkstraNode<int>& k) const
        {
            using std::size_t;
            using std::hash;

            // Compute individual hash values for first,
            // second and third and combine them using XOR
            // and bit shifting:

            return hash<int>()(k.getNode()->getValue());
        }
    };

}

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
			minCut = kragersMinCut(graph);
            ASSERT_EQ(17, minCut);
		}
	}

    std::vector<std::string> split(const std::string& input, const std::regex& re)
    {
        std::vector<std::string> results;
        std::copy(std::sregex_token_iterator(input.begin(), input.end(), re, -1),
                  std::sregex_token_iterator(),
                  std::back_inserter<std::vector<std::string> >(results));
        return results;
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
		}

        delete graph;
        graph = new Graph<int>(false);
        std::ifstream edgeArray("/Users/venkat/Documents/Projects/cplusplus/Algorithms/cpluspluspractice/src/dijkstraData.txt");
        if(edgeArray.is_open())
        {
            while(edgeArray.good())
            {
                std::string line;
                getline(edgeArray, line);
                std::regex ws_re("\\s+");
                std::vector<std::string> parts = split(line, ws_re);
                int v = atoi(parts[0].c_str());
                for(std::vector<std::string>::iterator it = parts.begin() + 1; it != parts.end(); ++it)
                {
                    std::string part = *it;
                    std::regex comma(",");
                    std::vector<std::string> subparts = split(part, comma);
                    graph->addEdge(v, atoi(subparts[0].c_str()), atoi(subparts[1].c_str()));
                }
            }
            edgeArray.close();
        }
        shortestPaths = graph->findShortestPaths(graph->getNodeForVertex(1));
        std::unordered_map<int, int> expectedResults;
        expectedResults[7] = 2599;
        expectedResults[37] = 2610;
        expectedResults[59] = 2947;
        expectedResults[82] = 2052;
        expectedResults[99] = 2367;
        expectedResults[115] = 2399;
        expectedResults[133] = 2029;
        expectedResults[165] = 2442;
        expectedResults[188] = 2505;
        expectedResults[197] = 3068;

        for(std::vector<DijkstraNode<int> >::iterator it = shortestPaths->begin(); it != shortestPaths->end(); ++it)
        {
            DijkstraNode<int> dNode = *it;
            try {
                int spd = expectedResults.at(dNode.getNode()->getValue());
                ASSERT_EQ(expectedResults[dNode.getNode()->getValue()], dNode.getScore());
            }
            catch(const std::out_of_range &oor)
            {

            }
        }
	}

    struct SetSizeLess {
        bool operator()( std::set<int> const *lhs, std::set<int> const *rhs ) const
        { return lhs->size() > rhs->size(); }
    };
    
    TEST(GraphTests, ConnectedComponentsTest)
    {
        Graph<int> * graph = new Graph<int>(false);
		graph->addEdge(1, 2);
		graph->addEdge(1, 3);
		graph->addEdge(2, 4);
		graph->addEdge(3, 4);
        graph->addVertex(5);

        std::vector<std::set<int> * > * comps = graph->getConnectedComponents(-1);
        EXPECT_EQ(2, comps->size());
        std::sort(comps->begin(), comps->end(), SetSizeLess());
        EXPECT_EQ(4, comps->at(0)->size());
        EXPECT_EQ(1, comps->at(1)->size());

        graph = new Graph<int>(true);
        graph->addEdge(1, 2);
        graph->addEdge(2, 3);
        graph->addEdge(3, 1);

        graph->addEdge(5, 7);
        graph->addEdge(7, 6);
        graph->addEdge(6, 5);

        graph->addEdge(8, 10);
        graph->addEdge(8, 11);
        graph->addEdge(10, 11);
        graph->addEdge(9, 8);
        graph->addEdge(11, 9);

        graph->addEdge(2, 4);
        graph->addEdge(4, 5);
        graph->addEdge(4, 6);

        graph->addEdge(3, 8);
        graph->addEdge(3, 9);

        graph->addEdge(8, 6);
        graph->addEdge(10, 7);

        comps = graph->getConnectedComponents(-1);
        std::sort(comps->begin(), comps->end(), SetSizeLess());
        EXPECT_EQ(4, comps->size());
        EXPECT_EQ(4, comps->at(0)->size());
        EXPECT_EQ(3, comps->at(1)->size());
        EXPECT_EQ(3, comps->at(2)->size());
        EXPECT_EQ(1, comps->at(3)->size());
    }

    TEST(GraphTests, StronglyConnectedComponentsTest)
    {
        Graph<int> * bigGraph = new Graph<int>(true);
        std::ifstream edgeArray("/Users/venkat/Documents/Projects/cplusplus/Algorithms/cpluspluspractice/src/SCC.txt");
        if(edgeArray.is_open())
        {
            while(edgeArray.good())
            {
                std::string line;
                getline(edgeArray, line);
                std::stringstream ss(line);
                std::string tail, head;
                std::getline(ss, tail, ' ');
                std::getline(ss, head, ' ');
                if(head.empty())
                {
                    bigGraph->addVertex(atoi(tail.c_str()));
                }
                else
                {
                    bigGraph->addEdge(atoi(tail.c_str()), atoi(head.c_str()));
                }
            }
            edgeArray.close();
        }
        std::vector<std::set<int> * > * comps = bigGraph->getConnectedComponents(5);
        std::sort(comps->begin(), comps->end(), SetSizeLess());
        EXPECT_EQ(371762, comps->size());
        EXPECT_EQ(434821, comps->at(0)->size());
        EXPECT_EQ(968, comps->at(1)->size());
        EXPECT_EQ(459, comps->at(2)->size());
        EXPECT_EQ(313, comps->at(3)->size());
        EXPECT_EQ(211, comps->at(4)->size());
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


