//
//  main.cpp
//  Cpluspluspractice
//
//  Created by Venkat Pedapati on 03/03/13.
//  Copyright (c) 2013 Venkat Pedapati. All rights reserved.
//

#include <iostream>
#include <istream>
#include <sstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>









/*
int main(int argc, const char * argv[])
{
	//std::cout << "Enter command:" << std::endl;
	std::string PUSH_PREFIX = "push";
	std::string QUEUE_PREFIX = "queue";
	std::string QUEUE_DOG_PREFIX = "queuedog";
	std::string QUEUE_CAT_PREFIX = "queuecat";
	std::string POP_PREFIX = "pop";
	std::string DEQUEUE_PREFIX = "dequeue";
	std::string DEQUEUE_DOG_PREFIX = "dequeue_dog";
	std::string DEQUEUE_CAT_PREFIX = "dequeue_cat";
	std::string DEQUEUE_ANY_PREFIX = "dequeue_any";
	std::string TOP_PREFIX = "top";
	std::string SORT_PREFIX = "sort";
	std::string PEEK_PREFIX = "peek";
	std::string MIN_PREFIX = "min";
	std::string ADD_EDGE_PREFIX = "add_edge";
	std::string DFS_PREFIX = "dfs";
	std::string BFS_PREFIX = "bfs";
	std::string PATH_CHECK_PREFIX = "path_exists";
	std::string EXIT_PREFIX = "exit";
	StackWithMin<int> *minStack = new StackWithMin<int>;
	SetOfStacks<int> *setOfStacks = new SetOfStacks<int>(3);
	stack<int> firstTower;
	stack<int> stackToSort;
	MyQueue<int> queue;
	AnimalQueue animalQueue;
	Graph<int> graph(true);

	while(true)
	{
		std::string command;
		getline(std::cin, command);
		std::vector<std::string> parts;
		split(command, ' ', parts);
		if(std::equal(ADD_EDGE_PREFIX.begin(), ADD_EDGE_PREFIX.end(), command.begin()))
		{
			std::stringstream iss1(parts[1]);
			std::stringstream iss2(parts[2]);
			int source, dest;
			iss1 >> source;
			iss2 >> dest;
			graph.addEdge(source, dest);
			std::cout << "Added edge: " << parts[1] << "->" << parts[2] << std::endl;
		}
		else if(std::equal(PATH_CHECK_PREFIX.begin(), PATH_CHECK_PREFIX.end(), command.begin()))
		{
			std::stringstream iss1(parts[1]);
			std::stringstream iss2(parts[2]);
			int source, dest;
			iss1 >> source;
			iss2 >> dest;
			std::cout << "Path exists: " << graph.pathExists(source, dest) << std::endl;
		}
		else if(std::equal(DFS_PREFIX.begin(), DFS_PREFIX.end(), command.begin()))
		{
			std::cout << "Printing DFS" << std::endl;
			graph.dfs();
			std::cout << std::endl;
		}
		else if(std::equal(BFS_PREFIX.begin(), BFS_PREFIX.end(), command.begin()))
		{
			std::cout << "Printing BFS" << std::endl;
			graph.bfs();
			std::cout << std::endl;
		}
		else if(std::equal(EXIT_PREFIX.begin(), EXIT_PREFIX.end(), command.begin())) {
			break;
		}
	}
	while(true)
	{
		std::string command;
		getline(std::cin, command);
		std::vector<std::string> parts;
		split(command, ' ', parts);
		if(std::equal(QUEUE_DOG_PREFIX.begin(), QUEUE_DOG_PREFIX.end(), command.begin()))
		{
			Dog *dog = new Dog(parts[1], 80);
			animalQueue.queueDog(*dog);
			std::cout << "Queued dog: " << parts[1] << std::endl;
		}
		else if(std::equal(QUEUE_CAT_PREFIX.begin(), QUEUE_CAT_PREFIX.end(), command.begin()))
		{
			Cat *cat = new Cat(parts[1], 10);
			animalQueue.queueCat(*cat);
			std::cout << "Queued cat: " << parts[1] << std::endl;
		}
		else if(std::equal(DEQUEUE_DOG_PREFIX.begin(), DEQUEUE_DOG_PREFIX.end(), command.begin()))
		{
			Dog *dog = animalQueue.dequeueDog();
			std::cout << "Dequeued dog is: " << dog->getName() << std::endl;
		}
		else if(std::equal(DEQUEUE_CAT_PREFIX.begin(), DEQUEUE_CAT_PREFIX.end(), command.begin()))
		{
			Cat *cat = animalQueue.dequeueCat();
			std::cout << "Dequeued cat is: " << cat->getName() << std::endl;
		}
		else if(std::equal(DEQUEUE_ANY_PREFIX.begin(), DEQUEUE_ANY_PREFIX.end(), command.begin()))
		{
			Animal *animal = animalQueue.dequeueAny();
			std::cout << "Dequeued animal is: " << animal->getName() << std::endl;
		}
		else if(std::equal(TOP_PREFIX.begin(), TOP_PREFIX.end(), command.begin()))
		{
			int top = stackToSort.top();
			std::cout << "Top element " << top << std::endl;
		}
		else if(std::equal(SORT_PREFIX.begin(), SORT_PREFIX.end(), command.begin()))
		{
			sort(&stackToSort);
			std::cout << "Sorted stack. New top is: " << stackToSort.top() << std::endl;
		}
		else if(std::equal(EXIT_PREFIX.begin(), EXIT_PREFIX.end(), command.begin())) {
			break;
		}
	}

	TowerOfHanoi<int> * towerOfHanoi = new TowerOfHanoi<int>(firstTower, 2);
	stack<int> * targetTower = towerOfHanoi->solve();
	while(!targetTower->empty())
	{
		std::cout << targetTower->top() << std::endl;
		targetTower->pop();
	}


	std::string input1, input2;
	std::vector<int> preorderlistElements, inorderlistElements;
	std::vector<int> treeList;
	//std::cout << "Enter a list of integers separated by spaces for preorder list" << std::endl;
	//getline(std::cin, input1);
	//std::cout << "Enter a list of integers separated by spaces for inorder list" << std::endl;
	//getline(std::cin, input2);
	std::cout << "Enter a list of integers separated by spaces" << std::endl;
	getline(std::cin, input1);
	std::stringstream iss1(input1);
	//std::stringstream iss2(input2);
	int value;
	while(iss1 >> value)
	{
		treeList.push_back(value);
	}

	while(iss2 >> value)
	{
		inorderlistElements.push_back(value);
	}

	BST<int> * bst = new BST<int>(&treeList);
	std::cout << "Binary Search Tree" << std::endl;
	bst->printNormal();
	for(vector<int>::iterator it = treeList.begin(); it != treeList.end(); ++it)
	{
		std::cout<< "Successor of " << *it << " is ";
		TreeNode<int> * successor = bst->getSuccessor(*it);
		if(successor)
		{
			std::cout << bst->getSuccessor(*it)->getValue() << std::endl;
		}
		else
		{
			std::cout << "None" << std::endl;
		}
	}

	//BinaryTree<int> * bt = new BinaryTree<int>(&inorderlistElements, &preorderlistElements);
	//BinaryTree<int> * bt = new BinaryTree<int>(&treeList);
	std::cout << "Tree" << std::endl;
	bst->printNormal();
	std::cout << "In order" << std::endl;
	bst->printInOrder();
	std::cout << "In order without recursion" << std::endl;
	bst->printInOrderNoRecurse();
	std::cout << "Pre order" << std::endl;
	bst->printPreOrder();
	std::cout << "Pre order without recursion" << std::endl;
	bst->printPreOrderNoRecurse();
	std::cout << "Post order" << std::endl;
	bst->printPostOrder();
	std::cout << "Post order without recursion" << std::endl;
	bst->printPostOrderNoRecurse();
	std::cout << std::endl;
	std::cout << "Levels in tree" << std::endl;
	vector<LinkedList<TreeNode<int> * > * > * levels = bst->getLevels();
	vector<LinkedList<TreeNode<int> * > * >::iterator it;
	for(it = levels->begin(); it != levels->end(); ++it)
	{
		LinkedList<TreeNode<int> * > * level = *it;
		level->print();
		std::cout << std::endl;
	}

	int height = 0;
	bool isBalanced = bst->isBalanced(height);
	if(isBalanced)
	{
		std::cout << "Binary tree is balanced" << endl;
	}
	else
	{
		std::cout << "Binary tree is imbalanced" << endl;
	}
	std::cout << "Height of the binary tree: " << height << endl;

	std::cout << "Is BST: " << bst->isBST() << std::endl;

	//LinkedList<int> num1(listElements);

	listElements.erase(listElements.begin(), listElements.end());
	while(iss2 >> value)
	{
		listElements.push_back(value);
	}
	LinkedList<int> num2(listElements);
	//cout << "Is list palindrome: " << num1.isPalindrome() << endl;
	//LinkedList<int> *result = sumReverse(&num1, &num2);
	//result->print();
	//LinkedList<int> *result2 = sum(&num1, &num2);
	//result2->print();
	std::string input;
	std::vector<int> listElements;
	std::cout << "Enter a list of integers separated by spaces" << std::endl;
	getline(std::cin, input);
	int x = 0;
	std::cout << "Enter value for x" << std::endl;
	std::cin >> x;
	std::stringstream iss(input);
	int value;
	while(iss >> value)
	{
		listElements.push_back(value);
	}
	LinkedList<int> intList (listElements);
	intList.rearrange(x);
	//std::cout << "kth element from rear is: " << charList.kthElementFromRear(k) << std::endl;
	//charList.deleteNodeSingle(charList[k]);
	//charList.deleteDuplicates();
	intList.print();
	std::string input;
	int m = 0, n = 0;
	std::cout << "Enter number of rows in the matrix" << std::endl;
	std::cin >> m;
	std::cout << "Enter number of columns in the matrix" << std::endl;
	std::cin >> n;
	std::vector<std::vector<int> > twodArray;
	std::vector<int> currentRow;
	for(int i = 0; i < m; i++)
	{
		std::cout << "Reading " << i << " row" << std::endl;
		std::cout << "Enter a list of integers separated by spaces" << std::endl;
		getline(std::cin, input);
		std::stringstream iss(input);
		int value;
		while(iss >> value)
		{
			currentRow.push_back(value);
		}
		twodArray.push_back(currentRow);
	}
	markZero(twodArray, m, n);
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			std::cout << twodArray[i][j] << " ";
		}
		std::cout << std::endl;
	}

	std::string input;
	std::cout << "Enter string with repeated characters" << std::endl;
	getline(std::cin, input);
	char *compressedStr = compress((char *) input.c_str(), input.size());
	std::cout << "Compressed string is: " << compressedStr << std::endl;
	std::string input;
	std::string exactLenStr;
	int exactLen;
	std::cout << "Enter any string with spaces" << std::endl;
	getline(std::cin, input);
	std::cout << "Enter exact length of the string" << std::endl;
	std::cin >> exactLen;
	char * normalizedStr = normalize((char *) input.c_str(), exactLen);
	std::cout << "Normalized string is: " << normalizedStr << std::endl;
	std::string a, b;
    std::cout << "Enter any string" << std::endl;
    std::cin >> a;
    std::cout << "Enter another string" << std::endl;
    std::cin >> b;
    std::cout << "Is a permutation: " << isPermutation((char *)a.c_str(), (char *)b.c_str()) << std::endl;
    std::string input;
     
    // insert code here...
    std::string input;
    std::cout << "Enter any string of characters" << std::endl;
    std::cin >> input;
    if(isUniqueStr(input))
    {
        std::cout << "String " << input << " has unique character" << std::endl;
    }
    else
    {
        std::cout << "String " << input << " does not have all unique characters" << std::endl;
    }
    return 0;
}
*/

