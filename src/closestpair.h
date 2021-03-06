/*
 * closetpair.h
 *
 *  Created on: Aug 1, 2013
 *      Author: venkat
 */

#include <cmath>
#include <algorithm>

#ifndef CLOSETPAIR_H_
#define CLOSETPAIR_H_


class Point
{
	int x, y;
public:
	Point();
	Point(int x, int y);
	int getX() const;
	int getY() const;
	bool operator<(const Point &other) const;
	bool operator>(const Point &other) const;
	bool operator==(const Point &other) const;
};

class PointPair
{
	std::pair<Point, Point> pointPair;
public:
	PointPair(const Point &, const Point &);
	Point getFirst();
	Point getSecond();
	double findEuclidianDistance() const;
	bool operator<(const PointPair & other) const;
	bool operator>(const PointPair & other) const;
	PointPair & operator=(const PointPair & other);
	bool operator==(const PointPair & other) const;
};

/**
 * Given a list of points in space, find a pair of points
 * with closest euclidian distance.
 */
PointPair findClosestPair(std::vector<Point> * allPoints);

PointPair findClosestPair(std::vector<Point> * xSortedPoints, std::vector<Point> * ySortedPoints);

#endif /* CLOSETPAIR_H_ */
