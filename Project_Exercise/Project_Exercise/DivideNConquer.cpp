#include "stdafx.h"
#include <iostream>
#include "DivideNConquer.h"

using namespace std;
#define MAX 100

//double findMedian(int A[], int B[], int l, int r, int nA, int nB) {
//	if (l > r) 
//		return findMedian(B, A, max(0, (nA+nB)/2-nA), min(nB, (nA+nB)/2), nB, nA);
//	int i = (l + r) / 2;
//	int j = (nA + nB) / 2 - i - 1;
//	if (j >= 0 && A[i] < B[j]) 
//		return findMedian(A, B, i+1, r, nA, nB);
//	else if (j < nB-1 && A[i] > B[j+1]) 
//		return findMedian(A, B, l, i-1, nA, nB);
//	else {
//		if ( (nA + nB) % 2 == 1 ) 
//			return A[i];
//		else if (i > 0) 
//			return (A[i] + max(B[j], A[i-1])) / 2.0;
//		else 
//			return (A[i] + B[j]) / 2.0;
//	}
//}

double findMedian(int A[], int B[], int l, int r, int nA, int nB) {
	if (l > r) 
		return findMedian(B, A, max(0, (nA + nB) / 2 - nA), min(nB, (nA + nB) / 2), nB, nA);
	int i = (l + r)/2;
	int j = (nA + nB)/2 - i - 1;
	if (j >= 0 && A[i] < B[j]) 
		return findMedian(A, B, i+1, r, nA, nB);
	else if (j < nB-1 && A[i] > B[j+1]) 
		return findMedian(A, B, l, i-1, nA, nB);
	else {
		if ( (nA + nB) % 2 == 1 ) 
			return A[i];
		else if (i > 0) 
			return (A[i] + max(B[j], A[i-1])) / 2.0;
		else 
			return (A[i] + B[j]) / 2.0;
	}
}

double findMedianSortedArrays(int A[], int n, int B[], int m) {
	if (n < m) 
		return findMedian(A, B, 0, n-1, n, m);
	else 
		return findMedian(B, A, 0, m-1, m, n);
}

void maxSubArrayCrossing(int A[], int l, int m, int h, int& lMost, int& rMost, int& sumArr){
	int leftsum = INT_MIN;
	int sum = 0;
	// m is floor - noted
	for(int i = m; i >= l; i--){
		sum += A[i];
		if(sum > leftsum){
			leftsum = sum;
			lMost = i;
		}
	}
	
	int rightsum = INT_MIN;
	sum = 0;
	// m is floor - noted
	for(int i = m + 1; i <= h; i++){
		sum += A[i];
		if(sum > rightsum){
			rightsum = sum;
			rMost = i;
		}
	}
	sumArr = leftsum + rightsum;
}

void maxSubArraySum(int A[], int l, int h, int& lMost, int& rMost, int& sumArr){
	int leftl, leftr, leftsum, rightl, rightr, rightsum, crossl, crossr, crosssum;
	leftl = leftr = leftsum = rightl = rightr = rightsum = crossl = crossr = crosssum = 0;
	if(l == h){
		lMost = l;
		rMost = h;
		sumArr = A[l];
		return;
	}
	else{
		int mid = l + (h - l) / 2;
		maxSubArraySum(A, l, mid, leftl, leftr, leftsum);
		maxSubArraySum(A, mid + 1, h, rightl, rightr, rightsum);
		maxSubArrayCrossing(A, l, mid, h, crossl, crossr, crosssum);

		if(leftsum >= rightsum && leftsum >= crosssum){
			lMost = leftl;
			rMost = leftr;
			sumArr = leftsum;
			return;
		}
		else if(rightsum >= leftsum && rightsum >= crosssum){
			lMost = rightl;
			rMost = rightr;
			sumArr = rightsum;
			return;
		}
		else{
			lMost = crossl;
			rMost = crossr;
			sumArr = crosssum;
			return;
		}
	}
}

int maxSubArraySum(vector<int> A) {
	int maxsofar = 0, maxendinghere = 0, len = A.size();
	for(int i = 0; i < len; ++i) {
		maxendinghere = max(maxendinghere + A[i], 0);
		maxsofar = max(maxsofar, maxendinghere);
	}
	return maxsofar;
}

int merge_count(int arr[], int l, int h)
{
	int arr_temp[MAX];
	int count, m = 0, t;
	m = l + (h - l) / 2;
	t = m;
	while(l <= m || 1)   
	//if(arr)
	return 1;
}

int swap_count(int arr[], int l, int h)
{
	int m, count = 0;
	if( h > 1)
		m = l + (h - l) / 2;
	swap_count(arr, l, m);
	swap_count(arr, m+1, h);
	return count + merge_count(arr, l, h);
}



map<int, int> mapIn;

NodeT* buildInPre(vector<int> &inorder, vector<int>&preorder, vector<int>::iterator &in, vector<int>::iterator &pre){
	// Put a break when in or pre has iterated over
	if(!(in != inorder.end()) || !(pre != preorder.end()))
		return NULL;
	int rootVal = *pre;
	int i = mapIn[rootVal];
	NodeT *root = new NodeT(rootVal);
	root->left = buildInPre(inorder, preorder, in, pre+1);
	root->right = buildInPre(inorder, preorder, in+i+1, pre+i+1);
	return root;
}

NodeT* CreateTree(vector<int> &inorder, vector<int>&preorder){
	int n = inorder.size();
	for(int i = 0; i < n; i++)
		mapIn[inorder[i]] = i;
	vector<int>::iterator in = inorder.begin();
	vector<int>::iterator pre = preorder.begin();
	return buildInPre(inorder, preorder, in, pre);
}





//int merge(int arr[], int left[], int right[]) {
//    int i = 0, j = 0, count = 0;
//    while (i < left.length || j < right.length) {
//        if (i == left.length) {
//            arr[i+j] = right[j];
//            j++;
//        } else if (j == right.length) {
//            arr[i+j] = left[i];
//            i++;
//        } else if (left[i] <= right[j]) {
//            arr[i+j] = left[i];
//            i++;                
//        } else {
//            arr[i+j] = right[j];
//            count += left.length-i;
//            j++;
//        }
//    }
//    return count;
//}
//
//int invCount(int arr[], int n) {
//    if (n < 2)
//        return 0;
//
//    int m = (n + 1) / 2;
//    int left[] = Arrays.copyOfRange(arr, 0, m);
//    int right[] = Arrays.copyOfRange(arr, m, arr.length);
//
//    return invCount(left) + invCount(right) + merge(arr, left, right);
//}