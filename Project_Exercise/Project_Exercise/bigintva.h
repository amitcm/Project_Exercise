#ifndef _BIGINT_H
#define _BIGINT_H

// author: Owen Astrachan
// 8/23/95, modified 7/5/96
//
// implements an arbitrary precision integer class
// 
// constructors:
//
// BigInt()            -- default constructor, value of integers is 0
// BigInt(int n)       -- initialize to value of n (C++ int)
// BigInt(const string & s) -- initialize to value specified by s
//        it is an error if s is an invalid integer, e.g.,
//        "1234abc567".  In this case the bigint value is garbage
// BigInt(const BigInt & b)  -- copy constructor
//
//
// *****  arithmetic operators:
//
// all arithmetic operators +, -, *, /, % are overloaded both
// in form +=, -=, *=, /=, %=, and as binary operators
//
// multiplication and division also overloaded for *= int and /= int
// e.g., BigInt a *= 3 (mostly to facilitate implementation)
//
//  ***** logical operators:
//
// bool operator == (const BigInt & lhs, const BigInt & rhs)
// bool operator != (const BigInt & lhs, const BitInt & rhs)
// bool operator <  (const BigInt & lhs, const BigInt & rhs)
// bool operator <= (const BigInt & lhs, const BigInt & rhs)
// bool operator >  (const BigInt & lhs, const BigInt & rhs)
// bool operator >= (const BigInt & lhs, const BigInt & rhs)
//
//  ***** I/O operators:
//
//  ostream & Print()
//        prints value of BigInt (member function)
//  ostream & operator << (ostream & os, const BigInt & b)
//        stream operator to print value
//


#include <iostream>
//#include <stdio.h>
//#include "CPstring.h"            // for strings
#include "Avector.h"              // for sequence of digits
#include <string>

using namespace std;

class BigInt
{
  public:
    
    BigInt();                  // default constructor, value = 0
    BigInt(int);               // assign an integer value
    BigInt(const string &);    // assign a string 
    BigInt(const BigInt &);    // copy constructor
    ~BigInt();                 // destructor

    ostream & Print(ostream & os) const;    // so << isn't a friend

    BigInt & operator = (const BigInt &);

    // operators: arithmetic, relational

    BigInt & operator += (const BigInt &);
    BigInt & operator -= (const BigInt &);
    BigInt & operator *= (const BigInt &);
    BigInt & operator *= (int num);
    BigInt & operator /= (const BigInt &);
    BigInt & operator /= (int num);
    BigInt & operator %= (const BigInt &);
    
    string toString() const;   // convert to string

    friend bool operator == (const BigInt &, const BigInt &);    
    friend bool operator < (const BigInt &, const BigInt &);

	// My modification
	BigInt operator >> (int shift);
    BigInt operator << (int shift);
    
  private:

    enum BigError{
	underflow, overflow, not_a_number,infinity,no_error
    };

    // private state/instance variables

    bool myIsNegative;
    AVector<char> myDigits;
    int myNumDigits;
    BigError myError;

    // helper functions

    bool IsNeg() const;        // return true iff number is negative
    int getDigit(int k) const;
    void addSigDigit(int value);
    void changeDigit(int digit, int value);
    int size() const;
    void Normalize();
    void DivideHelp(const BigInt & lhs, const BigInt & rhs,
		    BigInt & quotient, BigInt & remainder);
    
};

// free functions

ostream & operator <<(ostream &, const BigInt &);
istream & operator >>(istream &, BigInt &);

BigInt operator +(const BigInt & lhs, const BigInt & rhs);
BigInt operator -(const BigInt & lhs, const BigInt & rhs);
BigInt operator *(const BigInt & lhs, const BigInt & rhs);
BigInt operator *(const BigInt & lhs, int num);
BigInt operator *(int num, const BigInt & rhs);
BigInt operator /(const BigInt & lhs, const BigInt & rhs);
BigInt operator /(const BigInt & lhs, int num);
BigInt operator %(const BigInt & lhs, const BigInt & rhs);

bool operator != (const BigInt & lhs, const BigInt & rhs);
bool operator >  (const BigInt & lhs, const BigInt & rhs);
bool operator >= (const BigInt & lhs, const BigInt & rhs);
bool operator <= (const BigInt & lhs, const BigInt & rhs);


#endif   // _BIGINT_H not defined
