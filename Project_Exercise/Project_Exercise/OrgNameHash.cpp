#include <stdio.h>
#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <list>
#include <time.h>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

#define INT_N 1000
#define INT_SIMILARITY 1
//map<string, int> g_WordsAndCount;
list<string> g_listWordsAndCount;

static string TrimSpacesAtEnds(string line)
{
	/*if( line.length() == NULL)
		return 0;*/
	while(!line.empty() && line.at(0) == ' ' )
		line.replace(0, 1, "");
	while(!line.empty() && line.at(line.length() - 1) == ' ' )
		line.replace(line.length() - 1, line.length(), "");
	if(!line.empty())
		return line;
	else
		return "erro org name";
	
	// Need to put an extra check here. But, ignoring time being as this case will not arrive because error case is handled eralier.
}

static string RemovePunctuationAndToLowerCase(string line)
{	
	string::iterator it;
	char c;
	// remove '.', '!', ',' 
	for(it = line.begin() ; it < line.end(); )
	{
		c = it[0];
		if (c >= 'A' && c <= 'Z')
		{	
			c = c + 'a' - 'A';
			line.replace(it, it+1, 1, c);
			it++;
			continue;
		}
		
		if (*(it) == '.' || *(it) == ',' || *(it) == '!' || *(it) == ';')
		{			
			line.erase(it);
			if(line.empty())
				return "erro org name";
		}
		else
			it++;
	}
	return line;
}
static string SameCase(string line)
{
	string::iterator it;
	char c;
	for(it = line.begin() ; it < line.end(); it++ )
	{
		c = it[0];
		if (c >= 'A' && c <= 'Z')
		{	
			c = c + 'a' - 'A';
			line.replace(it, it+1, 1, c);
		}
	}
	return line;
}

//static int FindWord(string line)
//{
//	
//	string::iterator it;
//	for(it = line.begin() ; it < line.end(); it++ )
//	{
//		if(
//	}
//}


static string RemoveWords(string line)
{
	// trim space in the left most and right most position.
	line = TrimSpacesAtEnds(line);

	string str;
	string::iterator it;
	list<string>::iterator itList;
	int pos = 0;

	/* Assumption: Only one of the fluffy word can come to any company name.
	 Assumption: Only the last occurence has to be removed which is also a word " corp " or " co" BUT NOT "bencorp " or " bencorp".*/
	itList = g_listWordsAndCount.begin();
	while(itList != g_listWordsAndCount.end())
	{
		pos = line.rfind(*itList);
		if( pos == string::npos)
		{
			itList++;
			// Check for the next fluffy word from the beginning.
			//it = line.begin() ;
		}			
		else 
		{
			/* Check for being a word.
			 It passes these scenarios:
			 Single word "word"
			 last word "microsoft corp"
			 word in middle "microsoft corp systems"
			 Doesn't pass:
			 "microsoft incorp"
			 "microsoftcorp"
			 "microsoft indiacorp"*/

			if(( pos == 0 && (pos + (*itList).length() == line.length()) ) ||
				( pos != 0 && (pos + (*itList).length() == line.length()) && line[pos-1] == ' '  ) ||
				( pos != 0 && (pos + (*itList).length() != line.length()) && line[pos-1] == ' ' && line[pos + (*itList).length()] == ' ') 
				)
			{
				line.replace(pos, pos + (*itList).length(), "");
				if(!line.empty())
					line = TrimSpacesAtEnds(line);
				else
					return "blank org name";
			}
			// Irrespective of the case whether It passes or not, we must go to next list item.
			itList++;
		}
	}
	return line;
}


#define TRUE    1
#define FALSE   0

//typedef int bool;


#define MAXLEN          100     /* longest possible string */

#define MATCH           0       /* enumerated type symbol for match */
#define INSERT          1       /* enumerated type symbol for insert */
#define DELETE          2       /* enumerated type symbol for delete */

typedef struct {
        int cost;               /* cost of reaching this cell */
        int parent;             /* parent cell */
} cell;



/********************************************************************************************/
/********************************************************************************************/
/********************************      EDIT DISTANCE      ***********************************/
/********************************************************************************************/
/********************************************************************************************/

cell m[MAXLEN][MAXLEN];         /* dynamic programming table */

/******************************************************************/
//Forward declaration

void print_matrix(char *s, char *t, bool costQ);
int string_compare(const char *s, const char *t);
void reconstruct_path(char *s, char *t, int i, int j);


/******************************************************************/

/*	For normal edit distance computation  */

void goal_cell(char *s, char *t, unsigned int *i, unsigned int *j)
{
	*i = strlen(s) - 1;
	*j = strlen(t) - 1;
}

int match(char c, char d)
{
	if (c == d) return(0);
	else return(1);
}

int indel(char c)
{
	return(1);
}

void row_init(int i)		/* what is m[0][i]? */
{
	m[0][i].cost = i;
	if (i>0)
		m[0][i].parent =  INSERT;
	else
		m[0][i].parent = -1;
}

void column_init(int i)	/* what is m[i][0]? */
{
        m[i][0].cost = i;
	if (i>0)
		m[i][0].parent = DELETE;
	else
		m[0][i].parent = -1;
}

/**********************************************************************/

void match_out(char *s, char *t, int i, int j)
{
	if (s[i] == t[j]) printf("M");
	else printf("S");
}

void insert_out(char *t, int j)
{
	printf("I");
}

void delete_out(char *s, int i)
{
        printf("D");
}

int string_compare(const char *s, const char *t)
{
	unsigned int i,j,k;		/* counters */
	int opt[3];		/* cost of the three options */

	for (i=0; i<MAXLEN; i++) {
		row_init(i);
		column_init(i);
	}

	for (i=1; i<strlen(s); i++)
		for (j=1; j<strlen(t); j++) {
			opt[MATCH] = m[i-1][j-1].cost + match(s[i],t[j]);
			opt[INSERT] = m[i][j-1].cost + indel(t[j]);
			opt[DELETE] = m[i-1][j].cost + indel(s[i]);

			m[i][j].cost = opt[MATCH];
			m[i][j].parent = MATCH;
			for (k=INSERT; k<=DELETE; k++)
				if (opt[k] < m[i][j].cost) {
					m[i][j].cost = opt[k];
					m[i][j].parent = k;
				}
		}

	goal_cell((char *)s,(char *)t,&i,&j);
	return( m[i][j].cost );
} 

/********************************************************************************************/
/********************************************************************************************/
/********************************      EDIT DISTANCE ENDS     *******************************/
/********************************************************************************************/
/********************************************************************************************/

int main_1()
{
	//char *strRepeatedWords[] = {"corp", "co", "corporation", "inc" };
	//string strCompanyName[501] = {};

	g_listWordsAndCount.push_back("corp");
	g_listWordsAndCount.push_back("co");
	g_listWordsAndCount.push_back("corporation");
	g_listWordsAndCount.push_back("inc");
	g_listWordsAndCount.push_back("cos");
	g_listWordsAndCount.push_back("gmbh");
	g_listWordsAndCount.push_back("ltd");
	g_listWordsAndCount.push_back("llc");
	g_listWordsAndCount.push_back("llp");
	g_listWordsAndCount.push_back("lp");
	g_listWordsAndCount.push_back("sa");
	g_listWordsAndCount.push_back("mbh");
	g_listWordsAndCount.push_back("pty");
	g_listWordsAndCount.push_back("company");
	g_listWordsAndCount.push_back("incorporated");
	g_listWordsAndCount.push_back("plc");
	g_listWordsAndCount.push_back("limited");
	g_listWordsAndCount.push_back("bv");	
  
	string line;
	string str;
	set<string> setB;
	set<string>::iterator setIt;
	set<string> setOrgAssignee;
	set<string>::iterator setOrgIt;
	// Reserve this vecotr before final use.
	vector<string> vectorOrgAssignee;
	vectorOrgAssignee.reserve(1050000);
	vector<pair<string, int>> vectorOrgName;
	vectorOrgAssignee.reserve(500);
	vector<pair<string, int>>::iterator vectorIt;
	map<string, int> mapOrgName;
	map<string, int>::iterator mapIt;

	time_t seconds;
	seconds = time (NULL);
	
	ifstream fileListA ("org.txt");
	ofstream fileListB ("listB.txt");
	ifstream fileListA_f500 ("ListOf500.txt");
	ofstream fileListB_f500 ("listB_f500_final.txt");

	if (fileListA.is_open() /*&& fileListB.is_open()*/)
	{
		while ( fileListA.good() )
		{
			getline (fileListA,line);

			// Process the lines, here.
			line = RemovePunctuationAndToLowerCase(line);
			line = RemoveWords(line);
			
			if(!line.empty())
			{
				//fileListB << line <<endl;
				//setOrgAssignee.insert(line);
				if(line.length() > 98)
					line.at(98) = '\0';
				vectorOrgAssignee.push_back(line);
			}
		}
		fileListA.close();
		//fileListB.close();
	}
	else 
		cout << "Unable to open file";

	if (fileListA_f500.is_open()/* && fileListB_f500.is_open()*/)
	{
		while ( fileListA_f500.good() )
		{
			getline (fileListA_f500,line);

			// Process the lines, here.
			line = RemovePunctuationAndToLowerCase(line);
			line = RemoveWords(line);
			
			if(!line.empty())
			{
				//fileListB_f500 << line <<endl;
				setB.insert(line);
			}
		}
		fileListA_f500.close();
		//fileListB_f500.close();
	}
	else 
		cout << "Unable to open file";

	/***********************************************************************/
	/***************************INITIALIZE**********************************/
	/***********************************************************************/

	for (setIt = setB.begin()/*, mapIt = mapOrgName.begin()*/; setIt != setB.end(); setIt++ )
	{
		//mapOrgName.insert(mapIt, pair<string, int>(*setIt, 0));
		vectorOrgName.push_back(pair<string, int>(*setIt, 0));
	}
	/***********************************************************************/
	/***********************************************************************/


	/************************************************************************/
	/***********************************************************************/
	string key;
	//int count_set_element_number = 0;

	//  For each string in our DB	
	//for (setOrgIt = setOrgAssignee.begin()/*, mapIt = mapOrgName.begin()*/; setOrgIt != setOrgAssignee.end(); setOrgIt++ )
	for(int x = 0; x < vectorOrgAssignee.size(); x++)
	{
		//count_set_element_number++;
		//key = *setOrgIt;
		key = vectorOrgAssignee[x];

		//while(low < high)
		//{
		//	mid = (low + high) / 2; /*(vectorOrgName.end() + vectorOrgName.begin())/2*/;
		//	if(string_compare(key.c_str(), vectorOrgName[mid].first.c_str()) <= 2)
		//	{
		//		vectorOrgName[mid].second++;
		//	}
		//	else if()
		//	{

		//	}
		//	else
		//	{

		//	}
		//}

		for (int i = 0; i < vectorOrgName.size(); i++ )
		{
			if(string_compare(key.c_str(), vectorOrgName[i].first.c_str()) <= INT_SIMILARITY)
			{
				vectorOrgName[i].second++;
				break;
			}
		}
	}
	/***********************************************************************/
	/***********************************************************************/

	/***********************************************************************/
	/***********************************************************************/
	if(fileListB_f500.is_open())
	{
		for (int i = 0; i < vectorOrgName.size(); i++ )
		{
			fileListB_f500 << vectorOrgName[i].first << "," << vectorOrgName[i].second << endl;
		}
		fileListB_f500.close();
	}
	else
		cout << "Unable to open file";
	/***********************************************************************/

	seconds = (time(NULL) - seconds);
	printf (" Time taken (in seconds): \t %ld", seconds);
	return 0;
}