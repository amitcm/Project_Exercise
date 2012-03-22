#include "stdafx.h"
#include <string>
#include <map>
#include <fstream>

using namespace std;

void ListAndCountWords(string filename);
void permute(string str, int d);
void permutewords(vector<string> sentence, int d);
void print_keypad(char* str, int k, vector<char> patt, int i);