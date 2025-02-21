#pragma once
#include <stack>
#include <string>
#include <chrono>
#include <utility>
using std::pair;
using std::make_pair;
using std::stack;
using std::string;
using std::chrono::steady_clock;

class TreeNode;

class DepthNode {
public:
	TreeNode* treeNode;
	int currOperation;

	DepthNode(TreeNode* node, int pCurrOperations);
	~DepthNode();
};

class DepthFirst
{
	int Start, End;
	stack<DepthNode*> myStack;


public:
	DepthFirst(int S, int E, TreeNode* root);
	pair<TreeNode*, double> Find();
};

