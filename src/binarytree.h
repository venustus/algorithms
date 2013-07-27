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
protected:
	vector<TreeNode<T> * > * nodeArray;
	TreeNode<T> * root;
public:
	/**
	 * Constructs an empty binary tree.
	 */
	BinaryTree();

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

	void printPreOrder(vector<T> &preorderList);

	void printPreOrderNoRecurse(vector<T> &preorderList);

	void printPostOrder(vector<T> &postorderList);

	void printPostOrderNoRecurse(vector<T> &postorderList);

	void printNormal(vector<T> &normalorderList);

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

	TreeNode<T> * getRoot();

	vector<TreeNode<T> * > * getNodeArray();

	/**
	 * Returns all possible paths in the binary tree whose node values sum up to a given sum.
	 * Paths can bend around roots.
	 * Time complexity: O(n)
	 */
	vector<SumPath<T> * > * findAllPathsWithSum(T sum);
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

template<class T>
BinaryTree<T>::BinaryTree(vector<T> * inorderList, vector<T> * preorderList)
{
	root = reconstructTree(inorderList, preorderList);
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

template<class T>
bool BinaryTree<T>::isBalanced(int &height)
{
	bool balanced = false;
	height = getHeight(root, balanced);
	return balanced;
}

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

template<class T>
TreeNode<T> * BinaryTree<T>::findCommonAncestor(TreeNode<T> * p, TreeNode<T> * q)
{
	return findFirstCommonAncestor(p, q, root);
}

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

template<class T>
bool BinaryTree<T>::matchTree(TreeNode<T> * source, TreeNode<T> * pattern)
{
	if(!pattern && !source) return true;
	if(!pattern || !source) return false;
	if(*pattern != *source) return false;
	return matchTree(source->getLeft(), pattern->getLeft()) &&
			matchTree(source->getRight(), pattern->getRight());
}

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

template<class T>
vector<SumPath<T> * > * BinaryTree<T>::findAllPathsWithSum(T sum)
{
	vector<SumPath<T> * > * results = new vector<SumPath<T> * >;
	findAllPaths(root, results, sum);
	return results;
}

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
	return pathsEndingInCurrentNode;
}

template<class T>
class BST: public BinaryTree<T>
{
	TreeNode<T> * getBST(vector<T> * sortedArray);
	TreeNode<T> * getLeftMostChild(TreeNode<T> * node);
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
};

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
bool BinaryTree<T>::isBST()
{
	return dfsBSTCheck(root);
}

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
