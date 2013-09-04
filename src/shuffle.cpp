/*
 * shuffle.cpp
 *
 *  Created on: Sep 4, 2013
 *      Author: venkat
 */

#include <ctime>
#include <cstdlib>
#include "shuffle.h"

using namespace std;

void swap(int (&input)[52], int i, int j)
{
	int tmp = input[i];
	input[i] = input[j];
	input[j] = tmp;
}

void deckShuffle(int (&input)[52])
{
	int size = sizeof(input)/sizeof(int);
	srand(time(NULL));
	for(int i=0; i < size; i++)
	{
		int j = (rand() % size);
		swap(input, i, j);
	}
}


