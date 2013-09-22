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
#include "max_overlapping_intervals.h"
#include "max_profit_buy_sell.h"
#include "median.h"
#include "permutations.h"
#include "steps_to_permutation.h"
#include "biggest_interval.h"
#include "lps.h"

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

	TEST(ArrayTests, MaxOverlappingIntervalsTest)
	{
		std::vector<Interval> intervals;
		Interval in1(1, 3), in2(12, 14), in3(2, 4), in4(13, 15), in5(5, 10);
		intervals.push_back(in1);
		intervals.push_back(in2);
		intervals.push_back(in3);
		intervals.push_back(in4);
		intervals.push_back(in5);
		int maxOverlappingIntervals = getMaxOverlappingIntervals(intervals);
		EXPECT_EQ(2, maxOverlappingIntervals);
	}

	TEST(ArrayTests, MedianTest)
	{
		static const int arr1[] = {1, 3, 5, 7, 9};
		static const int arr2[] = {2, 4, 6, 8, 10};
		std::vector<int> arrlist1(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]));
		std::vector<int> arrlist2(arr2, arr2 + sizeof(arr2)/sizeof(arr2[0]));
		EXPECT_EQ(5, getMedianOfSortedArrays(arrlist1, arrlist2));

		static const int arr3[] = {1, 3, 5, 7, 9};
		static const int arr4[] = {2, 12, 14, 16, 20};
		std::vector<int> arrlist3(arr3, arr3 + sizeof(arr3)/sizeof(arr3[0]));
		std::vector<int> arrlist4(arr4, arr4 + sizeof(arr4)/sizeof(arr4[0]));
		EXPECT_EQ(7, getMedianOfSortedArrays(arrlist3, arrlist4));
	}

	TEST(ArrayTests, PermutationsTest)
	{
		static const int arr1[] = {1, 2, 3, 4, 5};
		std::vector<int> arrlist1(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]));
		std::set<std::vector<int> * > * perms = getAllPermutations(&arrlist1);
		EXPECT_EQ(120, perms->size());
	}

	TEST(ArrayTests, StepsToPermutationsTest)
	{
		static const int arr1[] = {1, 4, 3, 0, 2, 5};
		static const int arr2[] = {0, 1, 2, 3, 4, 5};
		std::vector<int> arrlist1(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]));
		std::vector<int> arrlist2(arr2, arr2 + sizeof(arr2)/sizeof(arr2[0]));
		std::vector<SwapStep> * steps = getStepsToPermutation(arrlist1, arrlist2);
		EXPECT_EQ(6, steps->size());
		EXPECT_EQ(1, steps->at(0).srcValue);
		EXPECT_EQ(4, steps->at(1).srcValue);
		EXPECT_EQ(0, steps->at(2).srcValue);
		EXPECT_EQ(3, steps->at(3).srcValue);
		EXPECT_EQ(2, steps->at(4).srcValue);
		EXPECT_EQ(4, steps->at(5).srcValue);
	}

	TEST(ArrayTests, BiggestIntervalTest)
	{
		static const int arr1[] = {10, 1, 3, 4, 5, 2, 7};
		std::vector<int> arrlist1(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]));
		int min = 0, max = 0;
		int range = findBiggestContiguousInterval(arrlist1, min, max);
		EXPECT_EQ(5, range);
		EXPECT_EQ(1, min);
		EXPECT_EQ(5, max);
	}

	TEST(ArrayTests, MaxProfitBuySellTest)
	{
	  static const int arr1[] = {30, 31, 29, 28, 34, 26};
	  std::vector<int> arrlist1(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]));
	  int startIndex = 0, endIndex = 0;
	  int profit = findWhenToBuySellForMaxProfit(arrlist1, startIndex, endIndex);
	  EXPECT_EQ(6, profit);
	  EXPECT_EQ(3, startIndex);
	  EXPECT_EQ(4, endIndex);

	  arrlist1.push_back(27);
	  arrlist1.push_back(35);
	  profit = findWhenToBuySellForMaxProfit(arrlist1, startIndex, endIndex);
	  EXPECT_EQ(9, profit);
	  EXPECT_EQ(5, startIndex);
	  EXPECT_EQ(7, endIndex);
	}

	TEST(ArrayTests, LPSTest)
	{
	  static const int arr1[] = {1, 2, 3, -4, -5};
	  std::vector<int> arrlist1(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]));
	  int startIndex = 0, endIndex = 0;
	  int maxPro = getLargestProductSubsequence(arrlist1, startIndex, endIndex);
	  EXPECT_EQ(120, maxPro);
	  EXPECT_EQ(0, startIndex);
	  EXPECT_EQ(4, endIndex);

	  arrlist1.push_back(-9);
	  arrlist1.push_back(0);
	  arrlist1.push_back(5);
	  arrlist1.push_back(6);
	  maxPro = getLargestProductSubsequence(arrlist1, startIndex, endIndex);
	  EXPECT_EQ(120, maxPro);
	  EXPECT_EQ(0, startIndex);
	  EXPECT_EQ(4, endIndex);
	}
}


