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

  TEST(DynamicProgrammingTests, LPSTest)
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

  TEST(DynamicProgrammingTests, MinCoinsForSumTest)
  {
	  static const int arr1[] = {5, 5, 5, 5, 5};
	  std::vector<int> arrlist1(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]));
	  int minCoins = findMinNoOfCoinsForSum(10, arrlist1);
	  EXPECT_EQ(2, minCoins);
	  minCoins = findMinNoOfCoinsForSum(11, arrlist1);
	  EXPECT_EQ(-1, minCoins);
  }

  TEST(DynamicProgrammingTests, MaxProfitBuySellTest)
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
}


