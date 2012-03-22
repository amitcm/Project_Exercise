#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <new>

using namespace std;

int arr[10][100];

// Returns the length of longest suffix of s_1 which match with prefix of s_2.
int findOverlap(string s_1, string s_2)
{
	int len = 0, i = 0;
	for ( i = 0; i < s_2.size(); i++ )
	{
		len = s_1.rfind(s_2.substr(0, s_2.size() - i));
		if (len != -1)
		{
			if(i == len)
				return (s_2.size() - len);
		}
	}
	return 0;
}

void GreedySuperString(vector<string> vStr)
{
	
	int j = 0;
	for(int i = 0; i < vStr.size(); i++)
	{
		for(int j = 0; j < vStr.size(); j++)
		{
			if( i != j)
			{
				int val = findOverlap(vStr[i], vStr[j]);
				arr[i][j] = val;
			}
			else
			{
				arr[i][j] = 0;
			}
		}
	}
}

int main1()
{
	freopen("strings.in","r",stdin);
	
	string str;
	char ch;
	int i = 0;
	vector<string> vStr;
	vector<int> OLCount;
	
	while(i < 5)
	{
			scanf("%c", &ch); 
			if (ch == '\n')
			{
				vStr.push_back(str);
				str.clear();
				i++;
			}			
			else
				str.append(1, ch);
	}
	for(i=0; i < vStr.size(); i++) 
		cout << vStr[i] << endl;

	GreedySuperString(vStr);

	for(int i = 0; i < vStr.size(); i++)
	{
		for(int j = 0; j < vStr.size(); j++)
		{
			printf("%d\t", arr[i][j]);
			OLCount.push_back(arr[i][j]);
		}
		printf("\n");
	}

	//OLCount.
	

	//MaxValueRow();
	int sum = 0, temp = 0, index = 0;
	vector<int> vMatrix;
	for(int i = 0; i < vStr.size(); i++)
	{
		for(int j = 0; j < vStr.size(); j++)
		{
			vMatrix.push_back(arr[i][j]);
			sum += arr[i][j];
		}
		if (temp < sum)
		{
			temp = sum;
			index = i;
		}
		sum = 0;
	}
	printf("%d", index);
		
	//int max = max();

	string strFinal = "";
	strFinal.append(vStr.at(index));
	for(int j = 0; j < vStr.size(); j++)
	{
		if(index != j)
			strFinal.append(vStr.at(j).substr(arr[index][j], vStr.at(j).size()));
	}


	return 0;
}