/*
 * closetpair.h
 *
 *  Created on: Aug 1, 2013
 *      Author: venkat
 */

#ifndef CLOSETPAIR_H_
#define CLOSETPAIR_H_


class Point
{
	int x, y;
public:
	Point(int x, int y);
	int getX();
	int getY();
	bool operator<(Point &other);
	bool operator>(Point &other);
	bool operator==(Point &other);
};

Point::Point(int xVal, int yVal)
{
	x = xVal;
	y = yVal;
}

int Point::getX()
{
	return x;
}

int Point::getY()
{
	return y;
}

bool Point::operator<(Point &other)
{
	return x < other.getX() && y < other.getY();
}

bool Point::operator>(Point &other)
{
	return !operator<(other);
}

bool Point::operator==(Point &other)
{
	return x == other.getX() && y == other.getY();
}

struct PointXComparator
{
	bool operator()(Point a, Point b)
	{
		return a.getX() < b.getX();
	}
};

struct PointYComparator
{
	bool operator()(Point a, Point b)
	{
		return a.getY() < b.getY();
	}
};

/*
std::pair<Point, Point> findClosestPair(std::vector<Point> * allPoints)
{

}
*/

#endif /* CLOSETPAIR_H_ */
