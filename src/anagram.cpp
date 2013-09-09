/*
 * anagram.cpp
 *
 *  Created on: Sep 5, 2013
 *      Author: venkat
 */

#include <cstdlib>
#include "anagram.h"

/**
 * Algorithm:
 * 1) Concatenate strings 'a' and 'b' together.
 * 2) Loop through each character of 'a' + 'b'.
 * 3) Perform the XOR operation with a running 'result'.
 * 4) If 'result' is 0, then both are anagrams of each other.
 *
 * This results from the fact that X^X is 0. If every character
 * of 'a' is in 'b' and every character of 'b' is in 'a', then
 * each character appears exactly twice and they all cancel out
 * giving 0 as the result.
 *
 * Time complexity: O(m + n) - m is size of string 'a' and n is size of string 'b'.
 * Space complexity: O(1)
 */
bool areAnagrams(const std::string a, const std::string b)
{
	std::string c = a + b;
	const char * i = c.c_str();
	int result = 0;
	while((*i) != NULL)
	{
		result ^= (*i);
		i += sizeof(char);
	}
	return (result == 0);
}

