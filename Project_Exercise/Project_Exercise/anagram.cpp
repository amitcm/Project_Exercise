// Program to find all anagrams of a given word, using a dictionary
// read from a file
#include "stdafx.h"
#include "anagram.h"

using namespace std;






void anagram_aha(string dictionarytxt){

	ifstream in(dictionarytxt);
	ofstream out("anagram.txt");

	string temp;
	vector<string> dictionary;
	set< pair<string, string> > sorted_word;
	set< pair<string, string> >::iterator it;
	it = sorted_word.begin();
	int i = 0;
	while(!in.eof()){
		in >> temp;
		dictionary.push_back(temp);
		sort(temp.begin(), temp.end());
		pair<string, string> p(temp, dictionary[i++]);
		sorted_word.insert(it, p);
	}
	it = sorted_word.begin();
	set< pair<string, string> >::iterator it1;
	it1 = sorted_word.begin();
	while(it1 != sorted_word.end() && it != sorted_word.end()){
		out << it->second;
		it1 = it;
		it1++;
		while(it1 != sorted_word.end() && it->first == (it++)->first){
			out << "\t" << it->second;
			it1++;
		}
		out << endl;
	}
}

int anagram_permute() 
{
	// Do it differently using Hashing

	cout << "Anagram finding program:\n"
		<< "finds all words in a dictionary that can\n"
		<< "be formed with the letters of a given word.\n" << endl;
	cout << "First, enter the name of the file containing\n"
		<< "the dictionary: " << flush;
	string dictionary_name; 
	cin >> dictionary_name;
	ifstream ifs(dictionary_name.c_str());
	if (!ifs.is_open()) 
	{
		cout << "Eh? Could not open file named "
			<< dictionary_name << endl;
		exit(1);
	}
	cout << "\nReading the dictionary ..." << flush;
	typedef istream_iterator<string> string_input;
	vector<string> dictionary;
	copy(string_input(ifs), string_input(), 
		back_inserter(dictionary));
	cout << "\nThe dictionary contains "
		<< dictionary.size() << " words.\n\n";
	cout << "Now type a word (or any string of letters),\n"
		<< "and I'll see if it has any anagrams: " << flush;
	for (string_input j(cin); j != string_input(); ++j) 
	{
		string word = *j;
		sort(word.begin(), word.end());
		bool found_one = false;
		do 
		{
			if (binary_search(dictionary.begin(), dictionary.end(), word)) 
			{
					cout << "  " << word << endl;
					found_one = true;
			}
		} while (next_permutation(word.begin(), word.end()));
		if (!found_one) 
			cout << "  Sorry, none found.\n";
		cout << "\nType another word "
			<< "(or the end-of-file char to stop): " << flush;
	}
	return 0;
}