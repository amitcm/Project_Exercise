#include "stdafx.h"
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int a[2005][2005];



bool testPoint(vector <string> vertices, int testPointX, int testPointY) 
{
	testPointX += 1000;
	testPointY += 1000;

	int i;

	for (i = 0; i < vertices.size()-1; i ++)
	{
		int x0, y0, x1, y1;

		istringstream it(vertices[i]);
		it >> x0 >> y0;
		istringstream it2(vertices[i+1]);
		it2 >> x1 >> y1;

		x0 += 1000;
		y0 += 1000;
		x1 += 1000;
		y1 += 1000;

		if (x0 == x1)
		{
			int y = y0 < y1 ? y0 : y1;
			int Y = y0 > y1 ? y0 : y1;

			for (int j = y; j <= Y; j ++)
				a[x0][j] = 1;
		}
		else
		{
			int x = x0 < x1 ? x0 : x1;
			int X = x0 > x1 ? x0 : x1;        

			for (int j = x; j <= X; j ++)
				a[j][y0] = 1;
		}
	}

	int x0, y0, x1, y1;
	istringstream it(vertices[0]);
	it >> x0 >> y0;
	istringstream it2(vertices[vertices.size()-1]);
	it2 >> x1 >> y1;

	x0 += 1000;
	y0 += 1000;
	x1 += 1000;
	y1 += 1000;

	if (x0 == x1)
	{
		int y = y0 < y1 ? y0 : y1;
		int Y = y0 > y1 ? y0 : y1;

		for (int j = y; j <= Y; j ++)
			a[x0][j] = 1;
	}
	else
	{
		int x = x0 < x1 ? x0 : x1;
		int X = x0 > x1 ? x0 : x1;        

		for (int j = x; j <= X; j ++)
			a[j][y0] = 1;
	}

	//bool bret = false; 
	//string ret = "";
	if (a[testPointX][testPointY] == 1)
	{
		//ret += "BOUNDARY";
		return true;
	}

	int nl1 = 0;

	for (i = testPointX; i < 2005; i ++)
		if (a[i][testPointY] == 1) nl1 ++;

	if (nl1 % 2 == 0)
	{

		int nl2 = 0;

		for (i = testPointY; i < 2005; i ++)
			if (a[testPointX][i] == 1) nl2 ++;

		if (nl2 % 2 == 0)
		{

			//ret += "EXTERIOR";
			return false;
		}
		else
		{
			//ret += "INTERIOR";
			return true;
		}
	}

	else
	{
		//ret += "INTERIOR";
		return true;
	}
	return false;
}
