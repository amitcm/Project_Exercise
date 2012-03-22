#include "stdafx.h"
#include<iostream>
using namespace std;

typedef unsigned int uint_t;

	// this function returns next higher number with same number of set bits as x.
	/*	x = 156_10
		x = 10011100(2)
		10011100
		00011100 - right most string of 1's in x
		00000011 - right shifted pattern except left most bit ------> [A]
		00010000 - isolated left most bit of right most 1's pattern
		00100000 - shiftleft-ed the isolated bit by one position ------> [B]
		10000000 - left part of x, excluding right most 1's pattern ------> [C]
		10100000 - add B and C (OR operation) ------> [D]
		10100011 - add A and D which is required number 163(10)
	*/
uint_t snoob(uint_t x)
{

	uint_t rightOne;
	uint_t nextHigherOneBit;
	uint_t rightOnesPattern;

	uint_t next = 0;

	if(x)
	{
		// right most set bit
		rightOne = x & -(signed)x;

		// reset the pattern and set next higher bit
		// left part of x will be here
		nextHigherOneBit = x + rightOne;

		// nextHigherOneBit is now part [D] of the above explanation.

		// isolate the pattern
		rightOnesPattern = x ^ nextHigherOneBit;

		// right adjust pattern
		rightOnesPattern = (rightOnesPattern)/rightOne;

		// correction factor
		rightOnesPattern >>= 2;

		// rightOnesPattern is now part [A] of the above explanation.

		// integrate new pattern (Add [D] and [A])
		next = nextHigherOneBit | rightOnesPattern;
	}

	return next;
}

int addwithoutplusminus(int m,int n)
{
	int c;
	while(m&n)
	{
		c=m&n;
		n^=m;
		c<<=1;
		m=c;
	}
	n^=m;
	return n;
}

bool isPowerOfFour(unsigned int n)
{
	int count = 0;

	/*Check if there is only one bit set in n*/
	if ( n && !(n&(n-1)) )
	{
		/* count 0 bits before set bit */
		while(n > 1)
		{
			n  >>= 1;
			count += 1;
		}      

		/*If count is even then return true else false*/
		return (count%2 == 0)? 1 :0;
	}

	/* If there are more than 1 bit set
	then n is not a power of 4*/
	return 0;
}  

int add1(int x)
{
	return -(~x);
}

int add1_1(int x)
{
	int m = 1;
	while(x & m)
	{
		x = x ^ m;
		m <<= 1;
	}
	x = x | m;
	return x;
}