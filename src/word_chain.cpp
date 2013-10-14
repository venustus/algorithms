/*
 * word_chain.cpp
 *
 *  Created on: Oct 7, 2013
 *      Author: venkat
 */

#include <functional>
#include <vector>
#include "word_chain.h"
#include "graph.h"

/**
 * Problem:
 * Given a list of dictionary words, find out if
 * words can be arranged in such a way that they form a chain
 * with the first and last letters of individual words.
 * If it can be arranged, return a sequence of such words.
 * Otherwise, return empty vector.
 *
 * Ex: {"rainbow", "flipkart", "armour", "magenta", "telecom" } - Yes
 * Ex: something television machine rain elephant - No
 *
 * Algorithm:
 * 1) Construct a word graph from the given words each word represents
 *    vertices and there is a directed edge between two vertices v1 and v2
 *    if and only if v1 ends with the same character as v2 begins with.
 * 2) Simply perform a topological sort of the graph.
 * 3) The topological ordering is nothing but a word chain.
 *
 * NOTE: This algorithm does not work when there are directed cycles in the
 *       word graph. Because topological sort doesn't make sense
 *       when there are directed cycles.
 *
 * Time complexity: O(n^2)
 * Space complexity: O(n^2)
 */
std::vector<std::string> findWordChain(std::vector<std::string>& input)
{
	Graph<std::string> wordGraph(true);
	for(int i = 0; i < input.size(); i++)
	{
		for(int j = 0; j < input.size() && j != i; j++)
		{
			std::string a = input.at(i);
			std::string b = input.at(j);
			if(a.at(a.size() - 1) == b.at(0))
			{
				wordGraph.addEdge(a, b);
			}
			if(b.at(b.size() - 1) == a.at(0))
			{
				wordGraph.addEdge(b, a);
			}
		}
	}
	std::vector<std::string> dfsorder;
	std::vector<std::string> topoOrder;
	topoOrder.resize(input.size());
	wordGraph.dfs(&dfsorder, &topoOrder);
	std::string prev = topoOrder.at(0);
	for(std::vector<std::string>::iterator it = topoOrder.begin() + 1; it != topoOrder.end(); ++it)
	{
		std::string curr = *it;
		if(prev.at(prev.length() - 1) != curr.at(0))
		{
			std::vector<std::string> emptyList;
			return emptyList;
		}
		prev = curr;
	}
	return topoOrder;
}

std::vector<std::string> findWordChain2(std::vector<std::string>& input)
{
    std::vector<std::string> results;
    Graph<char> charGraph(true);
    for(std::vector<std::string>::iterator it = input.begin(); it != input.end(); ++it)
    {
        std::string currWord = *it;
        charGraph.addEdge(currWord.at(0), currWord.at(currWord.length() - 1), 1, currWord);
    }
    std::vector<GraphNode<char> * > * eulerianPath = charGraph.getEulerianPath();

    if(!eulerianPath)
    {
        return results;
    }
    for(std::vector<std::string>::iterator it = input.begin(); it != input.end(); ++it)
    {
        std::string currWord = *it;
        charGraph.addEdge(currWord.at(0), currWord.at(currWord.length() - 1), 1, currWord);
    }
    std::unordered_map<char, GraphNode<char> * > * vertices = charGraph.getVertices();
    for(std::vector<GraphNode<char> * >::iterator it = eulerianPath->begin(); it != eulerianPath->end(); ++it)
    {
        GraphNode<char> * u = *it;
        if(it != eulerianPath->end() - 1)
        {
            GraphNode<char> * v = *(it + 1);
            GraphNode<char> * w = vertices->find(u->getValue())->second;
            GraphNode<char> * x = vertices->find(v->getValue())->second;
            std::set<GraphEdge<char> * > * edges = w->getNeighbours()->at(x);
            std::set<GraphEdge<char> * >::iterator anyEdgeIter = edges->begin();
            GraphEdge<char> * anyEdge = *anyEdgeIter;
            results.push_back(anyEdge->getLabel());
        }
    }
    return results;
}






