/*
"Pairing pawns" is a game played on a strip of paper, divided into N cells. The cells are labeled 0 through N-1. 
Each cell may contain an arbitrary number of pawns.
You are given a vector <int> start with N elements. For each i, element i of start is the initial number of pawns on cell i.
The goal of the game is to bring as many pawns as possible to cell 0.
The only valid move looks as follows:
Find a pair of pawns that share the same cell X (other than cell 0).
Remove the pair of pawns from cell X.
Add a single new pawn into the cell X-1.
You may make as many moves as you wish, in any order.
Return the maximum number of pawns that can be in cell 0 at the end of the game.
Definition
    
Class:
PairingPawns
Method:
savedPawnCount
Parameters:
vector <int>
Returns:
int
Method signature:
int savedPawnCount(vector <int> start)
(be sure your method is public)
    

Notes
-
You may assume that the answer will always fit into an int.
-
Note that you are only given the vector <int> start. The number of cells N can be determined as the length of start.
Constraints
-
start will contain between 1 and 20 elements, inclusive.
-
Each element of start will be between 0 and 1,000,000, inclusive.
Examples
0)

    
{0,2}
Returns: 1
There are two pawns on cell 1. You can remove them both and place a pawn onto cell 0.
1)

    
{10,3}
Returns: 11
There are 10 pawns already on cell 0. You can add another one by removing two pawns from cell 1. Note that at the end of the game cell 1 will still contain one pawn that cannot be used anymore.
2)

    
{0,0,0,8}
Returns: 1
After 7 moves you can get a single pawn to cell 0. The rest of the board will be empty.
3)

    
{0,1,1,2}
Returns: 1
Again, a single pawn can reach the leftmost cell.
4)

    
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,123456}
Returns: 0
That's a lot of pawns! But they are too far away. In this case it is impossible for a pawn to reach cell 0.
5)

    
{1000,2000,3000,4000,5000,6000,7000,8000}
Returns: 3921

This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction of this information without the prior written consent of TopCoder, Inc. is strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved.
*/

#include "stdafx.h"
#include "tc.h"
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
class PairingPawns
{
public:
	int savedPawnCount(vector <int> start);
};
int PairingPawns::savedPawnCount(vector <int> start)
{
	int shift = 0;
	vector<int>::iterator it;
	shift = *it / 2;
	for ( it = start.end() - 1; it > start.begin(); it-- )
	{
		*it += shift;
		shift = *it / 2;
	}
	return start.at(0);
}

/*
Problem Statement
    
Every good encyclopedia has an index. The entries in the index are usually sorted in alphabetic order. 
However, there are some notable exceptions. In this task we will consider one such exception: the names of kings.
In many countries it was common that kings of the same name received ordinal numbers. This ordinal number was 
written as a Roman numeral and appended to the actual name of the king. For example, "Louis XIII" 
(read: Louis the thirteenth) was the thirteenth king of France having the actual name Louis.
In the index of an encyclopedia, kings who share the same name have to be sorted according to 
their ordinal numbers. For example, Louis the 9th should be listed after Louis the 8th.
You are given a vector <string> kings. Each element of kings is the name of one king. The name of 
each king consists of his actual name, a single space, and a Roman numeral. Return a vector <string> 
containing the names rearranged into their proper order: that is, the kings have to be in ascending 
lexicographic order according to their actual name, and kings with the same name have to be in the correct numerical order.
Definition
    
	Class:
		KingSort
	Method:
		getSortedList
	Parameters:
		vector <string>
	Returns:
		vector <string>
	Method signature:
		vector <string> getSortedList(vector <string> kings)
		(be sure your method is public)
    

Notes
-
The Roman numerals for 1 through 10 are I, II, III, IV, V, VI, VII, VIII, IX, and X.
-
The Roman numerals for 20, 30, 40, and 50 are XX, XXX, XL, and L.
-
The Roman numeral for any other two-digit number less than 50 can be constructed by concatenating the numeral for its tens and 
the numeral for its ones. For example, 47 is 40 + 7 = "XL" + "VII" = "XLVII".
-
Standard string comparison routines give the correct ordering for the actual names of kings.
-
Formally, given two different strings A and B we say that A is lexicographically smaller than B 
if either (A is a prefix of B) or (there is at least one index where A and B differ, and for the smallest 
such index the character in A has a lower ASCII value than the character in B).
Constraints
-
Each actual name of a king will be a string containing between 1 and 20 characters, inclusive.
-
Each actual name will start by an uppercase letter ('A'-'Z').
-
Each other character in each actual name will be a lowercase letter ('a'-'z').
-
kings will contain between 1 and 50 elements, inclusive.
-
Each element of kings will have the form "ACTUALNAME ORDINAL", where ACTUALNAME is an actual name 
as defined above, and ORDINAL is a valid Roman numeral representing a number between 1 and 50, inclusive.
-
The elements of kings will be pairwise distinct.
Examples
0)

    
{"Louis IX", "Louis VIII"}
Returns: {"Louis VIII", "Louis IX" }
Louis the 9th should be listed after Louis the 8th.
1)

    
{"Louis IX", "Philippe II"}
Returns: {"Louis IX", "Philippe II" }
Actual names take precedence over ordinal numbers.
2)

    
{"Richard III", "Richard I", "Richard II"}
Returns: {"Richard I", "Richard II", "Richard III" }

3)

    
{"John X", "John I", "John L", "John V"}
Returns: {"John I", "John V", "John X", "John L" }

4)

    
{"Philippe VI", "Jean II", "Charles V", "Charles VI", "Charles VII", "Louis XI"}
Returns: 
{"Charles V",
 "Charles VI",
 "Charles VII",
 "Jean II",
 "Louis XI",
 "Philippe VI" }
These are the French monarchs who ruled between 1328 and 1483.
5)

    
{"Philippe II", "Philip II"}
Returns: {"Philip II", "Philippe II" }
"Philippe" and "Philip" are distinct names, and "Philip" is lexicographically smaller than "Philippe".*/

class KingSort{
public:
vector <string> getSortedList(vector <string> kings);
};


static int romanToInt(string ordinal)
{
	return 1;
}

static string intToRoman(int intOrdinal)
{
	return " ";
}

vector <string> KingSort::getSortedList(vector <string> kings)
{
	/*vector<pair<string, int>> names;
	vector<string>::iterator it;
	string actualname, ordinal;

	for ( it = kings.begin(); it < kings.end(); it++)
	{
		sscanf((*it).c_str(), "%s %s", actualname, ordinal);
		names.push_back(make_pair(actualname, romanToInt(ordinal)));
	}
	sort(names.begin(), names.end());
	kings.clear();
	for (int i = 0; i < names.size(); i++)
	{
		kings.push_back(names[i].first.append(" ").append(intToRoman(names[i].second)));
	}*/
	return kings;
}