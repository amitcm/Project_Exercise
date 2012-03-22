// MyTriliza.cpp: implementation of the CMyTriliza class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyTriliza.h"
#include <string.h>
#include "windows.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyTriliza::CMyTriliza()
{

}

CMyTriliza::~CMyTriliza()
{

}

////////////////////////////////////////////////////
// Initialise some data and check who plays first //
////////////////////////////////////////////////////

void CMyTriliza::VerifyFirstPlayer()
{
	ZeroMemory(TrilizaMarks,sizeof(TrilizaMarks));
	IsFormed = false;
	NumberOfMovesPlayed = 0;
	while (WhoPlaysFirst != 'y' && WhoPlaysFirst!= 'n')
	{
		cout <<"Now,do you want to play first ? (y|n)\n";
		cin >> WhoPlaysFirst;
	}
	cout<<"\n";
	switch (WhoPlaysFirst)
	{
		case 'n':
		{
			DoIPlayFirst = true;
			break;
		}
		case 'y':
		{
			DoIPlayFirst = false;
			break;
		}
	}
}

///////////////////////////////////////////////////////
// CPU has to make a move.Perform MinMax Algorithm.  //
// Evaluate using EvaluatePosition() as a heuristic  // 
// function.Get the best position and output it.     //
// Then draw the Triliza on screen.                  //
///////////////////////////////////////////////////////

void CMyTriliza::MakeCPUMove()
{
	if (IsATrilizaFormed())
	{
		IsFormed = true;
		cout <<"\nA TRILIZA was formed !!! You have somehow beaten the machine !!!\n Did you cheat :) ?\n";
	}
	else
	{
		int TrilizaMarksBackUp[9];
		memcpy(TrilizaMarksBackUp,TrilizaMarks,sizeof(TrilizaMarks));  // Create Local BackUp With Current Positions
		int best_value=-30;
		int best_position=0;

		for(int i=0;i<=8;i++)
		{
			if (TrilizaMarks[i] != 1 && TrilizaMarks[i]!= 2)  // If there's not a mark there..
			{
				TrilizaMarks[i] = 1;
			    int returned_value = EvaluatePosition();
				if (returned_value >= best_value)
				{
					best_value = returned_value;
					best_position = i;
				}
			}
			memcpy(TrilizaMarks,TrilizaMarksBackUp,sizeof(TrilizaMarks));  // Recover Previous Values
		}

		cout <<"\n\nDuring my move I placed a mark in square number: ";
		cout << best_position+1;
		cout<<"\n";
		TrilizaMarks[best_position] = 1;
		NumberOfMovesPlayed++;
		}
	DrawTriliza();
}

//////////////////////////////////////
// Human has to make a move too.    //
// Then draw the Triliza on screen. //
//////////////////////////////////////

void CMyTriliza::MakeHumanMove()
{
	if (IsATrilizaFormed())
	{
		IsFormed = true;
		cout <<"\nA TRILIZA was formed !!! As usual,i won again.. :)\n";
	}
	else
	{
		int move=0;
		while (move>9 || move<1)
		{
			cout << "\nPlease give a number from 1-9 for your move: ";
			cin >> move;
		}

		TrilizaMarks[move-1] = 2;
		NumberOfMovesPlayed++;
	}
	DrawTriliza();
}

/////////////////////////////////////////////////////////////////////
// 3*x2 + x1 - ( 3*O2 + O1 )                                       //
// x2 = number of rows,columns or diagonals with 2 Xs and zero Os  // 
// x1 = number of rows,columns or diagonals with 1 X and zero Os   //
// O2 = number of rows,columns or diagonals with 2 Os and zero Xs  //
// O1 = number of rows,columns or diagonals with 1 Os and zero Xs  //
//                                                                 //
// X represents cpu = 1                                            //
// O represents human = 2                                          //
//                                                                 //
// Heuristic function for MinMax Algo is here                      //
/////////////////////////////////////////////////////////////////////

int CMyTriliza::EvaluatePosition() 
{
	if (GetMarkValue(3,0))
		return 30;
	else if (GetMarkValue(0,3))
		return 30;	
	else if (CheckForPitFalls())
		return -30;
	else
	{
		int X2 = GetMarkValue(2,0);  // determine x2 number
		int X1 = GetMarkValue(1,0);  // determine x1 number
		int O2 = GetMarkValue(0,2);  // determine O2 number
		int O1 = GetMarkValue(0,1);  // determine O1 number
		return 3*X2 + X1 - (3*O2 + O1);
	}
}

//////////////////////////////////////////////////////////
// You pass the number of Xs and Os in this function.   //
// Then it returns how many rows,columns and diagonals  //
// which have the same number of Xs and Os the Triliza  // 
// grid contains.                                       //
//////////////////////////////////////////////////////////

int CMyTriliza::GetMarkValue(int Xs, int Os)
{
	int MarkValue=0;
	int NumXs=0,NumOs=0;
	
	// Check Rows
	for (int i=0;i<=8;i++)  
	{
		if (TrilizaMarks[i] == 1) // If there's a CPU mark..
			NumXs++;
		else if (TrilizaMarks[i] == 2) // If there's a HUMAN mark..
			NumOs++;

		if ((i+1)%3 == 0)  // If three row positions are over..
		{
			if (NumXs == Xs && NumOs==Os)
			{
				MarkValue++;
			}
			NumXs=0;
			NumOs=0;
		}
	}

	NumXs=0,NumOs=0;
	
	// Check Columns
	int i=0;
	int next=0;
	while (next<=2)
	{
		for (int i=0;i<=8;i+=3)  
		{
			if (TrilizaMarks[i] == 1) // If there's CPU mark..
				NumXs++;
			else if (TrilizaMarks[i] == 2) // If there's HUMAN mark..
				NumOs++;
		}
		if (NumXs == Xs && NumOs==Os)
		{
			NumXs=0;
			NumOs=0;
			MarkValue++;
		}
		next++;
		i=next;
		NumXs=0,NumOs=0;
	}

	NumXs=0,NumOs=0;

	//Check Diagonal 1
	for (int i = 0;i<=8;i+=4)  
	{
		if (TrilizaMarks[i] == 1) // If there's CPU mark..
			NumXs++;
		else if (TrilizaMarks[i] == 2) // If there's HUMAN mark..
			NumOs++;
	}
	if (NumXs == Xs && NumOs==Os)
	{
			NumXs=0;
			NumOs=0;
			MarkValue++;
	}

	NumXs=0,NumOs=0;

	//Check Diagonal 2
	for (int i=2;i<=6;i+=2)  
	{
		if (TrilizaMarks[i] == 1) // If there's CPU mark..
			NumXs++;
		else if (TrilizaMarks[i] == 2) // If there's HUMAN mark..
			NumOs++;
	}
	if (NumXs == Xs && NumOs==Os)
	{
		NumXs=0;
		NumOs=0;
		MarkValue++;
	}

	return MarkValue;
}

////////////////////////////////////
// Check if a Triliza is formed   //
// Check for 3 Xs or Os for that  //
////////////////////////////////////

bool CMyTriliza::IsATrilizaFormed()
{
	if (GetMarkValue(3,0))  
		return true;
	else if (GetMarkValue(0,3))  
		return true;
	else
		return false;
}

////////////////////////////////////////////////////
// Check for some pitfalls of Triliza             //
// Like Double Trilizas.Find ways to bypass them  //
////////////////////////////////////////////////////

bool CMyTriliza::CheckForPitFalls()
{
	if (TrilizaMarks[4] == 1 && ((TrilizaMarks[0] == 2 && TrilizaMarks[8] == 2 ) || (TrilizaMarks[2] == 2 && TrilizaMarks[6] == 2)) && (TrilizaMarks[1]==0 && TrilizaMarks[3]==0  && TrilizaMarks[5]==0 && TrilizaMarks[7]==0))
		return true;
	else if (TrilizaMarks[4] == 1 && TrilizaMarks[8] == 1 && TrilizaMarks[2] == 2 && TrilizaMarks[3] == 2)
		return true;
	else if (TrilizaMarks[4] == 1 && TrilizaMarks[6] == 1 && TrilizaMarks[0] == 2 && TrilizaMarks[5] == 2)
		return true;
	else if (TrilizaMarks[4] == 1 && TrilizaMarks[6] == 1 && TrilizaMarks[1] == 2 && TrilizaMarks[8] == 2)
		return true;
	else if (TrilizaMarks[4] == 1 && TrilizaMarks[8] == 1 && TrilizaMarks[1] == 2 && TrilizaMarks[6] == 2)
		return true;
	else if (TrilizaMarks[4] == 1 && TrilizaMarks[8] == 1 && TrilizaMarks[1] == 2 && TrilizaMarks[3] == 2)
		return true;
	else if (TrilizaMarks[4] == 1 && TrilizaMarks[0] == 1 && TrilizaMarks[6] == 1 && TrilizaMarks[7] == 1 && TrilizaMarks[1] == 2 && TrilizaMarks[2] == 2 && TrilizaMarks[3] == 2 && TrilizaMarks[8] == 2)
		return true;
	else 
		return false;
}

///////////////////////////////////////////////////////////
// This function draws the Triliza grid after each move  //
///////////////////////////////////////////////////////////

void CMyTriliza::DrawTriliza()
{

	cout <<"\nThis is what the Triliza grid looks like after the last move : \n\n";

	for (int i=0;i<=8;i++)
	{
		if ((i+1)%3 != 0)
		{
			if (TrilizaMarks[i] == 1)
				cout<<" X|";
			else if (TrilizaMarks[i] == 2)
				cout<<" O|";
			else if (TrilizaMarks[i] == 0)
				cout<<"  |";
		}
		else
		{
			if (TrilizaMarks[i] == 1)
				cout<<" X\n";
			else if (TrilizaMarks[i] == 2)
				cout<<" O\n";
			else if (TrilizaMarks[i] == 0)
				cout<<"  \n";
			if ((i+1) % 9 != 0)
				cout <<"-------- \n";
		}
	}
}

void CMyTriliza::TrilizaLoop()
{
	if (DoIPlayFirst)  
	{
		while (NumberOfMovesPlayed<=8)
		{
			MakeCPUMove();  // CPU plays first here..
			if (IsFormed)
				break;
			if (NumberOfMovesPlayed!=9)
				MakeHumanMove();
			if (IsFormed)
				break;
		}
		if (!IsFormed)
			cout <<"\nNobody wins..That's OK,i'll win next time..\n";
	}
	else
	{
		while (NumberOfMovesPlayed<=8)
		{
			MakeHumanMove();  // Human plays first here..
			if (IsFormed)
				break;
			if (NumberOfMovesPlayed!=9)
				MakeCPUMove();
			if (IsFormed)
				break;
		}
		if (!IsFormed)
			cout <<"\nNobody wins..How can i win if i don't play first ?\n";
	}	
}

bool CMyTriliza::PlayAgain()
{
	char PlayAgain=0;
	while (PlayAgain != 'y' && PlayAgain!= 'n')
	{
		cout <<"\nDo you want to play again ?(y|n)\n";
		cin >> PlayAgain;
	}
	cout<<"\n";
	switch (PlayAgain)
	{
		case 'n':
			return false;
		case 'y':
			return true;
	}
	return false;
}
