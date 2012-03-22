#include "stdafx.h"
#include "BitVector.h"
#include <iostream>
#include <fstream>

using namespace std;

void SortedOutput(string fileName, int MAX_) {
	ifstream in(fileName);
	ofstream out("outputSorted.txt");
	vector<bool> num(MAX_, 0);
	
	while(!in.eof()) {
		int n;
		in >> n;
		num[n] = 1;
	}
	int sz = num.size() - 1;
	while(sz) {
		if (num[sz])
			out << sz << endl;
		--sz;
	}
}