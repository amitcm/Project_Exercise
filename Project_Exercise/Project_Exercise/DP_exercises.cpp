#include "stdafx.h"
#include "DP_exercises.h"
using namespace std;

// Fibonacci Bottom up
int Fibonacci(int n)
{
	int arrFib[MAX] = {0, };
	arrFib[0] = 0;
	arrFib[1] = 1;
	if (n <= 2)
		return 1;
	else
	{
		for(int i = 2; i < n; i++)
		{
			arrFib[i] = arrFib[i-1] + arrFib[i-2];
		}
	}
	return arrFib[n-1];
}

/*Given a list of N coins, their values (V1, V2, ... , VN), and the total sum S. 
Find the minimum number of coins the sum of which is S (we can use as many coins of one type as we want), 
or report that it's not possible to select coins in such a way that they sum up to S. */

int CoinSelection(int coins[], int value[], int n, int S)
{
	int arr[MAX][MAX];
	// Initialization
	for (int i = 0; i < n; i++){
		arr[0][i] = 0;
		arr[i][0] = 0;
	}
	return 1;
}

/*Knapsack problem (Using items only once)
Given: 
	a list of weights
	a list of values
	max weight that the knapsack can withstand
	
Problem:
	1. Find out if it is possible to fill the knapsack while taking a weight only once
	2. Find the min value of such a possible weight selection
	3. Do it when we can use one weight multiple times i.e, there are infinite source of weights*/

	/* Observations:
	Either take the current item/weight or not.
	1. Leave the weight: The value remains same and we are gonna reuse the value for this 'w' from the previous subset
						 The subset is untouched while consider current item/weight. Therefore, KS[i-1][w] => KS of current 'w' till last subset.
						 'i' denotes the item number until which we are using it for defining subset.
	2. Take the weight:  Add the value of current item/weight to previous best value we recorded for current 'w' minus 'the weight'.

	int weights[4] = {5, 4, 6, 3};
	int values[4] = {10, 40, 30, 50};

	Basically, our intent here is to compute optimal 'max value' for all possible 'w's using a 'subset of items'.
	if we want max value for a W = 7 using only first 3 items[in item/weight array] then we just need to look at KS[3][7]

	0       1       2       3       4       5       6       7       8       9       10
	-----------------------------------------------------------------------------------
	0       0       0       0       0       0       0       0       0       0       0 |	=> 0
	0       0       0       0       0       0       10      10      10      10      10|	=> 10 - 5
	0       0       0       0       0       40      40      40      40      40      50|	=> 40 - 4
	0       0       0       0       0       0       0       40      40      40      50|	=> 30 - 6
	0       0       0       0       50      50      50      50      50      50      90|	=> 50 - 3

	what does '90' signify?
	Using a subset of {items}, what is the max value we get with in a weight limit. => here we get max value = 90 using a subset of {weights[]}
	with in limit of 10 unit of weights. This is what KS[4][10] signifies. Alright!

	
	*/

int KnapsackUsingItemsOnce(int weights[], int values[], int n, int W)
{
	int KS[MAX][MAX] = {{0}, };
	// Initialization
	for (int i = 0; i <= W; i++){
		KS[0][i] = 0;
	}
	/*for (int i = 0; i <= n; i++){
		KS[i][0] = 0;
	}*/
	for (int i = 1; i <= n; i++){
		for(int w = 0; w <= W; w++){
			if(weights[i-1] < w){				///*(w - weights[i-1] >= 0 ?*/ is handled here
				KS[i][w] = max((values[i-1] + KS[i-1][/*(w - weights[i-1] >= 0 ?*/ w - weights[i-1] /*: 0)*/ ]), KS[i-1][w]);
			}
		}
	}
	PrintMatrixNormalView(KS, n+1, W+1);
	return KS[n][W];
}

	/*
		0       1       2       3       4       5       6       7       8       9       10
		-----------------------------------------------------------------------------------
		0       0       0       0       0       0       0       0       0       0       0 |	=> 0
		0       0       0       0       0       0       10      10      10      10      10|	=> 10 - 5
		0       0       0       0       0       40      40      40      40      40      50|	=> 40 - 4
		0       0       0       0       0       0       0       40      40      40      50|	=> 30 - 6
		0       0       0       0       50      50      50      50      50      50      90|	=> 50 - 3

		1       0       0       0       0       0       0       0       0       0       0
		1       1       1       1       1       1       0       0       0       0       0
		1       1       1       1       1       1       1       1       1       1       0
		1       1       1       1       1       1       1       1       1       1       1
		1       1       1       1       1       1       1       1       1       1       1
		1
	*/

bool KnapsackUsingItemsOnceBool(int weights[], int values[], int n, int W)
{
	int KS[MAX][MAX] = {{0}, };
	// Initialization
	for (int i = 0; i <= W; i++){
		KS[0][i] = 0;
	}
	for (int i = 0; i <= n; i++){
		KS[i][0] = 1;
	}
	for (int i = 1; i <= n; i++){
		for(int w = 1; w <= W; w++){
				KS[i][w] = (KS[i-1][w - weights[i-1]] || KS[i-1][w]);
		}
	}
	PrintMatrixNormalView(KS, n+1, W+1);
	return KS[n][W];
}




/*Compute the binomial coefficients*/
/*
The recurrence relation implicit in this is that
n C k = (n − 1) C (k − 1) + (n − 1) C k
Why does this work? Consider whether the nth element appears in one of the
n C k subsets of k elements. If so, we can complete the subset by picking k−1 other
items from the other n − 1. If not, we must pick all k items from the remaining
n − 1. There is no overlap between these cases, and all possibilities are included,
so the sum counts all k subsets.

Explanation: Consider nth element. there are two subsets that either include nth element or it doesn't.
(n − 1) C (k − 1) contains nth element while (n − 1) C k does not. The later subset choose all k elements from
(n-1) element excluding nth element.
n C k is choosing k elements from n elements' set.

n c k = (n − 1) C (k − 1) + (n − 1) C k
		= [(n − 2) C (k − 2) + (n − 2) C (k - 1)] + [(n − 2) C (k − 1) + (n − 2) C k]
		= 

		1       
		0       1       
		0       1       1       
		0       1       2       1       
		0       1       3       3       1       
		0       1       4       6       4       1     
		0		1		5		10		10		5		1
		0		1		6		15		20		15		6		1

Each number is the sum of the two numbers directly above it. 16 = 11 + 5, 7 = 4 + 3, 2 = 1 + 1 and so on..

*/

int ComputeBinomial(int n, int k)
{
	n++;
	k++;
	int arrBC[MAX][MAX] = {{0}, };
	for (int i = 0; i <= n; i++){
		arrBC[0][i] = 1;
		arrBC[i][i] = 1;
	}
	for(int i = 1; i <= n; i++)	{
		for(int j = 1; j < min(i, k); j++)		{
			arrBC[i][j] = arrBC[i-1][j-1] + arrBC[i-1][j];
		}
	}
	PrintMatrixNormalView(arrBC, n+1, n+1);
	return arrBC[n][k];
}

int Edit[18][18];

void printMatrix(int i, int j)
{
	for(int l = 0; l < i; l++)
		{
			for(int p = 0; p < j; p++)
			{
				printf("%d\t", Edit[l][p]);
			}
			printf("\n");
		}
}

int EditDistance(char* s, char* t)
{
	int m = strlen(s);
	int n = strlen(t);
	int j, i;
	for (j = 0; j <= n; j++)
		Edit[0][j] = 0;
	for (i = 0; i <= m; i++)
		Edit[i][0] = 0;

	printMatrix(m+1,n+1);

	for (i = 1; i <= m; i++)
	{
		//Edit[0][i] = i;
		for (j = 1; j <= n; j++)
		{
			if (s[i-1] == t[j-1])
				//Next 3 lines for LCS. Refer Wiki for most vivid example, tracing and ... 
				Edit[i][j] = /*max(max(Edit[i-1][j] , Edit[i][j-1]), Edit[i-1][j-1] + 1);*/ Edit[i][j] = Edit[i-1][j-1] + 1;
			else																				
				Edit[i][j] = /*max(max(Edit[i-1][j] , Edit[i][j-1] ), Edit[i-1][j-1]);*/ max(Edit[i-1][j] , Edit[i][j-1]);
			/*Edit Distance*/
			/*Edit[i][j] = min(min(Edit[i-1][j] + 1 , Edit[i][j-1] + 1) , Edit[i-1][j-1]);	
			else
				Edit[i][j] = max(max(Edit[i-1][j] + 1 , Edit[i][j-1] + 1), Edit[i-1][j-1] + 1);*/
		}
	}

	printMatrix(m+1,n+1);

	return Edit[m][n];
}

/* Finds longest strictly increasing subsequence. O(n log k) algorithm. */
void find_lis(vector<int> &a, vector<int> &b)
{
	// b is the vector of index
	vector<int> p(a.size());
	int u, v;
	if (a.empty()) 
		return;
	b.push_back(0);
	for (size_t i = 1; i < a.size(); i++) 
	{
		// If next element a[i] is greater than last element of current longest subsequence a[b.back()], 
		//just push it at back of "b" and continue
		if (a[b.back()] < a[i]) 
		{
			p[i] = b.back();
			b.push_back(i);
			continue;
		}
		// Binary search to find the smallest element referenced by b which is just bigger than a[i]
		// Note : Binary search is performed on b (and not a). Size of b is always <=k and hence contributes O(log k) to complexity.    
		for (u = 0, v = b.size()-1; u < v; ) 
		{
			int c = (u + v) / 2;
			if (a[b[c]] < a[i]) 
				u = c + 1; 
			else 
				v = c;
		}
		// Update b if new value is smaller then previously referenced value 
		if (a[i] < a[b[u]]) 
		{
			if (u > 0) p[i] = b[u-1];
			b[u] = i;
		}	
	}
	for (u = b.size(), v = b.back(); u--; v = p[v]) 
		b[u] = v;
}

const int MAX_N = 100;
 
void printMoves(int P[][MAX_N], int A[], int N) {
	int sum1 = 0, sum2 = 0;
	int m = 0, n = N-1;
	bool myTurn = true;
	while (m <= n) {
		int P1 = P[m+1][n]; // If take A[m], opponent can get...
		int P2 = P[m][n-1]; // If take A[n]
		cout << (myTurn ? "I" : "You") << " take coin no. ";
		if (P1 <= P2) {
			cout << m+1 << " (" << A[m] << ")";
			m++;
		} else {
			cout << n+1 << " (" << A[n] << ")";
			n--;
		}
		cout << (myTurn ? ", " : ".\n");
		myTurn = !myTurn;
	}
	cout << "\nThe total amount of money (maximum) I get is " << P[0][N-1] << ".\n";
}


// PIZZA PICKING / COIN SELECTION GAME

/*
Therefore, if you choose Ai, the maximum amount you can get is:

P1 = Sum{Ai ... Aj} - P(i+1, j)

Similarly, if you choose Aj, the maximum amount you can get is:

P2 = Sum{Ai ... Aj} - P(i, j-1)

Therefore,

P(i, j) = max { P1, P2 }
        = max { Sum{Ai ... Aj} - P(i+1, j),
                Sum{Ai ... Aj} - P(i, j-1) }
In fact, we are able to simplify the above relation further to (Why?):

P(i, j) = Sum{Ai ... Aj} - min { P(i+1, j), P(i, j-1) }


			BETTER SOLUTION:

This solution which does not compute ans store results of Sum{Ai … Aj}, 
therefore is more efficient in terms of time and space.

the maximum amount you can get when you choose Ai is:

P1 = Ai + min { P(i+2, j), P(i+1, j-1) }
Similarly, the maximum amount you can get when you choose Aj is:

P2 = Aj + min { P(i+1, j-1), P(i, j-2) }
Therefore,

P(i, j) = max { P1, P2 }
        = max { Ai + min { P(i+2, j),   P(i+1, j-1) },
                Aj + min { P(i+1, j-1), P(i,   j-2) } }


Memoization provides an efficient way by avoiding re-computations using intermediate results stored in a table. 
Below is the code which runs in O(n^2) time and takes O(n^2) space.

Reference: http://www.leetcode.com/2011/02/coins-in-line.html

*/

int maxMoney(int A[], int N) {
	int P[MAX_N][MAX_N] = {0};
	int a, b, c;
	for (int i = 0; i < N; i++) {
		for (int m = 0, n = i; n < N; m++, n++) {
			assert(m < N); 
			assert(n < N);

			a = ((m+2 <= N-1) ? P[m+2][n] : 0);
			b = ((m+1 <= N-1 && n-1 >= 0) ? P[m+1][n-1] : 0);
			c = ((n-2 >= 0) ? P[m][n-2] : 0);
			
			P[m][n] = max(A[m] + min(a, b), A[n] + min(b, c));
		}
	}
	printMoves(P, A, N);
	return P[0][N-1];
}