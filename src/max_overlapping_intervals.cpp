/*
 * max_overlapping_intervals.cpp
 *
 *  Created on: Sep 12, 2013
 *      Author: venkat
 */

#include <vector>
#include <algorithm>
#include "max_overlapping_intervals.h"

Interval::Interval(int s, int e)
{
	start = s;
	end = e;
}

Interval::~Interval()
{

}

int Interval::getStart() const
{
	return start;
}

int Interval::getEnd() const
{
	return end;
}

EdgePoint::EdgePoint(int pos, int t)
{
	position = pos;
	type = t;
}

int EdgePoint::getPosition() const
{
	return position;
}

int EdgePoint::getType() const
{
	return type;
}

bool compareEdgePoints (EdgePoint *i, EdgePoint *j)
{
	if(i->getPosition() == j->getPosition()){
		if(i->getType() == j->getType())
		{
			return true;
		}
		else if(i->getType() < j->getType())
		{
			return false;
		}
		else return true;
	}
	else return (i->getPosition() < j->getPosition());
}

/**
 * Given a list of intervals, find maximum number of overlapping
 * intervals.
 * Algorithm:
 * 1) Create an array of edge points where each edge point has a type
 *    - whether it is start or end.
 * 2) Convert the 'intervals' list into this array by putting
 *    start and end points in this array separately and marking them as such.
 *    If there are ties, put end points before start points.
 * 3) Sort the edge point array.
 * 4) Loop through the edge point array and whenever you see a start edge point
 *    increment 'numStarts' and whenever you see an end edge point, decrement it.
 * 5) Keep track of a running 'maxStarts' that keeps track of maximum value of
 *    'numStarts'.
 *
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
int getMaxOverlappingIntervals(std::vector<Interval>& intervals)
{
	std::vector<EdgePoint *> points;
	for(std::vector<Interval>::const_iterator it = intervals.begin(); it != intervals.end(); ++it)
	{
		EdgePoint * startPoint = new EdgePoint((*it).getStart(), 0);
		EdgePoint * endPoint = new EdgePoint((*it).getEnd(), 1);
		points.push_back(startPoint);
		points.push_back(endPoint);
	}
	std::sort(points.begin(), points.end(), compareEdgePoints);
	int numStarts = 0, maxStarts = 0;
	for(std::vector<EdgePoint *>::const_iterator it = points.begin(); it != points.end(); ++it)
	{
		switch((*it)->getType())
		{
		case 0:
			numStarts++;
			if(maxStarts < numStarts)
			{
				maxStarts = numStarts;
			}
			break;
		case 1:
			numStarts--;
			break;
		}
	}
	return maxStarts;
}
