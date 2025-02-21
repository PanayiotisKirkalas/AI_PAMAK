#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <iostream>
#include <utility>
using std::pair;
using std::make_pair;
using std::vector;
using std::string;
using std::chrono::steady_clock;

class TreeNode;

class BreadthFirst
{
	bool QueueUsed;
	int Start, End;
	vector<TreeNode*> Queue[2];

public:
	BreadthFirst(int S, int E, TreeNode* root);
	pair<TreeNode*, double> Find();
};
