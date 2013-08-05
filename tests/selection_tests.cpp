/*
 * selection_tests.cpp
 *
 *  Created on: Aug 3, 2013
 *      Author: venkat
 */

#include "gtest/gtest.h"
#include "sorting.h"
#include "selection.h"

namespace {
	class SelectionTests : public ::testing::Test {

	};

	TEST(SelectionTests, RandomSelectTest)
	{
		static const int listarr[] = {5, 9, 3, 10, 3, 7, 4, 8, 1, 2, 6};
		static const int sortedlistarr[] = {1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10};
		const std::vector<int> list(listarr, listarr + sizeof(listarr)/sizeof(listarr[0]));
		std::vector<int> sortedListRef(sortedlistarr, sortedlistarr + sizeof(sortedlistarr)/sizeof(sortedlistarr[0]));

		EXPECT_EQ(randomSelect(new std::vector<int>(list), 1), 1);
		EXPECT_EQ(randomSelect(new std::vector<int>(list), 2), 2);
		EXPECT_EQ(randomSelect(new std::vector<int>(list), 3), 3);
		EXPECT_EQ(randomSelect(new std::vector<int>(list), 4), 3);
		EXPECT_EQ(randomSelect(new std::vector<int>(list), 5), 4);
		EXPECT_EQ(randomSelect(new std::vector<int>(list), 6), 5);
		EXPECT_EQ(randomSelect(new std::vector<int>(list), 7), 6);
		EXPECT_EQ(randomSelect(new std::vector<int>(list), 8), 7);
		EXPECT_EQ(randomSelect(new std::vector<int>(list), 9), 8);
		EXPECT_EQ(randomSelect(new std::vector<int>(list), 10), 9);
		EXPECT_EQ(randomSelect(new std::vector<int>(list), 11), 10);
	}
}
