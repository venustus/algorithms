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
};

template<class T>
class BinaryTree
{
	int getParentIndex(int childIndex);
	int getLeftChildIndex(int parentIndex);
	int getRightChildIndex(int parentIndex);
	void traverseInOrder(TreeNode<T> * root);
	void traversePreOrder(TreeNode<T> * root);
	void traversePostOrder(TreeNode<T> * root);
	TreeNode<T> * reconstructTree(vector<T> * inorderList,
								  vector<T> * preorderList);
	int getHeight(TreeNode<T> * root, bool &isBalanced);
	bool dfsBSTCheck(TreeNode<T> * node);
protected:
	vector<TreeNode<T> * > * nodeArray;
	TreeNode<T> * root;
public:
	BinaryTree();

	BinaryTree(TreeNode<T> * root);

	BinaryTree(vector<T> * nodeList);

	BinaryTree(vector<T> * inorderList, vector<T> * preorderList);

	void printInOrder();

	void printInOrderNoRecurse();

	void printPreOrder();

	void printPreOrderNoRecurse();

	void printPostOrder();

	void printPostOrderNoRecurse();

	void printNormal();

	void appendNode(TreeNode<T> * newNode);

	bool isBalanced(int &height);

	vector<LinkedList<TreeNode<T> * > * > * getLevels();

	bool isBST();
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
T TreeNode<T>::getValue()
{
	return val;
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
}

template<class T>
BinaryTree<T>::BinaryTree(vector<T> * inorderList, vector<T> * preorderList)
{
	root = reconstructTree(inorderList, preorderList);
}

template<class T>
TreeNode<T> * BinaryTree<T>::reconstructTree(vector<T> * inorderList, vector<T> * preorderList)
{
	typename vector<T>::iterator itr  = find(inorderList->begin(),
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
void BinaryTree<T>::traverseInOrder(TreeNode<T> * root)
{
	if(!root)
	{
		return;
	}
	traverseInOrder(root->getLeft());
	cout << root->getValue() << " ";
	traverseInOrder(root->getRight());
}

template<class T>
void BinaryTree<T>::traversePostOrder(TreeNode<T> * root)
{
	if(!root)
	{
		return;
	}
	traversePostOrder(root->getLeft());
	traversePostOrder(root->getRight());
	cout << root->getValue() << " ";
}

template<class T>
void BinaryTree<T>::printInOrder()
{
	traverseInOrder(root);
	cout << endl;
}

template<class T>
void BinaryTree<T>::printPreOrder()
{
	traversePreOrder(root);
	cout << endl;
}

template<class T>
void BinaryTree<T>::printPostOrder()
{
	traversePostOrder(root);
	cout << endl;
}

template<class T>
void BinaryTree<T>::printInOrderNoRecurse()
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
void BinaryTree<T>::traversePreOrder(TreeNode<T> * n)
{
	if(!n)
	{
		return;
	}
	cout << n->getValue() << " ";
	traversePreOrder(n->getLeft());
	traversePreOrder(n->getRight());
}

template<class T>
void BinaryTree<T>::printPreOrderNoRecurse()
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
		}
	}
	cout << endl;
}

template<class T>
void BinaryTree<T>::printPostOrderNoRecurse()
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
		}
	}
}

template<class T>
void BinaryTree<T>::printNormal()
{
	queue<TreeNode<T> * > * bfsqueue = new queue<TreeNode<T> * >;
	bfsqueue->push(root);
	while(!bfsqueue->empty())
	{
		TreeNode<T> * front = bfsqueue->front();
		bfsqueue->pop();
		cout << front->getValue() << " ";
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
	if(abs(leftHeight - rightHeight) > 0)
	{
		balanced = false;
	}
	return max(leftHeight, rightHeight) + 1;
}

template<class T>
class BST: public BinaryTree<T>
{
	TreeNode<T> * getBST(vector<T> * sortedArray);
	TreeNode<T> * getLeftMostChild(TreeNode<T> * node);
public:
	BST(vector<T> * sortedArray);
	TreeNode<T> * getSuccessor(T nodeValue);
};

template<class T>
BST<T>::BST(vector<T> * sortedArray)
{
	BinaryTree<T>::root = getBST(sortedArray);
	vector<LinkedList<TreeNode<T> * > * > * levels = BinaryTree<T>::getLevels();
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
TreeNode<T> * BST<T>::getSuccessor(T nodeValue)
{
	const TreeNode<T> nodeToFind(nodeValue);
	typename vector<TreeNode<T> * >::iterator it =
			std::find_if(BinaryTree<T>::nodeArray->begin(),
				      	  BinaryTree<T>::nodeArray->end(),
				      	  FindValFromPointer<TreeNode<T> >(nodeToFind));
	if(it == BinaryTree<T>::nodeArray->end())
	{
		return NULL;
	}
	TreeNode<T> * node = *it;
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
