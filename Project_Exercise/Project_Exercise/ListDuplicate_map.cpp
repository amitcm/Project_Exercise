#include "stdafx.h"
#include <iostream>
#include <map>
#include <limits>
using namespace std;
#include <vector>
#include <stack>
#include <list>

struct BinaryTree
{
	int data;
	struct BinaryTree* left;
	struct BinaryTree* right;
};

// Find the largest BST subtree in a binary tree.
// If the subtree is a BST, return total number of nodes.
// If the subtree is not a BST, -1 is returned.
int findLargestBSTSubtree(BinaryTree *p, int &min, int &max,
	int &maxNodes, BinaryTree *& largestBST) {
		if (!p) return 0;
		bool isBST = true;
		int leftNodes = findLargestBSTSubtree(p->left, min, max, maxNodes, largestBST);
		int currMin = (leftNodes == 0) ? p->data : min;
		if (leftNodes == -1 ||
			(leftNodes != 0 && p->data <= max))
			isBST = false;
		int rightNodes = findLargestBSTSubtree(p->right, min, max, maxNodes, largestBST);
		int currMax = (rightNodes == 0) ? p->data : max;
		if (rightNodes == -1 ||
			(rightNodes != 0 && p->data >= min))
			isBST = false;
		if (isBST) {
			min = currMin;
			max = currMax;
			int totalNodes = leftNodes + rightNodes + 1;
			if (totalNodes > maxNodes) {
				maxNodes = totalNodes;
				largestBST = p;
			}
			return totalNodes;
		} else {
			return -1;   // This subtree is not a BST
		}
}

BinaryTree* findLargestBSTSubtree(BinaryTree *root) {
	BinaryTree *largestBST = NULL;
	int min, max;
	int maxNodes = INT_MIN;
	findLargestBSTSubtree(root, min, max, maxNodes, largestBST);
	return largestBST;
}

int main_List ()
{
	stack<int> mystack;
	vector<stack<int>> myStackVector;
	stack<stack<int>>stackOfStack;

	mystack.push(12);
	mystack.push(12);
	mystack.push(12);
	mystack.push(12);
	mystack.push(12);
	mystack.push(12);
	mystack.push(12);
	mystack.push(12);
	myStackVector.push_back(mystack);
	list<stack<int>>stackList;


	map<int,int> mymap;
	map<int,int>::iterator it;
	//pair<map<char,int>::iterator,bool> ret;

	//((INT_MAX/3) - (INT_MAX/11)) * 2 array size is Okay

	int arr[10][2] = {{5, 1}, {5, 2}, {15, 1}, {52, 1}, {51, 1}, {35, 1}, {45, 1}, {65, 1}, {75, 1}, {55, 1}, };
	it=mymap.begin();
	for(int i = 0; i < 10; i++)
	{
		mymap[arr[i][0]] = arr[i][1];
	}

	// showing contents:
	cout << "mymap contains:\n";
	for ( it=mymap.begin() ; it != mymap.end(); it++ )
		cout << (*it).first << " => " << (*it).second << endl;

	return 0;
}