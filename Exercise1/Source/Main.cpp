#include <iostream>
#include <fstream>
#include <string>
#include "BreadthFirst.h"
#include "TreeNode.h"
#include "DepthFirst.h"
#include "BestFirst.h"
#include "AStar.h"
using std::string;
using std::ofstream;

void WriteResult(pair<stack<TreeNode*>, int> &ResultingStack, string pResultFileName);

int main(int argc, char* argv[]) {
	if (argc != 5)
		return -1;

	int StartingNumber, EndingNumber;
	double resultTimeSec = 0.0;
	pair<TreeNode*, double> result;
	string ResultFileName;
	TreeNode *root, *ResultNode = nullptr;
	pair<stack<TreeNode*>, int> ResultPath;

	//int arguments[10][2]{
	//	779, 55,
	//	991, 242,
	//	985, 835,
	//	257, 999,
	//	22, 798,
	//	480, 344,
	//	77, 400,
	//	182, 261,
	//	775, 1010,
	//	640, 771
	//};

		StartingNumber = strtol(argv[2], NULL, 10);
		EndingNumber = strtol(argv[3], NULL, 10);
		ResultFileName = argv[4];
		//ResultFileName = "Solution" + string(argv[1]) + char('0' + 9) + ".txt";
		//StartingNumber = arguments[9][0];
		//EndingNumber = arguments[9][1];

		root = new TreeNode(StartingNumber, nullptr, -1);

		if (string(argv[1])._Equal("breadth")) {
			BreadthFirst bf(StartingNumber, EndingNumber, root);
			result = bf.Find();
		}
		else if (string(argv[1])._Equal("depth")) {
			DepthFirst df(StartingNumber, EndingNumber, root);
			result = df.Find();
		}
		else if (string(argv[1])._Equal("best")) {
			BestFirst bf(StartingNumber, EndingNumber, root);
			result = bf.Find();
		}
		else if (string(argv[1])._Equal("astar")) {
			AStar af(StartingNumber, EndingNumber, root);
			result = af.Find();
		}


		if (result.first == nullptr) {
			std::cout << "Failure" << std::endl;
			return -1;
		}

		std::cout << result.second / 1000.0;
		ResultPath = result.first->Retrace();
		WriteResult(ResultPath, ResultFileName);

	return 0;
}

void WriteResult(pair<stack<TreeNode*>, int> &ResultingStack, string pResultFileName) {
	int N = 0, C = 0;
	string instruction;
	TreeNode* curr;
	ofstream of;

	N = ResultingStack.first.size();
	C = ResultingStack.second;

	
	of.open(pResultFileName, std::ios::out);
	if (!of.is_open()) {
		std::cout << "Error opening file" << std::endl;
		return;
	}

	of << N << ", " << C << std::endl;

	while (!ResultingStack.first.empty()) {
		curr = ResultingStack.first.top();
		switch (curr->operation) {
		case 0:
			instruction = "increase";
			break;
		case 1:
			instruction = "decrease";
			break;
		case 2:
			instruction = "double";
			break;
		case 3:
			instruction = "half";
			break;
		case 4:
			instruction = "square";
			break;
		case 5:
			instruction = "root";
			break;
		default:
			instruction = "nothing";
			break;
		}

		of << instruction << " " << curr->parent->number << " " << curr->parent->ToChild(curr->operation).second << std::endl;
		ResultingStack.first.pop();
	}

	of.close();
}