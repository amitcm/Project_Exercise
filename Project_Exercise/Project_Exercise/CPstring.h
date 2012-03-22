#ifndef _MYSTRING_H
#define _MYSTRING_H

#include <iostream>
//#include <stdio.h>
#include <string>            // for strcmp, strlen, etc.
#include <stdlib.h>            // for exit,atof,atoi
#include <assert.h>            // for assert
#include <ctype.h>             // for tolower/toupper
//#include "bool.h"

// modeled (loosely) on Stroustrup 2nd edition, on Budd's String class,
// and Adams, Leestma, and Nyhoff Strings (and probably a host of others)
//
// written by Owen Astrachan April 1993 (with reference counts)
//      modified May 2, 1994
//      modified July 6, 1994 [fixed some inconsistencies found in DOS
//                             implementation]
//      modified October, 1994 [to re-use existing memory rather than
//                              than deleting when =, copy constructor used]
//
// provides a "standard" string class supporting operations given below
//
// constructors:
//
//        string(const char * s = 0);
//               copies a C-style '\0'-terminated string
//        string(const string & x);
//               copy constructor
//        string (char ch);
//               make a string from a single character
//
//  destructor
//        ~string()  destructor frees memory associated with string
//
//  operators
//
//        string & operator= (const string & x);
//               assigns one string to another
//        string & operator= (const char * s);
//               assigns a C-style string to a string
//
//        operator const char * s () const
//               cast/convert string to C-style string
//
//        int length() const
//               returns # of characters in string
//
//         char& operator[](int i)
//               returns i-th char of string (signals error if out-of-bounds)
//                       (char is assignable since reference)
//
//         const char& operator[](int i) const
//               returns i-th char of string (signals error if out-of-bounds)
//
//  I/O operators
//       << and >>
//               are "standard" for ostream and istream respectively
//       istream & getline(istream & is, string & s, char sentinel = '\n')
//               mimics iostream.h getline for istreams and strings
//
//  relational operators
//          ==, !=, <, >, >=, <=
//              for all combinations of C-style strings and string
//
//  concatenation operators and functions
//          string & operator +=(const string & x)
//              catenates x to the right of the string
//          friend string operator +(const string & x, const string & y)
//              catenates x to y and returns result
//
//
//  search/facilitator functions
//
//          string substr(int pos, int len)
//             returns string of len chars starting at pos
//             truncates if len too big, returns empty string
//             if pos too big
//
//          string Downcase() const
//          string Upcase() const
//               return lower/upper case versions of string, respectively
//
//          bool Contains(const string & s) const
//          bool Contains(char * s) const
//               returns true if string contains s, else returns false
//
// conversion functions
//
//          char * chars()
//             similar to (char *) cast, but member function
//          char * c_str()
//             identical to chars(), but ANSI compatible
//
//          int atoi(string &)
//             like <stdlib.h> atoi, but has string parameter
//             ensures that calling <stdlib.h> version is done
//             correctly
//
//          int atof(string &)
//             like <stdlib.h> atof, but has string parameter
//             ensures that calling <stdlib.h> version is done
//             correctly
//
//          string itoa(int n)
//             returns string equivalent of number n
//             i.e., itoa(123) returns "123", itoa(-56) returns "-56"


extern const int NPOS;

class string{
    
  public:
    string(const char * s = 0);           // for literals and C-style strings
    string(const string & x);             // copy constructor
    string(char ch);                      // make string from char

    string& operator = (const char * s);  // assign literal, C-style strings
    string& operator =(const string & x); // assign one string to another

    ~string();                            // free up memory

    // perhaps this cast should not be included

    operator const char *() const {return myCstring;}

    const char * chars() const {return myCstring;}    // explicit conversion to C-style
    const char * c_str() const {return myCstring;}

    int length() const {return strlen(myCstring);}  // returns # of chars
    char& operator[](int i);              // index character (range checked)
    const char& operator[](int i) const;  // constant index  (range checked)

    string& operator +=(const string & x);

    string Downcase() const;

    string Upcase() const;

    string substr(int pos, int len) const;
    // precondition: 0 <= pos < s.length() && pos + len <= s.length()
    // postcondition: returns substring starting at char pos of len chars
    
    bool Contains (const string & s) const;

    bool Contains(char * s) const;

    int find(const string & s) const;
    int find(char * s) const;

// relational operators for string/string comparisons

    friend int operator ==(const string & x, const string & y)
        {return strcmp(x.myCstring, y.myCstring)==0;}

    friend int operator !=(const string & x, const string & y)
        {return ! (x == y);}

    friend int operator < (const string & x, const string & y)
         {return strcmp(x.myCstring, y.myCstring) < 0;}

    friend int operator > (const string & x, const string & y)
         {return strcmp(x.myCstring, y.myCstring) > 0;}

    friend int operator >= (const string & x, const string & y)
         {return x > y || x == y;}

    friend int operator <= (const string & x, const string & y)
         {return x < y || x == y;}

// relational operators for string/char * comparisons

    friend int operator ==(const string & x, const char * s)
        {return strcmp(x.myCstring,s)==0;}

    friend int operator !=(const string & x, const char * s)
        {return ! (x == s);}

    friend int operator < (const string & x, const char * s)
          {return strcmp(x.myCstring, s) < 0;}

    friend int operator > (const string & x, const char *s)
          {return strcmp(x.myCstring, s) > 0;}

    friend int operator >= (const string & x, const char *s)
         {return x > s || x == s;}

    friend int operator <= (const string & x, const char *s)
         {return x < s || x == s;}


// relational operators for char */string comparisons

    friend int operator ==(const char * s, const string & x)
        {return strcmp(s, x.myCstring)==0;}

    friend int operator !=(const char * s, const string & x)
        {return ! (s == x);}

    friend int operator < (const char * s, const string & x)
          {return strcmp(s,x.myCstring) < 0;}

    friend int operator > (const char *s, const string & x)
          {return strcmp(s,x.myCstring) > 0;}

    friend int operator >= (const char *s, const string & x)
         {return s > x || s == x;}

    friend int operator <= (const char *s, const string & x)
         {return s < x || s == x;}

    enum {maxLength = 1024};  // maximum length of string read from input
  private:
    char * myCstring;         // private C-style string
    int myLength;
};

string operator +(const string & x, const string & y);
ostream& operator <<(ostream& os, const string& str);
istream& operator >>(istream& is, string& str);
istream & getline(istream & is, string & s, char sentinel = '\n');

int atoi(const string & s);         // returns int equivalent
double atof(const string & s);      // returns double equivalent
string itoa(int n);

//****************************************************************
//**************** pre/post conditions   *************************
/*****************************************************************

string::string(const char * s)
// precondition: s is '\0'-terminated C-style string
// postcondition: object constructed to have same value as s
// assertion: fails if memory can't be allocated

string::string(const string & x)
// postcondition: object constructed has same value as x
// assertion: fails if memory can't be allocated

string::string(char ch)
// postcondition: object is string of one character ch
// assertion: fails if memory can't be allocated

string& string::operator = (const char * s)
// precondition: s is '\0'-terminated C-style string
// postcondition: assign object the value of C-style string s
// assertion: fails if memory can't be allocated

string& string::operator =(const string & x)
// postcondition: object assigned string x
//                memory allocated only if x.length() > length()
// assertion: fails if memory can't be allocated

string::~string()
// postcondition: dynamically allocated memory freed

char& string::operator[](int i)
// precondition: 0 <= i < length()
// postcondition: returns i-th character
// assertion: fails if index not in range

const char& string::operator[](int i) const
// precondition: 0 <= i < length()
// postcondition: returns i-th character (constant)
// assertion: fails if index not in range

ostream& operator <<(ostream& os, const string& str)
// precondition: os is writeable
// postcondition: str is written to os (uses char * operator)

istream& operator >>(istream& is, string& str)
// precondition: is open for reading
// postcondition: string read from is, stored in str
//                maximum of string::maxLength chars read

istream & getline(istream & is, string & s, char sentinel)
// precondition: is open for reading
// postcondition: chars from is up to sentinel read, stored in s
//                sentinel is read, but NOT stored in s

string& string::operator +=(const string & x)
// postcondition: concatenates x onto object
// assertion: fails if memory can't be allocated     

string operator +(const string & x, const string & y)
// postcondition: returns concat(x,y)

string string::Downcase() const
// postcondition: returns lowercase equivalent of object
//                non-lowercase chars not changed

string string::Upcase() const
// postcondition: returns uppercase equivalent of object
//                non uppercase chars not changed

string string::substr(int pos, int len)
// precondition: 0 <= pos < s.length() && pos + len <= s.length()
// postcondition: returns substring starting at char pos of len chars
//                if len too large, takes s.length() chars

bool string::Contains (const string & s) const
// postcondition: returns true if s is a substring of object

inline int string::Contains(char * s) const
// postcondition: returns true if s is a substring of object

inline int atoi(string & s)
// precondition: s is a sequence of digits
// postcondition: returns integer equivalent of s
// exception: if s is not valid integer, 0 is returned

double atof(string & s)
// precondition: s is a sequence of digits
// postcondition: returns double equivalent of s
// exception: if s is not valid double, 0 is returned

***************************************************************
*************** pre/post conditions   *************************
***************************************************************/

#endif /* _MYSTRING_H not defined */
