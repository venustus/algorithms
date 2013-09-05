/*
 * anagram.cpp
 *
 *  Created on: Sep 5, 2013
 *      Author: venkat
 */

#include <cstdlib>
#include "anagram.h"

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

