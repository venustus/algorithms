/*
 * int_multiply.cpp
 *
 *  Created on: Jul 28, 2013
 *      Author: venkat
 */

#include <cmath>
#include "int_multiply.h"

int numDigits(long_int x)
{
	int digits = 0;
	if(x == 0) return 1;
	while(x > 0)
	{
		x = x/10;
		digits++;
	}
	return digits;
}

/**
 * Returns 10^n.
 */
long_int tenPower(int n)
{
	long_int x = 1;
	while(n > 0)
	{
		x = x * 10;
		n--;
	}
	return x;
}

/**
 * Performs right shift in base 10
 */
long_int rightShift(long_int x, int n)
{
	x = x/pow(10, n);
	return x;
}

long_int getSuffix(long_int x, int n)
{
	return x % tenPower(n);
}

long_int multiply(long_int num1, long_int num2)
{
	int digits1 = numDigits(num1);
	int digits2 = numDigits(num2);
	if(digits1 == 1 || digits2 == 1)
	{
		return num1 * num2;
	}
	long_int a = rightShift(num1, (digits1/2));
	long_int c = rightShift(num2, (digits2/2));
	long_int b = getSuffix(num1, digits1/2);
	long_int d = getSuffix(num2, digits2/2);
	long_int ac = multiply(a, c);
	long_int bd = multiply(b, d);
	long_int aplusbtimescplusd = multiply(a + b, c + d);
	long_int cof1 = tenPower((digits1/2) + (digits2/2));
	long_int cof2 = tenPower(digits1/2);
	long_int sum_term_1 = cof1 * ac;
	long_int sum_term_2 = cof2 * (aplusbtimescplusd - ac - bd);
	return (sum_term_1 + bd + sum_term_2);

}

