/*
 * wildcard_expansion.h
 *
 *  Created on: Sep 23, 2013
 *      Author: venkat
 */

#ifndef WILDCARD_EXPANSION_H_
#define WILDCARD_EXPANSION_H_

#include <vector>
#include <string>

/**
 * Problem:
 * Given a string with potential wild cards,
 * generate all possible strings by replacing wild cards with
 * either 0 or 1.
 * For example, for 1?00?101, generate {11001101, 11000101, 10001101, 10000101}.
 */
std::vector<std::string> * expandWildcards(std::string input);

#endif /* WILDCARD_EXPANSION_H_ */
