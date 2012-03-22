#include <iostream>
#include "stdafx.h"
#include <string>
using namespace std;
int AlienSymbol(char* input)
{
	//Find the number distinct symbols
	//Assign a value to each symbol according to their possition
	//
	string CharSetDistinct(" ");
	string CharSet(" ");
	char ch;
	int k = 0;
	for(int n = 0; *(input + n) != '\0' ;)
	{
		if(CharSetDistinct.find(*(input + n)))
			k++;
		CharSet.append("");
	}

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