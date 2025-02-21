#pragma once
#include <utility>
#include <cmath>
#include <fstream>
#include <stack>
#include <iostream>
using std::pair;
using std::make_pair;
using std::sqrt;
using std::ofstream;
using std::stack;

class TreeNode
{
public:
	int number, operation;
	TreeNode* parent;
	TreeNode* children[6];

	TreeNode(int data, TreeNode* parent, int pOperation);
	~TreeNode();
	pair<int, int> ToChild(int ChildNumber);
	//static int CostToChild(int ChildNumber, int X);
	void Expand();
	pair<stack<TreeNode*>, int> Retrace();
};

