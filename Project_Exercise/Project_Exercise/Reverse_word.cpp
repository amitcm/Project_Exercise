#include "stdafx.h"
#include "Reverse_word.h"

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cout;
using std::endl;

// Splits a sentence by spaces into a vector of words
void extract(const string& sentence, vector<string>& words)
{
	size_t pos = 0;
	while(pos != string::npos)
	{  
		// Find position of next space
		int next_space = sentence.find(" ", pos);
		// Store everything up to next space in the words vector
		words.push_back( sentence.substr(pos, next_space - pos));

		// Continue at the next character which is not a space.
		pos = sentence.find_first_not_of(" ", next_space);
	}
}

// Prints the strings in the vector separated by spaces
static void print_strings(const vector<string>& strings)
{
	for(size_t i = 0; i < strings.size(); i++) {
		cout << strings[i] << " ";
	}
	cout << endl;
}

// Reverse words in a sentence
void reverse_words(string sentence)
{
	vector<string> words;
	extract(sentence, words);
	int i = words.size() - 1; 
	while(i >= 0) {
		cout << words[i] << " ";
		--i;
	}
}
