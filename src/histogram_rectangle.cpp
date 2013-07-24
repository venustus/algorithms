/*
 * histogram_rectangle.cpp
 *
 *  Created on: Jul 24, 2013
 *      Author: venkat
 */

#include <vector>
#include <stack>
#include "histogram_rectangle.h"


Histogram::Histogram(std::vector<int> * heightsArr)
{
	heights = heightsArr;
}

std::pair<int, int> Histogram::computeMaxAreaRectangle(int &area)
{
	int maxarea = 0;
	std::pair<int, int> maxpair;
	std::stack<std::pair<int, int> > * barStack = new std::stack<std::pair<int, int> >;
	int index = 0;
	for(index=0; index < heights->size(); index++)
	{
		std::pair<int, int> bar = std::make_pair(index, heights->at(index));
		std::pair<int, int> bartopush = bar;
		while(!barStack->empty() && barStack->top().second >= bar.second)
		{
			int curarea1 = bar.second * (bar.first - barStack->top().first + 1);
			int curarea2 = barStack->top().second * (bar.first - barStack->top().first);
			maxarea = std::max(maxarea, std::max(curarea1, curarea2));
			if(maxarea == curarea1)
			{
				maxpair = std::make_pair(barStack->top().first, bar.first);
			}
			else if(maxarea == curarea2)
			{
				maxpair = std::make_pair(barStack->top().first, bar.first - 1);
			}
			bartopush.first = barStack->top().first;
			bartopush.second = bar.second;
			barStack->pop();
		}
		barStack->push(bartopush);
	}
	while(!barStack->empty())
	{
		int curarea = barStack->top().second * (heights->size() - barStack->top().first);
		maxarea = std::max(curarea, maxarea);
		if(maxarea == curarea)
		{
			maxpair = std::make_pair(barStack->top().first, index--);
		}
		barStack->pop();
	}
	area = maxarea;
	return maxpair;
}
