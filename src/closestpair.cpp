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

PointPair findClosestPair(std::vector<Point> * allPoints)
{
	if(allPoints->size() == 1)
	{
		// in case of only one point in a set, return a point pair paired with inifitely far point
		// so that the distance is subsumed, but the original point is taken
		return PointPair(allPoints->at(0), Point(std::numeric_limits<int>::max(), std::numeric_limits<int>::max()));
	}
	if(allPoints->size() == 2)
	{
		return PointPair(allPoints->at(0), allPoints->at(1));
	}
	std::vector<Point> * sortedX = mergesort(allPoints, &xCompare);
	std::vector<Point> * sortedY = mergesort(allPoints, &yCompare);
	int midX = sortedX->size()/2;
	PointPair leftPair = findClosestPair(new std::vector<Point>(sortedX->begin(),
																				sortedX->begin() + sortedX->size()/2));
	PointPair rightPair = findClosestPair(new std::vector<Point>(sortedX->begin() + sortedX->size()/2,
																				sortedX->end()));
	PointPair deltaPair = std::min(leftPair, rightPair);
	double delta = deltaPair.findEuclidianDistance();
	std::vector<Point> * deltaZone = new std::vector<Point>;
	for(std::vector<Point>::iterator it = sortedY->begin(); it != sortedY->end(); ++it)
	{
		if(abs(it->getX() - sortedX->at(midX).getX()) < delta)
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

