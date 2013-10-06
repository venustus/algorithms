/*
 * dyn_prog_tests.cpp
 *
 *  Created on: Sep 6, 2013
 *      Author: venkat
 */

#include "gtest/gtest.h"
#include "lcs.h"
#include "lss.h"
#include "max_profit_buy_sell.h"
#include "min_coins_for_sum.h"
#include "subsetswithsum.h"
#include "integer_knapsack.h"
#include "lpss.h"

namespace {
  class DynamicProgrammingTests : public ::testing::Test {

  };

  TEST(DynamicProgrammingTests, LCSTest)
  {
	  static const char arr1[] = {'A', 'B', 'C', 'B', 'D', 'A', 'B'};
	  std::vector<char> arrlist1(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]));
	  static const char arr2[] = {'B', 'D', 'C', 'A', 'B', 'A'};
	  std::vector<char> arrlist2(arr2, arr2 + sizeof(arr2)/sizeof(arr2[0]));
	  std::vector<char> * lcs = getLongestCommonSubsequence(arrlist1, arrlist2);
	  EXPECT_EQ(4, lcs->size());
	  EXPECT_EQ('B', lcs->at(0));
	  EXPECT_EQ('D', lcs->at(1));
	  EXPECT_EQ('A', lcs->at(2));
	  EXPECT_EQ('B', lcs->at(3));
	  delete(lcs);
  }

  TEST(DynamicProgrammingTests, EditDistanceTest)
  {
	static const char arr1[] = {'C', 'O', 'M', 'P', 'U', 'T', 'E', 'R'};
	std::vector<char> arrlist1(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]));
	static const char arr2[] = {'C', 'O', 'M', 'M', 'U', 'T', 'E', 'R'};
	std::vector<char> arrlist2(arr2, arr2 + sizeof(arr2)/sizeof(arr2[0]));
	int ed = getEditDistance(arrlist1, arrlist2);
	EXPECT_EQ(1, ed);
  }

  TEST(DynamicProgrammingTests, LSSTest)
  {
	  static const int arr1[] = {1, 2, 3, -4, -5};
	  std::vector<int> arrlist1(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]));
	  int startIndex = 0, endIndex = 0;
	  getLargestSumSubsequence(arrlist1, startIndex, endIndex);
	  EXPECT_EQ(0, startIndex);
	  EXPECT_EQ(2, endIndex);

	  arrlist1.push_back(9);
	  getLargestSumSubsequence(arrlist1, startIndex, endIndex);
	  EXPECT_EQ(5, startIndex);
	  EXPECT_EQ(5, endIndex);

	  static const int arr2[] = {-2, -4, -3, -5, -1};
	  std::vector<int> arrlist2(arr2, arr2 + sizeof(arr2)/sizeof(arr2[0]));
	  getLargestSumSubsequence(arrlist2, startIndex, endIndex);
	  EXPECT_EQ(4, startIndex);
	  EXPECT_EQ(4, endIndex);
  }

  TEST(DynamicProgrammingTests, MinCoinsForSumTest)
  {
	  static const int arr1[] = {5, 5, 5, 5, 5};
	  std::vector<int> arrlist1(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]));
	  int minCoins = findMinNoOfCoinsForSum(10, arrlist1);
	  EXPECT_EQ(2, minCoins);
	  minCoins = findMinNoOfCoinsForSum(11, arrlist1);
	  EXPECT_EQ(0, minCoins);

	  static const int arr2[] = {1, 2, 5, 10, 20, 50, 100, 500, 1000};
	  std::vector<int> arrlist2(arr2, arr2 + sizeof(arr2)/sizeof(arr2[0]));
	  minCoins = findMinNoOfCoinsForSum(78, arrlist2);
	  EXPECT_EQ(5, minCoins);
  }

  	TEST(DynamicProgrammingTests, IntegerKnapsackTest)
    {
  	  static const int values[] = {60, 100, 120};
  	  static const int weights[] = {10, 20, 30};
  	  std::vector<int> values_arr(values, values + sizeof(values)/sizeof(values[0]));
  	  std::vector<int> weights_arr(weights, weights + sizeof(weights)/sizeof(weights[0]));
  	  int maxValueInKnapSack = getMaximumValueForKnapSack(values_arr, weights_arr, 50);
  	  EXPECT_EQ(220, maxValueInKnapSack);
    }

  	TEST(DynamicProgrammingTests, LPSSTest)
  	{
  		std::string in = "BBABCBCAB";
  		std::string result = getLongestPalindromeSubsequence(in);
  		EXPECT_EQ("BACBCAB", result);

  		in = "ABACDXYZZYXDFGABA";
  		result = getLongestPalindromeSubsequence(in);
  		EXPECT_EQ("ABADXYZZYXDABA", result);
  	}

  TEST(DynamicProgrammingTests, SubsetWithSumTest)
  	{
  		static const int arr[] = {5, 10, 4, 6, 7, 8, 2, 1};
  		std::vector<int> arrlist(arr, arr + sizeof(arr)/sizeof(arr[0]));
  		std::set<int> * subsetWithSum = getSubsetsWithSum(&arrlist, 10);
  		ASSERT_TRUE(subsetWithSum != NULL);
  		for(std::set<int>::iterator it = subsetWithSum->begin(); it != subsetWithSum->end(); ++it)
  		{
  			std::cout << (*it) << ", ";
  		}
  		std::cout << std::endl;
  		subsetWithSum = getSubsetsWithSum(&arrlist, 19);
		ASSERT_TRUE(subsetWithSum != NULL);
		for(std::set<int>::iterator it = subsetWithSum->begin(); it != subsetWithSum->end(); ++it)
		{
			std::cout << (*it) << ", ";
		}
		std::cout << std::endl;
		subsetWithSum = getSubsetsWithSum(&arrlist, 15);
		ASSERT_TRUE(subsetWithSum != NULL);
		for(std::set<int>::iterator it = subsetWithSum->begin(); it != subsetWithSum->end(); ++it)
		{
			std::cout << (*it) << ", ";
		}
		std::cout << std::endl;
		subsetWithSum = getSubsetsWithSum(&arrlist, 45);
		ASSERT_TRUE(subsetWithSum == NULL);
  	}

}


