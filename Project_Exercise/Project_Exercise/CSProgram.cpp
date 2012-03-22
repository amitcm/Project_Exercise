/* Enter your code here. Read input from STDIN. Print output to STDOUT */

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include "BigInt.h"

using namespace std;
/*
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

  printf("%s", p);
  delete decimal_array;
*/



int main_not_in_use()
{
	static bigint billionbillion(1000000000000000000);
	print_bigint(billionbillion);
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
	        print_bigint(Flips);
			cout << endl;
		}
		else{
	        dX = (nHeads - nAlready) + ((nHeads - nAlready) > 0 ? (nFlips / 2) : 0);
	        print_bigint(dX);
			cout << endl;
		}
		Test = Test - 1;
	}
	
return 0;
}