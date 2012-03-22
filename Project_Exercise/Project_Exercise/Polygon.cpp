#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include "Polygon.h"

using namespace std;

//Compute the dot product AB ⋅ BC
int dot(int A[], int B[], int C[]){
	int AB[2];
	int BC[2];
	AB[0] = B[0]-A[0];
	AB[1] = B[1]-A[1];
	BC[0] = C[0]-B[0];
	BC[1] = C[1]-B[1];
	int dot = AB[0] * BC[0] + AB[1] * BC[1];
	return dot;
}
//Compute the cross product AB x AC
int cross(int A[], int B[], int C[]){
	int AB[2];
	int AC[2];
	AB[0] = B[0]-A[0];
	AB[1] = B[1]-A[1];
	AC[0] = C[0]-A[0];
	AC[1] = C[1]-A[1];
	int cross = AB[0] * AC[1] - AB[1] * AC[0];
	return cross;
}
//Compute the distance from A to B
double distance(int A[], int B[]){
	int d1 = A[0] - B[0];
	int d2 = A[1] - B[1];
	return sqrt(d1*d1 + d2*d2*1.0);
}
//Compute the distance from AB to C
//if isSegment is true, AB is a segment, not a line.
double linePointDist(int A[], int B[], int x, int y){
	int C[2];
	C[0] = x;
	C[1] = y;
	double dist = cross(A,B,C) / distance(A,B);
	int dot1 = dot(A,B,C);
	if(dot1 > 0)
		return distance(B,C);
	int dot2 = dot(B,A,C);
	if(dot2 > 0)
		return distance(A,C);
	return abs(dist);
}

bool segmentsIntersect(int A[], int B[], int C[], double D[]){
	int A1 = B[1] - A[1];
	int B1 = A[1] - B[0];
	int A2 = D[1] - C[1];
	int B2 = C[1] - D[0];
	double det = A1*B2 - A2*B1;
    if(det != 0)
		return true;
}

int testPoint1(int verts[][2], int N, int x, int y){
	int point[2] = {x, y};
	int cnt = 0;
	double x2 = rand() * 10000 + 1000;
	double y2 = rand() * 10000 + 1000;
	double ipoint[2] = {x2, y2};
	for(int i = 0; i < N; i++){
		if(linePointDist(verts[i], verts[(i + 1) % N], x, y) == 0)
			return 1;
		if( segmentsIntersect(verts[i], verts[(i + 1) % N], point, ipoint) )
			cnt++;
	}
	if(cnt % 2 == 0)
		return 0;
	else 
		return 1;
}
