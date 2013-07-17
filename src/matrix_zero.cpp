/*
 * matrix_zero.cpp
 *
 *  Created on: Apr 30, 2013
 *      Author: venkat
 */

#include <stdlib.h>
#include <vector>
#include "matrix_zero.h"

void markZero(std::vector<std::vector<int> > a, int M, int N)
{
	bool *rows = new bool[M];
	bool *cols = new bool[N];

	for(int i = 0; i < M; i++)
	{
		for(int j = 0; j < N; j++)
		{
			if(a[i][j] == 0)
			{
				rows[i] = true;
				cols[j] = true;
			}
		}
	}

	for(int i = 0; i < M;i++)
	{
		for(int j = 0; j < N;j++)
		{
			if(rows[i] || cols[j])
			{
				a[i][j] = 0;
			}
		}
	}
}

