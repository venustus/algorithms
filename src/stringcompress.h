/*
 * stringcompress.h
 *
 *  Created on: Apr 27, 2013
 *      Author: venkat
 */

#ifndef STRINGCOMPRESS_H_
#define STRINGCOMPRESS_H_

/**
 * Compresses string orig by replacing successively repeated characters by their count.
 * But if the compressed string is of the same length as the original string, then
 * the original string is returned. For example aabbccdd will be returned as is since the
 * compressed string a2b2c2d2 is of the same length.
 * Time complexity: O(n) where n is the length of original string.
 * Space complexity: O(n) where n is the length of the original string.
 */
char * compress(char *orig, int len);


#endif /* STRINGCOMPRESS_H_ */
