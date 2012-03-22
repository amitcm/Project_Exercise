#include <stdio.h>
#include "stdafx.h"

#define INT_N 1000

int main()
{
	//double Mat[][] = new double[INT_N][INT_N];

	for(int i = 0; i < INT_N; i++)
		for(int j = 0; j < INT_N; j++)
			Mat[i][j] = i + j;
	return 0;
}