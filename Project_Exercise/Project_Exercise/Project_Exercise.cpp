// Project_Exercise.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <iostream>
#include <string>
#include <intrin.h>
#include <bitset>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <math.h>
#include <time.h>
#include <Windows.h>
#include "BinarySearch.h"
#include "DivideNConquer.h"
#include "DP_exercises.h"
#include "Graphs.h"
#include "Helper.h"
#include "HashMap.h"
#include "BinaryTree.h"
#include "BitSetCount.h"
#include "RegEx.h"
#include "BitMagic.h"
#include "String.h"
#include "Reverse_word.h"
#include "HeapEtAl.h"
#include "BigInt.h"
#include "CardPick.h"
#include "Polygon.h"
#include "Sorting.h"
#include "SortedLLtoBST.h"
#include "binary_tree_pretty_print.h"
#include "BaseConversion.h"
#include "BitVector.h"
#include "anagram.h"
#include "epic.h"

using namespace std;

#define MAX_POLY 20000
#define MAX_POINTS 20000

int a[2005][2005];

int SecondSmallest(int arrA[], int m, int arrB[], int n);
int KthSmallest(int arrA[], int arrB[], int m, int n, int k);
static double BT(int k, double q, int n);
void print_bigint(const bigint& sq);
void print_vector(vector<int> numbers);
void permute(vector<int> numbers, int d);
void push_vector(vector<int> &final, vector<int> numbers);
vector<int> permute_return(vector<int> numbers, int d);
bool testPoint(vector <string> vertices, int testPointX, int testPointY);
int savedPawnCount(vector <int> start);

vector<int> nextcombination(vector<int> vec)
{
	vector<int>vec1;

	return vec1;
}

bool validate(vector<int> vec)
{

	return false;
}

#define IMPOSSIBLE 0
#define POSSIBLE 1

int day_from_date(int y, int m, int d){
	m = (m + 9) % 12;
	y = y - m/10;
	return (365*y + y/4 - y/100 + y/400 + (m*306 + 5)/10 + (d - 1));
}

bool date_from_day(int day, int& dd, int& mm, int& y) {
	y = (10000 * day + 14780) / 3652425;
	int ddd = day - (365*y + y/4 - y/100 + y/400);
	if (ddd < 0) { 
		y = y - 1;
		ddd = day - (365*y + y/4 - y/100 + y/400);
	}
	int mi = (100*ddd + 52)/3060;
	mm = (mi + 2) % 12 + 1;
	y = y + (mi + 2)/12;
	dd = ddd - (mi*306 + 5)/10 + 1;
	return true;
}

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void printboard(int board[][3]){
for(int i = 0; i < 3; i++){
  for(int j = 0; j < 3; j++)
  cout << board[i][j] << "\t";
cout << endl;
}

}

bool verifyGame(int board[][3], int player){
	bool flag = true;
	bool flag1 = true;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(board[i][j] != player)
				flag = false;
			if(board[j][i] != player)
				flag1 = false;
		}
		if(flag || flag1)
			return true;
	}
	if(board[0][0] == player && board[1][1] == player && board[2][2] == player)
		return true;
	
	/*flag = true;
	for(int i = 0; i < 3; i++){
			if(board[i][j] != player)
				flag = false;
	}
	if(flag)
		return true;*/

	if(board[2][0] != player && board[1][1] != player && board[0][2] != player)
		return true;
}

void tic_tac() {
	int board[3][3] = {1, 0, 0, 1, 2, 0, 1, 0, 0};
	int player = 1, x = 0, y = 0;
	bool gameover = false;
	while(true) {

		printboard(board);
		cout << "Player: " << player <<" please enter co-ordinate in following co-ordinate system fashion. \n\nleftmost top element is represented by (0,0), Rightmost, bottom element represented by (2,2)\n"; 
		cin >> x >> y;
		--x;
		--y;
		if(!( 0 <= x && x <= 2 && 0 <= y && y <= 2)){
			cout << "please re-enter the values with in limit \n";
			continue;
		}

		if(board[x][y] != 0){
			cout << "please re-enter the values at an empty place\n";
			continue;
		}

		board[x][y] = player;

		player =  (player == 1) ? 2 : 1 ;

		if(verifyGame(board, (player == 1) ? 2 : 1 )){
			cout << "Player" << (( player == 1) ? 2 : 1) << "won" << endl;
			return;
		}
	}
}

#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class LeftOrRight {
public:
	int maxDistance(string);
};

static int count(string program, char c){
	int cnt = 0;
	int mx = 0;
	int len  = program.length();
	for(int i = 0; i < len; ++i) {
    	if(program.at(i) == c){
    		++cnt;
			if(mx < cnt)
				mx = cnt;
		}
    	else
    		--cnt;
    }
    return cnt;
}

int LeftOrRight::maxDistance(string program) {
	string str(program);
	int cntl = 0;
	int cntr = 0;
	int len  = program.length();
	for(int i = 0; i < len; ++i) {
		if(program.at(i) == '?')
			program[i] = 'L';
	}
	cntl = 	count(program, 'L');
	for(int i = 0; i < len; ++i) {
		if(str.at(i) == '?')
			str[i] = 'R';
	}
	cntr = 	count(str, 'R');
	return max(cntl, cntr);
}




int _tmain(int argc, _TCHAR* argv[])
{

	LeftOrRight LoR;
	cout << LoR.maxDistance("LLRRL");

	//int  matrix[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
	int  matrix[3][3] = {{6, 5, 4}, {3,2,1},  {9, 8, 7}};
	/*vector<string> result = */BiggestInRowSmallestInCol(matrix , 3);
	
	/*******************************************************************/
	// epic
	/*******************************************************************/
	//tic_tac();
	PlusEqual pe1("25631");
	pe1.printRelation();
	cout << replace_vowel_but_first3("abcdeaedf") << endl;
	int e_min, o_max;
	max_odd_min_even_from_stream(o_max, e_min);
	cout << o_max << "\t" << e_min << endl;

	cout << day_of_year(2012, 02, 28) << endl;
	cout << day_of_year(2012, 03, 03) << endl;
	cout << day_of_year(2000, 02, 28) << endl;

	// (28022012, 03032012] or [28022012, 03032012)
	cout << difference_days("28022012", "03032012") << endl;
	cout << difference_days("28022000", "28022012") << endl;

	

	cout << security_keypad("1478", "1178") << endl;
	cout << security_keypad("1578", "1178") << endl;
	cout << security_keypad("", "1178") << endl;
	cout << security_keypad("", "") << endl;
	cout << security_keypad("23", "") << endl;
	/*******************************************************************/
	string permute_sentence[] = {"Amit", "Shekhar", "is"};
	vector<string> vec_sentence(permute_sentence, permute_sentence + 3 );
	permutewords(vec_sentence, 0);
	/*******************************************************************/
	// Keypad printing
	/*******************************************************************/
	char *input = new char[25];
	cout << "Enter the input string\n";
	cin >> input;
	int size = sizeof(input);
	vector<char> patt(25);
	print_keypad(input, 0, patt, 0);

	/*******************************************************************/
	anagram_aha("dictionary.txt");
	SortedOutput("numbers.txt", 100);

	/*******************************************************************/
	// Base Conversion
	/*******************************************************************/
	//string base26;
	cout << numToStr(5) << endl;
	cout << numToStr(26) << endl;
	cout << numToStr(727) << endl;
	cout << fromDecimal2(5, 16) << endl;
	cout << fromDecimal2(26, 16) << endl;
	cout << fromDecimal2(727, 16) << endl;


	/*******************************************************************/
	/*******************************************************************/
	// Divide and conquer
	/*******************************************************************/
	int in[] = {4,10,3,1,7,11,8,2};
	int pre[] = {7,10,4,3,1,2,8,11};
	vector<int> inorder(in, in + 8);
	vector<int> preorder(pre, pre + 8);
	//cout << (CreateTree(inorder, preorder))->data << endl;
	/*******************************************************************/

	/********************************************************************/
	// Sorting
	/********************************************************************/
	int s[] = { 45, 56, 1, 3, 213, 123, 789, 543, 2, 4, 3, 89 };
	//int s[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
	int low = 0, high = 11; // high = # of elts - 1;
	quicksort(s, low, high);
	//mergesort(s, low, high);
	while(high >= 0)
		cout << s[high--] << "\t";
	cout << endl;
	/********************************************************************/

	/********************************************************************/
	// Random stuffs
	/********************************************************************/
	
	PrettyBinaryTree();

	DWORD dwStart = GetTickCount();
	for(int j = 0; j < 100; ++j)
		for(int i = 0; i < 100000; ++i)
			;
	
	DWORD dwEnd = GetTickCount();
	time_t tickCount = dwEnd - dwStart;
	cout << tickCount << endl;
	
	
	for(int i = 0; i < 100000; ++i)
		for(int j = 0; j < 100; ++j)
			;
	
	DWORD dwEnd1 = GetTickCount();
	tickCount = dwEnd1 - dwEnd;
	cout << tickCount << endl;

	//////////////////////////////////////////////////////////////
	

	/************************************************************/
	// Application of Binary search [aka Discrete Binary Search]
	/************************************************************/
	double price = 2000; 
	double monthlyPayment = 510;
	int loanTerm = 4;
	cout << interestRate(price, monthlyPayment, loanTerm) << endl;


	vector <int> folders;
	int workers = 5;
	folders.push_back(10);
	folders.push_back(20);
	folders.push_back(30);
	folders.push_back(40);
	folders.push_back(50);
	folders.push_back(60);
	folders.push_back(70);
	folders.push_back(80);
	folders.push_back(90);
	cout << getMostWork(folders, workers) << endl; 

	/************************************************************/
	// Divide And Conquer
	/************************************************************/
	int lMost, rMost, sumArr;
	int A[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
	maxSubArraySum(A, 0, 15, lMost, rMost, sumArr);
	
	// Faster - O(n)
	int data[] = {31, -41, 59, 26, -53, 58, 97, -93, -23, 84};
	vector<int> vi(data, data+10);
	cout << maxSubArraySum(vi) << "\n";

	/************************************************************/
	
	/********************************************/
	// Dynamic programming
	/********************************************/

	int a_lis[] = { 1, 9, 3, 8, 11, 4, 5, 6, 4, 19, 7, 1, 7 };
	vector<int> seq(a_lis, a_lis + sizeof(a_lis) / sizeof(a_lis[0])); // seq : Input Vector
	vector<int> lis;                              // lis : Vector containing indexes of longest subsequence 
	find_lis(seq, lis);

	//Printing actual output 
	for (size_t i = 0; i < lis.size(); i++)
		printf("%d ", seq[lis[i]]);
	printf("\n");    


	printf("%d \n", Fibonacci(6));
	int weights[4] = {5, 4, 6, 3};
	int values[4] = {10, 40, 30, 50};
	cout << KnapsackUsingItemsOnce(weights, values, 4, 10) << endl;
	cout << KnapsackUsingItemsOnceBool(weights, values, 4, 10) << endl;
	cout << ComputeBinomial(5, 2) << endl;
	cout << endl << ComputeBinomial(5, 4) << endl;

	string str1("FOOD");
	string str2("MONEY");
	//cout << EditDistance(str1.c_str(), str2.c_str()) << endl;
	/********************************************/

	/************************************************************/
	// Hacker Cup

	cout << endl;
	////////////////////////cout/////////////////////
	static int ints; 
	int jk = 10;
	int &refjk = jk;

	/************************************************************/
	// SortedLLtoBST
	/************************************************************/
	/* Start with the empty list */
    struct LNode* headLL = NULL;
 
    /* Let us create a sorted linked list to test the functions
     Created linked list will be 7->6->5->4->3->2->1 */
    push(&headLL, 7);
    push(&headLL, 6);
    push(&headLL, 5);
    push(&headLL, 4);
    push(&headLL, 3);
    push(&headLL, 2);
    push(&headLL, 1);
 
    printf("\n Given Linked List ");
    printList(headLL);
 
    /* Convert List to BST */
    struct TNode *root = sortedListToBST(headLL);
    printf("\n PreOrder Traversal of constructed BST ");
    preOrder(root);

	/*************************************************************/

	/*************************************************************/
	// Topcoder
	/*************************************************************/
	
	/**************************************************************************/

	/********************************************/
	// Binary Tree
	/********************************************/
	struct node* head;
	head = NewNode(20);
	head = InsertNode(head, 15);
	head = InsertNode(head, 10);
	head = InsertNode(head, 25);
	head = InsertNode(head, 35);
	head = InsertNode(head, 1);
	head = InsertNode(head, 15);
	head = InsertNode(head, 12);
	head = InsertNode(head, 5);
	//Operations here

	/*INPUT
						20
					   /  \
					 15	   25
				    /  \    \
				  10   15	35
				 /  \
				1	12
				 \
				  5
	*/
	printf("Inorder traversal: \n");
	InorderTraversal(head);

	printf("Preorder traversal: \n");
	PreorderTraversal(head);

	printf("Postorder traversal: \n");
	PostorderTraversal(head);

	cout << "Level order traversal using BFS" << endl;
	printLevelOrder(head);

	//struct node* LinkedList = BinaryTreeToLinkedList(head);
	int iDepth = MaxDepth(head);
	int iMinN = MinValueNormal(head);
	int iMinR = MinValueRecursion(head);
	/********************************************/

	/********************************************/
	// Graphs
	/********************************************/
	graph g(1);
	graph *p_g = &g;

	// Limited feature insertion. vertex value is used as array index.
	p_g->insert_edge(5, 10, 1);
	p_g->insert_edge(15, 10, 1);
	p_g->insert_edge(5, 15, 1);
	p_g->insert_edge(5, 14, 1);
	p_g->insert_edge(10, 13, 1);
	p_g->insert_edge(1, 12, 1);
	p_g->insert_edge(1, 19, 1);
	//p_g->read_graph(1);
	p_g->print_graph();

	/********************************************/


	/****************************************************************/
	// TC
	/****************************************************************/
	//vector<int> strt;
	//strt.push_back(10);
	//strt.push_back(3);
	//cout << savedPawnCount(strt) << endl;
	/****************************************************************/

	

	/***************************************************************/
	// Tic tac toe
	/***************************************************************/
	/*cout <<"This is a TRILIZA(tic-tac-toe) game created by human_thought.In order to play\nthis game you first decide ";
	cout <<"whether YOU or the COMPUTER should play first.\n\n";
	cout <<"In order to choose a position on which you want to place your mark,think of the ";
	cout <<"TRILIZA grid as having numbered squares.A TRILIZA grid contains 9 squares,so\n";
	cout <<"just pick a number from 1-9 to identify where you want your mark put.";
	cout <<"Keep in\nmind that number 1 is the upper left corner,while 9 is the lower right corner..\n";
	cout <<"You can verify the positions watching the diagram below..\n";
	cout <<"Good Luck !!!\n\n";


	cout <<"  1| 2| 3  \n";
	cout <<" --------  \n";
	cout <<"  4| 5| 6  \n";
	cout <<" --------  \n";
	cout <<"  7| 8| 9  \n\n\n";

	cout <<"O is for the Computer Opponent.\n";
	cout <<"X is for the Human Opponent.\n\n\n";

	while (1)
	{
		Triliza = new CMyTriliza();
		Triliza->VerifyFirstPlayer();
		Triliza->TrilizaLoop();
	
		if (!Triliza->PlayAgain())
			break;
	}*/
	/***************************************************************/

	/***************************************************************/
	// Testing Matrix values
	/***************************************************************/
	int arr[MAX][MAX];
	int m = 5, n = 7;
	PopulateMatrixWithDefault(arr, m, n);
	PrintDiagonalLowerLeftMatrix(arr, m, n);
	PrintMatrixNormalView(arr, m, n);
	cout << endl;
	/***************************************************************/

	

	/*Given two sorted arrays A, B of size m and n respectively. 
	Find the k-th smallest element in the union of A and B. 
	You can assume that there are no duplicate elements.*/


	int arrA[5] = {1, 3, 5, 6, 9};
	int arrB[11] = {2, 4, 8, 10, 15, 16, 17, 21, 32, 45, 100};
	cout << KthSmallest(arrA, arrB, 0, 0, 6) << endl;
	cout << KthSmallest(arrA, arrB, 0, 0, 10) << endl;
	cout << KthSmallest(arrA, arrB, 0, 0, 1) << endl;
	cout << KthSmallest(arrA, arrB, 0, 0, 2) << endl;


	/***************************************/
	// Heap
	/***************************************/
	Heap myheap;
	myheap.addtoheap(15);
	myheap.addtoheap(5);
	myheap.addtoheap(25);
	myheap.addtoheap(51);
	myheap.addtoheap(59);
	myheap.addtoheap(1);
	myheap.addtoheap(60);
	vector<int> sorted_vector = myheap.heapsort();
	printf("%d\n",myheap.removefromheap());
	printf("%d\n",myheap.removefromheap());
	printf("%d\n",myheap.removefromheap());
	printf("%d\n",myheap.removefromheap());
	sorted_vector = myheap.heapsort();
	/***************************************/

	/***************************************/
	// Reverse Word (Nicely reviewed code)
	/***************************************/
	string sentence("Amit Shekhar is an Indian.");
	reverse_words(sentence);
	/***************************************/
	// Note there are functions available in C++ for finding next and previous permutation(Lexicographic one :)).
	string strPerm = "abc";
	permute(strPerm, 0);

	/***************************************/
	// Bit Magic
	/***************************************/
	int x1 = 13;
	printf("%d\n", add1(x1));
	printf("%d\n", add1_1(x1));
	cout << "Next higher number with same number of set bits is " << snoob(x1);

	/*int n,d,e,f;
	scanf("%d",&n);
	d=n<>1;
	f=addwithoutplusminus(d,e);
	printf("%d\n",addwithoutplusminus(f,n));*/
    /***************************************/

	/**************************************/
	// RegEx
	/**************************************/
	string strS = "abbc", strP = "ab*c";
	bool bMatch = false; 
	bMatch = isMatch(strS.c_str(), strP.c_str());
	/**************************************/

	/**************************************/
	// Bit Set Count
	/**************************************/
	int runs,a,b ;
	cin >> runs ;
	while(runs--)
	{
		cin >> a >> b ;
		long long ret = solve(a,b) ;
		cout << ret << endl ;
	}
	/***************************************/


	/***************************************/
	// Test here
	/***************************************/
	string str = "A quick brown fox jumped over";
	string p = "fox";
	//string::iterator strIt = str.begin();
	for(int i = 0; i <= str.length() - 5; i++)
	{
		//printf("%s \n", str.substr(i, 5));
		cout << str.substr(i, 5) << endl;
	}
	/********************************************/

	

	/********************************************/
	// Graphs
	/********************************************/
	//struct graph *g;

	//read_graph(g, true);
	//print_graph(g);
	/********************************************/

	
	/***************************************************/
	// Suffix tree
	/***************************************************/
	//cout << "Normally, suffix trees require that the last\n"
	//	<< "character in the input string be unique.  If\n"
	//	<< "you don't do this, your tree will contain\n"
	//	<< "suffixes that don't end in leaf nodes.  This is\n"
	//	<< "often a useful requirement. You can build a tree\n"
	//	<< "in this program without meeting this requirement,\n"
	//	<< "but the validation code will flag it as being an\n"
	//	<< "invalid tree\n\n";
	//cout << "Enter string: " << flush;
	//cin.getline( T, MAX_LENGTH - 1 );
	//N = strlen( T ) - 1;
	////
	//// The active point is the first non-leaf suffix in the
	//// tree.  We start by setting this to be the empty string
	//// at node 0.  The AddPrefix() function will update this
	//// value after every new prefix is added.
	////
	//Suffix active( 0, 0, -1 );  // The initial active prefix
	//for ( int i = 0 ; i <= N ; i++ )
	//	AddPrefix( active, i );
	////
	//// Once all N prefixes have been added, the resulting table
	//// of edges is printed out, and a validation step is
	//// optionally performed.
	////
	//dump_edges( N );
	//cout << "Would you like to validate the tree?"
	//	<< flush;
	//std::string s;
	//getline( cin, s ); 
	//if ( s.size() > 0 && s[ 0 ] == 'Y' || s[ 0 ] == 'y' )
	//	validate();
	/***************************************************************/

	/***************************************************************/
	// Hash in C++ stl
	/***************************************************************/
	//// collate::hash example
	//
	//#include <locale>
	//using namespace std;
	//
	//int main ()
	//{
	//	string myberry = "strawberry";
	//	string yourberry;
	//
	//	locale loc;                 // the "C" locale
	//
	//	const collate<char>& coll = use_facet<collate<char> >(loc);
	//
	//	long myhash = coll.hash(myberry.data(),myberry.data()+myberry.length());
	//
	//	cout << "Please, enter your favorite berry:";
	//	getline (cin,yourberry);
	//
	//	long yourhash = coll.hash(yourberry.data(),yourberry.data()+yourberry.length());
	//
	//	if (myhash == yourhash)
	//		cout << "Mine too!\n";
	//	else
	//		cout << "I prefer strawberries...\n";
	//
	//	return 0;
	//
	//}
	/***************************************************************/

	/******************************************************************************
	// Code Sprint 2
	/******************************************************************************
	/*vector<string> vec_coordinate;
	vec_coordinate.push_back("0 0");
	vec_coordinate.push_back("0 1");
	vec_coordinate.push_back("1 1");
	vec_coordinate.push_back("1 0");*/
	//int verts_pip[][2] = {{0, 0},{0, 1},{0, 2}, {0, 3}, {1,0},{1, 1},{1,2}, {1,3}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {3, 0}, {3, 1}, {3, 2}, {3, 3}};
	int verts_pip[][2] = {{1, 1},{3, 3},{3, 5}, {5, 2}, {6,3}, {7, 4}/*,{1,2}, {1,3}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {3, 0}, {3, 1}, {3, 2}, {3, 3}*/};
	//int verts_poly[][2] = {{0, 0},{0, 1},{1, 1},{1, 0}};
	int verts_poly[][2] = {{1,3},{1,6},{4,6},{4,3},{6,3},{6,1},{4,1},{4,2},{3,2},{3,3}};
	/*int po_ = 4, po_count = 0;

	for(int i = 0; i <= po_; i++){
		cout <<verts_pip[i][0] << "\t" << verts_pip[i][1];
		if(testPoint(vec_coordinate, verts_pip[i][0], verts_pip[i][1])){
			cout << "SUCCESS" << endl;
			po_count++;
		}
		else
			cout << "DOES NOT CONTAIN" << endl;
	}*/

	int po_Test, po_num_point, po_num_poly, po_x, po_y, po_poly_edge;
	int saved_num_point;
	
	vector<string> vec_poly_points;
	//int verts_pip[MAX_POINTS][2], verts[MAX_POLY][MAX][2];
	//cin >> po_Test;
	//while ( po_Test-- ){
	cin >> po_num_point >> po_num_poly;
	// Fill poits in plane matrix
	for(int i = 0; i < po_num_point; i++){
		cin >> verts_pip[po_num_point][0] >> verts_pip[po_num_point][1];
	}
	std::ostringstream oss;
	
	while (po_num_poly--) {
		cin >> po_poly_edge;
		saved_num_point = po_num_point;	// Make sure to change this one
		while ( po_poly_edge-- ){
			cin >> po_x >> po_y;
			oss << po_x << " " << po_y;
			vec_poly_points.push_back(oss.str());
			oss.str(std::string());
		}
		// Logic to do actual stuuf for polygon
		int count_point = 0;
		for(int i = 0; i < po_num_point; i++){
			cout <<verts_pip[i][0] << "\t" << verts_pip[i][1] << endl;
			if(testPoint(vec_poly_points, verts_pip[i][0], verts_pip[i][1])){
				count_point++;
			}
		}
		cout << count_point << endl;
		vec_poly_points.clear();
	}

	///////////////////////////////////////////////////////////////////////////////////
	int cp_Test, cp_N, cp_val;
	long long count;
	cin >> cp_Test;
	while(cp_Test--){
		cin >> cp_N;
		vector<int> vec = create(cp_N);
		while(cp_N--){
			cin >> cp_val;
			increase(vec, cp_val, 1);
		}
		// Logic of counting the number of ways.
		//long long count; 
		/*while( Not the end of vector, use i as current position and count is not zero)
		{
			count *= (query(vec, i, i) - 1) * query(vec, i + 1, i + 1));
		}
		*/
		//print count.
	}
	



	/*
	vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	print_vector(vec);
	print_vector(permute_return(vec, 0));
	permute(vec, 0);*/

	static bigint billionbillion(1000000000000000000);
	static bigint billionbillionhalf(100000000000000000);
	static bigint billion(1000000000);
	static bigint bi_two(2);
	static bigint bi_zero(0);
	print_bigint(billionbillion);
	print_bigint(billionbillionhalf);
	print_bigint(billion);
	print_bigint(bi_two);

	int nHeads, nAlready, Test;
	bigint nFlips, dX;
	//scanf("%d", &Test);
	cin >> Test;
	
	while(Test > 0){
		//scanf("%d", &nHeads);
		//scanf("%d", &nAlready);
	    cin >> nHeads;
	    cin >> nAlready;
		
		nFlips = (1 << (nHeads + 1)) - 2;
		if ((nHeads - nAlready) == nHeads){
	        print_bigint(nFlips);
			cout << endl;
		}
		else{
	        dX = (nHeads - nAlready) + ((nHeads - nAlready) > 0 ? (nFlips / bi_two) : bi_zero);
	        print_bigint(dX);
			cout << endl;
		}
		Test = Test - 1;
	}
	/***************************************************************************************************/

	printf("Hello world!");
	return 0;

}


int SecondSmallest(int arrA[], int m, int arrB[], int n)
{
	if(arrA[m + 0] == min(arrA[m + 0], arrB[n + 0]))
		return min(arrA[m + 1], arrB[n + 0]);
	else
		return min(arrA[m + 0], arrB[n + 1]);
}

// m = 0 and n = 0. starting index of the arrays.
int KthSmallest(int arrA[], int arrB[], int m, int n, int k)
{
	if (k <= 1)
		return min(arrA[m + 0], arrB[n + 0]);
	if(k == 2)
		return SecondSmallest(arrA, m, arrB, n);
	int MidA = arrA[m + k/2];
	int MidB = arrB[n + k/2];
	if (MidA < MidB)
		return KthSmallest(arrA, arrB, m + k/2, n, k % 2 ? (k/2 + 1) : k/2);
	else
		return KthSmallest(arrA, arrB, m, n + (k/2), k % 2 ? (k/2 + 1) : k/2);
}

/*
Pr{k,q,n} = Pr{k-1,q,n} + (q^n)(1-q) [1 - Pr{k-n-1,q,n}]       (1)

with the initial values 

                Pr{j,q,n} = 0       for j = 0,1,..,n-1

                Pr{j,q,n} = q^n     for j = n
				*/
static double BT(int k, double q, int n)
{
	if(k < n)
		return 0;
	if(k == n)
		return pow(q, n);
	return (BT(k-1, q, n) + pow(q, n)*(1-q)*(1 - BT(k-n-1, q, n)));
}

void print_bigint(const bigint& sq)
{
	static bigint billion(1000000000);
	static bigint zero(0);
	static bigint digit;
	static bigint q;
	BIGINT_BASE decimaldigit;
	ldiv_t divideresult;
	int i;
	char *decimal_array;
	char tmp;
	char *p;

	decimal_array = new char[8000];
	q = sq;
	p = decimal_array+3999;
	*p = 0;
	p--;

	if (q == zero)  // Special case 
	{
		*p = '0';
		p--;
	}

	for (;q>zero;)
	{
		q = q.Divide(q, billion, &digit);
		decimaldigit = digit;
		for(i=0; i<9; i++)
		{
			divideresult = ldiv(decimaldigit, 10);
			*p = divideresult.rem + 0x30;
			p--;
			decimaldigit = divideresult.quot;
		}
	}

	for (p++; *p=='0'; p++) // Strip off leading zeros.
	{
	}

	if (*p == 0)
		p--;

	printf("%s\n", p);
	delete decimal_array;
	//return p;
}

void print_vector(vector<int> numbers)
{
	int size = numbers.size() - 1;
	while(size >= 0){
		printf("%d\t", numbers.at(size--));
	}
	cout << endl;
}

void permute(vector<int> numbers, int d)
{
	if( d == numbers.size()){

		//print_vector(numbers);
		//cout << endl;
	}
	else
	{
		for (int i = d; i < numbers.size(); i++)
		{
			swap(numbers[d], numbers[i]);
			permute(numbers, d+1);
			swap(numbers[d], numbers[i]);
		}
	}
}

void push_vector(vector<int> &final, vector<int> numbers)
{
	int size = numbers.size() - 1;
	while(size >= 0){
		final.push_back(numbers.at(size--));
	}
}

vector<int> permute_return(vector<int> numbers, int d)
{
	vector<int>final;
	if( d == numbers.size()){
		push_vector(final, numbers);
		//print_vector(numbers);
		//cout << endl;
	}
	else
	{
		for (int i = d; i < numbers.size(); i++)
		{
			swap(numbers[d], numbers[i]);
			permute(numbers, d+1);
			swap(numbers[d], numbers[i]);
		}
	}
	return final;
}

bool testPoint(vector <string> vertices, int testPointX, int testPointY) 
{
	testPointX += 1000;
	testPointY += 1000;

	int i;

	for (i = 0; i < vertices.size()-1; i ++)
	{
		int x0, y0, x1, y1;

		istringstream it(vertices[i]);
		it >> x0 >> y0;
		istringstream it2(vertices[i+1]);
		it2 >> x1 >> y1;

		x0 += 1000;
		y0 += 1000;
		x1 += 1000;
		y1 += 1000;

		if (x0 == x1)
		{
			int y = y0 < y1 ? y0 : y1;
			int Y = y0 > y1 ? y0 : y1;

			for (int j = y; j <= Y; j ++)
				a[x0][j] = 1;
		}
		else
		{
			int x = x0 < x1 ? x0 : x1;
			int X = x0 > x1 ? x0 : x1;        

			for (int j = x; j <= X; j ++)
				a[j][y0] = 1;
		}
	}

	int x0, y0, x1, y1;
	istringstream it(vertices[0]);
	it >> x0 >> y0;
	istringstream it2(vertices[vertices.size()-1]);
	it2 >> x1 >> y1;

	x0 += 1000;
	y0 += 1000;
	x1 += 1000;
	y1 += 1000;

	if (x0 == x1)
	{
		int y = y0 < y1 ? y0 : y1;
		int Y = y0 > y1 ? y0 : y1;

		for (int j = y; j <= Y; j ++)
			a[x0][j] = 1;
	}
	else
	{
		int x = x0 < x1 ? x0 : x1;
		int X = x0 > x1 ? x0 : x1;        

		for (int j = x; j <= X; j ++)
			a[j][y0] = 1;
	}

	//bool bret = false; 
	//string ret = "";
	if (a[testPointX][testPointY] == 1)
	{
		//ret += "BOUNDARY";
		return true;
	}

	int nl1 = 0;

	for (i = testPointX; i < 2005; i ++)
		if (a[i][testPointY] == 1) nl1 ++;

	if (nl1 % 2 == 0)
	{

		int nl2 = 0;

		for (i = testPointY; i < 2005; i ++)
			if (a[testPointX][i] == 1) nl2 ++;

		if (nl2 % 2 == 0)
		{

			//ret += "EXTERIOR";
			return false;
		}
		else
		{
			//ret += "INTERIOR";
			return true;
		}
	}

	else
	{
		//ret += "INTERIOR";
		return true;
	}
	//return false;
}

int savedPawnCount(vector <int> start)
{
	int shift = 0;
	vector<int>::iterator it;
	it = start.end();
	it--;
	shift = *it / 2;
	for ( --it; it > start.begin(); it-- )
	{
		*it += shift;
		shift = *it / 2;
	}
	*it += shift;
	return start.at(0);
}


