#include "stdafx.h"
#include <vector>
#include <map>
#include <iostream>

using namespace std;


class NodeT{
public:
	int data;
	struct NodeT* left;
	struct NodeT* right;
	NodeT(int d):data(d){
		left = NULL;
		right = NULL;
	}
};


NodeT* CreateTree(vector<int> &inorder, vector<int>&preorder);
//double findMedian(int A[], int B[], int l, int r, int nA, int nB);
double findMedianSortedArrays(int A[], int n, int B[], int m);
int maxSubArraySum(vector<int> A);
void maxSubArraySum(int A[], int l, int h, int& lMost, int& rMost, int& sumArr);