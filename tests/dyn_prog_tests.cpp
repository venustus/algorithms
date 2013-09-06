/*
 * dyn_prog_tests.cpp
 *
 *  Created on: Sep 6, 2013
 *      Author: venkat
 */

#include "gtest/gtest.h"
#include "lcs.h"

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
}


