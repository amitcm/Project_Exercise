#include "stdafx.h"
#include "Helper.h"

void PopulateMatrixWithDefault(int arr[MAX][MAX], int m, int n)
{
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			arr[i][j] = i * 1000 + j;
		}
	}
}

void PrintDiagonalLowerLeftMatrix(int arr[][MAX], int m, int n)
{
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j <= i; j++)
		{
			printf("%d\t", arr[i][j]);
		}
		printf("\n");
	}
}

void PrintMatrixNormalView(int arr[][MAX], int m, int n)
{
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			printf("%d\t", arr[i][j]);
		}
		printf("\n");
	}
}