#include "stdafx.h"
#include <algorithm>
#include "Helper.h"
#include <vector>
#include <assert.h>

using namespace std;

#define MAX 100

int Fibonacci(int n);
int CoinSelection(int coins[], int value[], int n, int S);
int KnapsackUsingItemsOnce(int weights[], int values[], int n, int W);
bool KnapsackUsingItemsOnceBool(int weights[], int values[], int n, int W);
int ComputeBinomial(int n, int k);
int EditDistance(char* s, char* t);
void find_lis(vector<int> &a, vector<int> &b);
