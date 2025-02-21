#include "TreeNode.h"

TreeNode::TreeNode(int data, TreeNode* parent, int pOperation) 
: number(data), parent(parent), operation(pOperation)
{
	for (int i = 0; i < 6; ++i) {
		children[i] = nullptr;
	}
}

TreeNode::~TreeNode() {
	//std::cout << "[Check " << operation << "] Value:" << number << std::endl;
	for (int i = 0; i < 6; ++i) {
		//std::cout << i << std::endl;
		if (children[i] != nullptr) {
			children[i]->~TreeNode();
			children[i] = nullptr;
		}
	}
	//std::cout << "[Check]" << std::endl;
	if (parent != nullptr) {
		parent->children[operation] = nullptr;
		parent = nullptr;
	}
	delete this;
}

pair<int, int> TreeNode::ToChild(int ChildNumber) {
	switch (ChildNumber)
	{
	case 0:
		return make_pair(this->number + 1, 2);
		break;
	case 1:
		if (this->number > 0)
			return make_pair(this->number - 1, 2);
		break;
	case 2:
		return make_pair(this->number * 2, this->number / 2 + 1);
		break;
	case 3:
		if (this->number > 0)
			return make_pair(this->number / 2, this->number / 4 + 1);
		break;
	case 4:
		return make_pair(this->number * this->number, (((this->number * this->number) - this->number) / 4) + 1);
		break;
	case 5:
		if (this->number > 1 && this->number == int(sqrt(this->number)) * int(sqrt(this->number)))
			return make_pair(sqrt(this->number), (this->number - sqrt(this->number))/ 4 + 1);
		break;
	default:
		return make_pair(-1, -1);
		break;
	}
	return make_pair(-1, -1);
}

/*
int TreeNode::CostToChild(int ChildNumber, int X) {
	switch (ChildNumber)
	{
	case 0:
		return 2;
	case 1:
		if (X > 0)
			return 2);
		break;
	case 2:
		return X / 2 + 1;
	case 3:
		if (this->number > 0)
			return make_pair(this->number / 2, this->number / 4 + 1);
		break;
	case 4:
		return make_pair(this->number * this->number, (((this->number * this->number) - this->number) / 4) + 1);
	case 5:
		if (this->number > 1 && this->number == sqrt(this->number))
			return make_pair(sqrt(this->number), (this->number - sqrt(this->number)) / 4 + 1);
		break;
	default:
		return make_pair(-1, -1);
		break;
	}
}
*/

void TreeNode::Expand() {
	for (int i = 0; i < 6; ++i) {
		if (ToChild(i).second == -1)
			continue;

		try {
			children[i] = new TreeNode(ToChild(i).first, this, i);
		}
		catch (std::bad_alloc& e) {
			std::cerr << e.what();
			exit(-2);
		}
	}
}

pair<stack<TreeNode*>, int> TreeNode::Retrace() {
	int cost = 0;
	TreeNode* curr = this;
	stack<TreeNode*> result;

	//cost += ToChild(operation).second;
	while (curr->parent != nullptr) {
		result.push(curr);
		cost += curr->parent->ToChild(curr->operation).second;
		curr = curr->parent;
		//result.push(curr);
	}
	
	return make_pair(result, cost);
}