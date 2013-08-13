/*
 * sorting_tests.cpp
 *
 *  Created on: Jul 28, 2013
 *      Author: venkat
 */

#include <iostream>
#include <fstream>
#include <string>
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

	TEST(SortingTests, QuickSortTest)
	{
		static const int listarr[] = {5, 9, 3, 10, 3, 7, 4, 8, 1, 2, 6};
		static const int sortedlistarr[] = {1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10};
		std::vector<int> list(listarr, listarr + sizeof(listarr)/sizeof(listarr[0]));
		std::vector<int> sortedListRef(sortedlistarr, sortedlistarr + sizeof(sortedlistarr)/sizeof(sortedlistarr[0]));

		quicksort(&list);

		ASSERT_TRUE(sortedListRef == list);

		std::vector<int> * biglist = new std::vector<int>;
		std::ifstream integerArray("/Users/venkat/Documents/Projects/cplusplus/Algorithms/cpluspluspractice/src/QuickSort.txt");
		if(integerArray.is_open())
		{
			while(integerArray.good())
			{
				std::string line;
				getline(integerArray, line);
				int value;
				std::istringstream buffer(line);
				buffer >> value;
				biglist->push_back(value);
			}
			integerArray.close();
		}
		std::cout << "Size of the big list is: " << biglist->size() << std::endl;

		int numberOfComparisons = 0;
		std::vector<int> * biglistcopy = new std::vector<int>(*biglist);
		naivequicksort(biglistcopy, 0, biglist->size() - 1, numberOfComparisons);
		for(std::vector<int>::const_iterator it = biglistcopy->begin(); it != biglistcopy->end() - 1; ++it)
		{
			ASSERT_TRUE(*it < *(it + 1));
		}
		std::cout << "Number of comparisons for naivequicksort: " << numberOfComparisons << std::endl;

		biglistcopy = new std::vector<int>(*biglist);
		numberOfComparisons = 0;
		naivequicksort2(biglistcopy, 0, biglist->size() - 1, numberOfComparisons);
		std::cout << "Number of comparisons for naivequicksort 2: " << numberOfComparisons << std::endl;

		biglistcopy = new std::vector<int>(*biglist);
		numberOfComparisons = 0;
		medianof3quicksort(biglistcopy, 0, biglist->size() - 1, numberOfComparisons);
		std::cout << "Number of comparisons for median of 3 quicksort: " << numberOfComparisons << std::endl;
	}

	TEST(SortingTests, InversionsTest)
	{
		static const long long int listarr[] = {1, 3, 5, 2, 4, 6};
		std::vector<long long int> list(listarr, listarr + sizeof(listarr)/sizeof(listarr[0]));

		long long int numInversions;
		std::vector<long long int> * sortedList = sortAndCountInversions(&list, numInversions);

		EXPECT_EQ(numInversions, 3);

		static const long long int listarr2[] = {4, 1, 3, 10, 76, 11, 73, 95, 78, 26, 37, 93, 5, 47, 56};
		std::vector<long long int> list2(listarr2, listarr2 + sizeof(listarr2)/sizeof(listarr2[0]));

		numInversions = 0;
		sortedList = sortAndCountInversions(&list2, numInversions);

		EXPECT_EQ(numInversions, 33);

		std::vector<long long int> * biglist = new std::vector<long long int>;
		std::ifstream integerArray("/Users/venkat/Documents/Projects/cplusplus/Algorithms/cpluspluspractice/src/IntegerArray.txt");
		if(integerArray.is_open())
		{
			while(integerArray.good())
			{
				std::string line;
				getline(integerArray, line);
				long long int value;
				std::istringstream buffer(line);
				buffer >> value;
				biglist->push_back(value);
			}
			integerArray.close();
		}
		std::cout << "Size of the big list is: " << biglist->size() << std::endl;
		numInversions = 0;
		sortedList = sortAndCountInversions(biglist, numInversions);
		std::cout << "Number of inversions in an array of 100000 is: " << numInversions << std::endl;
		EXPECT_EQ(numInversions, 2407905288);
	}
}


