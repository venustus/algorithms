/*
 * stack_tests.cpp
 *
 *  Created on: Jul 17, 2013
 *      Author: venkat
 */

#include <stack>
#include "gtest/gtest.h"
#include "stack_min.h"
#include "stack_sort.h"

namespace {
	class StackTests : public ::testing::Test {

	};

	TEST(StackTests, MinStackTest) {
		StackWithMin<int> * minStack = new StackWithMin<int>;
		minStack->push(5);
		EXPECT_EQ(5, minStack->min());
		minStack->push(4);
		EXPECT_EQ(4, minStack->min());
		minStack->push(10);
		EXPECT_EQ(4, minStack->min());
		minStack->push(20);
		minStack->push(2);
		EXPECT_EQ(2, minStack->min());
		minStack->pop();
		EXPECT_EQ(4, minStack->min());
	}

	TEST(StackTests, StackSortTest) {
		stack<int> * mystack = new stack<int>;
		mystack->push(5);
		mystack->push(4);
		mystack->push(10);
		mystack->push(20);
		mystack->push(2);
		sort(mystack);

		static const int arr[] = {20, 10, 5, 4, 2};
		int i = 0;
		while(!mystack->empty())
		{
			int top = mystack->top();
			mystack->pop();
			EXPECT_EQ(arr[i++], top);
		}
	}
}


