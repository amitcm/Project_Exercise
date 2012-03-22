#include <fstream>
#include <iostream>
#include <deque>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

struct BinaryTree {
	BinaryTree *left, *right;
	int data;
	BinaryTree(int val) : left(NULL), right(NULL), data(val) { }
};

// Find the maximum height of the binary tree
int maxHeight(BinaryTree *p) ;

// Convert an integer value to string
string intToString(int val) ;

// Print the arm branches (eg, /    \ ) on a line
void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<BinaryTree*>& nodesQueue, ostream& out) ;

// Print the branches and node (eg, ___10___ )
void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<BinaryTree*>& nodesQueue, ostream& out) ;

// Print the leaves only (just for the bottom row)
void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<BinaryTree*>& nodesQueue, ostream& out) ;

// Pretty formatting of a binary tree to the output stream
// @ param
// level  Control how wide you want the tree to sparse (eg, level 1 has the minimum space between nodes, while level 2 has a larger space between nodes)
// indentSpace  Change this to add some indent space to the left (eg, indentSpace of 0 means the lowest level of the left node will stick to the left margin)
void printPretty(BinaryTree *root, int level, int indentSpace, ostream& out);

void PrettyBinaryTree();