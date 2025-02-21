#include "DepthFirst.h"
#include "TreeNode.h"
#include <iostream>
#include <cmath>

DepthNode::DepthNode(TreeNode* node, int pCurrOperations)
	:treeNode(node), currOperation(pCurrOperations)
{
}

DepthNode::~DepthNode() {
	treeNode->~TreeNode();
	treeNode = nullptr;
	delete this;
}

DepthFirst::DepthFirst(int S, int E, TreeNode* root) 
	:Start(S), End(E)//, pCurr(0)
{
	myStack.push(new DepthNode(root, 0));
	//p[0] = new DepthNode(root, 0);
}

pair<TreeNode*, double> DepthFirst::Find() { //Stack.top().treeNode;
	int recordedDistance = std::abs(End - Start);
	bool secondTime = false, backwards = false;
	DepthNode* curr = myStack.top();
	steady_clock::time_point start = steady_clock::now(), current = steady_clock::now();

	while (steady_clock::duration(current - start) <= std::chrono::seconds(60)) {
		if (curr->treeNode == nullptr) //p[pCurr]
			continue;
		if (curr->treeNode->number == End) {
			//std::cout << curr->treeNode->number;
			//return curr->treeNode;
			if (curr->treeNode->number == End) {
				double dur = std::chrono::duration_cast<std::chrono::milliseconds>(current - start).count();
				return make_pair(curr->treeNode, dur);
			}
		}

		if (std::abs(End - curr->treeNode->number) > recordedDistance) {
			//std::cout << "[Check]" << std::abs(End - curr->treeNode->number) << " " << recordedDistance << std::endl;
			if (secondTime) {
				//pCurr = !pCurr;
				//++p[pCurr]->currOperation;
				do {
					//std::cout << "[Check]" << curr->treeNode->number << std::endl;
					//curr->~DepthNode();
					//std::cout << "[Check]" << curr->treeNode->number << std::endl;
					myStack.pop();
					curr = myStack.top();
					++(curr->currOperation);

					if (myStack.empty()) {
						return make_pair(nullptr, 0.0);
					}
				} while (curr->currOperation >= 6);

				backwards = true;
				secondTime = false;
				continue;
			}
			//std::cout << "Second Time: " << secondTime << std::endl;
			recordedDistance = std::abs(End - curr->treeNode->number);
			secondTime = true;
		}

		if (!backwards)
			curr->treeNode->Expand();
		else
			backwards = false;
		
		//std::cout << "[Check]" << curr->treeNode->number << " " << secondTime << std::endl;
		myStack.push(new DepthNode(curr->treeNode->children[curr->currOperation], curr->currOperation));
		curr = myStack.top();

		current = steady_clock::now();
	}
	return make_pair(nullptr, 0.0);
}