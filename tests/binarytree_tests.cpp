/*
 * binarytree_tests.cpp
 *
 *  Created on: Jul 20, 2013
 *      Author: venkat
 */

#include "gtest/gtest.h"
#include "binarytree.h"

namespace {
	class BinaryTreeTests : public ::testing::Test {

	};

	TEST(BinaryTreeTests, TraversalTests) {
		static const int treelistarr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		std::vector<int> treelist(treelistarr, treelistarr + sizeof(treelistarr)/sizeof(treelistarr[0]));

		BinaryTree<int> * tree = new BinaryTree<int>(&treelist);

		std::vector<int> * bfsorder = new vector<int>;
		tree->printNormal(*bfsorder);
		ASSERT_TRUE(*bfsorder == treelist);

		std::vector<int> * inorder = new vector<int>;
		std::vector<int> * inordernorecurse = new vector<int>;
		tree->printInOrder(*inorder);
		tree->printInOrderNoRecurse(*inordernorecurse);
		static const int inorderlistarr[] = {8, 4, 9, 2, 10, 5, 1, 6, 3, 7};
		std::vector<int> inorderlist(inorderlistarr, inorderlistarr + sizeof(inorderlistarr)/sizeof(inorderlistarr[0]));
		ASSERT_TRUE(*inorder == inorderlist);
		ASSERT_TRUE(*inorder == *inordernorecurse);

		std::vector<int> * preorder = new vector<int>;
		std::vector<int> * preordernorecurse = new vector<int>;
		tree->printPreOrder(*preorder);
		tree->printPreOrderNoRecurse(*preordernorecurse);
		static const int preorderlistarr[] = {1, 2, 4, 8, 9, 5, 10, 3, 6, 7};
		std::vector<int> preorderlist(preorderlistarr,
								preorderlistarr + sizeof(preorderlistarr)/sizeof(preorderlistarr[0]));
		ASSERT_TRUE(*preorder == preorderlist);
		ASSERT_TRUE(*preorder == *preordernorecurse);

		std::vector<int> * postorder = new vector<int>;
		std::vector<int> * postordernorecurse = new vector<int>;
		tree->printPostOrder(*postorder);
		tree->printPostOrderNoRecurse(*postordernorecurse);
		static const int postorderlistarr[] = {8, 9, 4, 10, 5, 2, 6, 7, 3, 1};
		std::vector<int> postorderlist(postorderlistarr,
								postorderlistarr + sizeof(postorderlistarr)/sizeof(postorderlistarr[0]));
		ASSERT_TRUE(*postorder == postorderlist);
		ASSERT_TRUE(*postorder == *postordernorecurse);

		BinaryTree<int> * reconstructed_tree = new BinaryTree<int>(&inorderlist, &preorderlist);
		bfsorder = new vector<int>;
		reconstructed_tree->printNormal(*bfsorder);
		ASSERT_TRUE(*bfsorder == treelist);
	}

	TEST(BinaryTreeTests, BasicTest) {
		static const int treelistarr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		std::vector<int> treelist2(treelistarr2, treelistarr2 + sizeof(treelistarr2)/sizeof(treelistarr2[0]));

		BinaryTree<int> * tree2 = new BinaryTree<int>(&treelist2);

		int height;
		ASSERT_FALSE(tree2->isBST());
		ASSERT_TRUE(tree2->isBalanced(height));
		EXPECT_EQ(height, 4);

		tree2->appendNode(new TreeNode<int>(11));
		tree2->appendNode(new TreeNode<int>(12));
		tree2->appendNode(new TreeNode<int>(13));
		tree2->appendNode(new TreeNode<int>(14));
		tree2->appendNode(new TreeNode<int>(15));

		ASSERT_TRUE(tree2->isBalanced(height));

		static const int bstlistarr[] = {7, 4, 9, 2, 6, 8, 10, 1, 3, 5};
		std::vector<int> bstlist(bstlistarr, bstlistarr + sizeof(bstlistarr)/sizeof(bstlistarr[0]));

		BST<int> * bst = new BST<int>(&bstlist, true);
		ASSERT_TRUE(bst->isBST());

		TreeNode<int> * can = tree2->findCommonAncestor(new TreeNode<int>(8), new TreeNode<int>(5));
		ASSERT_TRUE(*can == 2);
		can = tree2->findCommonAncestor(new TreeNode<int>(8), new TreeNode<int>(6));
		ASSERT_TRUE(*can == 1);
		can = tree2->findCommonAncestor(new TreeNode<int>(8), new TreeNode<int>(4));
		ASSERT_TRUE(*can == 4);
		can = tree2->findCommonAncestor(new TreeNode<int>(3), new TreeNode<int>(7));
		ASSERT_TRUE(*can == 3);
		// TODO: The following case should return NULL instead of 3. Fix it.
		can = tree2->findCommonAncestor(new TreeNode<int>(3), new TreeNode<int>(26));
		ASSERT_TRUE(*can == 3);

		can = bst->findCommonAncestor(new TreeNode<int>(3), new TreeNode<int>(6));
		ASSERT_TRUE(*can == 4);
		can = bst->findCommonAncestor(new TreeNode<int>(3), new TreeNode<int>(8));
		ASSERT_TRUE(*can == 7);

		TreeNode<int> * node = bst->find(8);
		ASSERT_TRUE(node != NULL);
		node = bst->find(12);
		ASSERT_TRUE(node == NULL);
		bst->remove(4);
		node = bst->find(4);
		ASSERT_TRUE(node == NULL);
	}

	TEST(BinaryTreeTests, DiameterTest) {
		static const int treelistarr[] = {1, 2, 3, 4, 5, 6, 7, 8};
		std::vector<int> treelist(treelistarr, treelistarr + sizeof(treelistarr)/sizeof(treelistarr[0]));

		std::set<int> setToFind;
		setToFind.insert(4);
		setToFind.insert(6);
		setToFind.insert(7);

		BST<int> * tree = new BST<int>(&treelist);
		bool retVal = tree->allOccurOnSamePathFromRoot(setToFind);
		EXPECT_FALSE(retVal);

		std::set<int> setToFind2;
		setToFind.insert(2);
		setToFind.insert(3);
		setToFind.insert(5);
		delete tree;
		tree = new BST<int>(&treelist);
		retVal = tree->allOccurOnSamePathFromRoot(setToFind2);
		EXPECT_TRUE(retVal);
	}

	TEST(BinaryTreeTests, SetSearchTest) {
		static const int treelistarr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		std::vector<int> treelist(treelistarr, treelistarr + sizeof(treelistarr)/sizeof(treelistarr[0]));

		BinaryTree<int> * tree = new BinaryTree<int>(&treelist);
		EXPECT_EQ(6, tree->getDiameter());
	}

	TEST(BinaryTreeTests, ConvertToListTest) {
		static const int treelistarr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		std::vector<int> treelist(treelistarr, treelistarr + sizeof(treelistarr)/sizeof(treelistarr[0]));

		BST<int> * tree = new BST<int>(&treelist);
		LinkedList<int> * sortedList = tree->convertToSortedList();
		EXPECT_EQ(10, sortedList->size());
		Node<int> * head = sortedList->getHead();
		sortedList->print();
		for(int i = 1; i < 11; i++)
		{
			ASSERT_TRUE(head != NULL);
			EXPECT_EQ(i, head->getValue());
			head = head->getNext();
		}
	}

	TEST(BinaryTreeTests, AdvancedTests) {
		static const int treelistarr3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		std::vector<int> treelist3(treelistarr3, treelistarr3 + sizeof(treelistarr3)/sizeof(treelistarr3[0]));

		BinaryTree<int> * tree3 = new BinaryTree<int>(&treelist3);

		vector<TreeNode<int> * > * path = tree3->find(10);
		EXPECT_EQ(path->at(0)->getValue(), 10);
		EXPECT_EQ(path->at(1)->getValue(), 5);
		EXPECT_EQ(path->at(2)->getValue(), 2);
		EXPECT_EQ(path->at(3)->getValue(), 1);

		static const int subtreelistarr[] = {2, 4, 5, 8, 9, 10};
		std::vector<int> subtreelist(subtreelistarr, subtreelistarr + sizeof(subtreelistarr)/sizeof(subtreelistarr[0]));

		BinaryTree<int> * subtree = new BinaryTree<int>(&subtreelist);

		ASSERT_TRUE(*(tree3->isSubTree(subtree)) == TreeNode<int>(2));

		static const int subtreelistarr2[] = {3, 6, 7};
		std::vector<int> subtreelist2(subtreelistarr2, subtreelistarr2 + sizeof(subtreelistarr2)/sizeof(subtreelistarr2[0]));

		subtree = new BinaryTree<int>(&subtreelist2);

		ASSERT_TRUE(*(tree3->isSubTree(subtree)) == TreeNode<int>(3));

		static const int subtreelistarr3[] = {9};
		std::vector<int> subtreelist3(subtreelistarr3, subtreelistarr3 + sizeof(subtreelistarr3)/sizeof(subtreelistarr3[0]));

		subtree = new BinaryTree<int>(&subtreelist3);

		ASSERT_TRUE(*(tree3->isSubTree(subtree)) == TreeNode<int>(9));

		static const int pathsumarr[] = {1, 4, 2, 1, 6, 3, 5, 3, 2, 0, 0, 7, 4};
		std::vector<int> pathsumlist(pathsumarr, pathsumarr + sizeof(pathsumarr)/sizeof(pathsumarr[0]));

		BinaryTree<int> * pathsumtree = new BinaryTree<int>(&pathsumlist);
		vector<SumPath<int> * > * allpaths = pathsumtree->findAllPathsWithSum(13);
		for(std::vector<SumPath<int> * >::iterator it = allpaths->begin(); it != allpaths->end(); ++it) {
			EXPECT_EQ((*it)->getSum(), 13);
		}
	}
}


