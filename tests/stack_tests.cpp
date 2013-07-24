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
#include "setofstacks.h"
#include "threestacks.h"
#include "tower_of_hanoi.h"
#include "mystack.h"
#include "histogram_rectangle.h"

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

	TEST(StackTests, SetOfStacksTest) {
		SetOfStacks<int> * stackSet = new SetOfStacks<int>(2);
		stackSet->push(1);
		stackSet->push(2);
		stackSet->push(3);
		EXPECT_EQ(stackSet->top(), 3);
		stackSet->push(4);
		EXPECT_EQ(stackSet->top(), 4);
		stackSet->push(5);
		stackSet->pop();
		EXPECT_EQ(stackSet->top(), 4);
	}

	TEST(StackTests, ThreeStacksTest) {
		ThreeStack<int> *threeStacks = new ThreeStack<int>;
		for(int i = 1; i <= 16; i++)
		{
			threeStacks->push(((i-1)%3), i);
		}
		EXPECT_EQ(threeStacks->top(0), 16);
		EXPECT_EQ(threeStacks->top(1), 14);
		EXPECT_EQ(threeStacks->top(2), 15);
	}

	TEST(StackTests, TowerOfHanoiTest) {
		stack<int> * initialStack = new stack<int>;
		initialStack->push(4);
		initialStack->push(3);
		initialStack->push(2);
		initialStack->push(1);
		TowerOfHanoi<int> * hanoi = new TowerOfHanoi<int>(*initialStack, 2);
		stack<int> * targetTower = hanoi->solve();
		EXPECT_EQ(targetTower->top(), 1);
		targetTower->pop();
		EXPECT_EQ(targetTower->top(), 2);
		targetTower->pop();
		EXPECT_EQ(targetTower->top(), 3);
		targetTower->pop();
		EXPECT_EQ(targetTower->top(), 4);
	}

	TEST(StackTests, MyStackTest)
	{
		MyStack<int> * mystack = new MyStack<int>;
		mystack->push(1);
		mystack->push(2);
		mystack->push(3);
		mystack->push(4);
		EXPECT_EQ(mystack->top(), 4);
		mystack->pop();
		EXPECT_EQ(mystack->top(), 3);
		mystack->pop();
		EXPECT_EQ(mystack->top(), 2);
		mystack->pop();
		EXPECT_EQ(mystack->top(), 1);
		mystack->pop();
		ASSERT_TRUE(mystack->empty());
	}

	TEST(StackTests, HistogramAreaTest)
	{
		static const int histarr[] = {5, 6, 8, 7, 8, 4};
		std::vector<int> histlist(histarr, histarr + sizeof(histarr)/sizeof(histarr[0]));
		Histogram * hist = new Histogram(&histlist);
		int maxarea;
		std::pair<int, int> maxpair = hist->computeMaxAreaRectangle(maxarea);
		EXPECT_EQ(maxarea, 25);
		EXPECT_EQ(maxpair.first, 0);
		EXPECT_EQ(maxpair.second, 4);
	}
}


