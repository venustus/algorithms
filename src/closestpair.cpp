/*
 * closestpair.cpp
 *
 *  Created on: Aug 2, 2013
 *      Author: venkat
 */

#include <limits>
#include <vector>
#include "sorting.h"
#include "closestpair.h"

Point::Point(int xVal, int yVal)
{
	x = xVal;
	y = yVal;
}

Point::Point()
{
	x = 0;
	y = 0;
}

int Point::getX() const
{
	return x;
}

int Point::getY() const
{
	return y;
}

bool Point::operator<(const Point &other) const
{
	return x < other.getX() && y < other.getY();
}

bool Point::operator>(const Point &other) const
{
	return !operator<(other);
}

bool Point::operator==(const Point &other) const
{
	return x == other.getX() && y == other.getY();
}

bool xCompare(const void * a, const void * b)
{
	Point * aPoint = (Point *) a;
	Point * bPoint = (Point *) b;
	return aPoint->getX() < bPoint->getX();
}

bool yCompare(const void * a, const void * b)
{
	Point * aPoint = (Point *) a;
	Point * bPoint = (Point *) b;
	return aPoint->getY() < bPoint->getY();
}

PointPair::PointPair(const Point &a, const Point &b)
{
	pointPair = std::make_pair(a, b);
}

Point PointPair::getFirst()
{
	return pointPair.first;
}

Point PointPair::getSecond()
{
	return pointPair.second;
}

double PointPair::findEuclidianDistance() const
{
	Point a = pointPair.first;
	Point b = pointPair.second;
	int squared = ((a.getX() - b.getX()) * (a.getX() - b.getX())) + ((a.getY() - b.getY()) * (a.getY() - b.getY()));
	return sqrt(squared);
}

bool PointPair::operator<(const PointPair & other) const
{
	double currentDistance = findEuclidianDistance();
	double otherDistance = other.findEuclidianDistance();
	return currentDistance < otherDistance;
}

bool PointPair::operator>(const PointPair & other) const
{
	return !(operator<(other));
}

bool PointPair::operator==(const PointPair & other) const
{
	return pointPair.first == other.pointPair.first &&
			pointPair.second == other.pointPair.second;
}

PointPair & PointPair::operator=(const PointPair & other)
{
	pointPair.first = other.pointPair.first;
	pointPair.second = other.pointPair.second;
	return *this;
}

/**
 * Given a list of points in space, find a pair of points
 * with closest euclidian distance.
 *
 * Paradigm: Divide and conquer.
 * Algorithm:
 * 1) Sort points according to their x-coordinate and y-coordinate.
 * 2) Divide the point space in half.
 * 3) Find the closest pair of points recursively in left half
 *    and right half.
 * 4) Identify all points in the y-sorted array that are part of the delta
 *    zone - where delta d is the minimum of the euclidian distance
 *    found between closest pair of points in left half and right half
 *    respectively.
 * 5) For each point in the delta zone, compute and compare distances
 *    between previous 7 points in the y-sorted array of points in delta zone.
 * 6) If any pair in delta zone are closer than the closest pair of points
 *    in left or right half, keep track of closest pair of points by running min.
 * 7) Return the closest pair overall.
 *
 * Time complexity: O(n log n) where n is the number of points.
 */
PointPair findClosestPair(std::vector<Point> * allPoints)
{
	std::vector<Point> * sortedX = mergesort(allPoints, &xCompare);
	std::vector<Point> * sortedY = mergesort(allPoints, &yCompare);
	return findClosestPair(sortedX, sortedY);
}

PointPair findClosestPair(std::vector<Point> * xSortedPoints, std::vector<Point> * ySortedPoints)
{
	if(xSortedPoints->size() == 1)
	{
		// in case of only one point in a set, return a point pair paired with inifitely far point
		// so that the distance is subsumed, but the original point is taken
		return PointPair(xSortedPoints->at(0), Point(std::numeric_limits<int>::max(), std::numeric_limits<int>::max()));
	}
	if(xSortedPoints->size() == 2)
	{
		return PointPair(xSortedPoints->at(0), xSortedPoints->at(1));
	}

	int midX = xSortedPoints->size()/2;
	PointPair leftPair = findClosestPair(new std::vector<Point>(xSortedPoints->begin(),
			xSortedPoints->begin() + xSortedPoints->size()/2));
	PointPair rightPair = findClosestPair(new std::vector<Point>(xSortedPoints->begin() + xSortedPoints->size()/2,
			xSortedPoints->end()));
	PointPair deltaPair = std::min(leftPair, rightPair);
	double delta = deltaPair.findEuclidianDistance();
	std::vector<Point> * deltaZone = new std::vector<Point>;
	for(std::vector<Point>::iterator it = ySortedPoints->begin(); it != ySortedPoints->end(); ++it)
	{
		if(abs(it->getX() - xSortedPoints->at(midX).getX()) < delta)
		{
			deltaZone->push_back(*it);
		}
	}
	for(std::vector<Point>::const_iterator it = deltaZone->begin(); it < deltaZone->end() - 7; ++it)
	{
		for(int i = 1; i <=7; i++)
		{
			PointPair * potentialPair = new PointPair(*it, *(it + i));
			if(*potentialPair < deltaPair)
			{
				deltaPair = *potentialPair;
			}
		}
	}
	return deltaPair;
}

