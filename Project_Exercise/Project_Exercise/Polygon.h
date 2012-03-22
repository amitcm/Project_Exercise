#include <iostream>
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <math.h>

using namespace std;

int dot(int A[], int B[], int C[]);
int cross(int A[], int B[], int C[]);
double distance(int A[], int B[]);
double linePointDist(int A[], int B[], int x, int y);
bool segmentsIntersect(int A[], int B[], int C[], int D[]);
int testPoint1(int verts[][2], int N, int x, int y);