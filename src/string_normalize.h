/*
 * string_normalize.h
 *
 *  Created on: Apr 23, 2013
 *      Author: venkat
 */

#ifndef STRING_NORMALIZE_H_
#define STRING_NORMALIZE_H_

/**
 * Normalize a string for use in web URLs. For example 'this string with spaces'
 * becomes 'this%20string%20with%20spaces'.
 * This method should do it in place (without allocating new memory).
 * Assume that the input string already has space for the extra characters
 * and len stands for the index of last non-whitespace character.
 * For the above example string, the input will be 'this string with spaces      '
 * and len will be 23.
 * Time complexity: O(n) where n is the length of the original string.
 * Space complexity: O(1)
 */
char * normalize(char *str, int len);

#endif /* STRING_NORMALIZE_H_ */
