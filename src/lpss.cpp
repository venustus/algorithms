/*
 * lpss.cpp
 *
 *  Created on: Oct 1, 2013
 *      Author: venkat
 */

#include <vector>
#include <iostream>
#include "lpss.h"

std::string reconstructPalindromeSolution(std::string in,
		                                  std::vector<std::vector<int> >& trace,
		                                  int i, int j)
{
	std::string result = "";
	if(i == j)
	{
		result = result + in.at(i);
		return result;
	}
	if(i + 1 == j && in.at(i) == in.at(j))
	{
		result = result + in.at(i) + in.at(j);
		return result;
	}
	std::string subResult;
	switch(trace[i][j])
	{
	case 0:
		subResult = reconstructPalindromeSolution(in, trace, i + 1, j - 1);
		result = in.at(i) + subResult + in.at(j);
		break;
	case 1:
		result = reconstructPalindromeSolution(in, trace, i + 1, j);
		break;
	case 2:
		result = reconstructPalindromeSolution(in, trace, i, j - 1);
		break;
	}
	return result;
}

/**
 * Given a string 'in', find out the longest subsequence of
 * the string that is also a palindrome.
 *
 * Approach: Dynamic Programming
 * Algorithm:
 * 1) Initialize 2-dimensional arrays m and trace where
 *    m[i][j] represents longest palindrome subsequence of the string
 *    formed by substring of the input from ith position to the jth position.
 *    Similarly, trace[i][j] a pointer to a sub problem of smaller size.
 *    More precisely, trace[i][j] is 0 if the in[i] == in[j] and we recurse
 *    to the sub problem formed by indices i + 1, j - 1.
 *    trace[i][j] = 1 or 2 for cases where we recurse on sub problems formed
 *    by indices i + 1,j and i, j - 1 respectively.
 * 2) m[i][i] = 1 for all i.
 * 3) Compute m, start and end in a bottom up fashion where
 *    longest palindromes are computed for all substrings of length 2
 *	  then, for all substrings of length 2 and so on.
 * 4) The result is in m[0][in.length() - 1].
 *
 * Time complexity: O(n^2)
 * Space complexity: O(n^2)
 */
std::string getLongestPalindromeSubsequence(std::string in)
{
	std::vector<std::vector<int> > m;
	std::vector<std::vector<int> > trace;
	m.resize(in.length());
	trace.resize(in.length());
	for(int i = 0; i < in.length(); i++)
	{
		m[i].resize(in.length());
		trace[i].resize(in.length());
		m[i][i] = 1;
		trace[i][i] = 0;
	}
	int len = 2;
	while(len <= in.length())
	{
		for(int i = 0; i < in.length(); i++)
		{
			int j = i + len - 1;
			if(j >= in.length())
			{
				break;
			}

			int cand1 = 0, cand2 = 0, cand3 = 0;
			if(in.at(i) == in.at(j))
			{
				if(i + 1 == j)
				{
					cand1 = 2;
				}
				else
				{
					cand1 = 2 + m[i + 1][ j - 1];
				}
			}
			cand2 = m[i + 1][j];
			cand3 = m[i][j - 1];
			m[i][j] = std::max(cand1, std::max(cand2, cand3));
			if(m[i][j] == cand1)
			{
				trace[i][j] = 0;
			}
			else if(m[i][j] == cand2)
			{
				trace[i][j] = 1;
			}
			else
			{
				trace[i][j] = 2;
			}
		}
		len++;
	}
	return reconstructPalindromeSolution(in, trace, 0, in.length() - 1);
}

