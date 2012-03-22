#include <iostream>
#include "stdafx.h"

 int OptimizedBinarySearch(int A[], int N, int value) 
 {
       int low = 0;
       int high = N;
	   int mid = 0;
       while (low < high) {
           mid = low + (high - low)/2;
           if (A[mid] < value)
               low = mid + 1; 
           else
                //can't be high = mid-1: here A[mid] >= value,
                //so high can't be < mid if A[mid] == value
                high = mid; 
       }
       // high == low, using high or low depends on taste 
       if ((low < N) && (A[low] == value))
           return low; // found
       else
           return -1; // not found  
   }

int main()
{

//	int arr[] = {4,3,1,2,4};
//	int i, N = 5;
//	int dupe = 0;
//	for(i=0; i<N; i++) 
//	{
//		dupe = dupe ^ arr[i] ^ i; //value of Indices are XORed 0 ^ 1 ^ 2 ^ 3 ^ 4 along with 
//								  // Numbers from 1 to N(4 here) are XORed. Same numbers are canceled
//					//Leaving only the duplicate. When there is no duplicate the result is Zero.
//	}
//// dupe has the duplicate.
//	printf(" Final Value: %d", dupe);
//
//	int A[] = {4,13,21,22,41, 54, 23};
//	int n = 7;
//	int result = OptimizedBinarySearch(A, n, 21);
//	printf("\n\n%d",result);


}