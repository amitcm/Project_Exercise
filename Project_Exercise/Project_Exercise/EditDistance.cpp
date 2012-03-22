#include "stdafx.h"
#include<stdio.h>
#include<string>
using namespace std;

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
				Edit[i][j] = max(max(Edit[i-1][j] , Edit[i][j-1]), Edit[i-1][j-1] + 1); //Edit[i][j] = Edit[i-1][j-1] + 1;
			else																				
				Edit[i][j] = max(max(Edit[i-1][j] , Edit[i][j-1] ), Edit[i-1][j-1]); //max(Edit[i-1][j] , Edit[i][j-1]);
			/*Edit Distance*/
			/*Edit[i][j] = min(min(Edit[i-1][j] + 1 , Edit[i][j-1] + 1) , Edit[i-1][j-1]);	
			else
				Edit[i][j] = max(max(Edit[i-1][j] + 1 , Edit[i][j-1] + 1), Edit[i-1][j-1] + 1);*/
		}
	}

	printMatrix(m+1,n+1);

	return Edit[m][n];
}

int main_mine()
{
	char* s = "abracadabra";
	char* t = "abbababa";
	printf("%d",EditDistance(s, t));
	return 0;
}