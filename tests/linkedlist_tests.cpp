/*
 * linkedlist_tests.cpp
 *
 *  Created on: Jul 16, 2013
 *      Author: venkat
 */

#include "gtest/gtest.h"
#include "linked_lists.h"
#include "ll_sum.h"

namespace {
	class LinkedListTests : public ::testing::Test {

	};

	TEST(LinkedListTests, BasicTest) {
		  // create an empty list
		  LinkedList<int> * ll = new LinkedList<int>;
		  ll->append(new Node<int>(1));
		  // list is: [1]
		  EXPECT_EQ(1, ll->getHead()->getValue());
		  EXPECT_EQ(1, ll->getTail()->getValue());
		  Node<int> * secondNode = new Node<int>(2);
		  ll->append(secondNode);
		  // list is [1, 2]
		  EXPECT_EQ(1, ll->getHead()->getValue());
		  EXPECT_EQ(2, ll->getTail()->getValue());

		  Node<int> * thirdNode = new Node<int>(3);
		  ll->append(thirdNode);
		  // list is [1, 2, 3]
		  EXPECT_EQ(3, ll->getTail()->getValue());

		  ll->appendHead(new Node<int>(4));
		  // list is [4, 1, 2, 3]
		  EXPECT_EQ(4, ll->getHead()->getValue());

		  ll->append(new Node<int>(6));
		  // list is [4, 1, 2, 3, 6]
		  EXPECT_EQ(6, ll->getTail()->getValue());

		  Node<int> * fifthNode = new Node<int>(5);
		  ll->insert(fifthNode, secondNode);
		  // list is [4, 1, 2, 5, 3, 6]
		  EXPECT_EQ(5, (*ll)[3].getValue());

		  ll->deleteNode(fifthNode);
		  // list is [4, 1, 2, 3, 6]
		  EXPECT_EQ(3, (*ll)[3].getValue());

		  ll->deleteNodeSingle(thirdNode);
		  // list is [4, 1, 2, 6]
		  EXPECT_EQ(6, (*ll)[3].getValue());

		  EXPECT_EQ(2, ll->kthElementFromRear(2));
	}

	TEST(LinkedListTests, AdvancedTests)
	{
		  // circular list
		  static const int arr[] = {16,2,77,29, 24, 19, 2};
		  std::vector<int> mylist(arr, arr + sizeof(arr)/sizeof(arr[0]));
		  LinkedList<int> * ll2 = new LinkedList<int>(mylist, true);
		  // list is [16, 2, 77, 29, 24, 19, 2]

		  EXPECT_EQ(2, (*ll2)[6].getValue());
		  Node<int> * cycleStartNode = ll2->cycleStart();
		  EXPECT_EQ(2, cycleStartNode->getValue());

		  static const int arr2[] = {16,2,77,29, 24, 2, 24, 19, 78, 12};
		  std::vector<int> mylist2(arr2, arr2 + sizeof(arr2)/sizeof(arr2[0]));
		  LinkedList<int> * ll3 = new LinkedList<int>(mylist2);
		  ll3->deleteDuplicates();

		  static const int arr2_1[] = {16,2,77,29, 24, 19, 78, 12};
		  std::vector<int> mylist2_1(arr2_1, arr2_1 + sizeof(arr2_1)/sizeof(arr2_1[0]));
		  LinkedList<int> * ll3_1 = new LinkedList<int>(mylist2_1);

		  ASSERT_TRUE(*ll3_1 == *ll3);

		  ll3->rearrange(30);
		  static const int arr2_2[] = {16, 2, 29, 24, 19, 12, 77, 78};
		  std::vector<int> mylist2_2(arr2_2, arr2_2 + sizeof(arr2_2)/sizeof(arr2_2[0]));
		  LinkedList<int> * ll3_2 = new LinkedList<int>(mylist2_2);
		  // list is now [16, 2, 29, 24, 19, 12, 77, 78]
		  ASSERT_TRUE(*ll3_2 == *ll3);

		  ll3->rearrange(29);
		  // list is now [16, 2, 24, 19, 12, 29, 77, 78]
		  static const int arr2_3[] = {16, 2, 24, 19, 12, 29, 77, 78};
		  std::vector<int> mylist2_3(arr2_3, arr2_3 + sizeof(arr2_3)/sizeof(arr2_3[0]));
		  LinkedList<int> * ll3_3 = new LinkedList<int>(mylist2_3);
		  ASSERT_TRUE(*ll3_3 == *ll3);

		  static const int arr3[] = {1, 2, 3, 4, 3, 2, 1};
		  std::vector<int> mylist3(arr3, arr3 + sizeof(arr3)/sizeof(arr3[0]));
		  LinkedList<int> * ll4 = new LinkedList<int>(mylist3);
		  EXPECT_EQ(true, ll4->isPalindrome());

		  static const int arr4[] = {1, 2, 3, 3, 2, 1};
		  std::vector<int> mylist4(arr4, arr4 + sizeof(arr4)/sizeof(arr4[0]));
		  LinkedList<int> * ll5 = new LinkedList<int>(mylist4);
		  EXPECT_EQ(true, ll5->isPalindrome());

		  EXPECT_EQ(false, ll3->isPalindrome());
	}

	TEST(LinkedListTests, LLSumTests) {
		 static const int arr1[] = {6, 3, 4};
		 std::vector<int> mylist1(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]));
		 LinkedList<int> * ll1 = new LinkedList<int>(mylist1, true);

		 static const int arr2[] = {7, 1, 2};
		 std::vector<int> mylist2(arr2, arr2 + sizeof(arr2)/sizeof(arr2[0]));
		 LinkedList<int> * ll2 = new LinkedList<int>(mylist2, true);

		 LinkedList<int> * ll_sum = sum(ll1, ll2);

		 static const int arr_sum[] = {1, 3, 4, 6};
		 std::vector<int> mylist_sum(arr_sum, arr_sum + sizeof(arr_sum)/sizeof(arr_sum[0]));
		 LinkedList<int> * ll_sum_comp = new LinkedList<int>(mylist_sum, true);

		 ASSERT_TRUE(*ll_sum_comp == *ll_sum);

		 static const int arr_sum_reverse[] = {3, 5, 6};
		 std::vector<int> mylist_sum_reverse(arr_sum_reverse, arr_sum_reverse + sizeof(arr_sum_reverse)/sizeof(arr_sum_reverse[0]));
		 ll_sum_comp = new LinkedList<int>(mylist_sum_reverse, true);

		 ll_sum = sumReverse(ll1, ll2);

		 ASSERT_TRUE(*ll_sum_comp == *ll_sum);
	}
}



