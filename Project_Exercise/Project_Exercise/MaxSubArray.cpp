#include "stdafx.h"
#include <string>
#include "stdio.h"
#include <iostream>
#include <utility>
using namespace std;
#define MAX 20

//int arr[MAX] = {0, };

//bool recurLeft(int arr, int low, int mid, );
//bool recurRight(int arr, int mid, int high, );
//bool crossSum(int arr, int low, int mid, int high);

bool MaxSubArray(int arr, int n, int &lowMSA, int &highMSA)
{
	int low = 0, high = 0, mid = 0;
	int leftSum = 0, rightSum = 0, crossSum = 0;
	if( n <= 0)
		return false;
	else 
	{
		high = n - 1;
		mid = low + (high - low)/2;

		//recurLeft(arr, low, mid, );
		//recurRight(arr, mid + 1, high, );
		//crossSum(arr, low, mid, high);
		return true;
	}
}

int main12()
{

	return 0;
}