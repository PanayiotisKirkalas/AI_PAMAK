#include "BreadthFirst.h"
#include "TreeNode.h"

BreadthFirst::BreadthFirst(int S, int E, TreeNode* root) 
	:Start(S), End(E)
{
	Queue[0].push_back(root);
	QueueUsed = 0;

}

pair<TreeNode*, double> BreadthFirst::Find() {
	steady_clock::time_point start = steady_clock::now(), current = steady_clock::now();
	
	while (steady_clock::duration(current - start) <= std::chrono::seconds(60)) {
		for (TreeNode* node : Queue[QueueUsed])
		{
			if (node == nullptr)
				continue;
			//if (node->number == End)
			//	return node;
			if (node->number == End) {
				double dur = std::chrono::duration_cast<std::chrono::milliseconds>(current - start).count();
				return make_pair(node, dur);
			}
		}
		Queue[!QueueUsed].clear();
		for (TreeNode* node : Queue[QueueUsed])
		{
			if (node == nullptr)
				continue;

			node->Expand();
			//std::cout << "[Check]";
			//QueueUsed = !QueueUsed;
			for (TreeNode* node2 : node->children) {
				if (node == nullptr)
					continue;

				//Queue[!QueueUsed].push_back(node2);
				try {
					Queue[!QueueUsed].push_back(node2);
				}
				catch (std::bad_alloc& e) {
					std::cout << e.what() << std::endl << Queue[!QueueUsed].size() << std::endl << Queue[QueueUsed].size();
					std::cout << std::endl << node2->Retrace().first.size();
					exit(-3);
				}
			}
		}
		QueueUsed = !QueueUsed;
		current = steady_clock::now();
	}

	return make_pair(nullptr, 0.0);
}