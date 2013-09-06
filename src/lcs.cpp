/*
 * lcs.cpp
 *
 *  Created on: Sep 6, 2013
 *      Author: venkat
 */

#include <vector>
#include <algorithm>
#include "lcs.h"

void printLCS(std::vector<char> * result, const std::vector<char>& a, std::vector<std::vector<int> >& c,
			  std::vector<std::vector<int> >& lcstrack, int i, int j)
{
	if(i <= 0 || j <= 0)
	{
		return;
	}
	if(lcstrack[i][j] == 0)
	{
		result->push_back(a.at(i - 1));
		printLCS(result, a, c, lcstrack, i - 1, j - 1);
	}
	else if(lcstrack[i][j] == 1)
	{
		printLCS(result, a, c, lcstrack, i-1, j);
	}
	else
	{
		printLCS(result, a, c, lcstrack, i, j-1);
	}
}

std::vector<char> * getLongestCommonSubsequence(std::vector<char>& a, std::vector<char>& b)
{
	std::vector<std::vector<int> > c;
	std::vector<std::vector<int> > lcstrack;
	std::vector<char> * result = new std::vector<char>;
	c.resize(a.size() + 1);
	lcstrack.resize(a.size() + 1);
	for(int i = 0;i <= a.size();i++)
	{
		c[i].resize(b.size() + 1);
		lcstrack[i].resize(b.size() + 1);
		c[i][0] = 0;
	}
	for(int j = 0;j <=b.size();j++)
	{
		c[0][j] = 0;
	}
	for(int i = 1;i <= a.size();i++)
	{
		for(int j = 1;j <= b.size();j++)
		{
			if(a.at(i - 1) == b.at(j - 1))
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				lcstrack[i][j] = 0;
			}
			else if(c[i - 1][j] > c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
				lcstrack[i][j] = 1;
			}
			else
			{
				c[i][j] = c[i][j - 1];
				lcstrack[i][j] = 2;
			}
		}
	}
	printLCS(result, a, c, lcstrack, a.size(), b.size());
	std::reverse(result->begin(), result->end());
	return result;
}


