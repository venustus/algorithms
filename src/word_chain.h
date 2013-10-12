/*
 * word_chain.h
 *
 *  Created on: Oct 7, 2013
 *      Author: venkat
 */

#ifndef WORD_CHAIN_H_
#define WORD_CHAIN_H_

#include <vector>
#include <string>

/**
 * Problem:
 * Given a list of dictionary words, find out if
 * words can be arranged in such a way that they form a chain
 * with the first and last letters of individual words.
 * If it can be arranged, return a sequence of such words.
 * Otherwise, return empty vector.
 *
 * Ex: flipkart telecom magnet tower rainbow - Yes
 * Ex: something television machine rain elephant - No
 */
std::vector<std::string> findWordChain(std::vector<std::string>& input);

std::vector<std::string> findWordChain2(std::vector<std::string>& input);


#endif /* WORD_CHAIN_H_ */
