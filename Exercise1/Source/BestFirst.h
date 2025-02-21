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

class BestFirst
{
	vector<TreeNode*> Open;
	int Start, End;

	int FindMin();

public:
	BestFirst(int S, int E, TreeNode* root);
	pair<TreeNode*, double> Find();
};

