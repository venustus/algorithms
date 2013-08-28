/*
 * heap_tests.cpp
 *
 *  Created on: Jul 25, 2013
 *      Author: venkat
 */

#include <pthread.h>
#include "gtest/gtest.h"
#include "binaryheap.h"
#include "topkelements.h"

namespace {
	class BinaryHeapTests : public ::testing::Test {
	};

	TEST(BinaryHeapTests, BasicTests) {
		static const int heaplistarr[] = {1, 2, 3, 4, 5, 7};
		std::vector<int> heaplist(heaplistarr, heaplistarr + sizeof(heaplistarr)/sizeof(heaplistarr[0]));

		BinaryHeap<int> * heap = new BinaryHeap<int>(&heaplist, true);
		std::vector<int> * nodeArray = heap->getNodeArray();
		EXPECT_EQ(nodeArray->size(), heaplist.size());
		EXPECT_EQ(nodeArray->at(0), 7);
		EXPECT_EQ(nodeArray->at(1), 5);
		EXPECT_EQ(nodeArray->at(2), 3);
		EXPECT_EQ(nodeArray->at(3), 4);
		EXPECT_EQ(nodeArray->at(4), 2);
		EXPECT_EQ(nodeArray->at(5), 1);
		EXPECT_EQ(heap->findTop(), 7);
		heap->insert(6);
		EXPECT_EQ(nodeArray->size(), 7);
		EXPECT_EQ(nodeArray->at(2), 6);
		EXPECT_EQ(nodeArray->at(6), 3);
		heap->removeTop();
		EXPECT_EQ(heap->findTop(), 6);
		EXPECT_EQ(nodeArray->size(), 6);
		EXPECT_EQ(nodeArray->at(4), 2);
		EXPECT_EQ(nodeArray->at(5), 1);

		heap->enhanceKey(5, 10);
		EXPECT_EQ(heap->findTop(), 11);
	}



	TEST(BinaryHeapTests, TopKElementsTest) {
		std::vector<int> * fiveHundredElements = new std::vector<int>;
		for(int i = 1; i <= 500; i++)
		{
			fiveHundredElements->push_back(i);
		}
		BinaryHeap<int> * topkelements = findTopk(fiveHundredElements, 10);
		for(int i = 491; i <= 500; i++)
		{
			EXPECT_EQ(topkelements->findTop(), i);
			topkelements->removeTop();
		}
	}
}
