/*
 * fibonacci.cpp
 *
 *  Created on: Sep 6, 2013
 *      Author: venkat
 */


#include "fibonacci.h"

/**
 * Paradigm: Dynamic Programming
 * Algorithm:
 * 1) Initialize an integer array of size n
 * 2) Set the base case - initialize first two fibonacci numbers
 * 3) Iterate from 2 to n-1 and compute fibonacci number using
 *    the standard fibonacci formula. Use the pre-computed values
 *    from the array instead of recursive call.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
int getNthFibonacciNo(int n)
{
	int fibs_prev_prev = 0;
	int fibs_prev = 1;
	for(int i = 2; i < n; i++)
	{
		int new_fib = fibs_prev + fibs_prev_prev;
		fibs_prev_prev = fibs_prev;
		fibs_prev = new_fib;
	}
	return fibs_prev;
}

