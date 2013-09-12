/*
 * max_overlapping_intervals.h
 *
 *  Created on: Sep 12, 2013
 *      Author: venkat
 */

#ifndef MAX_OVERLAPPING_INTERVALS_H_
#define MAX_OVERLAPPING_INTERVALS_H_

#include <vector>

class Interval
{
	int start;
	int end;
public:
	Interval(int s, int e);
	~Interval();
	int getStart() const;
	int getEnd() const;
};

class EdgePoint
{
	int position;
	int type;
public:
	EdgePoint(int pos, int type);
	int getPosition() const;
	int getType() const;
};

/**
 * Problem Statement:
 * Given a list of intervals (s1, e1), (s2, e2), ... (sn, en)
 * find maximum number of overapping intervals. The intervals are
 * half-open - that is (1, 3) and (3, 6) do not overlap.
 */
int getMaxOverlappingIntervals(std::vector<Interval>& intervals);


#endif /* MAX_OVERLAPPING_INTERVALS_H_ */
