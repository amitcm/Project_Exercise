#include <iostream>
#include <iomanip>
#include "stdafx.h"
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int **M;
template <class RAI1,class RAI2>


void fastLongestPalindromes(RAI1 seq,RAI1 seqEnd,RAI2 out)
{
	int seqLen=seqEnd-seq;
	int i=0,j,d,s,e,lLen,k=0;
	int palLen=0;
	while (i<seqLen)
	{
		if (i>palLen && seq[i-palLen-1]==seq[i])
		{
			palLen+=2;
			i++;
			continue;
		}
		out[k++]=palLen;
		s=k-2;
		e=s-palLen;
		bool b=true;
		for (j=s; j>e; j--)
		{
			d=j-e-1;
			if (out[j]==d)
			{
				palLen=d;
				b=false;
				break;
			}
			out[k++]=min(d,out[j]);
		}
		if (b)
		{
			palLen=1;
			i++;
		}
	}
	out[k++]=palLen;
	lLen=k;
	s=lLen-2;
	e=s-(2*seqLen+1-lLen);
	for (i=s; i>e; i--)
	{
		d=i-e-1;
		out[k++]=min(d,out[i]);
	}
}

bool ispalindrome(const char *s, int i, int j)
{
    while (i < j) // Ignore middle char in odd length strings
        if (s[i++] != s[j--])
            return false;
    return true;
}

int minpalindromes(const char *s)
{
    int i, j, k, len;
    int n = strlen(s);
     // Allocate n x n array (not shown)

	//int **array;
	M = (int **) calloc(n, sizeof(int *));
	if(M == NULL)
		{
		fprintf(stderr, "out of memory\n");
		return 0;
		}
	for(i = 0; i < n; i++)
		{
		M[i] = (int *)calloc(n, sizeof(int));
		if(M[i] == NULL)
			{
			fprintf(stderr, "out of memory\n");
			return 0;
			}
		}

    for (len = 1; len <= n; len++) // Bottom-up: Start with short substrings.
        for (i = 0; i <= n - len; i++) {
            j = i + len - 1;
            if (ispalindrome(s, i, j))
                M[i][j] = 1;
            else {
                M[i][j] = len; // Assume worst-case. Improve on it below.
                for (k = i; k < j; k++) { // Consider splitting string at each position.
                    int sum = M[i][k] + M[k+1][j];
                    if (sum < M[i][j])
                        M[i][j] = sum; // Save minimum value
                }
            }
        }
    return M[0][n-1]; // Return result for entire string
}

int main1()
{
	string s = "abba";
	minpalindromes((const char *)s.c_str());
	for(int i = 0; i < s.length(); i++)
	{
		for(int j = 0; j < s.length(); j++)
		{
			printf("%d\t",M[i][j]);
		}
		printf("\n");
	}
	/*freopen("string.in","r",stdin);
	
	char ch;
	
	scanf("%c",&ch);
	while(ch != '\n')
	{
		s.append(1, ch);
		scanf("%c",&ch);
	}*/
	//cin >> s;
	vector<int> V(2*s.length()+1);
	fastLongestPalindromes(s.begin(),s.end(),V.begin());
	int best=0;
	printf("[");
	for (int i=0; i<V.size(); i++)
	{
		if (i>0)
			printf(", ");
		printf("%d", V[i]);
		best=max(best,V[i]);
	}
	printf("] \n Longest palindrome has length %d \n" );
	return 0;
}