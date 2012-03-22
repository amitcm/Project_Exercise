#include "stdafx.h"
#include "epic.h"

using namespace std;


string replace_vowel_but_first3(string str) {
	const string vowel = "aAeEiIoOuU";
	string ss = "";
	int vowellen = 3, flag = 0;
	const int len = str.length();
	for(int i = 0; i < len; i++) {
		if(-1 != vowel.find(str[i])){
			if( vowellen > 0)
				vowellen--;
			else
				flag = 1;
		}
		ss.push_back(str[i]);
		if(flag){
			ss.push_back('^');
			flag = 0;
		}
	}
	return ss;
}

void max_odd_min_even_from_stream(int& o_max, int& e_min) {
	int n = 0;
	e_min = INT_MAX;
	o_max = INT_MIN;
	while(true) {
		cout << "Enter number\n";
		cin >> n;
		if( !n )
			return;
		else{
			if(n & 1){
				if(o_max < n)
					o_max = n;
			}
			else{
				if(e_min > n)
					e_min = n;
			}
		}
	}
}

bool sanity_check(string key, string key_enter) {
	if(key.length() == key_enter.length() || key.empty() || !(!key.empty() && key_enter.empty()))
		return true;
	else
		return false;
}

bool valid_try(char key_ch, char key_en_ch) {
	/*
	1 2 3
	4 5 6
	7 8 9
	*/
	const string safe_key[] = {"24", "135", "26", "157", "2468", "359", "48", "579", "68"};
	if(safe_key[atoi(&key_en_ch) - 1].find(key_ch) == -1)
		return false;
	else 
		return true;
}

string security_keypad(string key, string key_enter) {
	bool failed_try = false;
	if(!sanity_check(key, key_enter))
		return "NOT ALLOWED";
	int len = key.length();
	for(int i = 0; i < len; ++i) {
		if(key[i] != key_enter[i]){
			if( !failed_try && valid_try(key[i], key_enter[i]))
				failed_try = true;
			else
				return "NOT ALLOWED";
		}
	}
	return "ALLOWED";
}

int is_leap_year(int year) {
	return ((year % 400 == 0) || (!(year % 100 == 0) && (year % 4 == 0))) ? 1 : 0; 
}

// gives the day including current date.
//
int day_of_year(int year, int month, int day) {

	int days_per_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	// leap year
	int result = is_leap_year( year ) ? 1 : 0;

	// if date before feb 28th, then we don't need to consider leap day.
	if((result == 1) && (month <= 2) && (day < 29))
		result -= 1;
	
	// Adjust month.
	month -= 1;
	
	// simple Sanity check
	if ((month < 1)	||  (month > 12) ||  (day < 1) ||  (day > (days_per_month[month] + result)))
		return 0;
	
	while (month--)
		result += days_per_month[month];
	
	result += day;

	return result;
}

// excludes both years
int leap_years(int year1, int year2) {
	int num = 0;
	while (++year1 < year2) {
		num += is_leap_year(year1);
	}
	return num;
}

int difference_days(string date1, string date2) {

	int d[2], m[2], y[2];
	d[0] = atoi(date1.substr(0, 2).c_str());
	d[1] = atoi(date2.substr(0, 2).c_str());
	m[0] = atoi(date1.substr(2, 2).c_str());
	m[1] = atoi(date2.substr(2, 2).c_str());
	y[0] = atoi(date1.substr(4, 4).c_str());
	y[1] = atoi(date2.substr(4, 4).c_str());

	// days in newer year + days remaining in the old year + 365*years in between(excluding end years) + Number of leap years in between.
	// the negative term account for extra day counted in first and second term in a leap year.
	// Note that it takes care of dates falling in same year, as well[the third term becomes negative].
	return (day_of_year(y[1], m[1], d[1]) 
		 + (is_leap_year(y[0]) + 365 - day_of_year(y[0], m[0], d[0])) 
		 + (365 * (y[1] - y[0] - 1))
		 + leap_years(y[0], y[1])
		 - ((is_leap_year(y[0]) && (y[1] == y[0])) ? 1 : 0)
		   );
}

bool digits_equation(string str) {
	return true;
}

class PlusEqual;
void PlusEqual::parse(){
	for(unsigned int i = 1; i < digits.length(); i++){
		for(unsigned int j = 1; j < digits.length() - i; j++){
			a.push_back(digits.substr(0, i));
			b.push_back(digits.substr(i, j));
			c.push_back(digits.substr((i + j), digits.length()));
		}
	}
}

PlusEqual::PlusEqual(string str): digits(str)
	{
		parse();
	}

void PlusEqual::printRelation(){
	for(unsigned int i = 0; i < a.size(); i++){
		buff.clear();
		buff << a.at(i);
		buff >> A;

		buff.clear();
		buff << b.at(i);
		buff >> B;

		buff.clear();
		buff << c.at(i);
		buff >> C;

		if(A == B + C)
			cout << A << "=" << B << "+" << C << endl;
		if(B == A + C)
			cout << B << "=" << A << "+" << C << endl;
		if(C == B + A)
			cout << C << "=" << A << "+" << B << endl;
	}
}


void BiggestInRowSmallestInCol(int  matrix[][3], int N){
	int BiggestInRow[3];
	int SmallestInCol[3];
	int max_n, max_i;
	int min_n, min_i;
	for(int i = 0; i < N; ++i){
		max_n = matrix[i][0];
		min_n = matrix[0][i];
		min_i = 0;
		max_i = 0;
		for(int j= 1; j < N; ++j){
			if(matrix[i][j] > max_n){
				max_n = matrix[i][j];
				max_i = j;
			}
			if(matrix[j][i] < min_n){
				min_n = matrix[j][i];
				min_i = j;
			}
		}
		BiggestInRow[i] = max_i;
		SmallestInCol[i] = min_i;
	}
	for(int k = 0; k < 3; k++){
		(k == SmallestInCol[BiggestInRow[k]] ) ? cout << matrix[k][BiggestInRow[k]] : cout << "" << endl;;
	}
}

string pattern[] = {"0",".,!","ABC","DEF","GHI","JKL","MNO","PQRS","TUV","WXYZ"};
ofstream keyout("keypad.txt");
void print_keypad(char* str, int k, vector<char> patt, int i)
{
	if(str[k] != '\0')
	{
		int x = str[k] - '0';
		for(int l = 0; l < pattern[x].length(); l++)
		{
			patt[i] = pattern[x][l];
			print_keypad(str, k+1, patt, i+1);
		}
		keyout << endl;
	}
	else if(i == k)
	{
		string st(patt.data());
		keyout << st << endl;
		return;
	}
}


void permute(string str, int d)
{
	if( d == str.length())
		cout << str << endl;
	else
	{
		for (int i = d; i < str.length(); i++)
		{
			swap(str[d], str[i]);
			permute(str, d+1);
			swap(str[d], str[i]);
		}
	}
}

static void printSentence(vector<string> sentence){
	for(vector<string>::iterator i = sentence.begin(); i != sentence.end(); i++)
		cout << *i << "  ";
}

void permutewords(vector<string> sentence, int d)
{
	if( d == sentence.size()) {
		printSentence(sentence);
		cout << endl;
	}
	else
	{
		for (int i = d; i < sentence.size(); i++)
		{
			swap(sentence[d], sentence[i]);
			permutewords(sentence, d+1);
			swap(sentence[d], sentence[i]);
		}
	}
}
