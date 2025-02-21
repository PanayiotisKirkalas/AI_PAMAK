#include "AStar.h"
#include "TreeNode.h"

AStarNode::AStarNode(TreeNode* p_node, int p_cost) 
	:node(p_node), cost(p_cost)
{
	
}
AStarNode::~AStarNode() {
	delete node;
}

AStar::AStar(int S, int E, TreeNode* root)
	:Start(S), End(E)
{
	Open.push_back(new AStarNode(root, 0));
}

pair<TreeNode*, double> AStar::Find() {
	steady_clock::time_point start = steady_clock::now(), current = steady_clock::now();
	int min = 0;
	bool itsLoop = false;
	AStarNode* curr = nullptr;

	while (steady_clock::duration(current - start) <= std::chrono::seconds(60)) {
		min = FindMin();
		curr = Open.at(min);
		//std::cout << curr->node->number << std::endl << '\t';
		
		if (curr->node->number == End) {
			double dur = std::chrono::duration_cast<std::chrono::milliseconds>(current - start).count();
			return make_pair(curr->node, dur);
		}
		Closed.push_back(Open.at(min));
		Open.erase(Open.begin() + min);

		curr->node->Expand();
		
		for (int i = 0; i < 6; ++i) {
			itsLoop = false;
			if (curr->node->children[i] == nullptr)
				continue;
			for (AStarNode* n : Closed) {
				if (n->node->number == curr->node->children[i]->number) {
					itsLoop = true;
					break;
				}
			}
			if (itsLoop)
				continue;

			Open.push_back(new AStarNode(curr->node->children[i], curr->cost + curr->node->ToChild(i).second));
		}

		//for (int i = 0; i < Open.size(); ++i) {
		//	std::cout << Open.at(i)->node->number << " ";
		//}
		//std::cout << std::endl;
		//std::getchar();

		current = steady_clock::now();
	}

	return make_pair(nullptr, 0.0);
}

int AStar::FindMin() {
	int min = abs(End - Open.at(0)->node->number) + Open.at(0)->cost, minI = 0;

	for (int i = 1; i < Open.size(); ++i) {
		if (min > (abs(End - Open.at(i)->node->number) + Open.at(i)->cost)) {
			min = abs(End - Open.at(i)->node->number) + Open.at(i)->cost;
			minI = i;
		}
	}

	return minI;
}