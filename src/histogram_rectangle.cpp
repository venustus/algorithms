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

/**
 * Given a histogram (an array of heights),
 * find out a rectangle with largest area.
 *
 * Idea: Use stack data structure.
 * Algorithm:
 * 1) Maintain a stack of integer pairs - pair of the index of bar and
 *    height of the bar at given index.
 * 2) As long as the height increases, keep pushing bars to stack.
 * 3) As soon as the height decreases, keep popping the bars from
 *    stack until you encounter a bar that is of lesser height
 *    than the current bar. At each such iteration, compute
 *    the areas and keep a running max.
 * 4) If the stack is not empty, make one final pass
 *    over the stack and keep popping and computing areas
 *    and updating max area if required.
 * 5) Return the running max.
 *
 * Time complexity: O(n) where n is the number of bars.
 * Space complexity: O(n)
 */
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
