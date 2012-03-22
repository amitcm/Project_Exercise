// myProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int BinarySearchOptimized(int arr[], int length, int key)
{
	int l = 0, r = length-1;
	int mid;
	while( l != r)
	{
		mid = (l+r)/2;
		if (arr[mid] > key)
			r = mid - 1;
		else
			l = mid;
	}
	if( arr[mid] == key)
		return mid;
	else
		if( arr[mid-1] == key)
			return mid - 1;
		else
			return -1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int length = 15;
	int arr[15] = {3, 5, 15, 56, 78, 123, 456, 1000, 1004, 1005, 1006, 1007, 3567, 23455, 56789,};
	int key = 78;
	

	printf("Key Found at: %d", BinarySearchOptimized(arr, length, key));
	return 0;
}

