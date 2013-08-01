/*
 * int_multiply.h
 *
 *  Created on: Jul 28, 2013
 *      Author: venkat
 */

#ifndef INT_MULTIPLY_H_
#define INT_MULTIPLY_H_

typedef unsigned long long int long_int;

/**
 * Multiply 2 integers (each having n digits) using Karatsuba multiplication.
 * Gives better asymptotic running time than usual
 * multiplication we do by-hand.
 * Complexity: O(n^(log 3)) where n is the number of digits in a and b.
 */
long_int multiply(long_int a, long_int b);


#endif /* INT_MULTIPLY_H_ */
