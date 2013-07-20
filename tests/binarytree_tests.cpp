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
		ASSERT_FALSE(tree2->isBalanced(height));
		EXPECT_EQ(height, 4);

		tree2->appendNode(new TreeNode<int>(11));
		tree2->appendNode(new TreeNode<int>(12));
		tree2->appendNode(new TreeNode<int>(13));
		tree2->appendNode(new TreeNode<int>(14));
		tree2->appendNode(new TreeNode<int>(15));

		ASSERT_TRUE(tree2->isBalanced(height));

		static const int bstlistarr[] = {7, 4, 9, 2, 6, 8, 10, 1, 3, 5};
		std::vector<int> bstlist(bstlistarr, bstlistarr + sizeof(bstlistarr)/sizeof(bstlistarr[0]));

		BinaryTree<int> * bst = new BinaryTree<int>(&bstlist);
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
	}
}


