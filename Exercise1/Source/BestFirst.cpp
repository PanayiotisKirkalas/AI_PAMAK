#include "BestFirst.h"
#include "TreeNode.h"
#include <cmath>
using std::abs;

BestFirst::BestFirst(int S, int E, TreeNode* root) 
	:Start(S), End(E)
{
	Open.push_back(root);
}

pair<TreeNode*, double> BestFirst::Find() {
	steady_clock::time_point start = steady_clock::now(), current = steady_clock::now();
	int min = 0;
	TreeNode* curr = nullptr;
	
	while (steady_clock::duration(current - start) <= std::chrono::seconds(60)) {
		min = FindMin();
		curr = Open.at(min);
		//if (curr->number == End)
		//	return curr;
		if (curr->number == End) {
			double dur = std::chrono::duration_cast<std::chrono::milliseconds>(current - start).count();
			return make_pair(curr, dur);
		}
		Open.erase(Open.begin() + min);
		curr->Expand();
		for (int i = 0; i < 6; ++i) {
			if (curr->children[i] == nullptr)
				continue;
			Open.push_back(curr->children[i]);
		}
		current = steady_clock::now();
	}

	return make_pair(nullptr, 0.0);
}

int BestFirst::FindMin() {
	int min = abs(End - Open.at(0)->number), minI = 0;

	for (int i = 1; i < Open.size(); ++i) {
		if (min > abs(End - Open.at(i)->number)) {
			min = abs(End - Open.at(i)->number);
			minI = i;
		}
	}

	return minI;
}