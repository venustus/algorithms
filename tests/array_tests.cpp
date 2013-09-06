/*
 * array_tests.cpp
 *
 *  Created on: Aug 27, 2013
 *      Author: venkat
 */

#include "gtest/gtest.h"
#include "stable_partition.h"
#include "subsetswithsum.h"
#include "lis.h"
#include "fibonacci.h"

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

	TEST(ArrayTests, SubsetWithHalfsubTest)
	{
		static const int arr[] = {5, 10, 4, -5, 7, 8, -2, 1};
		std::vector<int> arrlist(arr, arr + sizeof(arr)/sizeof(arr[0]));
		std::set<int> * subsetWithHalfSum = getSubsetsWithHalfSum(&arrlist, 30);
		std::cout << "Subset found: ";
		for(std::set<int>::iterator it = subsetWithHalfSum->begin(); it != subsetWithHalfSum->end(); ++it)
		{
			std::cout << (*it) << ", ";
		}
		std::cout << std::endl;
	}

	TEST(ArrayTests, LongestIncreasingSubsequenceTest)
	{
		static const int arr[] = {5, 2, 6, 3, 4, 1, 9, 9, 8, 9, 5};
		std::vector<int> arrlist(arr, arr + sizeof(arr)/sizeof(arr[0]));
		std::vector<int> lis;
		int size = getLongestIncreasingSubsequence(&arrlist, lis);
		EXPECT_EQ(5, size);
		EXPECT_EQ(2, lis[0]);
		EXPECT_EQ(3, lis[1]);
		EXPECT_EQ(4, lis[2]);
		EXPECT_EQ(8, lis[3]);
		EXPECT_EQ(9, lis[4]);
	}

	TEST(ArrayTests, FibonacciTest)
	{
		EXPECT_EQ(144, getNthFibonacciNo(13));
		EXPECT_EQ(233, getNthFibonacciNo(14));
		EXPECT_EQ(377, getNthFibonacciNo(15));
	}
}

