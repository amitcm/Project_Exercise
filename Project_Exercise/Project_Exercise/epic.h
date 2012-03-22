#include "stdafx.h"
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

string replace_vowel_but_first3(string str);
void max_odd_min_even_from_stream(int& o_max, int& e_min);
string security_keypad(string key, string key_enter);
int day_of_year(int year, int month, int day);
int difference_days(string date1, string date2);
bool digits_equation(string str);
void/*vector<string> */BiggestInRowSmallestInCol(int  matrix[][3], int N);

/******************************************************/
class PlusEqual{
private:
	vector<string> a,b,c;
	string digits;
	int A,B,C;
	stringstream buff;
public:
	PlusEqual(string str);
	void parse();
	void printRelation();
};
