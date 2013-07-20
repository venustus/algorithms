/*
 * queue_tests.cpp
 *
 *  Created on: Jul 19, 2013
 *      Author: venkat
 */

#include "gtest/gtest.h"
#include "myqueue.h"

namespace {
	class QueueTests : public ::testing::Test {

	};

	TEST(QueueTests, MyQueueTest) {
		MyQueue<int> * stackBasedQueue = new MyQueue<int>;
		stackBasedQueue->queue(1);
		stackBasedQueue->queue(2);
		stackBasedQueue->queue(3);
		stackBasedQueue->queue(4);
		EXPECT_EQ(stackBasedQueue->peek(), 1);
		stackBasedQueue->dequeue();
		EXPECT_EQ(stackBasedQueue->peek(), 2);
	}
}

