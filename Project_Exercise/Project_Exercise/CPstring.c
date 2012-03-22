#include "CPstring.h"
#include <strstream>
#include <iostream>
//#include "bool.h"

const int NPOS = -1;

string::string(const char * s)
// precondition: s is '\0'-terminated C-style string
// postcondition: object constructed to have same value as s
// assertion: fails if memory can't be allocated
{
    if (s != 0){                // C-string not NULL 
        myLength = strlen(s) + 1; // make room for '\0'  
        myCstring = new char[myLength];
        assert(myCstring != 0);
        strcpy(myCstring,s);
    }
    else{
        myLength = 1;
        myCstring = new char[1];
        assert(myCstring != 0);
        myCstring[0] = '\0';
    }
    
}   


string::string(const string & x)
// postcondition: object constructed has same value as x     
// assertion: fails if memory can't be allocated
{
    if (this != &x){
        myLength = x.length() + 1;
        myCstring = new char[myLength];
        assert(myCstring != 0);
        strcpy(myCstring,x.myCstring);
    }
}

string::string(char ch)
// postcondition: object is string of one character ch
// assertion: fails if memory can't be allocated
{
    myLength = 2;
    myCstring = new char[myLength];
    assert(myCstring != 0);
    myCstring[0] = ch;
    myCstring[1] = '\0';
}



string& string::operator = (const char * s)
// precondition: s is '\0'-terminated C-style string
// postcondition: assign object the value of C-style string s
// assertion: fails if memory can't be allocated
{
    
    int len = 0;                // length of newly constructed string
    if (s != 0){
        len = strlen(s);                // assume '\0' terminated
    }
    
    // free old string if necessary
    
    if (myLength < len + 1)
    {
        delete [] myCstring;
        myLength = len + 1;
        myCstring = new char[myLength];
        assert(myCstring != 0);
    }
    
    strcpy(myCstring,s);
    return *this;
}

string& string::operator =(const string & x)
// postcondition: object assigned string x
//                memory allocated only if x.length() > length()
// assertion: fails if memory can't be allocated
{
    if (this != &x){
        if (myLength < x.length() + 1){ // need more chars
            delete[] myCstring;                 // delete old space
            myLength = x.length() + 1;
            myCstring = new char[myLength]; // get new space
            assert(myCstring != 0);
        }
        strcpy(myCstring,x.myCstring);
    }
    return *this;   
}

string::~string()
// postcondition: dynamically allocated memory freed
{
    delete[] myCstring;
    myCstring = 0;
    myLength = 0;
}

char& string::operator[](int i)
// precondition: 0 <= i < length()
// postcondition: returns i-th character
// assertion: fails if index not in range
{
    if (i < 0 || strlen(myCstring) <= i){
        cerr << "index out of range: " << i << " string: " << myCstring
            << endl;
        assert(0 <= i && i < strlen(myCstring));
    }
    return myCstring[i];
}
const char& string::operator[](int i) const
// precondition: 0 <= i < length()
// postcondition: returns i-th character (constant)
// assertion: fails if index not in range     
{
    if (i < 0 || strlen(myCstring) <= i){
        cerr << "index out of range: " << i << " string: " << myCstring
            << endl;
        assert(0 <= i && i < strlen(myCstring));
    }
    return myCstring[i];
}

ostream& operator <<(ostream& os, const string& str)
// precondition: os is writeable
// postcondition: str is written to os (uses char * operator)
{
    return os << str.c_str();
}

istream& operator >>(istream& is, string& str)
// precondition: is open for reading
// postcondition: string read from is, stored in str
//                maximum of string::maxLength chars read
{
    char buf[string::maxLength];
    is >> buf;
    str = buf;
    return is;
}


istream & getline(istream & is, string & s, char sentinel)
// precondition: is open for reading
// postcondition: chars from is up to sentinel read, stored in s
//                sentinel is read, but NOT stored in s
{
    char buf[string::maxLength+1];
    is.getline(buf,string::maxLength, sentinel);
    s = buf;
    return is;
}



string& string::operator +=(const string & x)
// postcondition: concatenates x onto object
// assertion: fails if memory can't be allocated
{
    int newLength = length() + x.length(); // object + added string
    int lastLocation = length();           // location of '\0'

    char * copyStr = x.myCstring;          // copy this one
    char * delStr  = myCstring;            // delete this one
    bool doDelete = false;                 // delete old string?
    // check to see if local buffer not big enough
    if (newLength >= myLength)
    {
        char * newBuffer = new char[newLength + 1];        
        strcpy(newBuffer,myCstring); // copy into new buffer
        doDelete = true;
        myLength = newLength + 1;            // update information
        myCstring = newBuffer;
    }
    // now catenate x to end of myCstring

    strcpy(myCstring+lastLocation,copyStr);
    
    if (doDelete)                            // delete here for aliasing
    {
	delete [] delStr;                    // old string
    }
    
    return *this;
}

string operator +(const string & x, const string & y)
// postcondition: returns concat(x,y)
{
    string result(x);           // copies x to result
    result += y;                // catenate y
    return result;              // returns a copy of result
}


string string::Downcase() const
// postcondition: returns lowercase equivalent of object
//                non-lowercase chars not changed
{
    string result = myCstring;
    int len = length();
    int k;
    for(k=0; k < len; k++)
    {
        result[k] = tolower(result[k]);
    }
    return result;  
}

string string::Upcase() const
// postcondition: returns uppercase equivalent of object
//                non uppercase chars not changed
{
    string result = myCstring;
    int len = length();
    int k;
    for(k=0; k < len; k++)
    {
        result[k] = toupper(result[k]);
    }
    return result;  
}

string string::substr(int pos, int len) const
// precondition: 0 <= pos < s.length() && pos + len <= s.length()
// postcondition: returns substring starting at char pos of len chars
//                if len too large, takes s.length() chars
{
    string result = "";
    int mylen = length();
    int lastIndex = pos + len - 1; // last char's index (to copy)
    
    if (pos >= mylen) return result; // empty string
    
    if (lastIndex >= mylen)     // off end of string?
    {
        lastIndex = mylen-1;
    }
    
    int k;
    for(k=pos; k <= lastIndex; k++)
    {
        result += myCstring[k];
    }
    
    return result;
}

int string::find(const string & s) const
{
    return find(s.myCstring);
}

int string::find(char * s) const
{
    int len = strlen(s);
    int lastIndex = length() - len;
    int k;
    for(k=0; k <= lastIndex; k++)
    {
        if (strncmp(myCstring + k,s,len) == 0) return k;
    }
    return NPOS;    
}

bool string::Contains (const string & s) const
// postcondition: returns true if s is a substring of object
{
    return Contains(s.myCstring);
}

bool string::Contains(char * s) const
// postcondition: returns true if s is a substring of object
{
    return find(s) != NPOS;
}



int atoi(const string & s)
// precondition: s is a sequence of digits
// postcondition: returns integer equivalent of s
// exception: if s is not valid integer, 0 is returned
{
    return atoi(s.c_str());
}

double atof(const string & s)
// precondition: s is a sequence of digits
// postcondition: returns double equivalent of s
// exception: if s is not valid double, 0 is returned
{
    return atof(s.c_str());
}


string itoa(int n)
// postcondition: return string equivalent of int n
{
    char buf[string::maxLength];
    ostrstream output(buf,string::maxLength);
    string local;
    output << n << ends;
    local = output.str();
    return local;

    // old version, hard(er) to get robust
    
    if (n == 0) return "0";
    else
    {
        string temp = "";
        bool isneg = false;
        if (n < 0)
        {
            isneg = true;
            n = -n;
        }
        
        while (n > 0)
        {
            temp = string('0'+ (n%10)) + temp;
            n /= 10;
        }
        return string(isneg?"-":"") + temp;
    }   
}
