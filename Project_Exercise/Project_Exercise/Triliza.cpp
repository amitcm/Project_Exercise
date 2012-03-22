// Triliza.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
using namespace std;
#include "MyTriliza.h"

CMyTriliza *Triliza;

int main___tic_tac(int argc, char* argv[])
{
	cout <<"This is a TRILIZA(tic-tac-toe) game created by human_thought.In order to play\nthis game you first decide ";
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
	}

	return 0;
}