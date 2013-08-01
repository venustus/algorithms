/*
 * sorting_tests.cpp
 *
 *  Created on: Jul 28, 2013
 *      Author: venkat
 */

#include "gtest/gtest.h"
#include "sorting.h"
#include "countinversions.h"

namespace {
	class SortingTests : public ::testing::Test {

	};

	bool compare(const void * a, const void * b)
	{
		int * aInt = (int *) a;
		int * bInt = (int *) b;
		return *aInt < *bInt;
	}

	TEST(SortingTests, MergeSortTest)
	{
		static const int listarr[] = {5, 9, 3, 10, 3, 7, 4, 8, 1, 2, 6};
		static const int sortedlistarr[] = {1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10};
		std::vector<int> list(listarr, listarr + sizeof(listarr)/sizeof(listarr[0]));
		std::vector<int> sortedListRef(sortedlistarr, sortedlistarr + sizeof(sortedlistarr)/sizeof(sortedlistarr[0]));

		std::vector<int> * sortedList = mergesort(&list, &compare);

		ASSERT_TRUE(sortedListRef == *sortedList);

	}

	TEST(SortingTests, InversionsTest)
	{
		static const int listarr[] = {1, 3, 5, 2, 4, 6};
		std::vector<int> list(listarr, listarr + sizeof(listarr)/sizeof(listarr[0]));

		int numInversions;
		std::vector<int> * sortedList = sortAndCountInversions(&list, numInversions);

		EXPECT_EQ(numInversions, 3);

	}
}


