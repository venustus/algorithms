/*
 * fibonacci.cpp
 *
 *  Created on: Sep 6, 2013
 *      Author: venkat
 */


#include "fibonacci.h"

/**
 * Algorithm:
 * 1) Initialize an integer array of size n
 * 2) Set the base case - initialize first two fibonacci numbers
 * 3) Iterate from 2 to n-1 and compute fibonacci number using
 *    the standard fibonacci formula. Use the pre-computed values
 *    from the array instead of recursive call.
 */
int getNthFibonacciNo(int n)
{
	int fibs[n];
	fibs[0] = 0;
	fibs[1] = 1;
	for(int i = 2; i < n; i++)
	{
		fibs[i] = fibs[i - 1] + fibs[i - 2];
	}
	return fibs[n - 1];
}

