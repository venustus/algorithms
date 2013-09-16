/*
 * binarytree.h
 *
 *  Created on: Jun 9, 2013
 *      Author: venkat
 */

#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <cmath>
#include <set>
#include "linked_lists.h"

using namespace std;

#ifndef BINARYTREE_H_
#define BINARYTREE_H_

template<class T> class TreeNode;
template<class T> std::ostream& operator<<(std::ostream&, TreeNode<T>&);

template<typename T>
struct FindValFromPointer
{
	FindValFromPointer(T i) : n(i) { }
	bool operator()(T * p) { return n == *p; }
	private:
		T n;
};

/**
 * Represents a tree node with left, right and child pointers.
 * An auxillary visited variable is also available for
 * all typical algorithms with trees.
 */
template<class T>
class TreeNode
{
	T val;
	TreeNode<T> * left;
	TreeNode<T> * right;
	TreeNode<T> * parent;
	bool visited;

public:
	TreeNode(T val);
	TreeNode();
	~TreeNode();

	T getValue();
	void setValue(T val);
	TreeNode<T> * getLeft();
	TreeNode<T> * getRight();
	TreeNode<T> * getParent();
	bool isVisited();

	void setLeft(TreeNode<T> * leftChild);
	void setRight(TreeNode<T> * rightChild);
	void setParent(TreeNode<T> * parent);
	void setVisited();
	void resetVisited();

	template<typename U>
	friend std::ostream& operator<<(std::ostream& out, TreeNode<U> &ref)
	{
		out << ref.getValue();
		return out;
	}

	bool operator==(const TreeNode<T> &other);
	bool operator!=(const TreeNode<T> &other);
	bool operator<(const TreeNode<T> &other);
	bool operator>(const TreeNode<T> &other);
};

template<class T>
class SumPath {
	vector<TreeNode<T> * > * elements;
	T sum;

public:
	SumPath();
	void appendToPath(TreeNode<T> * node);
	void appendToPath(SumPath<T> * other);
	T getSum();
	vector<TreeNode<T> * > * getElements();
	void print();
};

/**
 * Represents a binary tree data structure.
 * Implements several algorithms related to binary trees.
 * This internally stores two representations of the binary tree:
 * One is normal tree representation with nodes and links between nodes
 * and the other is an array of nodes in breadth-first-search order.
 */
template<class T>
class BinaryTree
{
	int getParentIndex(int childIndex);
	int getLeftChildIndex(int parentIndex);
	int getRightChildIndex(int parentIndex);
	void traverseInOrder(TreeNode<T> * root, vector<T> &inorderList);
	void traversePreOrder(TreeNode<T> * root, vector<T> &preorderList);
	void traversePostOrder(TreeNode<T> * root, vector<T> &postorderList);
	TreeNode<T> * reconstructTree(vector<T> * inorderList,
								  vector<T> * preorderList);
	int getHeight(TreeNode<T> * root, bool &isBalanced);
	bool dfsBSTCheck(TreeNode<T> * node);
	TreeNode<T> * findFirstCommonAncestor(TreeNode<T> * p, TreeNode<T> * q, TreeNode<T> * root);
	TreeNode<T> * isSubTree(TreeNode<T> * source, TreeNode<T> * pattern);
	bool matchTree(TreeNode<T> * source, TreeNode<T> * pattern);
	vector<SumPath<T> * > * findAllPaths(TreeNode<T> * root, vector<SumPath<T> * > * results, T sum);
	bool findRecurse(TreeNode<T> * node, T val, stack<TreeNode<T> * > *);
	int getDiameter(TreeNode<T> * root, int& height);
protected:
	vector<TreeNode<T> * > * nodeArray;
	TreeNode<T> * root;
public:
	/**
	 * Constructs an empty binary tree.
	 */
	BinaryTree();

	/**
	 * Destroys this binary tree.
	 */
	~BinaryTree();

	/**
	 * Constructs a binary tree with only one node which becomes the root node.
	 */
	BinaryTree(TreeNode<T> * root);

	/**
	 * Constructs a binary tree with nodes created from a list of values.
	 * The nodes are arranged in the tree in breadth-first order.
	 */
	BinaryTree(vector<T> * nodeList);

	/**
	 * Reconstructs a binary tree from two lists - inorderList and preorderList
	 * where these lists are the list of nodes converted from inorder and
	 * preorder traversals of the same tree.
	 */
	BinaryTree(vector<T> * inorderList, vector<T> * preorderList);

	/**
	 * Traverses the tree inorder and then prints the nodes. It also
	 * fills the vector with the nodes in same order.
	 */
	void printInOrder(vector<T> &inorderList);

	/**
	 * Traverses the tree inorder without using recursion and then prints
	 * the nodes. It also fills the vector with the nodes in same order.
	 */
	void printInOrderNoRecurse(vector<T> &inorderList);

	/**
	 * Traverses the tree in pre-order by using recursion and prints
	 * the nodes (fills the vector 'preorderlist') in same order.
	 */
	void printPreOrder(vector<T> &preorderList);

	/**
	 * Traverses the tree in pre-order but without using recursion
	 * and fills the vector 'preorderList' with the elements in same
	 * order.
	 */
	void printPreOrderNoRecurse(vector<T> &preorderList);

	/**
	 * Traverse the tree in post-order with recursion.
	 */
	void printPostOrder(vector<T> &postorderList);

	/**
	 * Traverses the tree in post-order without recursion.
	 */
	void printPostOrderNoRecurse(vector<T> &postorderList);

	/**
	 * Prints the tree in breadth first order.
	 */
	void printNormal(vector<T> &normalorderList);

	/**
	 * Appends a new node to the tree at the end of the
	 * tree.
	 */
	void appendNode(TreeNode<T> * newNode);

	/**
	 * Finds a value in a binary tree and returns the path from root.
	 * Returns NULL if val is not found.
	 */
	vector<TreeNode<T> * > * find(T val);

	/**
	 * Returns true if the binary tree is balanced.
	 * The height of the binary tree is put in the height variable.
	 */
	bool isBalanced(int &height);

	/**
	 * Gets different levels in the binary tree as a vector of
	 * linked lists. Each linked list is a list of siblings at that level.
	 * That is the list at index 0 is root, list at index 1 contains two
	 * nodes at level 2.
	 */
	vector<LinkedList<TreeNode<T> * > * > * getLevels();

	/**
	 * Returns true if this binary tree is a binary search tree.
	 */
	bool isBST();

	/**
	 * Finds and returns first common ancestore of given nodes p and q.
	 * Time complexity: O(n)
	 * Space complexity: O(1)
	 */
	TreeNode<T> * findCommonAncestor(TreeNode<T> * p, TreeNode<T> * q);

	/**
	 * Checks if the 'other' binary tree is a sub-tree of the current
	 * binary tree and returns a pointer to the root of the sub-tree
	 * if it is. Returns NULL otherwise.
	 * Time complexity: O(k + nm) - where k is the number of matches of root node of other
	 *                  in the current tree and n is the number of nodes in the current tree
	 *                  and m is the number of nodes in the other tree.
	 *                  NOTE: This is not a tight bound.
	 * Space complexity: O(log(n) + log(m))
	 */
	TreeNode<T> * isSubTree(BinaryTree<T> * other);

	/**
	 * Returns the root of the current tree.
	 */
	TreeNode<T> * getRoot();

	/**
	 * Returns all tree nodes as an array in breadth first order.
	 */
	vector<TreeNode<T> * > * getNodeArray();

	/**
	 * Returns all possible paths in the binary tree whose node values sum up to a given sum.
	 * Paths can bend around roots.
	 * Time complexity: O(n)
	 */
	vector<SumPath<T> * > * findAllPathsWithSum(T sum);

	/**
	 * Returns diameter of a tree.
	 * Diameter of a tree is the longest path between any two nodes of the tree.
	 * Time complexity: O(n)
	 */
	int getDiameter();
};

template<class T>
TreeNode<T>::TreeNode(T value)
{
	val = value;
	left = NULL;
	right = NULL;
	parent = NULL;
	visited = false;
}

template<class T>
TreeNode<T>::~TreeNode()
{
	// nothing to delete as the values
	// are not initialized within the constructor
	// of tree node.
}

template<class T>
TreeNode<T>::TreeNode()
{
	val = NULL;
	left = right = parent = NULL;
	visited = false;
}

template<class T>
bool TreeNode<T>::operator==(const TreeNode<T> &other)
{
	return val == other.val;
}

template<class T>
bool TreeNode<T>::operator!=(const TreeNode<T> &other)
{
	return !(val == other.val);
}

template<class T>
bool TreeNode<T>::operator<(const TreeNode<T> &other)
{
	return val < other.val;
}

template<class T>
bool TreeNode<T>::operator>(const TreeNode<T> &other)
{
	return val > other.val;
}

template<class T>
T TreeNode<T>::getValue()
{
	return val;
}

template<class T>
void TreeNode<T>::setValue(T value)
{
	val = value;
}

template<class T>
TreeNode<T> * TreeNode<T>::getLeft()
{
	return left;
}

template<class T>
TreeNode<T> * TreeNode<T>::getRight()
{
	return right;
}

template<class T>
TreeNode<T> * TreeNode<T>::getParent()
{
	return parent;
}

template<class T>
bool TreeNode<T>::isVisited()
{
	return visited;
}

template<class T>
void TreeNode<T>::setLeft(TreeNode<T> * leftChild)
{
	left = leftChild;
}

template<class T>
void TreeNode<T>::setRight(TreeNode<T> * rightChild)
{
	right = rightChild;
}

template<class T>
void TreeNode<T>::setParent(TreeNode<T> * parentNode)
{
	parent = parentNode;
}

template<class T>
void TreeNode<T>::setVisited()
{
	visited = true;
}

template<class T>
void TreeNode<T>::resetVisited()
{
	visited = false;
}

template<class T>
BinaryTree<T>::BinaryTree()
{
	root = NULL;
	nodeArray = new vector<TreeNode<T> * >;
}

template<class T>
BinaryTree<T>::BinaryTree(TreeNode<T> * rootNode)
{
	root = rootNode;
	nodeArray = new vector<TreeNode<T> * >;
	nodeArray->push_back(root);
}

/**
 * Constructs a full binary tree from a vector.
 * This behaves just like a heap, but no heap property
 * is followed.
 *
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
template<class T>
BinaryTree<T>::BinaryTree(vector<T> * allNodes)
{
	nodeArray = new vector<TreeNode<T> * >;
	for(typename vector<T>::iterator it = allNodes->begin(); it != allNodes->end(); ++it)
	{
		TreeNode<T> * newNode = new TreeNode<T>(*it);
		appendNode(newNode);
	}
	if(allNodes->size() == 0)
	{
		root = NULL;
	}
}

/**
 * Reconstructs a binary tree from the inorder and preorder
 * lists of the same tree. This reconstructs the tree exactly as it
 * was. Only inorder or only preorder listing is not enough to
 * reconstruct the tree exactly as it was, but both together
 * are enough to do so.
 *
 * Time complexity: O(n^2)
 * Space complexity: O(n)
 */
template<class T>
BinaryTree<T>::BinaryTree(vector<T> * inorderList, vector<T> * preorderList)
{
	root = reconstructTree(inorderList, preorderList);
}


template<class T>
BinaryTree<T>::~BinaryTree()
{
	delete nodeArray;
}

template<class T>
int BinaryTree<T>::getParentIndex(int childIndex)
{
	return (childIndex - 1) / 2;
}

template<class T>
int BinaryTree<T>::getLeftChildIndex(int parentIndex)
{
	return (parentIndex * 2) + 1;
}

template<class T>
int BinaryTree<T>::getRightChildIndex(int parentIndex)
{
	return (parentIndex * 2) + 2;
}

/**
 * Appends new 'node' to the tree at the end of the tree
 * assuming the tree is a full binary tree.
 * If you have used the constructor which constructs the
 * tree from an array, then you can use this to append
 * more nodes.
 *
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
template<class T>
void BinaryTree<T>::appendNode(TreeNode<T> * node)
{
	int nextIndex = nodeArray->size();
	if(nextIndex == 0)
	{
		root = node;
		nodeArray->push_back(node);
		return;
	}
	TreeNode<T> * parent = nodeArray->at(getParentIndex(nextIndex));
	if(nextIndex % 2 != 0)
	{
		parent->setLeft(node);
	}
	else
	{
		parent->setRight(node);
	}
	node->setParent(parent);
	nodeArray->push_back(node);
}


template<class T>
TreeNode<T> * BinaryTree<T>::getRoot()
{
	return root;
}

template<class T>
vector<TreeNode<T> * > * BinaryTree<T>::getNodeArray()
{
	return nodeArray;
}

/**
 * Algorithm:
 * 1) The first element in the preorder list is the root.
 * 2) To find the left child, we search for the root in the inorder list
 *    and then find the index and size of the left sub tree.
 * 3) Recursively call 'reconstructTree' with a sub-list which represents the
 *    left sub-tree and get the root.
 * 4) Recursively call 'reconstructTree' with a sub-list which represents the
 *    right sub-tree and get the root.
 * 5) Assign the left and right children and return the root.
 *
 * Time complexity: O(n^2) - we are accessing each element in both arrays exactly once
 * 							 but we are searching for the element in inorder list.
 * Space complexity: O(n)
 */
template<class T>
TreeNode<T> * BinaryTree<T>::reconstructTree(vector<T> * inorderList, vector<T> * preorderList)
{
	typename vector<T>::iterator itr  = std::find(inorderList->begin(),
			                                 inorderList->end(),
			                                 preorderList->at(0));
	TreeNode<T> * currentRoot = new TreeNode<T>(*itr);
	if(itr != inorderList->begin())
	{
		vector<T> * leftSubTree = new vector<T>(inorderList->begin(), itr);
		vector<T> * leftSubTreePre = new vector<T>(preorderList->begin() + 1, preorderList->begin() + 1 + leftSubTree->size());
		TreeNode<T> * leftSubTreeRoot = reconstructTree(leftSubTree, leftSubTreePre);
		currentRoot->setLeft(leftSubTreeRoot);
		leftSubTreeRoot->setParent(currentRoot);
	}
	if(itr + 1 != inorderList->end())
	{
		vector<T> * rightSubTree = new vector<T>(itr + 1, inorderList->end());
		vector<T> * rightSubTreePre = new vector<T>(preorderList->begin() + inorderList->size() - rightSubTree->size(),
													preorderList->begin() + inorderList->size());
		TreeNode<T> * rightSubTreeRoot = reconstructTree(rightSubTree, rightSubTreePre);
		currentRoot->setRight(rightSubTreeRoot);
		rightSubTreeRoot->setParent(currentRoot);
	}
	return currentRoot;
}

template<class T>
void BinaryTree<T>::traverseInOrder(TreeNode<T> * root, vector<T> &inorderList)
{
	if(!root)
	{
		return;
	}
	traverseInOrder(root->getLeft(), inorderList);
	cout << root->getValue() << " ";
	inorderList.push_back(root->getValue());
	traverseInOrder(root->getRight(), inorderList);
}

template<class T>
void BinaryTree<T>::traversePostOrder(TreeNode<T> * root, vector<T> &postorderList)
{
	if(!root)
	{
		return;
	}
	traversePostOrder(root->getLeft(), postorderList);
	traversePostOrder(root->getRight(), postorderList);
	cout << root->getValue() << " ";
	postorderList.push_back(root->getValue());
}

template<class T>
void BinaryTree<T>::printInOrder(vector<T> &inorderList)
{
	traverseInOrder(root, inorderList);
	cout << endl;
}

template<class T>
void BinaryTree<T>::printPreOrder(vector<T> &preorderList)
{
	traversePreOrder(root, preorderList);
	cout << endl;
}

template<class T>
void BinaryTree<T>::printPostOrder(vector<T> &postorderList)
{
	traversePostOrder(root, postorderList);
	cout << endl;
}

template<class T>
void BinaryTree<T>::printInOrderNoRecurse(vector<T> &inorderList)
{
	stack<TreeNode<T> * > * nodeStack = new stack<TreeNode<T> * >;
	nodeStack->push(root);
	while(!nodeStack->empty())
	{
		TreeNode<T> * topNode = nodeStack->top();
		nodeStack->pop();
		if(topNode->isVisited())
		{
			cout << topNode->getValue() << " ";
			topNode->resetVisited();
			inorderList.push_back(topNode->getValue());
		}
		else
		{
			if(topNode->getRight())
			{
				nodeStack->push(topNode->getRight());
			}
			nodeStack->push(topNode);
			if(topNode->getLeft())
			{
				nodeStack->push(topNode->getLeft());
			}
			topNode->setVisited();
		}
	}
	cout << endl;
}

template<class T>
void BinaryTree<T>::traversePreOrder(TreeNode<T> * n, vector<T> &preorderList)
{
	if(!n)
	{
		return;
	}
	cout << n->getValue() << " ";
	preorderList.push_back(n->getValue());
	traversePreOrder(n->getLeft(), preorderList);
	traversePreOrder(n->getRight(), preorderList);
}

template<class T>
void BinaryTree<T>::printPreOrderNoRecurse(vector<T> &preorderList)
{
	stack<TreeNode<T> *> * nodeStack = new stack<TreeNode<T> *>;
	nodeStack->push(root);
	while(!nodeStack->empty())
	{
		TreeNode<T> * top = nodeStack->top();
		nodeStack->pop();
		if(!top->isVisited())
		{
			if(top->getRight())
			{
				nodeStack->push(top->getRight());
			}
			if(top->getLeft())
			{
				nodeStack->push(top->getLeft());
			}
			top->setVisited();
			nodeStack->push(top);
		}
		else
		{
			cout << top->getValue() << " ";
			top->resetVisited();
			preorderList.push_back(top->getValue());
		}
	}
	cout << endl;
}

template<class T>
void BinaryTree<T>::printPostOrderNoRecurse(vector<T> &postorderList)
{
	stack<TreeNode<T> *> * nodeStack = new stack<TreeNode<T> *>;
	nodeStack->push(root);
	while(!nodeStack->empty())
	{
		TreeNode<T> * top = nodeStack->top();
		nodeStack->pop();
		if(!top->isVisited())
		{
			nodeStack->push(top);
			if(top->getRight())
			{
				nodeStack->push(top->getRight());
			}
			if(top->getLeft())
			{
				nodeStack->push(top->getLeft());
			}
			top->setVisited();
		}
		else
		{
			cout << top->getValue() << " ";
			top->resetVisited();
			postorderList.push_back(top->getValue());
		}
	}
}

template<class T>
void BinaryTree<T>::printNormal(vector<T> &normalorderList)
{
	queue<TreeNode<T> * > * bfsqueue = new queue<TreeNode<T> * >;
	bfsqueue->push(root);
	while(!bfsqueue->empty())
	{
		TreeNode<T> * front = bfsqueue->front();
		bfsqueue->pop();
		cout << front->getValue() << " ";
		normalorderList.push_back(front->getValue());
		if(front->getLeft())
		{
			bfsqueue->push(front->getLeft());
		}
		if(front->getRight())
		{
			bfsqueue->push(front->getRight());
		}
	}
	cout << endl;
}

/**
 * Returns an array of lists, where each list represents one level
 * in the binary tree.
 *
 * This uses breadth first search technique with a sentinel
 * node pushed at the end of each level.
 *
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
template<class T>
vector<LinkedList<TreeNode<T> * > * > * BinaryTree<T>::getLevels()
{
	nodeArray = new vector<TreeNode<T> * >;
	vector<LinkedList<TreeNode<T> * > * > * levels = new vector<LinkedList<TreeNode<T> * > * >;
	LinkedList<TreeNode<T> * > * currentLevel = new LinkedList<TreeNode<T> * >;
	TreeNode<T> * sentinel = new TreeNode<T>;
	queue<TreeNode<T> * > * bfsQueue = new queue<TreeNode<T> * >;
	bfsQueue->push(root);
	bfsQueue->push(sentinel);

	while(!bfsQueue->empty())
	{
		TreeNode<T> * currNode = bfsQueue->front();
		bfsQueue->pop();
		nodeArray->push_back(currNode);
		if(currNode == sentinel)
		{
			levels->push_back(currentLevel);
			currentLevel = new LinkedList<TreeNode<T> * >;
			continue;
		}
		if(currNode->getLeft())
		{
			bfsQueue->push(currNode->getLeft());
		}
		if(currNode->getRight())
		{
			bfsQueue->push(currNode->getRight());
		}
		if(bfsQueue->front() == sentinel)
		{
			bfsQueue->push(sentinel);
		}
		currentLevel->append(new Node<TreeNode<T> * >(currNode));
	}
	return levels;
}

/**
 * Searches for an element 'val' in the binary tree and
 * returns the path from root to that element if found
 * and NULL otherwise.
 *
 * Uses find recursively on left and right children.
 *
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
template<class T>
vector<TreeNode<T> * > * BinaryTree<T>::find(T val)
{
	stack<TreeNode<T> * > * nodeStack = new stack<TreeNode<T> * >;
	bool found = findRecurse(root, val, nodeStack);
	if(!found) return NULL;
	vector<TreeNode<T> * > * path = new vector<TreeNode<T> * >;
	while(!nodeStack->empty())
	{
		path->push_back(nodeStack->top());
		nodeStack->pop();
	}
	delete nodeStack;
	return path;
}

/**
 * Algorithm:
 * 1) If root is equal to the value passed, we found the element. Push the root on stack
 *    and return true.
 * 2) The element might be in left or right sub-tree. Recursively invoke
 *    the same sub-routine to find the element in left or right sub-tree.
 * 3) If found in either of them, return as it is and the stack will have the path
 *    to the element.
 * 4) If not found in both children, pop the current root from the stack and return.
 */
template<class T>
bool BinaryTree<T>::findRecurse(TreeNode<T> * node, T val, stack<TreeNode<T> * > * nodeStack)
{
	if(!node) {
		return false;
	}
	nodeStack->push(node);
	if(node->getValue() == val) {
		return true;
	}
	if(findRecurse(node->getLeft(), val, nodeStack) ||
			findRecurse(node->getRight(), val, nodeStack))
	{
		return true;
	}
	nodeStack->pop();
	return false;
}

/**
 * Determines if this binary tree is balanced or not.
 * Also returns the height of the binary tree in the output
 * parameter 'height'.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template<class T>
bool BinaryTree<T>::isBalanced(int &height)
{
	bool balanced = false;
	height = getHeight(root, balanced);
	return balanced;
}

/**
 * Returns the height of the sub-tree rooted at node and
 * fills the variable 'balanced' with 'true' if the sub-tree is balanced
 * and with 'false' otherwise.
 *
 * Algorithm:
 * 1) Get height of the left sub-tree and check if it is balanced.
 * 2) Get height of the right sub-tree and check if it is balanced.
 * 3) If either of the left or right sub-trees are not balanced,
 *    then the current sub-tree is also not balanced.
 * 4) If both left and right sub-trees are balanced then the
 *    current sub-tree is balanced if difference between left height
 *    and right height is at most 1.
 * 5) Return the height of the current sub-tree as max(left height, right height)
 *    + 1.
 */
template<class T>
int BinaryTree<T>::getHeight(TreeNode<T> * node, bool &balanced)
{
	bool leftBalanced = true, rightBalanced = true;
	int leftHeight = 0, rightHeight = 0;
	if(node->getLeft())
	{
		leftHeight = getHeight(node->getLeft(), leftBalanced);
	}
	if(node->getRight())
	{
		rightHeight = getHeight(node->getRight(), rightBalanced);
	}
	if(!leftBalanced || !rightBalanced)
	{
		balanced = false;
	}
	else
	{
		balanced =true;
	}
	if(abs(leftHeight - rightHeight) > 1)
	{
		balanced = false;
	}
	return max(leftHeight, rightHeight) + 1;
}

/**
 * Finds the common ancestore between two given tree nodes p and q.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template<class T>
TreeNode<T> * BinaryTree<T>::findCommonAncestor(TreeNode<T> * p, TreeNode<T> * q)
{
	return findFirstCommonAncestor(p, q, root);
}

/**
 * Algorithm:
 * 1) If root itself is p or q, return root.
 * 2) Call 'findFirstCommonAncestor' recursively to find for p and q in left
 *    and right sub-trees respectively.
 * 3) If left recursive call returns a node which is neither p nor q, then it has
 *    found common ancestor return it as it is.
 * 4) Similarly if right recursive call returns a node which is neither p nor q, then
 *    it has found common ancestor return it as it is.
 * 5) If left and right recursive calls both return nothing, neither p, nor q
 *    nor the common ancestor are found. Return NULL.
 * 6) Now, something is found in either left or right subtree, but not in both and it could be
 *    either p or q. Return it as it is.
 * 7) If something is found in both left and right sub-trees and we know that
 *    they must be p and q respectively (since we exhausted all other possibilities).
 *    In this case, root is the first common ancestor. Return root.
 *
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
template<class T>
TreeNode<T> * BinaryTree<T>::findFirstCommonAncestor(TreeNode<T> * p, TreeNode<T> * q, TreeNode<T> * root)
{
	// if root itself is p or q just return it
	if(*root == *p || *root == *q)
	{
		return root;
	}
	TreeNode<T> * foundLeft = NULL, * foundRight = NULL;
	if(root->getLeft())
	{
		// if there is a left child recursively find
		foundLeft = findFirstCommonAncestor(p, q, root->getLeft());
		if(foundLeft && *foundLeft != *p && *foundLeft != *q)
		{
			// the recursive call returned the first common ancestor
			// just return it
			return foundLeft;
		}
	}
	if(root->getRight())
	{
		// if there is a right child recursively find
		foundRight = findFirstCommonAncestor(p, q, root->getRight());
		if(foundRight && *foundRight != *p && *foundRight != *q)
		{
			// the recursive call returned the first common ancestor
			// just return it
			return foundRight;
		}
	}
	// either p and q are on either sides or only one of them is present in one of the sub trees
	// or none of them is found
	if(!foundLeft && !foundRight)
	{
		return NULL;
	}
	if(!foundLeft) return foundRight;
	else if(!foundRight) return foundLeft;

	// by now we know that both of them are not null and both of them are either p or q
	// by assumption that the nodes are unique, we can just return the root here
	// since root is the common ancestor
	return root;
}

/**
 * Returns the diameter of a tree. The diameter of a tree
 * is the longest distance between any two nodes in the tree.
 *
 * Time compexity: O(n)
 * Space complexity: O(1)
 */
template<class T>
int BinaryTree<T>::getDiameter()
{
	int height = 0;
	return getDiameter(root, height);
}

/**
 * Algorithm:
 * 1) Get the diameter of left sub-tree (also get the height of it).
 * 2) Get the diameter of right sub-tree (also get the height of it).
 * 3) The diameter of the current sub-tree is the maximum of 3 values
 *    - the diameter of left subtree
 *    - the diameter of right subtree
 *    - (height of left sub-tree) + (height of right sub-tree) + 1
 * 4) Set the height of current sub-tree as maximum of
 *    - (height of left sub-tree, height of right sub-tree) + 1
 * 5) Return the diameter.
 */
template<class T>
int BinaryTree<T>::getDiameter(TreeNode<T> * root, int& height)
{
	if(root == NULL)
	{
		height = 0;
		return 0;
	}
	int leftHeight = 0, rightHeight = 0;
	int leftDia = getDiameter(root->getLeft(), leftHeight);
	int rightDia = getDiameter(root->getRight(), rightHeight);
	height = std::max(leftHeight, rightHeight) + 1;
	return std::max(std::max(leftDia, rightDia), leftHeight + rightHeight + 1);
}

template<class T>
bool BinaryTree<T>::matchTree(TreeNode<T> * source, TreeNode<T> * pattern)
{
	if(!pattern && !source) return true;
	if(!pattern || !source) return false;
	if(*pattern != *source) return false;
	return matchTree(source->getLeft(), pattern->getLeft()) &&
			matchTree(source->getRight(), pattern->getRight());
}

/**
 * Algorithm:
 * 1) Check if the pattern tree is equal to the tree rooted at source.
 * 2) If so, then return current root.
 * 3) Else, recursively check if the pattern matches with left sub-tree
 *    or right sub-tree.
 */
template<class T>
TreeNode<T> * BinaryTree<T>::isSubTree(TreeNode<T> * source, TreeNode<T> * pattern)
{
	if(!pattern) return source;
	if(matchTree(source, pattern)) return source;
	if(source->getLeft())
	{
		TreeNode<T> * matchedRoot = isSubTree(source->getLeft(), pattern);
		if(matchedRoot) return matchedRoot;
	}
	if(source->getRight()) {
		TreeNode<T> * matchedRoot = isSubTree(source->getRight(), pattern);
		if(matchedRoot) return matchedRoot;
	}
	return NULL;
}

/**
 * Checks if the binary tree 'other' is a subtree of the
 * current tree.
 *
 * Time complexity: O(n * m) where n is the size of the current tree
 *                  and m is the size of the sub-tree to be matched.
 * Space complexity: O(1)
 */
template<class T>
TreeNode<T> * BinaryTree<T>::isSubTree(BinaryTree<T> * other)
{
	if(!other) return root;
	return isSubTree(root, other->getRoot());
}

template<class T>
SumPath<T>::SumPath() {
	elements = new vector<TreeNode<T> * >;
	sum = 0;
}

template<class T>
void SumPath<T>::appendToPath(TreeNode<T> * node) {
	elements->push_back(node);
	sum += node->getValue();
}

template<class T>
void SumPath<T>::appendToPath(SumPath<T> * other) {
	vector<TreeNode<T> * > * otherElements = other->getElements();
	for(typename std::vector<TreeNode<T> * >::iterator it = otherElements->begin(); it != otherElements->end(); ++it)
	{
		elements->push_back(*it);
		sum += (*it)->getValue();
	}
}

template<class T>
void SumPath<T>::print() {
	for(typename std::vector<TreeNode<T> * >::iterator it = elements->begin(); it != elements->end(); ++it)
	{
		std::cout << (*it)->getValue() << " ";
	}
	std::cout << "Sum is: " << sum << std::endl;
}

template<class T>
void printVector(vector<SumPath<T> * > * paths)
{
	for(typename std::vector<SumPath<T> * >::iterator it = paths->begin(); it != paths->end(); ++it)
	{
		(*it)->print();
	}
}

template<class T>
T SumPath<T>::getSum() {
	return sum;
}

template<class T>
vector<TreeNode<T> * > * SumPath<T>::getElements()
{
	return elements;
}

/**
 * Returns all paths in a given binary tree that sum up to a given value.
 * Paths can be any paths including that traverse a root of the sub-tree
 * across.
 *
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
template<class T>
vector<SumPath<T> * > * BinaryTree<T>::findAllPathsWithSum(T sum)
{
	vector<SumPath<T> * > * results = new vector<SumPath<T> * >;
	findAllPaths(root, results, sum);
	return results;
}

/**
 * Algorithm:
 * 1) Find all paths ending in left child and right child by recursively
 *    calling the same procedure.
 * 2) The recursive procedure also fills the results with all paths
 *    found that sum upto 'sum'.
 * 3) Try combining paths from left child with the root and also with the
 *    paths from right child. There can be three new paths
 *    3.1) Paths ending in left child + root
 *    3.2) Paths ending in right child + root
 *    3.3) Paths ending in left child + root + Paths ending in right child
 *    Iterate through all such paths and find paths which sum upto 'sum'
 *    and push them to results.
 *
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
template<class T>
vector<SumPath<T> * > * BinaryTree<T>::findAllPaths(TreeNode<T> * root, vector<SumPath<T> * > * results, T sum)
{
	vector<SumPath<T> * > * pathsEndingInLeftChild = NULL, * pathsEndingInRightChild = NULL;
	vector<SumPath<T> * > * pathsEndingInCurrentNode = new vector<SumPath<T> * >;
	SumPath<T> * singleElementResult = new SumPath<T>;
	singleElementResult->appendToPath(root);

	if(root->getValue() == sum) {
		results->push_back(singleElementResult);
	}
	pathsEndingInCurrentNode->push_back(singleElementResult);

	if(root->getLeft())
	{
		pathsEndingInLeftChild = findAllPaths(root->getLeft(), results, sum);
	}
	if(root->getRight())
	{
		pathsEndingInRightChild = findAllPaths(root->getRight(), results, sum);
	}
	if(pathsEndingInRightChild)
	{
		// there is at least one right child
		for(typename std::vector<SumPath<T> * >::iterator it_right = pathsEndingInRightChild->begin(); it_right != pathsEndingInRightChild->end(); ++it_right)
		{
			SumPath<T> * newPath = new SumPath<T>;
			newPath->appendToPath(*it_right);
			newPath->appendToPath(root);
			pathsEndingInCurrentNode->push_back(newPath);
			if(newPath->getSum() == sum)
			{
				results->push_back(newPath);
			}
		}
	}
	if(pathsEndingInLeftChild)
	{
		for(typename std::vector<SumPath<T> * >::iterator it_left = pathsEndingInLeftChild->begin(); it_left != pathsEndingInLeftChild->end(); ++it_left)
		{
			SumPath<T> * newPath = new SumPath<T>;
			newPath->appendToPath(*it_left);
			newPath->appendToPath(root);
			pathsEndingInCurrentNode->push_back(newPath);
			if(newPath->getSum() == sum) {
				results->push_back(newPath);
			}
		}
	}
	if(pathsEndingInLeftChild && pathsEndingInRightChild)
	{
		for(typename std::vector<SumPath<T> * >::iterator it_left = pathsEndingInLeftChild->begin(); it_left != pathsEndingInLeftChild->end(); ++it_left)
		{
			for(typename std::vector<SumPath<T> * >::iterator it_right = pathsEndingInRightChild->begin(); it_right != pathsEndingInRightChild->end(); ++it_right)
			{
				if((*it_left)->getSum() + root->getValue() + (*it_right)->getSum() == sum)
				{
					SumPath<T> * newPath = new SumPath<T>;
					newPath->appendToPath(*it_left);
					newPath->appendToPath(root);
					newPath->appendToPath(*it_right);
					results->push_back(newPath);
				}
			}
		}
	}
	delete pathsEndingInLeftChild;
	delete pathsEndingInRightChild;
	return pathsEndingInCurrentNode;
}

/**
 * Binary search tree data structure.
 * Can be used for quickly finding elements and also
 * provides logarithmic running time for insertion and
 * deletion.
 */
template<class T>
class BST: public BinaryTree<T>
{
	TreeNode<T> * getBST(vector<T> * sortedArray);
	TreeNode<T> * getLeftMostChild(TreeNode<T> * node);
	TreeNode<T> * findSettingVisited(T val, int& visitedCount,
			  	  	  	  	  	  	 std::set<T>& setToFind);
	LinkedList<T> * convertSubtreeToSortedList(TreeNode<T> * node);
public:
	/**
	 * Constructs a binary search tree from a sorted array.
	 * Time complexity: O(n)
	 */
	BST(vector<T> * sortedArray);
	/**
	 * Constructs a binary search tree from an unsorted array.
	 * Time complexity: O(n)
	 */
	BST(vector<T> * array, bool unsorted);
	/**
	 * Returns the successor of a node with a given value.
	 * Time complexity: O(log n)
	 */
	TreeNode<T> * getSuccessor(T nodeValue);
	/**
	 * Returns the successor of a given node.
	 * Time complexity: O(log n)
	 */
	TreeNode<T> * getSuccessor(TreeNode<T> * node);

	/**
	 * Returns the least common ancestor of two given nodes.
	 * Time complexity: O(log n)
	 */
	TreeNode<T> * findCommonAncestor(TreeNode<T> * p, TreeNode<T> * q);

	/**
	 * Inserts a new node into the binary search tree while preserving the BST properties.
	 * Time complexity: O(log n)
	 */
	void appendNode(TreeNode<T> * newNode);

	/**
	 * Searches for a given value in a binary search tree.
	 * Time complexity: O(log n)
	 */
	TreeNode<T> * find(T val);

	/**
	 * Searches and removes a node with a given value in a binary search tree.
	 * Time complexity: O(log n)
	 */
	void remove(T val);

	/**
	 * Given a set of values, return true if and only if
	 * all the values in the set occur in same path from root
	 * to any leaf.
	 *
	 * Time complexity: O(m log n) where m is the size of the set and assuming
	 *                  balanced binary search tree.
	 * Space complexity: O(1)
	 */
	bool allOccurOnSamePathFromRoot(std::set<T>& vals);

	/**
	 * Convert this binary search tree into a sorted doubly
	 * linked list.
	 *
	 * Time complexity: O(n)
	 * Space complexity: O(1)
	 */
	LinkedList<T> * convertToSortedList();
};

/**
 * Constructs a BST from a sorted array.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template<class T>
BST<T>::BST(vector<T> * sortedArray)
{
	BinaryTree<T>::root = getBST(sortedArray);
	vector<LinkedList<TreeNode<T> * > * > * levels = BinaryTree<T>::getLevels();
}

template<class T>
BST<T>::BST(vector<T> * array, bool unsorted)
{
	for(typename std::vector<T>::iterator it = array->begin(); it != array->end(); ++it)
	{
		appendNode(new TreeNode<T>(*it));
	}
	BinaryTree<T>::getLevels();
}

/**
 * Constructs a binary search tree from a sorted array.
 * Algorithm:
 * 1) Find the middle element and create root from that element.
 * 2) Recursively call the same procedure for the left half of
 *    the array and get the left child to assign.
 * 3) Recursively call the same procedure for the right half
 *    of the array and get the right child to assign.
 * 4) Return the current root.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template<class T>
TreeNode<T> * BST<T>::getBST(vector<T> * sortedArray)
{
	int middleIndex = sortedArray->size()/2;
	TreeNode<T> * currentRoot = new TreeNode<T>(sortedArray->at(middleIndex));
	if(sortedArray->size() > 1)
	{
		if(sortedArray->size() > 2)
		{
			TreeNode<T> * rightChild = getBST(new vector<T>(sortedArray->begin() + middleIndex + 1,
												sortedArray->end()));
			currentRoot->setRight(rightChild);
			rightChild->setParent(currentRoot);
		}
		TreeNode<T> * leftChild = getBST(new vector<T>(sortedArray->begin(),
											sortedArray->begin() + middleIndex));
		currentRoot->setLeft(leftChild);
		leftChild->setParent(currentRoot);
	}
	return currentRoot;
}

template<class T>
TreeNode<T> * BST<T>::getSuccessor(T nodeValue) {
	TreeNode<T> * nodeToFind = find(nodeValue);
	if(!nodeToFind) return NULL;
	return getSuccessor(nodeToFind);
}

/**
 * Returns the successor of a given node in a binary search tree.
 * Algorithm:
 * 1) If node has a right child, return the left most child
 *    of the right child.
 * 2) Move up towards root until we take a right turn.
 *    The parent at that point is the successor.
 *
 * Time complexity: O(log n)
 * Space complexity: O(1)
 */
template<class T>
TreeNode<T> * BST<T>::getSuccessor(TreeNode<T> * node)
{
	if(node->getRight())
	{
		return getLeftMostChild(node->getRight());
	}
	TreeNode<T> * parent = node->getParent();
	if(parent->getLeft() == node)
	{
		return parent;
	}
	TreeNode<T> * temp = parent;
	TreeNode<T> * currNode = node;
	while(temp != NULL && temp->getRight() == currNode)
	{
		currNode = temp;
		temp = temp->getParent();
	}
	return temp;
}

/**
 * Removes a node with a given value from binary search tree
 * while preserving the BST property.
 * Algorithm:
 * 1) Find the node to remove in O(log n) time.
 * 2) If there are no children, remove it right away.
 * 3) If there is only one child, remove the node and
 *    make that child a left or right child of the original
 *    parent depending on whether root was left or right child
 *    of the original parent.
 * 4) If both children are present, find the successor
 *    and exchange the successor value with the current root
 *    and remove the successor - successor is guaranteed to not
 *    have both children.
 *
 * Time complexity: O(log n)
 * Space complexity: O(1)
 */
template<class T>
void BST<T>::remove(T val) {
	TreeNode<T> * nodeToRemove = find(val);
	if(!nodeToRemove) {
		return;
	}
	if(nodeToRemove->getLeft() && nodeToRemove->getRight()) {
		TreeNode<T> * successor = getSuccessor(nodeToRemove);
		nodeToRemove->setValue(successor->getValue());
		TreeNode<T> * successorParent = successor->getParent();
		successorParent->setLeft(successor->getRight());
		if(successor->getRight()) {
			successor->getRight()->setParent(successorParent);
		}
		delete successor;
		return;
	}
	if(!nodeToRemove->getLeft() && !nodeToRemove->getRight()) {
		TreeNode<T> * parent = nodeToRemove->getParent();
		if(parent->getLeft() == nodeToRemove) {
			parent->setLeft(NULL);
		}
		else {
			parent->setRight(NULL);
		}
		delete nodeToRemove;
		return;
	}
	TreeNode<T> * nodeToReplace = nodeToRemove->getLeft();
	if(!nodeToReplace) {
		nodeToReplace = nodeToRemove->getRight();
	}
	TreeNode<T> * parent = nodeToRemove->getParent();
	if(parent->getLeft() == nodeToRemove) {
		parent->setLeft(nodeToReplace);
	}
	else {
		parent->setRight(nodeToReplace);
	}
	delete nodeToRemove;
}

template<class T>
TreeNode<T> * BST<T>::getLeftMostChild(TreeNode<T> * node)
{
	TreeNode<T> * temp = node;
	while(temp)
	{
		if(temp->getLeft())
		{
			temp = temp->getLeft();
		}
		else
		{
			break;
		}
	}
	return temp;
}

/**
 * Finds common ancestor of two given tree nodes.
 * Algorithm:
 * 1) Start with root.
 * 2) Keep going left or right in the direction
 *    where both p and q are present (that is the
 *    current root element is either less than both
 *    or greater than both).
 * 3) Stop when current root element is greater than p
 *    but less than p. The current root
 *    is the common ancestor.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template<class T>
TreeNode<T> * BST<T>::findCommonAncestor(TreeNode<T> * p, TreeNode<T> * q)
{
	TreeNode<T> * temp = BinaryTree<T>::root;
	while(temp)
	{
		if(*p < *temp && *temp < *q)
		{
			return temp;
		}
		if(*temp < *p && *temp < *q)
		{
			temp = temp->getRight();
		}
		else {
			temp = temp->getLeft();
		}
	}
}

/**
 * Inserts a new node in the binary search tree.
 * Algorithm:
 * 1) If root doesn't exists, mark the current node
 *    as root.
 * 2) If current root value is less than the new node value
 *    move to right child else move to left child.
 * 3) When you encounter NULL pointer, insert the new node
 *    to replace the NULL pointer.
 *
 * Time complexity: O(log n)
 * Space complexity: O(1)
 */
template<class T>
void BST<T>::appendNode(TreeNode<T> * newNode)
{
	if(!BinaryTree<T>::root) {
		BinaryTree<T>::root = newNode;
		return;
	}
	TreeNode<T> * parent = BinaryTree<T>::root;
	while(parent) {
		if(parent->getValue() < newNode->getValue()) {
			if(parent->getRight()) {
				parent = parent->getRight();
			}
			else {
				parent->setRight(newNode);
				newNode->setParent(parent);
				break;
			}
		}
		else {
			if(parent->getLeft()) {
				parent = parent->getLeft();
			}
			else {
				parent->setLeft(newNode);
				newNode->setParent(parent);
				break;
			}
		}
	}
}

/**
 * Finds a given value in the binary search tree.
 * Algorithm: Too easy to write - see 'appendNode' above.
 *
 * Time complexity: O(log n)
 * Space complexity: O(1)
 */
template<class T>
TreeNode<T> * BST<T>::find(T val) {
	if(!BinaryTree<T>::root) {
		return NULL;
	}
	TreeNode<T> * temp = BinaryTree<T>::root;
	while(temp) {
		if(temp->getValue() < val) {
			temp = temp->getRight();
		}
		else if(temp->getValue() > val){
			temp = temp->getLeft();
		}
		else {
			return temp;
		}
	}
	return temp;
}

template<class T>
TreeNode<T> * BST<T>::findSettingVisited(T val, int& visitedCount,
										std::set<T>& setToFind)
{
	if(!BinaryTree<T>::root) {
		return NULL;
	}
	TreeNode<T> * temp = BinaryTree<T>::root;
	while(temp)
	{
		if(!temp->isVisited())
		{
			typename std::set<T>::iterator it = setToFind.find(temp->getValue());
			if(it != setToFind.end())
			{
				temp->setVisited();
				visitedCount++;
			}
		}
		else
		{
			visitedCount++;
		}
		if(temp->getValue() < val) {
			temp = temp->getRight();
		}
		else if(temp->getValue() > val){
			temp = temp->getLeft();
		}
		else {
			return temp;
		}
	}
	return temp;
}

/**
 * Checks if the current tree is a binary search tree.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template<class T>
bool BinaryTree<T>::isBST()
{
	return dfsBSTCheck(root);
}

/**
 * Checks if all the values in a given set occur on the same root-leaf path
 * from the root.
 *
 * Algorithm:
 * 1) For each element in the input set, perform a 'find' operation
 *    on binary search.
 * 2) While performing find, for every node, check if the value
 *    is in the set. If it is, set the visited variable and increment
 *    the count.
 * 3) If the visited count after the last iteration is equal to the size
 *    of the input set, then all the nodes occur on the same root to null path.
 *    Return true.
 *
 * Time complexity: O(m log n) where m is the size of input set and n is the size of the tree
 * Space complexity: O(1)
 */
template<class T>
bool BST<T>::allOccurOnSamePathFromRoot(std::set<T>& vals)
{
	int visitedCount = 0;
	for(typename std::set<T>::const_iterator it = vals.begin(); it != vals.end(); ++it)
	{
		visitedCount = 0;
		findSettingVisited(*it, visitedCount, vals);
	}
	return visitedCount == vals.size();
}

/**
 * Converts a sub tree rooted at node to a sorted linked list.
 *
 * Algorithm:
 * 1) Get the sorted list for left subtree recursively.
 * 2) Get the sorted list for right subtree recursively.
 * 3) Stitch the two lists together by inserting the root
 *    in between.
 * 4) Return the new list.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template<class T>
LinkedList<T> * BST<T>::convertSubtreeToSortedList(TreeNode<T> * node)
{
	LinkedList<T> * result = new LinkedList<T>;
	LinkedList<T> * leftResult = NULL, * rightResult = NULL;
	if(node->getLeft())
	{
		leftResult = convertSubtreeToSortedList(node->getLeft());
	}
	if(node->getRight())
	{
		rightResult = convertSubtreeToSortedList(node->getRight());
	}
	Node<T> * rootNode = new Node<T>(node->getValue());
	if(leftResult)
	{
		delete result;
		result = leftResult;
	}
	result->append(rootNode);
	if(rightResult)
	{
		result->appendList(rightResult);
	}
	return result;
}

template<class T>
LinkedList<T> * BST<T>::convertToSortedList()
{
	return convertSubtreeToSortedList(BST<T>::root);
}

/**
 * Checks if the sub-tree rooted at node is a binary search tree.
 * Algorithm:
 * 1) Check if the left sub-tree is BST recursively.
 * 2) Check if the right sub-tree is BST recursively.
 * 3) Return false if either of them are not BSTs.
 * 4) If both left and right sub-trees are BSTs, then
 *    compare the values - left must be less than the root
 *    and right must be more than the root.
 *    If this condition satisfies, then return true.
 * 5) Else return false.
 */
template<class T>
bool BinaryTree<T>::dfsBSTCheck(TreeNode<T> * node)
{
	bool ret = true;
	if(node->getLeft())
	{
		if(node->getLeft()->getValue() > node->getValue())
		{
			return false;
		}
		ret = ret && dfsBSTCheck(node->getLeft());
	}
	if(node->getRight())
	{
		if(node->getRight()->getValue() < node->getValue())
		{
			return false;
		}
		ret = ret && dfsBSTCheck(node->getRight());
	}
	return ret;
}

#endif /* BINARYTREE_H_ */
