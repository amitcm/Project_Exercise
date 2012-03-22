// MyTriliza.h: interface for the CMyTriliza class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTRILIZA_H__CC7D3B18_55F5_49FE_BD98_E2DB8958DF8B__INCLUDED_)
#define AFX_MYTRILIZA_H__CC7D3B18_55F5_49FE_BD98_E2DB8958DF8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream>

class CMyTriliza  
{
public:
	bool PlayAgain();
	void TrilizaLoop();
	void DrawTriliza();
	bool CheckForPitFalls();
	bool IsATrilizaFormed();
	int GetMarkValue(int Xs,int Os);
	int EvaluatePosition();
	int NumberOfMovesPlayed;
	void MakeHumanMove();
	void MakeCPUMove();
	void VerifyFirstPlayer();
	CMyTriliza();
	virtual ~CMyTriliza();
	bool IsFormed;
	bool DoIPlayFirst;

private:
	int TrilizaMarks[9];   // 1 for human,2 for cpu
	char WhoPlaysFirst;
	

};

#endif // !defined(AFX_MYTRILIZA_H__CC7D3B18_55F5_49FE_BD98_E2DB8958DF8B__INCLUDED_)
