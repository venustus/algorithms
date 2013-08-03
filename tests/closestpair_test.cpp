/*
 * closestpair_test.cpp
 *
 *  Created on: Aug 2, 2013
 *      Author: venkat
 */

#include "gtest/gtest.h"
#include "closestpair.h"

namespace {
	class ClosestPairTest : public ::testing::Test {

	};

	TEST(ClosestPairTest, FindClosestPair) {
		std::vector<Point> * allPoints = new std::vector<Point>;
		allPoints->push_back(Point(3, 1));
		allPoints->push_back(Point(3, 4));
		allPoints->push_back(Point(4, 2));
		allPoints->push_back(Point(1, 1));
		allPoints->push_back(Point(1, 5));
		allPoints->push_back(Point(5, 0));
		allPoints->push_back(Point(5, 4));

		PointPair closestPair = findClosestPair(allPoints);
		EXPECT_EQ(closestPair.getFirst(), Point(3, 1));
		EXPECT_EQ(closestPair.getSecond(), Point(4, 2));
	}
}


