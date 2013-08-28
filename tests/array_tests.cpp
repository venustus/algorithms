/*
 * array_tests.cpp
 *
 *  Created on: Aug 27, 2013
 *      Author: venkat
 */

#include "gtest/gtest.h"
#include "stable_partition.h"

namespace {
	class ArrayTests : public ::testing::Test {

	};

	TEST(ArrayTests, StablePartitionTest)
	{
		int a[8] = {-1, 1, -4, 7, -5, 3, -2, 2};
		stablePartition(a, 0, 7);
		EXPECT_EQ(a[0], -1);
		EXPECT_EQ(a[1], -4);
		EXPECT_EQ(a[2], -5);
		EXPECT_EQ(a[3], -2);
		EXPECT_EQ(a[4], 1);
		EXPECT_EQ(a[5], 7);
		EXPECT_EQ(a[6], 3);
		EXPECT_EQ(a[7], 2);
	}
}


