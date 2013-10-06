/*
 * wildcard_expansion.cpp
 *
 *  Created on: Sep 23, 2013
 *      Author: venkat
 */

#include <vector>
#include <string>
#include "wildcard_expansion.h"

/**
 * Problem:
 * Given a list of strings with potential wild cards,
 * generate all possible strings by replacing wild cards with
 * either 0 or 1.
 * For example, for 1?00?101, generate {11001101, 11000101, 10001101, 10000101}.
 *
 * Algorithm:
 * 1)
 */
std::vector<std::string> * expandWildcards(std::string input)
{
	std::vector<std::string> * results = new std::vector<std::string>;
	if(input.size() == 1)
	{
		std::string result(input.begin(), input.end());
		results->push_back(result);
		return results;
	}
	const char ch = input.at(0);
	std::string substr(input.begin() + 1, input.end());
	std::vector<std::string> * subResults = expandWildcards(substr);
	for(std::vector<std::string>::iterator it = subResults->begin(); it != subResults->end(); ++it)
	{
		std::string subPerm = *it;
		if('?' == ch)
		{
			results->push_back('0' + subPerm);
			results->push_back('1' + subPerm);
		}
		else
		{
			results->push_back(ch + subPerm);
		}
	}
	delete subResults;
	return results;
}

