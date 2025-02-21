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

class AStarNode {
public:
	TreeNode* node;
	int cost;

	AStarNode(TreeNode* p_node, int p_cost);
	~AStarNode();
};

class AStar
{
	vector<AStarNode*> Open, Closed;
	int Start, End;

	int FindMin();

public:
	AStar(int S, int E, TreeNode* root);
	pair<TreeNode*, double> Find();
};

